# sm-md-self-organizing-system

First assignment for the Simulation Methods course. Molecular dynamics / pedestrian crossing simulation.

## Description

See [Assignment_1_MD.pdf](Assignment_1_MD.pdf).

## Requirements

- C++11 (compiled using C++17)
- OpenGL (for visualization only. Coded for compatibility with Linux / *freeglut*)

## Usage

Using [Makefile](Makefile):

- `make build_opt_none` - compiles non-optimized code with g++.
- `make build_opt_none_debug` - compiles non-optimized code with g++, with debug information.
- `make run_opt_none` - runs non-optimized code.
- `make build_visualization` - compiles visualization code with g++.
- `make build_visualization_debug` - compiles visualization code with g++, with debug information.
- `make run_visualization` - runs visualization code
