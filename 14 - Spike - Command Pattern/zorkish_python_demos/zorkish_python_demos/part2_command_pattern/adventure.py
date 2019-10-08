from world import World
from commands import CommandManager

class Adventure(object):
    def __init__(self):
        self._reset()

    def _reset(self):
        self.world = World()
        self.cmd_mgr = CommandManager(self.world)

    def load(self, filename):
        self._reset()
        f = open(filename)
        for line in f:
            line = line.strip()
            if len(line) > 0 and line[0] != '#':
                if line[0] == 'L': # new location
                    self.world.add_location(line.split(':'))
                elif line[0] == 'I': # new item
                    self.world.add_item(line.split(':'))
                elif line[0] == 'S': # start node S:id:desc
                    _, id, desc = line.split(':')
                    self.world.player.loc = int(id)
                else:
                    raise IOError('Error - adventure line', line)

    def play(self):
        # play the game
        print('Another Zorkish Adventure.')
        print('-'*80)

        self.world.player.playing = True

        while self.world.player.playing:
            values = input('> ').strip().lower() # make sure \n or \r is gone.
            print(self.cmd_mgr.process(values))

        print('-'*80)
        print('Thanks for playing.')

