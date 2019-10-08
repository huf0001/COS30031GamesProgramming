from world import World, Location, Player

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
        dir = Location.dir_check(args[1])
        edges = self.world.current_loc().edges
        # is a valid move?
        if dir in edges:
            # move it!
            self.world.player.loc = edges[dir]
            return "You have moved %s to %s" % (dir, self.world.current_loc().name)
        else:
            return "Can't move %s." % dir


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
                    dir = Location.dir_check(list(curr_loc.edges.keys())[0])
                    result.append("There is a single exit leading %s" % dir)
                else:
                    result.append("There are %d exits" % len(curr_loc.edges))
                    for edge in curr_loc.edges:
                        result.append(" - %s " % Location.dir_check(edge))  # directions
            else:
                result.append("There are no exits. Are you stuck?")

            # join everything into a single string and return
            return "\n".join(result)
        # default eh?
        return "Eh? Look at what?"


class CommandQuit(Command):
    def process(self, args):
        self.world.player.playing = False
        return 'Leaving the adventure...'


class CommandAlias(Command):
    # needs special __init__ that also knows about manager.
    def __init__(self, world, manager):
        super().__init__(world)
        self.manager = manager

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

#==============================================================================

class CommandManager(object):

    def __init__(self, world):
        # keep a ref to the world (locations, items and player objects)
        self.world = world
        # create a map (dictionary) of the commands we need to know about
        cmds = self.cmds = {}
        # Move
        cmds['move'] = CommandMove(self.world)
        cmds['go'] = cmds['move']
        # Look (location) at items (current inventory/location) OR in items
        cmds['look'] = CommandLook(self.world)
        cmds['inspect'] = cmds['l'] = cmds['look']

        # Quit/Exit the adventure game (set playing = False)
        cmds['quit'] = CommandQuit(self.world)
        cmds['exit'] = cmds['q'] = cmds['bye'] = cmds['quit']

        # Special commands
        cmds['alias'] = CommandAlias(self.world, self)  # needs manager

        cmds['treeview'] = CommandTreeView(self.world)
        cmds['help'] = cmds['?'] = cmds['h'] = CommandHelp(self.world, self)

        # store self reference for singleton-like behaviour
        global _command_manager
        _command_manager = self


    def process(self, input):
        # check for single arg as possible "move" and insert "move" command word
        args = input.split()  # whitespace
        if len(args) == 0:
            return ''
        if (len(args) == 1) and (args[0] not in self.cmds):
            args.insert(0, 'move')
        # based on the first argument command word, call the command object
        if args[0] in self.cmds:
            return self.cmds[args[0]].process(args)
        # else - command not understood
        else:
            return "Sorry - no idea what that command is."


