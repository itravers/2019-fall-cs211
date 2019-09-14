So far creating a text editor with the curses library hasn't been that
difficult. The most challenging aspect is figuring out how to wrangle
an old library that does things much differently than I'm used to
into some sort of usable object oriented format. I find that the curses
library is much lower level than most libraries that have the the ability
to manipulate things on screen. For example when designing an android game
I used LibGDX, which not only provides low level access to the primitive
object on the screen, but it also provides layers upon layers of higher
level access, such as the ability to move an object through the physics
system just by applying an impulse. The mouse handling features of a 
library like LibGDX is much more advanced than the api that curses supplies.

With curses you have to completely handle each mouse and keyboard event yourself.
This includes designing some sort of structure where the mouse handling events
have a change to reach any part of the system that wants them. Curses would benefit
immensly from a higher level even dispatching library. Something using a
![dispatcher/receiver](https://camo.githubusercontent.com/33642f04ec637d7f1787d94fc4a944e3e1c41732/687474703a2f2f692e696d6775722e636f6d2f45654f6d464f332e706e67) pattern to allow any part of the system to handle an event
without having to write a ton of scaffolding to support it. I suppose I could
make this library, but that's a bit out of scope of the assignment. I believe
I would be better served by using the scaffolding that i've errected already.
I'll leave refactoring the event handling code into something better designed later.

Right now I'm embracing the idea of leaving some refectoring for later. I have
the tendency to want perfection, which when programming can be self defeating,
because perfecting is completely impossible. For instance, right now I have
several numbers in my program that are functionally magic numbers. I know this
isn't a good design to use, but I'm weighing the tradeoffs of actually going
in and fixing all such instances with the ability to get the program running.

Lastly, I'm trying not to work ahead too far. If I get too far ahead I'll start
turning this into one of my own private software project. I could implement something
in a different way than the teacher would want me to. So I won't get too far into
working ahead so I don't have to dump large amounts of time into backtracking
and redoing something I've already done.
