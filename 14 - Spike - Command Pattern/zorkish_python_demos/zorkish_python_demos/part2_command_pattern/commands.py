from world import World, Location, Item, Player, dir_check

#------------------------------------------------------------------------------
# abstract command class...
#------------------------------------------------------------------------------

class Command(object):

    def __init__(self, world):
        self.world = world

    def process(self, args):  # ABSTRACT!!
        pass


#------------------------------------------------------------------------------
# Concrete command classes....
#------------------------------------------------------------------------------

class CommandMove(Command):
    def process(self, args):
        # move [n,s,e,u ... etc] if valid direction from current player location
        if len(args) != 2:
            return "Can't move like that! Syntax: \"move (direction)\""
        # convert any alias direction into full "key" version (n -> "north")
        dir = dir_check(args[1])
        edges = self.world.current_loc().edges
        # is a valid move?
        if dir in edges:
            # move it!
            self.world.player.loc = edges[dir]
            return "You have moved %s to %s" % (dir, self.world.current_loc().name)
        else:
            return "Can't move %s." % dir


class CommandTake(Command):
    def process(self, args):
        # take (item_name)
        if len(args) == 2:
            named_item = self.world.find_item(args[1])
            player_items = self.world.player.items
            if named_item:
                if named_item.id in player_items:
                    return "You already have the %s in your inventory." % args[1]
                else:
                    self.world.current_loc().items.remove(named_item.id)
                    player_items.append(named_item.id)
                    return 'Item "%s" taken.' % args[1]
            else:
                return 'Can\'t find item "%s" to take.' % args[1]
        # take (item name) [from (item name)]
        elif len(args) == 4 and args[2] == "from":
            container_item = self.world.find_item(args[3])
            if container_item:
                named_item = self.world.find_item_in(args[1], container_item)
                if named_item:
                    container_item.items.remove(named_item.id)
                    self.world.player.items.append(named_item.id)
                    return '%s has been taken from %s.' % (args[1], args[3])
                else:
                    return 'I can\'t find "%s" inside "%s"' % (args[1], args[3])
            else:
                return "I can't find \"%s\" to look inside." % (args[3])
        else:
            return "Eh? Syntax: take (item) [from (item)]?"


class CommandPut(Command):
    def process(self, args):
        # put (item name)
        if len(args) == 2:
            named_item = self.world.find_item(args[1])
            if named_item:
                self.world.player.items.remove(named_item.id)
                self.world.current_loc().items.append(named_item.id)
                return 'Item "%s" dropped.' % args[1]
            else:
                return 'Can\'t find item "%s" to drop.' % args[1]
        # put (item name) [in (item name)]
        elif len(args) == 4 and args[2] in ("in", "into", "inside"):
            container_item = self.world.find_item(args[3])
            if container_item:
                named_item = self.world.find_item(args[1])
                if named_item:
                    # check to find out where moved item came from - player inv or current location
                    player_items = self.world.player.items
                    if named_item.id in player_items:
                        self.world.player.items.remove(named_item.id)
                    else:
                        self.world.current_loc().items.remove(named_item.id)
                    # put named_item into new container
                    container_item.items.append(named_item.id)
                    return '%s has been placed inside %s.' % (args[1], args[3])
                else:
                    return 'I can\'t find "%s" to put inside "%s"' % (args[1], args[3])
            else:
                return "I can't find \"%s\" to put item inside." % (args[3])
        else:
            return "Eh? Syntax: put (item) [in (item)]"


class CommandLook(Command):
    def process(self, args):
        # look (default to current location)
        if len(args) == 1:
            curr_loc = self.world.current_loc()
            # the location description, edges and items
            result = []
            # desc
            result.append("You are "+curr_loc.desc)
            # edges
            if curr_loc.edges:
                if len(curr_loc.edges) == 1:
                    result.append("There is a single exit leading %s" % dir_check(list(curr_loc.edges.keys())[0]))
                else:
                    result.append("There are %d exits" % len(curr_loc.edges))
                    for edge in curr_loc.edges:
                        result.append(" - %s " % dir_check(edge))  # directions
            else:
                result.append("There are no exits. Are you stuck?")
            # items
            if curr_loc.items:
                result.append("You can also see a")
                for i in curr_loc.items:
                    result.append(" - %s" % self.world.items[i].name)
            # debug info?
            if self.world.debug['look']:
                result.append('')
                result.append(self.world.debug_treeview())

            # join everything into a single string and return
            return "\n".join(result)
        # look at (item) OR look in (item)
        elif len(args) == 3 and args[1] in ('at', 'in', 'into', 'inside'):
            # check for a valid "named" item...
            named_item = self.world.find_item(args[2])
            if not named_item:
                return "I don't know what '%s' is." % args[2]
            # check for "at" or "in" version
            if args[1] == 'at':
                return "You can see %s" % named_item.desc
            elif args[1] in ('in', 'into', 'inside'):
                if not named_item.items:
                    return "Can't see anything in the %s" % args[2]
                # show list of things "in" the container (names only)
                result = []
                result.append("The %s contains ..." % args[2])
                for i in named_item.items:
                    result.append(' - %s ' % self.world.items[i].name)
                return '\n'.join(result)
        # look at (item) in (item)
        elif len(args) == 5:
            container_item = self.world.find_item(args[4])
            if args[1] == 'at' and args[3] == 'in' and container_item:
                named_item = self.world.find_item_in(args[3], container_item)
            else:
                return "Eh? Don't know how to look like that..."
        # default eh?
        return "Eh? Look at what?"


