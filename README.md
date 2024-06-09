# Engine specifics and Design choices
So my engine is, of course, based on a Game Loop and an Update Loop. Next to that I have used numerous Components to implement specific behaviors. For example for my enemy, I have implemented 
2 different components to simulate 2 different behaviors that my enemies display. I can then assign to each enemy 1 specific behavior that they will then mimic on screen. 
I have also used Components for my Bomb mechanic and it's Explosion after the bomb has exploded. They are also used for more general things like my BoundingBox Component. The Components then
add a rectangle with a given width and height to the object so collisions can be simulated on the GameObject.

Next thing to add, I also use the Observer pattern. This is used to broadcast and receive certain events that happen in-game. For example, if my player has picked up a specific Power-Up, then my Bomb Component needs to know if it needs to extent the range of the explosion or if an extra bomb can be added to the scene via the BombManager. I have used the Observer Pattern over the EventQueue as in my mind broadcasting events and other classes receiving them seems like a logical way of sending out important information without classes being too tightly coupled.

I also make use of several commands in my game. I mostly use them for receiving and responding to user input but I also have other examples that don't implement a command for a movement action.
An example is my HealthCommand that decreases the score when the player hurts themselves.
I also implement user input with these commands in combination with an InputManager class. This class is a singleton as I don't need multiple instances of this class present in the runtime of
my project/ game. InputManager is picking up Keyboard and Controller user inputs, that are Pimpled away. My Movement Command is bound to the Keyboard and Controller Command so both can be used at the same time.

I did implement 1 Event Queue pattern, and I have used this pattern for my Sound Engine. Together with some threading, it is a good way of receiving and transmitting sound without interupting the gameplay. I have split this engine up in multiple sound files. The Game Audio System is the class handling incoming sounds and putting them on the queue. It also Pimpls away the SDL sound library I am using. The Game Audio System inherits from the abstract Audio System class. With this class, I make multiple Audio systems with each a different purpose like the Audio Log System that logs a message when music and soundeffects are played or stopped.

Lastly I have also implemented the State pattern. This is not part of my engine as I am using these states for switching between different game states. For example : MenuState, PlayingState, LevelCompleteState, HighScoreState, ...


# Minigin

Minigin is a very small project using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

# Goal

Minigin can/may be used as a start project for the exam assignment in the course 'Programming 4' at DAE. In that assignment students need to recreate a popular 80's arcade game with a game engine they need to program themselves. During the course we discuss several game programming patterns, using the book '[Game Programming Patterns](https://gameprogrammingpatterns.com/)' by Robert Nystrom as reading material. 

# Disclaimer

Minigin is, despite perhaps the suggestion in its name, not a game engine. It is just a very simple sdl2 ready project with some of the scaffolding in place to get started. None of the patterns discussed in the course are used yet (except singleton which use we challenge during the course). It is up to the students to implement their own vision for their engine, apply patterns as they see fit, create their game as efficient as possible.

# Use

Download the latest release of this project and compile/run in visual studio. Since students need to have their work on github too, they can use this repository as a template.
