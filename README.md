# Metamorphosis
A short story film, rendered using OpenGL (having implemented the Bresenham midpoint algorithm for rasterization).

## Build Instructions

Build using [CMake](https://cmake.org/). For more details, see [BUILDING.md](BUILDING.md).

```bash
git clone git@github.com:the-hyp0cr1t3/rasterization-algos.git
cd rasterization-algos

# Build
mkdir build
cd build
cmake ..
make

# Install
sudo make install
```

## Usage

```console
foo@bar:~$ render [input_file]
```