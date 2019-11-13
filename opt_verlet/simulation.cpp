// Implementation file for "simulation.hpp"

#include "simulation.hpp"

MD::Simulation::Simulation(bool t_verbose, int t_n_particles, double t_dt,
                           double t_particle_particle_screening_length,
                           double t_particle_driving_force)
    : m_verbose(t_verbose),
      m_n_particles(t_n_particles),
      m_dt(t_dt),
      m_particle_particle_screening_length(
          t_particle_particle_screening_length),
      m_particle_driving_force(t_particle_driving_force) {
  // Calculating Verlet variables
  m_verlet_cutoff_distance =
      VERLET_CUTOFF_RATIO * m_particle_particle_screening_length;
  m_verlet_cutoff_distance_squared =
      m_verlet_cutoff_distance * m_verlet_cutoff_distance;
  m_verlet_intershell_squared =
      (m_verlet_cutoff_distance - m_particle_particle_screening_length) / 2.0;
  m_verlet_intershell_squared /= 2.0;
  m_verlet_intershell_squared *= m_verlet_intershell_squared;

  // Printing input information
  if (m_verbose) {
    std::cout << "Initializing simulation" << std::endl;
    std::cout << "Number of particles = " << m_n_particles << std::endl;
    std::cout << "Timestep (dt) = " << m_dt << std::endl;
    std::cout << "Screening length = " << m_particle_particle_screening_length
              << std::endl;
    std::cout << "Driving force on particles = " << m_particle_driving_force
              << std::endl;
    std::cout << "Verlet cutoff distance = " << m_verlet_cutoff_distance
              << std::endl;
    std::cout << "Verlet cutoff distance squared = "
              << m_verlet_cutoff_distance_squared << std::endl;
    std::cout << "Half of Verlet intershell distance = "
              << sqrt(m_verlet_intershell_squared) << std::endl;
    std::cout << "Half of Verlet intershell distance squared = "
              << m_verlet_intershell_squared << std::endl;
  }

  // Calculating box size, based on the number of particles
  m_sx = m_sy = round(sqrt(m_n_particles / PARTICLE_DENSITY));
  m_half_sx = m_half_sy = m_sx / 2.0;
  if (m_verbose)
    std::cout << "Box size = " << m_sx << " x " << m_sy << std::endl;

  // initializing particles
  m_particle_x.resize(m_n_particles);
  m_particle_y.resize(m_n_particles);
  m_particle_fx.resize(m_n_particles);
  m_particle_fy.resize(m_n_particles);
  m_particle_direction.resize(m_n_particles);
  m_particle_color.resize(m_n_particles);

  // initializing dx_so_far and dy_so_far vectors
  m_particle_dx_so_far.resize(m_n_particles);
  m_particle_dy_so_far.resize(m_n_particles);

  // Try to assign a position to each particle
  if (m_verbose)
    std::cout << "Random arrangement of particles initialized" << std::endl;

  for (int i = 0; i < m_n_particles; i++) {
    double x_try = 0.0, y_try = 0.0;
    bool overlap = true;  // check overlap with other particles
    int n_trials = 0;     // limit number of trials before giving up

    while (overlap && n_trials < m_n_particles * m_n_particles) {
      // try to position particle randomly
      x_try = m_sx * std::rand() / (RAND_MAX + 1.0);
      y_try = m_sy * std::rand() / (RAND_MAX + 1.0);

      overlap = false;

      for (int j = 0; j < i; j++) {
        // Calculating distances between particle i and others

        // PBC fold back
        // if any distance is larger than half the box
        // the copy in the neighboring box is closer
        double dx = m_particle_x[i] - x_try, dy = m_particle_y[i] - y_try;
        if (dx > m_half_sx) dx -= m_sx;
        if (dx <= -m_half_sx) dx += m_sx;
        if (dy > m_half_sy) dy -= m_sy;
        if (dy <= -m_half_sy) dy += m_sy;

        if (std::sqrt(dx * dx + dy * dy) < MINIMUM_PLACEMENT_DISTANCE) {
          overlap = true;
          n_trials++;
          break;
        }
      }
    }

    // If we can't place all particles, raise error and exit
    if (n_trials == m_n_particles * m_n_particles) {
      std::cout << "Can't place particles randomly, (system too dense) quitting"
                << std::endl;
      std::exit(1);
    }

    // assign position, direction and color for particle
    m_particle_x[i] = x_try;
    m_particle_y[i] = y_try;
    m_particle_fx[i] = 0.0;
    m_particle_fy[i] = 0.0;

    // dx_so_far, dy_so_far
    m_particle_dx_so_far[i] = 0.0;
    m_particle_dy_so_far[i] = 0.0;

    if (std::rand() / (RAND_MAX + 1.0) < DIRECTION_PROBABILITY) {
      m_particle_direction[i] = -1.0;
      m_particle_color[i] = 2;
    } else {
      m_particle_direction[i] = +1.0;
      m_particle_color[i] = 3;
    }
  }

  // particles initialized
  if (m_verbose)
    std::cout << "N_particles = " << m_n_particles << " placed" << std::endl;

  // Initializing files
  if (m_verbose) std::cout << "Opening file \"particles.mvi\"" << std::endl;
  m_moviefile.open("./particles.mvi", std::fstream::binary | std::fstream::out |
                                          std::fstream::trunc);
  if (m_verbose) std::cout << "Output file opened successfully" << std::endl;
}

