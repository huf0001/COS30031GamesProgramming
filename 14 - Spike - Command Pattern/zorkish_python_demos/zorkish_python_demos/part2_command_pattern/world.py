from collections import defaultdict

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

def dir_check(dir):
    # if its in the DIR_ALIAS convert it, else return as-is
    if dir in DIR_ALIAS: 
        return DIR_ALIAS[dir]
    else:
        return dir


class Location(object):
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
            dir = dir_check(dir) # store direction in "long" format ("north" not "n" etc)
            self.edges[dir] = int(loc_id)
        # simple list of item id values contained here (set really)
        self.items = [int(bit) for bit in bits[5].split(',')]

    
class Item(object):
    def __init__(self, bits):
        # assume bits is a list of strings to describe this item
        #I:id:name:desc:(flags):(contains)
        self.id = int(bits[1])
        self.name = bits[2].strip()
        self.desc = bits[3].strip()
        # flags: takeable, container, closed, locked, opaque
        # turn string '2,3,5' into list [2,3,5] of int's
        self.items = [int(bit) for bit in bits[5].split(',') if bit]

class Player(object):
    def __init__(self):
        self.loc = 0 # current world ID (int)
        self.items = [] # inventory list of item id's (ints)
        self.steps = 0 # move/action counter
        self.gold = 0 # gold
        self.playing = False # well.. are you?

        
class World(object):
    # contains locations, items and player information
    # shared around (known about) b/w commands/manager/adventure
    def __init__(self):
        self.locations = {} # <int id, Location obj>, id is key
        self.items = {} # <int id, Item obj>, id is key
        self.player = Player()
        self.about = ''
        self.debug = defaultdict(bool)
    
    def add_location(self, bits):
        l = Location(bits)
        self.locations[l.id] = l
    
    def add_item(self, bits):
        i = Item(bits)
        self.items[i.id] = i
        
    def find_item(self, name):
        # looks for an item in players inventory
        for i in self.player.items:
            if self.items[i].name == name:
                return self.items[i]
        # check in the current location
        for i in self.current_loc().items:
            if self.items[i].name == name:
                return self.items[i] 
        # named item not found - return 'none'
        return None
    
    def find_item_in(self, name, container):
        # check for named item in provided container object
        for i in container.items:
            if self.items[i].name == name:
                return self.items[i]
        # named item not found
        return None
            
    
    def current_loc(self):
        return self.locations[self.player.loc]


    def _debug_itemview(self, item_id, level, result):
        item = self.items[item_id]
        result.append("%s--: %s [id=%d]" % (level, item.name, item.id))
        level += '  '
        for ci in item.items:
            self._debug_itemview(ci, level, result)

    def debug_treeview(self):
        # show
        result = []
        result.append('--- debug info -------------------')
        current = self.current_loc()
        result.append("--[Current Location]")
        result.append("  -- id=%d\n  --short/long: %s/%s " % (current.id, current.name, current.desc))
        
        result.append("--[Edges]")
        for dir in current.edges:
            edge = self.locations[current.edges[dir]]
            result.append("  --[%s]: [%d] %s " % (dir, edge.id, edge.name))

        i = Item(['I','-1','[Location Items]','','',','.join([str(bit) for bit in current.items])])
        self.items[-1] = i 
        self._debug_itemview(-1, '', result)
            
        i = Item(['I','-1','[Player Inventory]','','',','.join([str(bit) for bit in self.player.items])])
        self.items[-1] = i 
        self._debug_itemview(-1, '', result)
          
        return "\n".join(result)


if __name__ == '__main__':
    l1 = Location('L:3:short:desc:n=3,se=5,u=12:2,3'.split(':'))
    assert l1.id == 3
    assert l1.name == 'short'
    assert l1.desc == 'desc'
    assert l1.edges == dict(n=3,se=5,u=12)
    assert l1.items == [2,3]
    
    i1 = Item('I:5:short:desc::3,4'.split(':'))
    assert i1.id == 5
    assert i1.name == 'short'
    assert i1.desc == 'desc'
    assert i1.items == [3,4]
              
    
            