RATTY
=====

Cars are loud. It's often difficult to hear what was said over a radio. "Can you
repeat that" is said way too often. Radios sometime get unplugged. Radio
communications suck. Also, some people are deaf or hearing imparied. We need an
alternative.

RATTY is a minimialist racing communications application for text communication
among the driver, spotters, and pit. All parties communicate with a text
messaging service (e.g. Discord) via the Internet.

## Components ##

+ Vehicle:
	+ Mobile HotSpot (e.g. Verizon Jetpack)
	+ Arudino with WiFi connected to a single button
	+ Display screen (e.g. a phone or tablet)
+ Pit: Computer connected to internet
+ Spotters: Phones connect to cellular

## Button-based Communication ##

There's quite a bit you could do with a single button by recording any number of
short and long clicks. One could also have more than a single button. For
simplcity, the current design is for 4 types of actions with a single button.
It's easy enough to modify the messages (see `config.h`).

+ Single-click: "Yes"
+ Double-click: "No"
+ Panic-clicks: "Bad things have happened"
+ Long-click: "Pit request"

When the driver signals "bad things" or "pit request" the pit can start to ask
questions.

+ Pit: "Everything OK?"
+ Driver: "Yes"
+ Pit: "Yellow flag in T5"
+ Pit: "Emergency vehicle on track"
+ Pit: "All flags are cleared"
+ Driver: "Pit request"
+ Pit: "Are you running out of fuel?"
+ Driver: "Yes"
+ Pit: "OK, we're getting ready"
+ Driver: "Bad things have happened"
+ Pit: "Are you still pitting for fuel?"
+ Driver: "No"
+ Pit: "OK, come into the paddock"
