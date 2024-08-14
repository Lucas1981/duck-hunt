# Duck Hunt

So, with this repository I want to make a clone of the Duck Hunt game, using a mouse pointer to control the target with. My aim is to be able to make use of mouse controls in C++ using SFML, and to make use of animations. For this I have chosen to instantiate the frames as a singleton, that all the animator class instances can then use. That way we'd only have to load the frame assets once, and use it as a flyweight. It was also good to learn more about how you might instantiate a singleton in C++... but then actually also abandoning that architectural approach.

A word on some struggles. This game can actually feel pretty complex to create. There are a lot of states to take into account, and missing strict conditions to ensure transitions from one to the next is easy, because sometimes they depend on time, sometimes on the behaviour of the player and sometimes on the behaviour of the ducks. Fly away and flown away states for instance, was tricky to distinguish between. Another tricky thing is displaying the ducks shot. You might have to sort and tally at the end of the round, because there's no intuitive way to display them concisely on the go.

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
- [ ] Substitute assets and expand animations:
    - [x] Background
    - [x] Duck animations
    - [ ] Fix first duck animation (inner wing should be white)
    - [ ] Bullet and duck symbols
    - [ ] Title screen
- [ ] Implement background / foreground distinctions
- [ ] Substitute sounds
- [ ] ?Consider taking the player out of the agent pool?
- [ ] Test hit boxes
- [ ] Test application with leak trackers

