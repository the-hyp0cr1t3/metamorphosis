# Metamorphosis
So there's this thing called the [Bresenham algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm) for rasterization. We came up with an idea for a short story/film(?) and tried using this algorithm to render a few frames from it. This is how it turned out.

Find the summary, storyboard and code documentation [here](https://the-hyp0cr1t3.github.io/metamorphosis/).

## Build Instructions

Build using [CMake](https://cmake.org/). For more details, see [BUILDING.md](BUILDING.md).

```bash
git clone git@github.com:the-hyp0cr1t3/metamorphosis.git
cd metamorphosis

# Build
mkdir build
cd build
cmake ..
make

# Install
sudo make install
```


## Usage

The `render` executable takes a series of [set color](https://the-hyp0cr1t3.github.io/metamorphosis/pages/code-reference/figure.html#_CPPv4N9bresenham6figure9set_colorE5color), [add line](https://the-hyp0cr1t3.github.io/metamorphosis/pages/code-reference/figure.html#_CPPv4N9bresenham6figure8add_lineE4uint4uint4uint4uint), [add circle](https://the-hyp0cr1t3.github.io/metamorphosis/pages/code-reference/figure.html#_CPPv4N9bresenham6figure10add_circleE4uint4uint4uint), [add ellipse](https://the-hyp0cr1t3.github.io/metamorphosis/pages/code-reference/figure.html#_CPPv4N9bresenham6figure11add_ellipseE4uint4uint4uint4uint) and [fill](https://the-hyp0cr1t3.github.io/metamorphosis/pages/code-reference/figure.html#_CPPv4N9bresenham6figure11add_ellipseE4uint4uint4uint4uint) inputs and renders a frame. See [frames](./example/frames) for more details on the input format. All of this is done of course using the Bresenham library, that goes pixel-by-pixel determining which ones to color.

```console
foo@bar:~$ render [input_file]
```