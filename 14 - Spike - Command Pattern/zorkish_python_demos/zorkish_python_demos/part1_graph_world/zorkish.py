#!/usr/bin/python
"""
Run this program with "python zorkish.py" from a command prompt, or you might
be able to simply "double click" the zorkish.py file if your OS+configuration
supports this.

This version supports a graph based world of locations with path edges.

This version also supports the "command processor" pattern (later spike) but note
however that it is *not* required for early spike work. A simple hacked-in "go"
command would be fine.

Commands to try
- look (inspect, l)
- [move/go] direction eg. go north
- treeview // handy location details for debugging
- quit (q, exit, bye)
- help (h, ?)

There is also an "alias" command which lets you bind arbitrary words as
commands. eg
> alias glide move
would then enable you to type ...
> glide north


"""

if __name__ == '__main__':

    from adventure import Adventure
    adv = Adventure()
    adv.load('testworld.txt')
    adv.play()
