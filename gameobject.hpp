#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class GameObject
{
	public:
		GLfloat m_pos_y;
		GLfloat m_pos_x;
		GLfloat m_color_r;
		GLfloat m_color_g;
		GLfloat m_color_b;

	public:
		GameObject(GLfloat pos_y, GLfloat pos_x):m_pos_x(pos_x),m_pos_y(pos_y),m_color_r(0.0f),m_color_g(0.0f),m_color_b(0.0f){}
		GameObject(GLfloat pos_y, GLfloat pos_x, GLfloat color_r,GLfloat color_g,GLfloat color_b):m_pos_x(pos_x),m_pos_y(pos_y),m_color_r(color_r),m_color_g(color_g),m_color_b(color_b){}
		GLfloat Distance(GameObject another_g_o);
		virtual void Render();
};

#endif