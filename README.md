# sm-md-self-organizing-system

First assignment for the Simulation Methods course. Molecular dynamics / pedestrian crossing simulation.

## Description

See [Assignment_1_MD.pdf](Assignment_1_MD.pdf).

## Requirements

- C++11 (compiled using C++17)
- OpenGL (for visualization only. Coded for compatibility with Linux / *freeglut*)

## Usage

### Molecular dynamics

Using [Makefile](Makefile):

- `make build_opt_none` - compiles non-optimized code with g++.
- `make build_opt_none_debug` - compiles non-optimized code with g++, with debug information.
- `make ARGS="true 800 0.001 4.0 0.5 100000 1000 100" run_opt_none` - runs non-optimized code with specific arguments. Arguments should be given in the following order:
  - VERBOSE_BOOL: determines if the simulation will output additional information to stdout;
  - N_PARTICLES: determines number of particles in the simulation;
  - DT: determines the timestep for each iteration of the simulation;
  - PARTICLE_PARTICLE_SCREENING_LENGTH: determines the screening length between particles;
  - PARTICLE_DRIVING_FORCE: determines the initial external driving force on the particles;
  - TOTAL_TIME: number of time cycles of the simulation;
  - ECHO_TIME: interval of time cycles for echoing simulation progress;
  - MOVIE TIME: interval of time cycles for writing a frame into the output file.
- `make run_opt_verlet_default` - runs non-optimized code, with default arguments;
- `make build_opt_verlet` - compiles non-optimized code with g++.
- `make build_opt_verlet_debug` - compiles non-optimized code with g++, with debug information.
- `make ARGS="true 800 0.001 4.0 0.5 100000 1000 100" run_opt_verlet` - runs non-optimized code with specific arguments. Arguments should be given in the following order:
  - VERBOSE_BOOL: determines if the simulation will output additional information to stdout;
  - N_PARTICLES: determines number of particles in the simulation;
  - DT: determines the timestep for each iteration of the simulation;
  - PARTICLE_PARTICLE_SCREENING_LENGTH: determines the screening length between particles;
  - PARTICLE_DRIVING_FORCE: determines the initial external driving force on the particles;
  - TOTAL_TIME: number of time cycles of the simulation;
  - ECHO_TIME: interval of time cycles for echoing simulation progress;
  - MOVIE TIME: interval of time cycles for writing a frame into the output file.
- `make run_opt_verlet_tabulated_default` - runs non-optimized code, with default arguments;
- `make build_opt_verlet_tabulated` - compiles non-optimized code with g++.
- `make build_opt_verlet_tabulated_debug` - compiles non-optimized code with g++, with debug information.
- `make ARGS="true 800 0.001 4.0 0.5 100000 1000 100" run_opt_verlet_tabulated` - runs non-optimized code with specific arguments. Arguments should be given in the following order:
  - VERBOSE_BOOL: determines if the simulation will output additional information to stdout;
  - N_PARTICLES: determines number of particles in the simulation;
  - DT: determines the timestep for each iteration of the simulation;
  - PARTICLE_PARTICLE_SCREENING_LENGTH: determines the screening length between particles;
  - PARTICLE_DRIVING_FORCE: determines the initial external driving force on the particles;
  - TOTAL_TIME: number of time cycles of the simulation;
  - ECHO_TIME: interval of time cycles for echoing simulation progress;
  - MOVIE TIME: interval of time cycles for writing a frame into the output file.
- `make run_opt_none_default` - runs non-optimized code, with default arguments;
- `make build_visualization` - compiles visualization code with g++.
- `make build_visualization_debug` - compiles visualization code with g++, with debug information.
- `make run_visualization` - runs visualization code
