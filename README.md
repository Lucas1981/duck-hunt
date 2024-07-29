# Duck Hunt

So, with this repository I want to make a clone of the Duck Hunt game, using a mouse pointer to control the target with. My aim is to be able to make use of mouse controls in C++ using SFML, and to make use of animations. For this I have chosen to instantiate the frames as a singleton, that all the animator class instances can then use. That way we'd only have to load the frame assets once, and use it as a flyweight. It was also good to learn more about how you might instantiate a singleton in C++.

Todo:
- [x] Refine mouse controls
- [x] Add screens:
    - [x] Title screen
    - [x] Background
- [x] Add double-buffer layer
- [ ] Add ducks
- [ ] Add shot white-overlay
- [ ] Add collision
- [ ] Refine gameplay lifecycle:
    - [ ] Ready state
    - [ ] Running state
    - [ ] Shot state
    - [ ] Fly away state
    - [ ] End of turn state
    - [ ] Congratulations state
    - [ ] Game over state
    - [ ] Game beat state
- [ ] Add UI
- [ ] Add sound


