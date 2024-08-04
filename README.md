# Duck Hunt

So, with this repository I want to make a clone of the Duck Hunt game, using a mouse pointer to control the target with. My aim is to be able to make use of mouse controls in C++ using SFML, and to make use of animations. For this I have chosen to instantiate the frames as a singleton, that all the animator class instances can then use. That way we'd only have to load the frame assets once, and use it as a flyweight. It was also good to learn more about how you might instantiate a singleton in C++.

Todo:
- [x] Refine mouse controls
- [x] Add screens:
    - [x] Title screen
    - [x] Background
- [x] Add double-buffer layer
- [x] Add ducks
- [x] Refactor game loop out to play module
- [x] Add collision
- [x] Add text module
- [ ] Refine gameplay lifecycle:
    - [x] Title screen state
    - [ ] ?Begin round state?
    - [x] Reset state
    - [x] Ready state
    - [x] Running state
    - [x] Shot state
    - [x] Fly away state
    - [ ] ?Flew away state?
    - [ ] End of round state (tally?)
    - [ ] Congratulations state
    - [ ] Game over state
    - [ ] Game beat state
- [ ] Manage round configuration (with rounds module maybe)
- [ ] Add listener on red window button
- [ ] Add shot white-overlay
- [ ] Add states and state animations for player
- [ ] Add UI
- [ ] Add sounds
- [ ] Substitute assets 

