//
//  drawing.h
//  softplot
//
//  Created by András Libál on 8/7/18.
//  Copyright © 2018 András Libál. All rights reserved.
//

#ifndef drawing_h
#define drawing_h

#include "globaldata.h"

void init_OpenGl(void);
void init_glut();

void DrawCircle(float cx, float cy, float r, int num_segments,int filled);
void draw_all_particles(int frame);

int inside_zoomed_box(float x, float y);
void transform_to_opengl(float *x,float *y);

void display_function(void);
void reshape_function(int w, int h);

void start_main_loop_glut(void);

#endif /* drawing_h */
