# PS4a: AniPlayer

## Description
This project implements a lightweight animation player in C++ using SFML and JSON-driven scene data. It reads a `.json` scene description, constructs a scene graph of drawable components, and renders the animation window using the provided geometry and keyframe definitions.

The implementation follows the assignment structure by modeling the application under the `AP` namespace, with a core `AniPlayer`, `KeyFrame`, and `Component` hierarchy. It supports static rendering in Part A and the interpolation-based motion logic expected for Part B.

## Features
### Part A
- JSON scene loading from a file path
- Window creation sized to the animation dimensions
- Component factory creation from JSON data
- Support for:
  - circle components
  - rectangle components
  - image components
  - text components
  - composite components
- Correct color parsing and default values
- Base scene rendering for the first frame

### Part B
- Keyframe interpolation using `t` values
- Transform application for position, rotation, and scale
- Motion updates over time via the `tween()` flow
- Composite child transforms relative to parent components

### Design choices
The project uses a factory pattern for component construction (`Component::fromJson`) so the caller does not need to know the exact concrete type being built. Each component stores its own keyframe sequence and computes the current frame as needed. Composite components are used to compose nested children and render them relative to the parent transform, which mirrors the assignment’s expected object model.

### Memory model
The implementation uses smart pointers (`std::unique_ptr`) for ownership of component instances created by the factory and for scene ownership within `AniPlayer`. This avoids slicing and keeps resource lifetime clear for the component tree. Image assets are loaded into shared texture objects so they can be reused across multiple render passes without duplicating raw asset state.

### Issues and learning notes
The main challenges involved adapting the assignment’s older C++/SFML conventions to the SFML 3 API present in this environment, especially around transform APIs, event polling, and font/text construction. The implementation also needed careful handling of relative asset paths so the example videos and default fonts could resolve correctly when run from the project directory.

## Project layout
- `src/` contains the runtime implementation
- `include/` contains the public class declarations
- `README.md` documents the project and assignment context
- `Roboto-Regular.ttf` is included so the sample text-based scenes can run locally

## Build and run
From the project directory:

```bash
make
./AniPlayer ../videos/hello-world.json
```

You can point the program at any valid JSON animation file in the repository’s `videos/` folder.

## Acknowledgements
- Kenney Shape Characters (CC0): https://kenney.nl/assets/shape-characters
- "Morning Mood" by Edvard Grieg, performed by Musopen Symphony Orchestra (CC-PDM): https://en.wikipedia.org/wiki/Morning_Mood
- Roboto font by Christian Robertson (SIL Open Font License): https://fonts.google.com/specimen/Roboto/license
- Assignment reference files in `AniPlayer-starter/` were used for implementation guidance, not as the active project source.

