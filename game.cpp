#include <iostream>
#include <stack> //std::stack

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "players.hpp"
#include "gameobject.hpp"

#define M_PLAYER_SPEED 0.40f
#define M_BASE_BALL_SPEED 360.0f

Player* human=new Player(true,-200.0f,0.0f,1.0f,0.0f,2.5f,20.0f);
Player* cpu=new Player(true,200.0f,1.0f,0.0f,0.0f,2.5f,20.0f);
Ball* ball=new Ball(5.0f,1.0f,1.0f,1.0f,250.0f,250.0f);

GameObject* objects[3]={human,cpu,ball};

void ResetRound()
{
	ball->m_pos_x=0.0f;
	ball->m_pos_y=0.0f;

	ball-> m_speed_x=250.0f;
	ball-> m_speed_y=250.0f;

	human->m_pos_y=0.0f;
	cpu->m_pos_y=0.0f;
}

void TestEndRound()
{
	if(ball->m_pos_x<human->m_pos_x-10.0f-ball->m_radius)
	{
		cpu->m_score++;
		ResetRound();		
	}
	else if(ball->m_pos_x>cpu->m_pos_x+10.0f+ball->m_radius)
	{
		human->m_score++;
		ResetRound();
	}
}

void SimpleBallControl()
{
	if(ball->m_pos_y<cpu->m_pos_y)
	{
		cpu->m_speed=-M_PLAYER_SPEED;
	}
	else
	{
		cpu->m_speed=M_PLAYER_SPEED;
	}
}

char U2Char(unsigned u)
{
	unsigned decimal=u%10;
	switch(decimal)
	{
		case 0:return '0';
		case 1:return '1';
		case 2:return '2';
		case 3:return '3';
		case 4:return '4';
		case 5:return '5';
		case 6:return '6';
		case 7:return '7';
		case 8:return '8';
		case 9:return '9';
		default:break;
	}
	return '0';
}
void RenderScore()
{
	std::stack<char> char_stack;
	glColor3f(1.0f,1.0f,1.0f);
	glRasterPos2f(-20.0f,0.0f);
	unsigned temp_score=human->m_score;
	do
	{
		char_stack.push(U2Char(temp_score));
		temp_score/=10;
	}while(temp_score!=0);

	while(!char_stack.empty())
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,char_stack.top());
		char_stack.pop();
	}
	glRasterPos2f(+20.0f,0.0f);
	temp_score=cpu->m_score;
	do
	{
		char_stack.push(U2Char(temp_score));
		temp_score/=10;
	}while(temp_score!=0);

	while(!char_stack.empty())
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,char_stack.top());
		char_stack.pop();
	}
}
/* Todo: gérer rendu des GameObjects avec une file */

/* Called 60 times per second */
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//ball.Render();
	
	glPushMatrix();
	for(int i=0;i<3;i++)
	{
		objects[i]->Render();
	}
	glPopMatrix();
	RenderScore();

	glutSwapBuffers();
}

void SetupRC(void)
{
	glClearColor(0.0f,0.0f,0.0f,1.0f);

}

void ChangeSize(GLsizei w, GLsizei h)
{
	GLfloat nRange=250.0f;
	GLfloat aspectRatio;
	if(h==0)
		h=1;
	glViewport(0,0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	aspectRatio=(GLfloat)w/(GLfloat)h;

	if(w<=h)
		glOrtho(-nRange,nRange,-nRange/aspectRatio,nRange/aspectRatio,-nRange,nRange);
	else
		glOrtho(-nRange*aspectRatio,nRange*aspectRatio,-nRange,nRange,-nRange,nRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void GameLoop(int value)
{
	glutPostRedisplay();
	glutTimerFunc(16.5f,GameLoop,1);
	ball->Move(16.5, *human, *cpu);
	TestEndRound();
	if(ball->CollisionDetection(*human)
	|| ball->CollisionDetection(*cpu))
		{
			//ball->Move(-16.5);
			//ball->m_speed_x*=-1.0f;
			//ball->m_speed_y*=-1.0f;
		}
	if(human->KeyUp)
	{
		human->m_speed=M_PLAYER_SPEED;
	}
	if(human->KeyDown)
	{
		human->m_speed=-M_PLAYER_SPEED;
	}
	if(!human->KeyDown && !human->KeyUp)
	{
		human->m_speed=0.0f;
	}
	human->Move(16.5f);
	SimpleBallControl();
	cpu->Move(16.5f);
	glutPostRedisplay();

}

void DeleteAll()
{
	delete ball;
	delete cpu;
	delete human;
}

void GetKeyDown(unsigned char key, int x, int y)
{
	std::cout << "Key pressed down" << std::endl;
	switch(key)
	{
		case 'z':human->KeyUp=true;//human->m_speed+=0.1f;//Move(100.0f);
		break;
		
		case 's':human->KeyDown=true;//human->m_speed-=0.1f;
		break;

		default:
		break;
	}
}

void GetKeyUp(unsigned char key, int x, int y)
{
	std::cout << "Key released up" << std::endl;
	switch(key)
	{
		case 'z':human->KeyUp=false;//human->m_speed+=0.1f;//Move(100.0f);
		break;
		
		case 's':human->KeyDown=false;//human->m_speed-=0.1f;
		break;

		default:
		break;
	}
}


int main(int argc, char* argv[])
{
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowSize(1000,1000);
	glutCreateWindow("Pong");
	
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutKeyboardFunc(GetKeyDown);
	glutKeyboardUpFunc(GetKeyUp);
	glutTimerFunc(16.5,GameLoop,1);

	SetupRC();

	glutMainLoop();

	return 0;
}