void MD::Simulation::calcPairwiseForces() {
  for (int ii = 0; ii < m_n_verlet; ii++) {
    int i = m_verletlist_i[ii], j = m_verletlist_j[ii];

    // calculating squared distance between particles
    double dx = m_particle_x[j] - m_particle_x[i];
    double dy = m_particle_y[j] - m_particle_y[i];
    double r2;

    // PBC fold back
    // if any distance is larger than half the box
    // the copy in the neighboring box is closer
    if (dx > m_half_sx) dx -= m_sx;
    if (dx <= -m_half_sx) dx += m_sx;
    if (dy > m_half_sy) dy -= m_sy;
    if (dy <= -m_half_sy) dy += m_sy;

    r2 = dx * dx + dy * dy;

    // the particles are close enough to interact
    if (r2 < INTERACTION_THRESHOLD) {
      double r = sqrt(r2), f;

      // If too close, raise warning and use a constant high force
      if (r < MINIMUM_INTERACTION_DISTANCE) {
        if (m_verbose)
          std::cout << "WARNING:PARTICLES TOO CLOSE. LOWER CUTOFF FORCE USED"
                    << std::endl;
        f = TOO_CLOSE_FORCE;
      } else {
        // calculate the force
        f = 1 / r2 * std::exp(-r / m_particle_particle_screening_length);
      }

      // projection to the x,y axes
      f /= r;

      m_particle_fx[i] -= f * dx;
      m_particle_fy[i] -= f * dy;
      m_particle_fx[j] += f * dx;
      m_particle_fy[j] += f * dy;
    }
  }
}

void MD::Simulation::writeCMovieFrame() {
  float floatholder;

  // writing frame data to .mvi
  // each frame will have the number of particles and the cycle number of the
  // simulation
  m_moviefile.write(reinterpret_cast<char *>(&m_n_particles), sizeof(int));
  m_moviefile.write(reinterpret_cast<char *>(&m_time), sizeof(int));

  // for each particle, write its color, number, position, and "existence" value
  for (int i = 0; i < m_n_particles; i++) {
    m_moviefile.write(reinterpret_cast<char *>(&(m_particle_color[i])),
                      sizeof(int));
    m_moviefile.write(reinterpret_cast<char *>(&i), sizeof(int));

    floatholder = (float)m_particle_x[i];
    m_moviefile.write(reinterpret_cast<char *>(&floatholder), sizeof(float));
    floatholder = (float)m_particle_y[i];
    m_moviefile.write(reinterpret_cast<char *>(&floatholder), sizeof(float));
    floatholder = 1.0;  // cum_disp, c movie format
    m_moviefile.write(reinterpret_cast<char *>(&floatholder), sizeof(float));
  }
}

