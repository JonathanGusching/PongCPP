#ifndef RENDER_HPP
#define RENDER_HPP
#define M_PI 3.1415
#define M_DELTA 0.0001f
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void glRenderCircle(GLfloat centre_x,GLfloat centre_y, GLfloat radius)
{
	glBegin(GL_TRIANGLE_FAN);
		//First square
		GLfloat angle=0.0f;
		while(angle<2*M_PI)
		{
			glVertex3f(centre_x+radius*cos(angle),centre_y+radius*sin(angle),0.0f);
			angle+=M_PI*M_DELTA;
		}
	glEnd();

}

#endif