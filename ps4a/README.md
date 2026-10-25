# AniPlayer Project

This folder contains a minimal, runnable SFML project scaffold for the PS4a assignment.

## Build

```bash
cd ps4a
make
```

## Run

```bash
./AniPlayer
```

You can optionally pass a JSON animation file as a command-line argument. The app will parse the file if it is valid JSON and print the scene metadata to the terminal.

## Notes

- The project intentionally starts with a minimal launch window so the environment is verified before full AniPlayer logic is added.
- The assignment reference files in `AniPlayer-starter/` are kept separate and are used as design guidance, not as the working implementation.
