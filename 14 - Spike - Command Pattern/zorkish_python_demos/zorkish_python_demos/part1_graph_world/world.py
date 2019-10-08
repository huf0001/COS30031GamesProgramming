"""Location, Player and World classes.

The World is the owner of locations which are added to it (by the Adventure
class as it reads an adventure text file), and the Player instance.

We can ask the world instance where the players current location is.

This simple Spike 5 version does not include Items (but if it did they would be
declared and used here in this module also).

"""

class Location(object):
    # Each location has
    # - id int (the global identifier)
    # - name string (simple text name)
    # - desc string (a short description)
    # - edges dict (a dictionary map of direction "key" to location id int)

    # Internally, direction keys are stored in "long" format eg "north"
    # so need an easy way to convert short "h" form to long "north" forms
    DIR_ALIAS = {
        'n':'north',
        'e':'east',
        's':'south',
        'w':'west',
        'ne':'northeast',
        'se':'southeast',
        'sw':'southwest',
        'nw':'northwest',
        'u':'up',
        'd':'down'
    }

    @classmethod
    def dir_check(cls, dir):
        # if its in the DIR_ALIAS convert it, else return as-is
        if dir in cls.DIR_ALIAS:
            return cls.DIR_ALIAS[dir]
        else:
            return dir

    def __init__(self, bits):
        # assume bits is a list of strings to describe the location
        #L:id:name:desc:(edges):(items)
        self.id = int(bits[1])
        self.name = bits[2].strip()
        self.desc = bits[3].strip()
        # create a dictionary (map) of edge directions
        # convert a string of "n=3,ne=6,u=7" to dictionary of edges
        self.edges = dict()
        for bit in bits[4].split(','):
            dir, loc_id = bit.split('=')
            dir = self.dir_check(dir) # store direction in "long" format ("north" not "n" etc)
            self.edges[dir] = int(loc_id)


class Player(object):
    def __init__(self):
        self.loc = 0 # current world ID (int)
        self.steps = 0 # move/action counter
        self.gold = 0 # gold
        self.playing = False # well.. are you?


class World(object):
    # contains locations, items and player information
    # shared around (known about) b/w commands/manager/adventure
    def __init__(self):
        self.locations = {} # <int id, Location obj>, id is key
        self.player = Player()
        self.about = ''

    def add_location(self, bits):
        l = Location(bits)
        self.locations[l.id] = l

    def current_loc(self):
        return self.locations[self.player.loc]

    def debug_treeview(self):
        # show
        result = []
        result.append('--- debug info -------------------')
        current = self.current_loc()
        result.append("--[Current Location]")
        tmp = (current.id, current.name, current.desc)
        result.append("  -- id=%d\n  --short/long: %s/%s " % tmp)

        result.append("--[Edges]")
        for dir in current.edges:
            edge = self.locations[current.edges[dir]]
            result.append("  --[%s]: [%d] %s " % (dir, edge.id, edge.name))

        return "\n".join(result)


#==============================================================================

if __name__ == '__main__':
    l1 = Location('L:3:short:desc:n=3,se=5,u=12'.split(':'))
    assert l1.id == 3
    assert l1.name == 'short'
    assert l1.desc == 'desc'
    assert l1.edges == dict(n=3,se=5,u=12)
