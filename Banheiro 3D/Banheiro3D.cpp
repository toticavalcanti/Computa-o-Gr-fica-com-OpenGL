//banheiro 3D



 #include <stdlib.h>
 #include <GL/glut.h>

 GLfloat angle, fAspect;
 GLfloat rotX, rotY, rotX_ini, rotY_ini;
 GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
 int x_ini,y_ini,bot;

// Matrizes do modelo de iluminação
 const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
 const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
 const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
 const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
 
//Matrizes dos tipos de material dos objetos
 const GLfloat mat_ambient[]    = { 0.8f, 0.8f, 0.7f, 1.0f };
 const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
 const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
 const GLfloat high_shininess[] = { 100.0f };
 
 float ang=0;
 float a=0;
 float b=0;   
     
void inicia_luz()
{
	 glClearColor(1,1,1,1);
     glEnable(GL_CULL_FACE);
     glCullFace(GL_BACK);

     glEnable(GL_DEPTH_TEST);
     glDepthFunc(GL_LESS);

     glEnable(GL_LIGHT0);
     glEnable(GL_NORMALIZE);
     glEnable(GL_COLOR_MATERIAL);
     glEnable(GL_LIGHTING);

     glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
     glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
     glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
     glLightfv(GL_LIGHT0, GL_POSITION, light_position);

     glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     
}
 void PosicionaObservador(void)
 {
	 glMatrixMode(GL_MODELVIEW);
	 glLoadIdentity();
	 glTranslatef(-obsX,-obsY,-obsZ);          
	 glRotatef(rotX,1,0,0);
	 glRotatef(rotY,0,1,0);
 }
 void EspecificaParametrosVisualizacao(void)
 {
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 gluPerspective(angle,fAspect,0.1,600);
	 PosicionaObservador();
 }
 void AlteraTamanhoJanela(GLsizei w, GLsizei h)
 {
	 if ( h == 0 ) h = 1;

	 glViewport(0, 0, w, h);
	 fAspect = (GLfloat)w/(GLfloat)h;

	 EspecificaParametrosVisualizacao();
 }
 void GerenciaMouse(int button, int state, int x, int y)
 {
	 if(state==GLUT_DOWN)
	 {
		 x_ini = x;
		 y_ini = y;
		 obsX_ini = obsX;
		 obsY_ini = obsY;
		 obsZ_ini = obsZ;
		 rotX_ini = rotX;
		 rotY_ini = rotY;
		 bot = button;
	 }
	 else bot = -1;
 }

 #define SENS_ROT	5.0
 #define SENS_OBS	15.0
 #define SENS_TRANSL	30.0
 void GerenciaMovim(int x, int y)
 {
	 if(bot==GLUT_LEFT_BUTTON)
	 {
		 int deltax = x_ini - x;
		 int deltay = y_ini - y;
		
		 rotY = rotY_ini - deltax/SENS_ROT;
		 rotX = rotX_ini - deltay/SENS_ROT;
	 }
	 else if(bot==GLUT_RIGHT_BUTTON)
	 {
		 int deltaz = y_ini - y;
		
		 obsZ = obsZ_ini + deltaz/SENS_OBS;
	 }
	
	 else if(bot==GLUT_MIDDLE_BUTTON)
	 {
		 int deltax = x_ini - x;
		 int deltay = y_ini - y;
	
		 obsX = obsX_ini + deltax/SENS_TRANSL;
		 obsY = obsY_ini - deltay/SENS_TRANSL;
	 }
	 PosicionaObservador();
	 glutPostRedisplay();
 }

 void Inicializa (void)
 {	
	 glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 
	 angle = 75;
	
	 rotX = 0;
	 rotY = 0;
	 obsX = 0;
	 obsY = 0;
	 obsZ = 15;
 }

 void DesenhaDentroArmario(void){

	 glPushMatrix();
		 glTranslated(-1.7,-1.1,0.3);
		 glScalef(0.1,0.1,0.1);
		 glColor3d(1,1,1);
		 glutSolidSphere(1.5,50,50);
	 glPopMatrix();
	 
	 glPushMatrix();
		 glTranslated(-1.7,-0.8,0.3);
		 glScalef(0.1,0.1,0.1);
		 glColor3d(0.4,0.6,1);
		 glutSolidSphere(1.5,50,50);
	 glPopMatrix();
	 
	 glPushMatrix();
		 glTranslated(-1.7,-0.5,0.3);
		 glScalef(0.1,0.1,0.1);
		 glColor3d(0.7,0.4,0.6);
		 glutSolidSphere(1.5,50,50);
	 glPopMatrix();

	 glPushMatrix();
		 glTranslated(-2,-1.1,0.3);
		 glScalef(0.1,0.1,0.1);
		 glColor3d(0.1,0.4,0.1);
		 glutSolidSphere(1.5,50,50);
	 glPopMatrix();
	 
	 glPushMatrix();
		 glTranslated(-2,-0.8,0.3);
		 glScalef(0.1,0.1,0.1);
		 glColor3d(0.2,0.2,0.2);
		 glutSolidSphere(1.5,50,50);
	 glPopMatrix();
	 
	 glPushMatrix();
		 glTranslated(-2,-0.5,0.3);
		 glScalef(0.1,0.1,0.1);
		 glColor3d(1,1,1);
		 glutSolidSphere(1.5,50,50);
	 glPopMatrix();
 }

 void DesenhaArmario(void)
 {
	 //Parte superior 
     glPushMatrix();
         glTranslated(-2,0,0.2);
         glScalef(1.6,0.1,1);
         glColor3d(0.8,0.7,0);
         glutSolidCube(1);
     glPopMatrix();
     glPushMatrix();
         glTranslated(-2,-1.3,0.2);
         glScalef(1.6,0.08,1);
         glColor3d(0.8,0.7,0);
         glutSolidCube(1);
     glPopMatrix();
	
	 //Parte inferior
     glPushMatrix();
         glTranslated(-2.6,-0.7,0.18);
         glScalef(0.2,1.5,1);
         glColor3d(0.8,0.7,0);
         glutSolidCube(1);
     glPopMatrix();
     glPushMatrix();
         glTranslated(-1.4,-0.7,0.18);
         glScalef(0.2,1.5,1);
         glColor3d(0.8,0.7,0);
         glutSolidCube(1);
     glPopMatrix();

     //movimento da porta esquerda
     glPushMatrix();
		 glRotatef(-ang,0,1,0);
		 glTranslatef(a,0,b);
		 
		 //porta esquerda
		 glPushMatrix();
			 glTranslated(-2.35,-0.7,0.7);
			 glScalef(0.7,1.3,0);
			 glColor3d(1,1,0);
			 glutSolidCube(1);
		 glPopMatrix();
		 
		 //maçaneta esquerda
		 glPushMatrix();
			 glTranslated(-2.1,-0.7,0.7);
			 glScalef(0.04,0.04,0.02);
			 glColor3d(1,0,0);
			 glutSolidSphere(1,15,15);
		 glPopMatrix();
     glPopMatrix(); 
     //fim movimento
    
    //inicio movimento porta direita
	 glPushMatrix();
		 glRotatef(ang,0,1,0);
		 glTranslatef(-a,0,b);
		 
		 //porta direita
		 glPushMatrix();
			 glTranslated(-1.65,-0.7,0.7);
			 glScalef(0.7,1.3,0);
			 glColor3d(1,1,0);
			 glutSolidCube(1);
		 glPopMatrix();
		 
		 //maçaneta direita
		 glPushMatrix();
			 glTranslated(-1.9,-0.7,0.7);
			 glScalef(0.04,0.04,0.02);
			 glColor3d(1,0,0);
			 glutSolidSphere(1,15,15);
		 glPopMatrix();
     glPopMatrix();
     //Bibelô em cima do armário
     	 glPushMatrix();
			 glTranslated(-1.9,0.2,0.4);
			 glScalef(0.2,0.2,0.2);
			 glColor3d(0, 0.3, 0.5);
			 glutSolidIcosahedron();
		 glPopMatrix();
     glPopMatrix();
     //fim do movimento
 }

 void DesenhaBanheiro(void)
 {
	 //Parede de trás
	 glPushMatrix();
         glTranslated(0,1.7,-0.5);
         glScalef(1.6,1.0,0.01);
         glColor3d(0.3,0.5,0.3);
         glutSolidCube(6.5);
     glPopMatrix();

	 //Chão
	 glPushMatrix();
         glTranslated(0,-1.5,3.4);
         glScalef(1.6,0.01,1.2);
         glColor3d(0.6,0.5,0.5);
         glutSolidCube(6.5);
     glPopMatrix();

	 //Teto
	 glPushMatrix();
         glTranslated(0.0,4.8,3.4);
		 glRotatef(90,1,0,0);
         glScalef(1.6,1.2,0.01);
         glColor3d(0.3,0.5,0.3);
         glutSolidCube(6.5);
     glPopMatrix();

	 //Parede da Esquerda
	 glPushMatrix();
         glTranslated(5.2,1.7,3.35);
         glRotatef(90,0,1,0);
		 glScalef(1.2,1.0,0.01);
         glColor3d(0.3,0.5,0.3);
         glutSolidCube(6.5);
     glPopMatrix();
	
	 //Parede da Direita
	 glPushMatrix();
         glTranslated(-5.2,1.7,3.35);
		 glRotatef(90,0,1,0);
         glScalef(1.2,1.0,0.01);
         glColor3d(0.3,0.5,0.3);
         glutSolidCube(6.5);
     glPopMatrix();
 }

 void DesenhaBox(void)
 {
	 //Parede do Box
	 glPushMatrix();
		 glRotatef(90,0,1,0);
		 glTranslated(-1.08,-0.9,1);
         glScalef(1.0,0.4,0.1);
		 glColor3d(0.3,0.3,0.3);
         glutSolidCube(3);
     glPopMatrix();

	 //Vidro do Box
	 glPushMatrix();
		 glRotatef(90,0,1,0);
		 glTranslated(-1.08,1.65,1);
         glScalef(1.0,1.3,0.1);
         glutWireCube(3);
     glPopMatrix();

	 //Parede do Box
	 glPushMatrix();
		 glTranslated(3.0,-0.9,4.3);
         glScalef(1.45,0.4,0.1);
		 glColor3d(0.3,0.3,0.3);
         glutSolidCube(3);
     glPopMatrix();

	 //Vidro do Box
	 glPushMatrix();
		 glTranslated(3,1.65,4.3);
         glScalef(1.45,1.3,0.1);
         glutWireCube(3);
     glPopMatrix();
	
	 //Porta do Box
	 glPushMatrix();
		 glRotatef(90,0,1,0);
		 glTranslated(-3.4,1.05,1);
         glScalef(0.50,1.68,0.1);
         glutWireCube(3);
     glPopMatrix();

	 //Beirada do Box
	 glPushMatrix();
		 glRotatef(90,0,1,0);
		 glTranslated(-3.4,-1.4,1);
         glScalef(0.55,0.05,0.1);
		 glColor3d(0.3,0.3,0.3);
         glutSolidCube(3);
     glPopMatrix();

	 //Chuveiro
	 glPushMatrix();
		 glTranslated(3.0,3.5,0.3);
         glScalef(0.08,0.08,1.5);
		 glColor3d(0.2,0.3,0.3);
		 glutSolidTorus(0.5,0.5,50,50);
     glPopMatrix();

	 glPushMatrix();
		 glTranslated(3.0,3.0,0.8);
		 glRotatef(-90,1,0,0);
         glScalef(0.08,0.08,1.5);
		 glColor3d(0.2,0.3,0.3);
		 glutSolidCone(4,0.5,50,50);
     glPopMatrix();

 }

 void DesenhaTapete(void)
 {
	 
	 glPushMatrix();
		 glTranslated(-2,-1.4,3.4);
		 glRotatef(-90,1,0,0);
	
		 glLineWidth(3.0);

		 glColor3f(1,1,1);	 
		 GLUquadric *anel1 = gluNewQuadric();
		 gluDisk(anel1, 0.0, 0.5, 100, 150);

		 glColor3f(0.8,0.3,0.3);	 
		 GLUquadric *anel2 = gluNewQuadric();
		 gluDisk(anel2, 0.5, 0.7, 100, 150);

		 glColor3f(0.5,0.1,0.5);	 
		 GLUquadric *anel3 = gluNewQuadric();
		 gluDisk(anel3, 0.7, 1.0, 100, 150);

		 glRotatef(-90,1,0,0);
		 
	 glPopMatrix();
  }

