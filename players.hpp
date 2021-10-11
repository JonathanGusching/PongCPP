#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include "gameobject.hpp"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class Player : public GameObject
{
	public:
		bool m_is_human;
		unsigned m_score;
		GLfloat m_half_width;
		GLfloat m_half_length;
		GLfloat m_speed;
		bool KeyUp;
		bool KeyDown;

	public:
		/* */
		Player(bool is_human):GameObject(0.0f,10.0f),KeyUp(false),KeyDown(false),m_is_human(is_human),m_speed(0.0f),m_score(0),m_half_width(2.5f),m_half_length(10.0f){}
		Player(bool is_human, GLfloat pos_x):GameObject(0.0f,pos_x),KeyUp(false),KeyDown(false),m_is_human(is_human),m_speed(0.0f),m_score(0),m_half_width(2.5f),m_half_length(10.0f){}
		Player(bool is_human, GLfloat pos_x, GLfloat color_r,GLfloat color_g,GLfloat color_b):GameObject(0.0f,pos_x, color_r,color_g,color_b),m_is_human(is_human),m_speed(0.0f),m_score(0),m_half_width(2.5f),m_half_length(10.0f){}
		Player(bool is_human, GLfloat pos_x, GLfloat color_r,GLfloat color_g,GLfloat color_b,GLfloat half_width, GLfloat half_length):GameObject(0.0f,pos_x, color_r,color_g,color_b),m_half_length(half_length),m_half_width(half_width),m_is_human(is_human),m_speed(0.0f),m_score(0){}
		~Player();
		void Move(const GLfloat delta_t);
		void Render();

};

class Ball : public GameObject
{
	public:
		GLfloat m_radius;
		GLfloat m_speed_x;
		GLfloat m_speed_y;

	public:
		Ball(GLfloat radius):GameObject(0.0f,0.0f),m_radius(radius),m_speed_x(0.0f),m_speed_y(0.0f){}
		Ball(GLfloat radius,GLfloat speed_x, GLfloat speed_y):GameObject(0.0f,0.0f),m_radius(radius),m_speed_x(speed_x),m_speed_y(speed_y){}
		Ball(GLfloat radius, GLfloat color_r, GLfloat color_g, GLfloat color_b):GameObject(0.0f,0.0f,color_r, color_g, color_b),m_radius(radius),m_speed_x(0.0f),m_speed_y(0.0f){}
		Ball(GLfloat radius, GLfloat color_r, GLfloat color_g, GLfloat color_b, GLfloat speed_x, GLfloat speed_y):GameObject(0.0f,0.0f,color_r, color_g, color_b),m_radius(radius),m_speed_x(speed_x),m_speed_y(speed_y){}
		~Ball();

		GLfloat GetRadius() const;
		bool CollisionDetection(Ball another_ball);
		bool CollisionDetection(Player &a_player);

		void Render();
		void Move(const GLfloat delta_t_ms,Player& human, Player& cpu);
};


#endif