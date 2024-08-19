# Duck Shot

<img width="682" alt="Screenshot 2024-08-19 at 22 02 37" src="https://github.com/user-attachments/assets/9b9b0b3b-7299-4f77-8ad5-807fb2429717">

So, with this repository I want to make a clone of the Duck Hunt game, using a mouse pointer to control the target with. My aim is to be able to make use of mouse controls in C++ using SFML, and to make use of animations. For this I have chosen to instantiate the frames as a singleton, that all the animator class instances can then use. That way we'd only have to load the frame assets once, and use it as a flyweight. It was also good to learn more about how you might instantiate a singleton in C++... but then actually also abandoning that architectural approach.

A word on some struggles. This game can actually feel pretty complex to create. There are a lot of states to take into account, and missing strict conditions to ensure transitions from one to the next is easy, because sometimes they depend on time, sometimes on the behaviour of the player and sometimes on the behaviour of the ducks. Fly away and flown away states for instance, was tricky to distinguish between. Another tricky thing is displaying the ducks shot. You might have to sort and tally at the end of the round, because there's no intuitive way to display them concisely on the go.

## Reflection

Oeh! What a homecoming! I wanted to make this for 30 years but couldn't figure things out and/or couldn't be bothered. Now - yes, with the aid of ChatGPT as well - I saw it through. I actually really liked the production process and going all punk on graphical assets, coming up with silly sounds to play as well - like the dog barking as a nod to the original game. Felt good to finally do this.

So having finished the whole setup of the game, how do I look back on that process? It was actually very awesome to develop a game like this in such a relatively short period of time with ChatGPT guiding me through setting up all the classes and helping out on details of compiler issues, SFML implementations, tools to use, and when I got into syntax trouble. It really only took three weeks in total!

One thing I definitely might reconsider is how to draw graphics. Right now, I just draw them and there is no order except for the order in which they just occur. I actually took out the main player class from my pool of actors so that I could draw that animation at the right time. Whether or not that is the right way to treat the actor - @igorski claimed it is actually a part of the UI so its representation should be handled by the UI class - can be debated. But to have the drawing hierarchy depend on the order in which elements are handled seems a little naive. I should probably stage all of these drawing actions, use a queue like I do for the sounds. Actually, you can use a priority queue and enqueue all the graphical assets with a "z-index" for priority, then dequeue the whole thing once the scene is set up in priority-order.

I would probably also add some more tools to make things neater and more precise, like Clang-Tidy or Cppcheck. I'd do this early on, so that you kind of can keep up with the suggested changes, much like in the case of the IWYU tool. I'd also set up a Docker instance and run it with the ability to monitor the memory leaks. Clang-Tidy and Cppcheck prove tricky at times though, and annoyingly Cppcheck doesn't seem capable of applying the changes it suggests. I'd probably also set up a Docker image so I can monitor memory allocation and spot mem-leaks in runtime if they occur. I'll save it 

## Todo

- [x] Refine mouse controls
- [x] Add screens:
    - [x] Title screen
    - [x] Background
- [x] Add double-buffer layer
- [x] Add ducks
- [x] Refactor game loop out to play module
- [x] Add collision
- [x] Add text module
- [x] Add listener on red window button
- [x] Refine gameplay lifecycle:
    - [x] Title screen state
    - [x] Begin round state
    - [x] Reset state
    - [x] Ready state
    - [x] Running state
    - [x] Shot state
    - [x] Fly away state
    - [x] Flew away state
    - [x] Round beat state
    - [x] Game over state
    - [x] Game beat state
- [x] Finalize shot animations
- [x] Make sure falling speed is independent of moving speed
- [x] Add UI
- [x] Add time between last duck shot / missed and final "you beat the round" message
    -  [x] Maybe reorder READY and RESET states.
- [x] Manage round configuration
- [x] Display 'ducks shot / ducks left / ducks missed' properly in the UI
- [x] Garbage collect deactivated agents
- [x] Cut up steps in UI module
- [x] Refactor out handlers
- [x] Include tallying mechanism at the end of the round
- [x] Display target in the UI
- [x] Add score animation
- [x] Add sounds
- [x] Add left-facing variant of the flying duck animation
- [x] Implement background / foreground distinctions
- [x] Take the player out of the agents pool
- [x] Adjust starting baseline for new duck spawning
- [x] Figure out how to stop all or somes sound playback prematurely
- [x] Substitute and expand sounds:
    - [x] For Title screen (music)
    - [x] For start round (music)
    - [x] For round won (music)
    - [x] For round lost (music)
    - [x] For game won (music)
    - [x] For shot
    - [x] For duck flying
    - [x] For duck hit
    - [x] For duck falling
    - [x] For duck fallen
- [x] Substitute assets and expand animations:
    - [x] Background
    - [x] Duck animations
    - [x] Fix first duck animation (inner wing should be white)
    - [x] Title screen
    - [x] Bullet, crosshairs and duck symbols

