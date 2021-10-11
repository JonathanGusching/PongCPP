#include <cmath>

#include "gameobject.hpp"

float GameObject::Distance(GameObject another_g_o)
{
	return abs(this->m_pos_x-another_g_o.m_pos_x)+abs(this->m_pos_y-another_g_o.m_pos_y);
}
void GameObject::Render()
{
	
}