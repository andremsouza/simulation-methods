//  drawing.c
//  softplot
//  Simulation Methods course, 2018
//  First Assignment: Molecular Dynamics (Brownian Dynamics) Simulation

#include "drawing.h"
#include "globaldata.h"

#include <math.h>
#include <unistd.h>

#include <GL/freeglut.h>
// #include <GLUT/glut.h>
#include <GL/gl.h>
// #include <OpenGL/gl.h>
#include <GL/glu.h>
// #include <OpenGL/glu.h>

// initialize OpenGl
void init_OpenGl() {
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);
}

// initialize everything related to glut
void init_glut() {
  int argc;
  char **argv;

  argc = 0;
  argv = NULL;

  // Initializes glut
  glutInit(&argc, argv);

  // Sets up a double buffer with RGBA components and a depth component
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

  // Sets the window size to 512*512 square pixels
  glutInitWindowSize(global.Windowsize_x, global.Windowsize_y);

  // Sets the window position to the upper left
  glutInitWindowPosition(0, 0);

  // Creates a window using internal glut functionality
  glutCreateWindow("Softplot - Soft Matter Plotter");

  // passes reshape and display functions to the OpenGL machine for callback
  glutReshapeFunc(reshape_function);
  glutDisplayFunc(display_function);
  glutIdleFunc(display_function);
}

// Draws a circle with triangle segments
void DrawCircle(float cx, float cy, float r, int num_segments, int filled) {
  float theta, c, s, t;

  theta = 2 * 3.1415926 / float(num_segments);
  c = cosf(theta);  // precalculate the sine and cosine
  s = sinf(theta);

  // we start at angle = 0
  float x = r;
  float y = 0;

  // draw a filled circle
  if (filled == 1) {
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++) {
      // output vertex
      glVertex3f(x + cx, y + cy, -10);

      // apply the rotation matrix
      t = x;
      x = c * x - s * y;
      y = s * t + c * y;
    }
    glEnd();
  }

  // draw a circle without fill
  if (filled == 0) {
    glBegin(GL_LINE_LOOP);

    for (int ii = 0; ii < num_segments; ii++) {
      glVertex3f(x + cx, y + cy, -10);  // output vertex

      // apply the rotation matrix
      t = x;
      x = c * x - s * y;
      y = s * t + c * y;
    }
    glEnd();
  }
}

// draws the particles from a frame
void draw_all_particles(int frame) {
  int i;
  float x, y;
  int color;

  float x0, y0, x1, y1;

  // transform simulation box size
  // to Opengl display coordinates

  x0 = 0.0625 - 2.0;
  y0 = 0.0625 - 1.25;
  x1 = 2.5 - 0.0625 - 2.0;
  y1 = 2.5 - 0.0625 - 1.25;
  // printf("%f %f\n",x0,y0);
  // printf("%f %f\n",x1,y1);

  // simulation box
  glColor3f(0.0, 0.0, 0.0);
  glLineWidth(1.0);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x0, y0, -10);
  glVertex3f(x0, y1, -10);
  glVertex3f(x1, y1, -10);
  glVertex3f(x1, y0, -10);
  glEnd();

  // draw all the particles

  for (i = 0; i < global.N_objects; i++) {
    x = global.objects[frame][i].x;
    y = global.objects[frame][i].y;

    if (inside_zoomed_box(x, y)) {
      color = global.objects[frame][i].color;
      // default: black

      /*
      if (color==2) glColor3f(1.0, 0.0, 0.0);
          else if (color==3) glColor3f(0.0, 0.0, 1.0);
          else if (color==4) glColor3f(0.0, 1.0, 1.0);
          else if (color==5) glColor3f(1.0, 0.0, 1.0);*/

      if (color == 2)
        glColor3f(1.0, 1.0,
                  1.0);  // white, no particle (not filled in percolation)
      else if (color == 3)
        glColor3f(31 / 255.0, 120 / 255.0, 180 / 255.0);
      else if (color == 4)
        glColor3f(178 / 255.0, 223 / 255.0, 138 / 255.0);
      else if (color == 5)
        glColor3f(51 / 255.0, 160 / 255.0, 44 / 255.0);
      else if (color == 6)
        glColor3f(251 / 255.0, 154 / 255.0, 153 / 255.0);
      else if (color == 7)
        glColor3f(227 / 255.0, 26 / 255.0, 28 / 255.0);
      else if (color == 8)
        glColor3f(253 / 255.0, 191 / 255.0, 111 / 255.0);
      else if (color == 9)
        glColor3f(255 / 255.0, 127 / 255.0, 0 / 255.0);
      else if (color == 10)
        glColor3f(202 / 255.0, 178 / 255.0, 214 / 255.0);

      else
        glColor3f(0.7, 0.7, 0.7);

      // remap to OpenGl coord

      // main window is an 1280x800
      // I want to be in the right side 800x800 for the plot
      // max coordinates are -2,-2 (x) and -1.25,1.25 (y)

      transform_to_opengl(&x, &y);

      DrawCircle(x, y, global.radius_particle, 36, 1);
    }
  }
}

int inside_zoomed_box(float x, float y) {
  if ((x >= global.zoom_x0) && (x <= global.zoom_x1) && (y >= global.zoom_y0) &&
      (y <= global.zoom_y1))
    return 1;
  else
    return 0;
}

// transforms from simulation units to Opengl units
void transform_to_opengl(float *x, float *y) {
  *x = *x - global.zoom_x0;
  *y = *y - global.zoom_y0;

  *x = *x / global.zoom_deltax * 2.375 - 2.0 + 0.0625;
  *y = *y / global.zoom_deltay * 2.375 - 1.25 + 0.0625;
}

// transforms from simulation unit distances to Opengl units
void transform_distance_to_opengl(float *r) { *r = *r / global.SX * 2.375; }

void display_function() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  draw_all_particles(global.current_frame);
  glutSwapBuffers();

  // step through the frames
  if (global.current_frame < global.N_frames - 1) {
    global.current_frame += 1;
    printf("%d/%d\n", global.current_frame, global.N_frames);
    fflush(stdout);
  } else
    global.current_frame = 0;

  getchar();
}

void reshape_function(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-0.1, 0.1, -float(h) / (10.0 * float(w)),
            float(h) / (10.0 * float(w)), 0.5, 1000.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void start_main_loop_glut() { glutMainLoop(); }