class CommandInventory(Command):
    def process(self, args):
        """ Show what the player currently has in his/her inventory... """
        if self.world.player.items:
            result = []
            result.append("You currently have: ")
            for i in self.world.player.items:
                item = self.world.items[i]
                result.append(" - %s; %s" % (item.name, item.desc))
            return "\n".join(result)
        else:
            return "You have nothing. Boring."


class CommandQuit(Command):
    def process(self, args):
        self.world.player.playing = False
        return 'Leaving the adventure...'


class CommandDebug(Command):
    def process(self, args):
        """ toggle debug status and show it"""
        debug = self.world.debug
        if len(args) == 3:
            debug[args[1]] = bool(args[2] == 'on')
        return "--debug ON for: %s" % (','.join([k for k in debug if debug[k]]))


class CommandAlias(Command):
    # needs special __init__ that also knows about manager.
    def __init__(self, world, manager):
        super().__init__(world)
        self.manager = manager

    # Note: relies on the singleton-like _command_manager being available
    def process(self, args):
        """ create new command alias's on the fly to existing commands"""
        if len(args) != 3:
            return 'syntax: "alias NEW_WORD COMMAND_WORD"'
        if args[1] in self.manager.cmds:
            return "Alias failed. New command word '%s' already exists." % args[1]
        if args[2] not in self.manager.cmds:
            return "Alias failed. Command word '%s' does not exist." % args[2]
        # create the commnd
        self.manager.cmds[args[1]] = self.manager.cmds[args[2]]
        return 'Command alias "%s" for "%s" created.' % (args[1], args[2])


class CommandTreeView(Command):
    def process(self, args):
        """ show the world tree-view """
        return self.world.debug_treeview()


class CommandHelp(Command):
    # needs special __init__ that also knows about manager.
    def __init__(self, world, manager):
        super().__init__(world)
        self.manager = manager

    def process(self, args):
        """ simple print all the commands that are available """
        # build a reverse list of object and multiple keys
        cmds = {}
        for key, cmd in self.manager.cmds.items():
            if cmd in cmds:
                cmds[cmd].append(key)
            else:
                cmds[cmd] = [key]
        # build a result string with the key details we have per command object
        result = []
        for cmd, keys in cmds.items():
            result.append("  * " + ", ".join(keys))
        return "\n".join(result)


class CommandManager(object):
    def __init__(self, world):
        # keep a ref to the world (locations, items and player objects)
        self.world = world
        # create a map (dictionary) of the commands we need to know about
        self.cmds = {}
        # Move
        self.cmds['move'] = CommandMove(self.world)
        self.cmds['go'] = self.cmds['move']
        # Take items (from world into inventory)
        self.cmds['take'] = CommandTake(self.world)
        self.cmds['get'] = self.cmds['take']
        self.cmds['pick'] = self.cmds['take']
        self.cmds['remove'] = self.cmds['take']
        # Put items (from inventory into current world location/taget object
        self.cmds['put'] = CommandPut(self.world)
        self.cmds['drop'] = self.cmds['put']
        self.cmds['place'] = self.cmds['put']
        self.cmds['put'] = self.cmds['put']
        # Look (location) at items (current inventory/location) OR in items
        self.cmds['look'] = CommandLook(self.world)
        self.cmds['inspect'] = self.cmds['look']
        # Inventory (player's collection of stuff)
        self.cmds['inventory'] = CommandInventory(self.world)
        self.cmds['inv'] = self.cmds['inventory']

        # Quit/Exit the adventure game (set playing = False)
        self.cmds['quit'] = CommandQuit(self.world)
        self.cmds['exit'] = self.cmds['quit']
        self.cmds['q'] = self.cmds['quit']
        self.cmds['bye'] = self.cmds['quit']

        # Special debug and alias showoff commands
        self.cmds['debug'] = CommandDebug(self.world)
        self.cmds['alias'] = CommandAlias(self.world, self)
        self.cmds['treeview'] = CommandTreeView(self.world)
        self.cmds['help'] = CommandHelp(self.world, self)

    def process(self, input):
        # check for single arg as possible "move" and insert "move" command word
        args = input.split()  # whitespace
        if len(args) == 0:
            return ''
        if self.world.debug['commands']:
            print('ARGS:', args)
            print('CMDS:', self.cmds.keys())
        if (len(args) == 1) and (args[0] not in self.cmds):
            args.insert(0, 'move')
        # based on the first argument command word, call the command object
        if args[0] in self.cmds:
            return self.cmds[args[0]].process(args)
        # else - command not understood
        else:
            return "Sorry - no idea what that command is."
