# PS4: AniPlayer

## Contact
Name:
Section:

Partner Name:
Partner Section:

Time to Complete:

## Description
This project implements a small animation player that reads a JSON scene description and renders the first frame in an SFML window. The application follows the assignment's object-oriented structure by using an `AP::AniPlayer` as the top-level controller, a `KeyFrame` type for animation timing and interpolation data, and a `Component` hierarchy for all drawable shapes and composite structures.

The main goal is to model a scene as a collection of components and render it correctly from the specified data file. In part A, the focus is on parsing the JSON and displaying the initial frame. In part B, the code extends this into tweening and animated motion.

### Features
Describe what your major decisions were and why you did things that way.

#### Part a
The Part A implementation focuses on loading a JSON animation file, validating its required fields, and creating the scene graph. The project supports different component types including circles, rectangles, images, text, and composite groups. Each component is created through a factory function so the client code does not need to know which subtype should be constructed.

The scene is rendered using SFML with the window size and background specified by the JSON. The first frame is drawn correctly before any animation updates are applied.

#### Part b
The Part B implementation adds keyframe-based interpolation. Each `KeyFrame` stores a time value along with transform data such as x, y, scale, and theta. The player computes intermediate states between keyframes so the animation transitions smoothly over time. Transform updates are applied to components and parent composites so movement and rotation work correctly in a nested scene structure.

### Memory
The component graph is stored using smart pointer ownership so each object has a clear lifetime. `Component::fromJson` creates `std::unique_ptr<Component>` instances, which prevents object slicing and makes the tree easy to manage. The scene itself is owned by `AniPlayer`, and image textures are shared by the relevant component objects to avoid unnecessary duplication.

### Issues
The main difficulty involved adapting the assignment's older SFML usage patterns to the version installed in this environment. In particular, the transform API and event handling differ from the textbook examples, so the code had to be written against the local SFML 3 interfaces. Another challenge was resolving relative asset paths for fonts and images from the project directory so the sample scenes could run cleanly.

### Extra Credit
This project includes a robust factory-based scene parser, composite rendering, and path resolution for local assets. It also keeps the implementation organized around the assignment's required API so the code is easy to extend for additional animation features.

## Pair Programming
This project was implemented as a single-person effort with the assignment reference files used for structure and verification. The process was still organized around incremental development: build a working baseline, then add the component model, then implement rendering and tweening.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Kenney Shape Characters (CC0): https://kenney.nl/assets/shape-characters
"Morning Mood" By Edvard Grieg, performed by Musopen Symphony Orchestra (CC-PDM): https://en.wikipedia.org/wiki/Morning_Mood
Roboto font by Christian Robertson (SIL Open Font License): https://fonts.google.com/specimen/Roboto/license
Assignment starter templates and JSON example files in the project repository were used as code and specification references for the AniPlayer design.