void DesenhaSuporteShampoo(void)
{
     //Desenha Suporte
    glPushMatrix();
         glRotatef(90,1,0,0);
         glTranslated(2, 0,0);
         glScalef(1,1.1,0.03);

         glColor3d(0.4,0.4,0.5);
         glutSolidCube(1);
     glPopMatrix();
    
    //Desenha Shampoo   
     glPushMatrix();
     glShadeModel(GL_SMOOTH);
         glTranslated(2, 0,0);
         glColor3d(0.2,0.3,0.6);
         glRotatef(-90,1,0,0);
         glScalef(0.1,0.1,0.1);
         glutSolidCone(2, 10, 20,4);
     glPopMatrix();
 }

 void DesenhaVasoSanitario(void)
 {
	 //Assento do vaso
	 glPushMatrix();
		 glTranslated(-4,-0.9,0.3);
		 glScalef(0.1,0.1,0.17);
		 glRotatef(90,1,0,0);
		 glColor3d(1,0.9,0.3);
		 glutSolidTorus(1.0,3.3,50,50);
	 glPopMatrix();
	 
	 //Tampa do assento
	 glPushMatrix();
		 glTranslated(-4,-0.4,-0.2);
		 glScalef(0.2,0.3,0.08);
		 glColor3d(1,0.9,0.3);
		 glutSolidTorus(1,1,50,50);
	 glPopMatrix();
	 
	 //Bacia do vaso
	 glPushMatrix();
		 glTranslated(-4,-1.1,0.3);
		 glScalef(0.09,0.09,0.13);
		 glRotatef(90,1,0,0);
		 glColor3d(0.8,0.3,0.3);
		 glutSolidTorus(1.8,3.3,50,50);
	 glPopMatrix();
	 
	 //Pé do vaso
	 glPushMatrix();
		 glTranslated(-4,-1.3,0.3);
		 glScalef(0.2,0.2,0.3);
		 glRotatef(90,1,0,0);
		 glColor3d(0.8,0.3,0.3);
		 glutSolidCube(2);
	 glPopMatrix();
     
 }

 void DesenhaEspelho(void)
 {
	 
     glPushMatrix();
         glTranslated(-2,1.2,0);
         glScalef(1,1.1,0.03);
         glColor3d(1,1,1);
         glutSolidCube(1);
     glPopMatrix();
	 glPushMatrix();
         glTranslated(-2,1.2,0);
         glScalef(1.2,1.3,0);
         glColor3d(0.8,0.3,0.3);
         glutSolidCube(1);
     glPopMatrix();
 }

 static void desenha(void)
 {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glColor3d(0,0,0);
     
	 DesenhaBanheiro();

	 DesenhaBox();
	 
	 DesenhaSuporteShampoo();

	 DesenhaEspelho();
    
	 DesenhaTapete();

	 DesenhaArmario();    

	 DesenhaDentroArmario();

	 DesenhaVasoSanitario();

     glutSwapBuffers();
 }

 static void teclado(unsigned char key, int x, int y)
 {
     switch (key) 
	 {
         case 'A':
		 case 'a' : ang=120;a=1.4;b=-0.5; break;
		 case 'F' :
		 case 'f' : ang=0;a=0;b=0; break;
      
		 case '+': angle-=2.5; break;
		 case '-': angle+=2.5; break;
     }
	 EspecificaParametrosVisualizacao();
     glutPostRedisplay();
 }






 int 
 main(int argc, char *argv[])
 {
     glutInit(&argc, argv);
     glutInitWindowSize(800,800);
     glutInitWindowPosition(100,100);
     glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

     glutCreateWindow("Banheiro 3D");

     glutDisplayFunc(desenha);
     glutKeyboardFunc(teclado);
     glutMouseFunc(GerenciaMouse);
   	 glutReshapeFunc(AlteraTamanhoJanela);
	 inicia_luz();
	 glutMotionFunc(GerenciaMovim);
	 
	 Inicializa();
  
     glutMainLoop();

     return EXIT_SUCCESS;
 }

