Fluffy is still a work in progress.

# Fluffy

Fluffy is a video game basic framework. It's objective is not to be the 
better and the fastest out there, but simply to help prototyping games.

Fluffy proposes (or will propose) a bunch of utility tools, an ECS, a state
machine, an event system, Lua scripting and whatever comes to my mind or yours.

Even if I'm planning to use it mainly with [SFML](https://github.com/SFML/SFML), 
I don't want Fluffy to be tied to it so that anyone can use it with whatever
multimedia lib he wants. So that means there will be no window handling, 
no media, GUI, keyboard and mouse nor drawing included in Fluffy.

For all of that I already have my Potato framework, that I might re-code to
work in concert with Fluffy, someday.

## Fluffy needs

* A compiler that supports c++11 at least
* Lua 5.3.3 (the lib is included but you still need the include files)

## Fluffy uses

* [Bandit/Bandit](https://github.com/banditcpp/) For unit testing
* [open-source-parsers/jsoncpp](https://github.com/open-source-parsers/jsoncpp) For serialization stuff and loading data
* [jeremyong/Selene](https://github.com/jeremyong/Selene) Lua to C++ binding

## How to compile

Use  `cmake` and the compiler of your choice