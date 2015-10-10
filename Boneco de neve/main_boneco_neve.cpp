#include <windows.h>
/* Inclui os headers do OpenGL, GLU, e GLUT */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

//Protótipos
void init();
void display_callback(void);
void reshape_callback(int w, int h);
void timer_callback(int);

float rot_r_braco = 0;
float inc_r_braco = 0;
float rot_l_braco = 0;
float inc_l_braco = 5;
float rot_r_pe = 0;
float inc_r_pe = 10;
float rot_l_pe = 0;
float inc_l_pe = 20;

float rot_corpo = 0;
float rot_olho = 0;

float dist = 0;

int main(){

   /* inicia o GLUT e alguns parâmetros do OpenGL */

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Antonio Cavalcante de Paula Filho");
    init();

    glutDisplayFunc(display_callback);
    glutReshapeFunc(reshape_callback);
    glutTimerFunc(100, &timer_callback, 1);
   /* função de controlo do GLUT */
   glutMainLoop();
   


   return 0;
}



void init(){
     //Matrizes da modelagem da luz
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {25.0};
    GLfloat light_position[] = {-1.0, 1.0, 1.0, 0.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glColor3f(0.0, 0.0, 1.0);

    return;
}

void desenha_membro(float rot, int desenha_mao)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	
	glTranslatef(0.0f, -1.0f, 0.5f);
	
	glPushMatrix();
	//glRotatef(45, 0.0f, 0.0f, 1.0f);
	glTranslatef(1*sin(rot), 1*cos(rot), -0.5f);
	glTranslatef((0.25f * sin(dist)) - 0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);
	glPopMatrix();
		if (desenha_mao)
	{
       glPushMatrix();
	   glTranslatef(1.35*sin(rot), 1.35*cos(rot), -0.5f);
   	   glTranslatef((0.5f * sin(dist)) - 0.1f, 0.0f, 0.0f);
       glutSolidSphere(0.1f, 20, 20);
	   glPopMatrix();
    }
	
	glTranslatef(0.0f, 1.0f, -0.5f);
	
	/*glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);*/
}


void desenha_boneco_neve(float rot)
{

	glColor3f(1.0f, 1.0f, 1.0f);

    glRotatef(rot_olho, 0.0f, 1.0f, 0.0f);

	glRotatef(10.0f + 45*sin(rot), 0.0f, 0.0f, 1.0f);
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	glColor3f(1.0f, 0.5f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.08f, 0.5f, 10, 2);
}


void display_callback(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt (0.0f, 2.0f, 10.0f , 0.0f, 0.6f, 0.0f, 0.0f, 1.0f, 0.0f);

    desenha_boneco_neve(rot_corpo);
    desenha_membro(1.0f + rot_r_braco, 1);
    desenha_membro(-1.0f + rot_l_braco, 1);
    desenha_membro(2.5f + rot_r_pe, 0);
    desenha_membro(-2.5f + rot_l_pe, 0);
    
    glutSwapBuffers();
    return;
}


void timer_callback(int n)
{
    glutPostRedisplay();  

    inc_r_braco += 0.5;
    rot_r_braco = sin(inc_r_braco)/5;

    inc_l_braco += 0.5;
    rot_l_braco = sin(inc_l_braco)/5;
    
    inc_r_pe += 0.5;
    rot_r_pe = sin(inc_r_pe)/5;
    
    inc_l_pe += 0.5;
    rot_l_pe = sin(inc_l_pe)/5;
    
    dist += 0.2;
    rot_corpo += 0.1;
    rot_olho += 1;
    
	glutTimerFunc(50, timer_callback, 1);   
}

void reshape_callback(int w, int h){

    glViewport (0, 0, (GLsizei) w, (GLsizei) h);


    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(20, (float)w/(float)h, 1.0, 100.0);

    glMatrixMode (GL_MODELVIEW);
    return;
}
