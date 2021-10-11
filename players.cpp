#include "players.hpp"
#include "render.hpp"
#define MAX_SCREEN_Y 250
#define MAX_SCREEN_X 250

#include <iostream>


Player::~Player()
{
}


void Player::Move(const GLfloat delta_t)
{
	if(m_pos_y+delta_t*m_speed<=MAX_SCREEN_Y && m_pos_y+delta_t*m_speed>=-MAX_SCREEN_Y)
		m_pos_y+=delta_t*m_speed;
}

void Player::Render()
{

	glColor3f(m_color_r,m_color_g,m_color_b);
	glRectf(m_pos_x-m_half_width,m_pos_y-m_half_length,m_pos_x+m_half_width,m_pos_y+m_half_length);
}

GLfloat Ball::GetRadius() const
{
	return m_radius;
}

bool Ball::CollisionDetection(Ball another_ball)
{
	std::cout << "detect collisions balls" << std::endl;
	if(this->Distance(another_ball)<=another_ball.GetRadius()+this->GetRadius())
	{
		m_speed_x*=-1;
		m_speed_y*=-1;
		return true;
	}
	return false;

}
GLfloat clamp(GLfloat val, GLfloat min, GLfloat max)
{
	return std::max(min,std::min(max,val));
}
GLint sgn(GLfloat f)
{
	if(f<0)
	{
		return -1;
	}
	else if(f>0)
	{
		return 1;
	}
	else return 0;
}
/* TO DO: revoir la détection */
bool Ball::CollisionDetection(Player &a_player)
{	
	if((m_pos_x>a_player.m_pos_x && a_player.m_is_human) || ((m_pos_x<a_player.m_pos_x && !a_player.m_is_human)))
	{
		GLfloat center_x=m_pos_x+m_radius;//*sgn(m_speed_x);
		GLfloat center_y=m_pos_y+m_radius;//*sgn(m_speed_y);

		GLfloat aabb_center_x=a_player.m_pos_x;//+a_player.m_half_width;
		GLfloat aabb_center_y=a_player.m_pos_y;//+a_player.m_half_length;

		
		GLfloat difference_x=center_x-aabb_center_x;
		GLfloat difference_y=center_y-aabb_center_y;
		
		GLfloat clamped_y=clamp(difference_y,-a_player.m_half_length,a_player.m_half_length);
		GLfloat clamped_x=clamp(difference_x,-a_player.m_half_width,a_player.m_half_width);


		GLfloat closest_x=aabb_center_x+clamped_x;
		GLfloat closest_y=aabb_center_y+clamped_y;

		difference_x=closest_x-center_x;
		difference_y=closest_y-center_y;

		GLfloat sq_distance= difference_x*difference_x+difference_y*difference_y;

		if(sq_distance<=m_radius*m_radius)
		{
			std::cout << m_radius*m_radius << std::endl;
			std::cout << sq_distance << std::endl;
			GLfloat angle=atan((a_player.m_pos_y-m_pos_y)/(a_player.m_pos_x-m_pos_x));
			GLfloat speed=sqrt(m_speed_x*m_speed_x + m_speed_y*m_speed_y);
			
			std::cout << "Angle: " << angle << std::endl;
			m_speed_x*=-1;//cos(-angle)*speed;
			m_speed_y=sin(angle)*speed;
			std::cout << "Vitesse en x: " << m_speed_x << " Vitesse en y: " << m_speed_y << std::endl;
			return true;
		}
	}
	return false;
}

Ball::~Ball()
{

}

void Ball::Render()
{
	glColor3f(m_color_r,m_color_g,m_color_b);
	glRenderCircle(this->m_pos_x,this->m_pos_y, this->m_radius);
}

void Ball::Move(const GLfloat delta_t_ms, Player& human, Player& cpu)
{
	GLfloat delta_t=delta_t_ms*0.001;
	if((m_pos_y+delta_t*m_speed_y<=MAX_SCREEN_Y && m_pos_y+delta_t*m_speed_y>=-MAX_SCREEN_Y) && (m_pos_x+delta_t*m_speed_x<=MAX_SCREEN_X && m_pos_x+delta_t*m_speed_x>=-MAX_SCREEN_X))
	{
		m_pos_y+=delta_t*m_speed_y;
		m_pos_x+=delta_t*m_speed_x;
	}
	else
	{
		m_speed_y*=-1;
	}
}
