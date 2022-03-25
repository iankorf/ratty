RATTY
=====

RATTY is a minimialist racing communications application for text communication
among the driver, spotters, and pit. All parties communicate in a Discord
channel (or the equivalent).

## Vehicle Components ##

+ Mobile HotSpot (e.g. Verizon Jetpack)
+ Arudino with WiFi connected to a single button
+ Display screen running Discord (e.g. a phone or tablet)

Both the Arduino and the display connect to the WiFi provided by the mobile
HotSpot. 

## Pit and Spotters ##

The pit and spotters use computers, tablets, or phones to connect to Discord
over the Internet.

## Button-based Communication ##

There's quite a bit you could do with a single button by recording any number of
short and long clicks. One could also have more than a single button. For
simplcity, the current design is for 4 types of actions with a single button.

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
