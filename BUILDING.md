# Building with CMake

This project requires [CMake](https://cmake.org/).

## Build

To build in release mode with a single-configuration generator (eg. Unix Makefiles):
```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

To build in release mode with a multi-configuration generator (eg. Visual Studio):
```sh
cmake -S . -B build
cmake --build build --config Release
```

### Building with MSVC

Note that MSVC by default is not standards compliant and you need to pass some
flags to make it behave properly. See the `flags-windows` preset in the
[CMakePresets.json](CMakePresets.json) file for the flags and variables to provide to CMake during configuration.

### Build Options

The following options can be passed to cmake for finer control.

* `Metamorphosis_BUILD_DOCS` (default: `ON`): Builds documentation. Open `build/docs/html/index.html` to view them.
* `Metamorphosis_BUILD_EXAMPLES` (default: `ON`): Builds example programs in `examples/`.

<details>
    <summary>Example</summary>

```bash
cmake -S . -B build -D Metamorphosis_BUILD_DOCS=OFF -D Metamorphosis_BUILD_EXAMPLES=OFF
```

</details>

## Install

To install in release mode with a single-configuration generator (eg. Unix Makefiles):
```sh
cmake --install build
```

To install in release mode with a multi-configuration generator (eg. Visual Studio):
```sh
cmake --install build --config Release
```

To install to a location other than the standard one:
```sh
cmake --install build --prefix "/foo/bar/baz"
```

To uninstall:
```sh
cmake --build build --target uninstall
```
