# PS4a: Static Animation Player

This Markdown file was produced from the assignment PDF and the starter project files in this repository.

## Assignment overview

Inbetweening (shortened to tweening) is the process of creating key frames and then interpolating intermediate frames between them. This lets animation look smooth without manually specifying every frame.

In this assignment, the student builds an application named `AniPlayer` that reads an animation specification from a JSON file and draws the scene on screen. Part A covers loading the file and drawing the first frame. Part B adds tweening and movement.

The background color is set to `0x01010101`.

## Required behavior

The program must:

- take a filename as a command-line argument
- read a JSON animation file
- create the scene graph from the file data
- draw the first frame in an SFML window
- support animation and movement in the later part of the assignment

## JSON format

The animation file uses JSON, a human-readable text format with field-value pairs. The `nlohmann/json` C++ library is expected for parsing.

Example:

```json
{
  "shape": "circle",
  "radius": 50,
  "keyframes": [
    {"t": 0, "x": 50, "y": 50},
    {"t": 5, "x": 300, "y": 300}
  ]
}
```

The JSON object may contain strings, numbers, booleans, arrays, or nested objects.

## Core classes

The project uses a namespace called `AP` and includes the following major types:

### `AniPlayer`

Fields:

- `width` (unsigned int, required)
- `height` (unsigned int, required)
- `scene` (Component, required)
- `bgm` (string, optional)

### `KeyFrame`

Fields:

- `t` (float, required)
- `x` (float, default 0)
- `y` (float, default 0)
- `scale-x` (float, default 1)
- `scale-y` (float, default 1)
- `theta` (float, default 0, in degrees)

### `Component`

Base class for all drawable objects.

Fields:

- `shape` (string, required)
- `color` (string, hex, default `FFFFFFFF`)
- `keyframes` (KeyFrame[], default empty)

Component includes a factory method:

```cpp
static std::unique_ptr<Component> fromJson(const Json& data);
```

This is the factory pattern: the correct concrete component type is created from the JSON data.

## Component subclasses

### CircleComponent

- `radius` (float, default 0)
- `sides` (size_t, default 30)
- centered at the given position

### RectangleComponent

- `x`, `y`, `width`, `height`
- defaults are zero

### ImageComponent

- `file` (string, required)
- file path relative to the project

### TextComponent

- `text` (string, default empty)
- `font` (string, required)
- drawn from the upper-left corner

### CompositeComponent

- `children` (Component[], default empty)
- children are drawn relative to the parent composite

## Design patterns required

### Factory pattern

Rather than writing repeated conditional logic to decide which component to build, the assignment asks for a `fromJson` factory. That centralizes construction and returns a `std::unique_ptr<Component>`.

### Composite pattern

The animation consists of figures and nested groups. A composite component organizes children and renders them relative to the parent.

## Rendering rules

The PDF specifies that:

- `CircleComponent` and `ImageComponent` are centered at their positions
- `TextComponent` uses its upper-left corner as the origin
- `CompositeComponent` draws children relative to the parent
- the scene is displayed in a window sized according to `width` and `height`

## Part A and Part B

### Part A

- read JSON
- build the scene
- render the first frame
- handle defaults and invalid shapes
- set the correct window size and background

### Part B

- add tweening between keyframes
- interpolate position, scale, and rotation
- animate movement over time
- apply transforms to the scene

## Starter files

The starter code includes:

- `AniPlayer-starter/AniPlayer.hpp`
- `AniPlayer-starter/Component.hpp`
- `AniPlayer-starter/KeyFrame.hpp`
- `AniPlayer-starter/jsonsample.cpp`
- `AniPlayer-starter/Readme-ps4.md`

These files define the expected classes and show a basic JSON parsing example.

## Summary

This is a C++/SFML assignment in which students build a small animation system from a JSON description. The project emphasizes object-oriented design, factory construction, scene composition, and interpolation-based animation. The assignment is a strong undergrad exercise in graphics rendering and structured software design.