void MD::Simulation::rebuildVerletList() {
  // If m_n_verlet_max == 0, initialize list for the first time
  if (!m_n_verlet_max) {
    double system_density = m_n_particles / (double)m_sx / (double)m_sy;
    double shell = system_density * M_PI * m_verlet_cutoff_distance_squared;
    m_n_verlet_max = (int)shell * m_n_particles / 2;

    m_verletlist_i.resize(m_n_verlet_max);
    m_verletlist_j.resize(m_n_verlet_max);

    if (m_verbose)
      std::cout << "Verlet list will be built for the first time" << std::endl
                << "System density is " << system_density << std::endl
                << "Particles in a R = " << m_verlet_cutoff_distance
                << " shell = " << shell << std::endl
                << "Estimated n_verlet_max = " << m_n_verlet_max << std::endl;
  }

  // Building verlet list
  m_n_verlet = 0;
  for (int i = 0; i < m_n_particles; i++) {
    for (int j = i + 1; j < m_n_particles; j++) {
      // calculating squared distance between particles
      double dx = m_particle_x[j] - m_particle_x[i];
      double dy = m_particle_y[j] - m_particle_y[i];
      double r2;

      // PBC fold back
      // if any distance is larger than half the box
      // the copy in the neighboring box is closer
      if (dx > m_half_sx) dx -= m_sx;
      if (dx <= -m_half_sx) dx += m_sx;
      if (dy > m_half_sy) dy -= m_sy;
      if (dy <= -m_half_sy) dy += m_sy;

      r2 = dx * dx + dy * dy;

      if (r2 < VERLET_CUTOFF_DISTANCE) {
        m_verletlist_i[m_n_verlet] = i;
        m_verletlist_j[m_n_verlet] = j;

        m_n_verlet++;
        if (m_n_verlet >= m_n_verlet_max) {
          if (m_verbose)
            std::cout << "Verlet list reallocated from" << m_n_verlet_max
                      << std::endl;
          m_n_verlet_max = (int)(VERLET_GROWTH_RATIO * m_n_verlet);
          m_verletlist_i.resize(m_n_verlet_max);
          m_verletlist_j.resize(m_n_verlet_max);
          if (m_verbose)
            std::cout << "New Verlet list max size = " << m_n_verlet_max
                      << std::endl;
        }
      }
    }
  }

  if (m_verbose)
    std::cout << "Counted Verlet list length = " << m_n_verlet << std::endl;

  // Reseting rebuild state
  m_flag_verlet_rebuild = false;
  for (int i = 0; i < m_n_particles; i++) {
    m_particle_dx_so_far[i] = 0.0;
    m_particle_dy_so_far[i] = 0.0;
  }

  // Recoloring
  for (int i = 0; i < m_n_particles; i++)
    if (m_particle_direction[i] == 1)
      m_particle_color[i] = 3;
    else
      m_particle_color[i] = 2;

  for (int i = 0; i < m_n_verlet; i++) {
    if (m_verletlist_i[i] == VERLET_RECOLORING_VALUE)
      m_particle_color[m_verletlist_j[i]] = 4;
    if (m_verletlist_j[i] == VERLET_RECOLORING_VALUE)
      m_particle_color[m_verletlist_i[i]] = 4;
  }
}

void MD::Simulation::checkVerletRebuildCondition() {
  // check if any particle moved (potentially) enough to enter the inner Verlet
  // shell
  // the worst case scenario is when the center particle moved out and the
  // external particle moved inward this is why we divide by 2.0 when we set the
  // intershell up
  m_flag_verlet_rebuild = false;

  for (int i = 0; i < m_n_particles; i++) {
    double dr2 = m_particle_dx_so_far[i] * m_particle_dx_so_far[i] +
                 m_particle_dy_so_far[i] * m_particle_dy_so_far[i];
    if (dr2 >= m_verlet_intershell_squared) {
      m_flag_verlet_rebuild = true;
      break;
    }
  }
}

void MD::Simulation::runSimulation(int t_total_time, int t_echo_time,
                                   int t_movie_time) {
  // Build Verlet list for the first time
  rebuildVerletList();

  // record current time
  m_time_begin = clock_t::now();
  if (m_verbose)
    std::cout << "Run starting on: " << m_time_begin.time_since_epoch().count()
              << std::endl;

  // begin simulation
  for (m_time = 0; m_time < t_total_time; m_time++) {
    // calculating external forces on particles
    for (int i = 0; i < m_n_particles; i++)
      m_particle_fx[i] += m_particle_direction[i] * m_particle_driving_force;

    // calculating pairwise forces between particles
    calcPairwiseForces();

    // moving particles
    for (int i = 0; i < m_n_particles; i++) {
      double dx = m_particle_fx[i] * m_dt;
      double dy = m_particle_fy[i] * m_dt;

      m_particle_x[i] += dx;
      m_particle_y[i] += dy;

      m_particle_dx_so_far[i] += dx;
      m_particle_dy_so_far[i] += dy;

      // fold back if on border
      if (m_particle_x[i] < 0) m_particle_x[i] += m_sx;
      if (m_particle_y[i] < 0) m_particle_y[i] += m_sy;
      if (m_particle_x[i] >= m_sx) m_particle_x[i] -= m_sx;
      if (m_particle_y[i] >= m_sy) m_particle_y[i] -= m_sy;

      m_particle_fx[i] = 0.0;
      m_particle_fy[i] = 0.0;
    }

    checkVerletRebuildCondition();

    if (m_flag_verlet_rebuild) {
      rebuildVerletList();
    }

    // echo time
    if (m_verbose && m_time % t_echo_time == 0)
      std::cout << "Timestep: " << m_time << " / " << t_total_time << std::endl;

    // movie write time
    if (m_time % t_movie_time == 0) writeCMovieFrame();
  }

  // display information on running times
  m_time_end = clock_t::now();
  if (m_verbose)
    std::cout << "Run finished on: " << m_time_end.time_since_epoch().count()
              << std::endl;
  std::cout
      << "Particles: " << m_n_particles << "; "
      << "Running time (seconds): "
      << std::chrono::duration_cast<second_t>(m_time_end - m_time_begin).count()
      << std::endl;
  m_moviefile.close();
}
