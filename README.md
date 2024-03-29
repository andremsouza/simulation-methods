# Simulation Methods: Assignments

Assignments for the simulation methods course.

## Description

### Assignment 1

See [Assignment_1_MD.pdf](assignment1_md/Assignment_1_MD.pdf).

### Assignment 2

See [Assignment_2_MD.pdf](assignment2_md_pinning/Assignment_2 MD.pdf).

### Assignment 3

See [Assignment_3_MC.pdf](assignment3_mc/Assignment_3_MC.pdf).

### Assignment 4

See [Assignment_4_CA_Perk_DLA.pdf](assignment4_ca/Assignment_4_CA_Perk_DLA.pdf).

## Requirements

- C++11 (compiled using C++17)
- OpenGL (for visualization only. Coded for compatibility with Linux / *freeglut*)

## Usage

### Molecular dynamics

Using [Makefile](assignment1_md/Makefile):

- `make build_opt_none` - compiles non-optimized code with g++.
- `make build_opt_none_debug` - compiles non-optimized code with g++, with debug information.
- `make ARGS="true 800" run_opt_none` - runs non-optimized code with specific arguments. Arguments should be given in the following order:
  - VERBOSE_BOOL: determines if the simulation will output additional information to stdout;
  - N_PARTICLES: determines number of particles in the simulation;
- `make run_opt_verlet_default` - runs non-optimized code, with default arguments;
- `make build_opt_verlet` - compiles non-optimized code with g++.
- `make build_opt_verlet_debug` - compiles non-optimized code with g++, with debug information.
- `make ARGS="true 800" run_opt_verlet` - runs non-optimized code with specific arguments. Arguments should be given in the following order:
  - VERBOSE_BOOL: determines if the simulation will output additional information to stdout;
  - N_PARTICLES: determines number of particles in the simulation;
- `make run_opt_verlet_tabulated_default` - runs non-optimized code, with default arguments;
- `make build_opt_verlet_tabulated` - compiles non-optimized code with g++.
- `make build_opt_verlet_tabulated_debug` - compiles non-optimized code with g++, with debug information.
- `make ARGS="true 800" run_opt_verlet_tabulated` - runs non-optimized code with specific arguments. Arguments should be given in the following order:
  - VERBOSE_BOOL: determines if the simulation will output additional information to stdout;
  - N_PARTICLES: determines number of particles in the simulation;
- `make run_opt_none_default` - runs non-optimized code, with default arguments;
- `make build_visualization` - compiles visualization code with g++.
- `make build_visualization_debug` - compiles visualization code with g++, with debug information.
- `make run_visualization` - runs visualization code

### Molecular dynamics with pinning sites

Using [Makefile](assignment2_md_pinning/Makefile):

- `make build` - compiles code with gcc.
- `make build_debug` - compiles code with gcc, with debug information.
- `make run` - runs simulation
- `make build_visualization` - compiles visualization code with g++.
- `make build_visualization_debug` - compiles visualization code with g++, with debug information.
- `make run_visualization` - runs visualization code

### Monte Carlos methods

- Compile using gcc for each method;
- Compile visualization using [Makefile](assignment3_mc/softplot/Makefile).
