# How to Run and Test AniPlayer

The project uses CMake and SFML 3, so it can be built on Windows, macOS, and Linux.
The project folder includes a bundled font and sample scenes; it does not require the
macOS-only Homebrew paths or the repository's external reference folders.

## Windows setup

1. Install Visual Studio 2022 with the **Desktop development with C++** workload,
   Git, and CMake. Open **Developer PowerShell for VS 2022**.
2. Install vcpkg once:

   ```powershell
   git clone https://github.com/microsoft/vcpkg.git C:\vcpkg
   C:\vcpkg\bootstrap-vcpkg.bat
   ```

3. Change to the `ps4a` project directory and configure/build:

   ```powershell
   cmake -S . -B build `
     -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake `
     -DVCPKG_TARGET_TRIPLET=x64-windows
   cmake --build build --config Release
   ```

   The `vcpkg.json` manifest installs SFML 3 and nlohmann-json during configuration.
   If CMake cannot find vcpkg, replace `C:/vcpkg` with the location where vcpkg was
   installed.

4. From the project directory, run a bundled sample:

   ```powershell
   $env:PATH = "C:\vcpkg\installed\x64-windows\bin;$env:PATH"
   .\build\Release\AniPlayer.exe .\examples\hello-world.json
   ```

   Keep the terminal's current directory at the project root so the application can
   find `Roboto-Regular.ttf`. If no scene argument is provided, it opens this bundled
   sample by default. Press **Escape** or close the window to exit.

## Build and run on macOS or Linux

Install a C++17 compiler, CMake, SFML 3, and nlohmann-json using the platform's
package manager. Then, from the `ps4a` project directory:

```sh
cmake -S . -B build
cmake --build build
./build/AniPlayer examples/hello-world.json
```

On a multi-configuration generator, such as Visual Studio, specify a configuration
when building and running, for example `build/Release/AniPlayer.exe`.

The optional Makefile workflow is also available on systems with GNU Make, SFML, and
pkg-config:

```sh
make
./AniPlayer examples/hello-world.json
```

## Test

There is no automated unit-test target. Use these manual checks from the project root:

1. **Build:** Configure and build successfully using the commands for your platform.
2. **Render:** Run `examples/hello-world.json` and confirm a window opens with the text
   displayed.
3. **Invalid input:** Run the invalid scene and confirm the application prints an error
   and exits with a non-zero status:

   ```powershell
   .\build\Release\AniPlayer.exe .\examples\invalid-shape.json
   $LASTEXITCODE
   ```

   On macOS or Linux, use:

   ```sh
   ./build/AniPlayer examples/invalid-shape.json
   echo $?
   ```

## Lint

If `cpplint` is installed and available on your `PATH`, run from the project directory:

```sh
make lint
```

The lint settings are in `CPPLINT.cfg`.
