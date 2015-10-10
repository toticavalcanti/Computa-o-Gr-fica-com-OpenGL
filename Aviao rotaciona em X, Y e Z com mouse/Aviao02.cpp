#include <GL/glut.h>
#include <stdlib.h>

// Variáveis para controles de navegação
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotZ, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;

// Função responsável pela especificação dos parâmetros de iluminação
void DefineIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );   
}

void desenha_eixo()
{
   /* Limpa o Buffer de Pixels */
   glClear (GL_COLOR_BUFFER_BIT);
   // desenha os eixos
   glPushMatrix();
   glLineWidth(2.0);
   glBegin(GL_LINES);
      // Define a cor de eixo X como vermelho
   glColor3f (1.0, 0.0, 0.0);
      glVertex3d(-30,0,0);
      glVertex3d(30,0,0);
      // Define a cor de eixo Y como verde
    glColor3f (0.0, 1.0, 0.0);
      glVertex3d(0,-30,0);
      glVertex3d(0 ,30,0);
      // Define a cor de eixo Z como amarelo
    glColor3f (1.0, 1.0, 0.0);
      glVertex3d(0,0,-30);
      glVertex3d(0,0,30);
   glEnd();
   glPopMatrix();
}
// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Chama a função que especifica os parâmetros de iluminação
	DefineIluminacao();
    desenha_eixo();
	// Altera a cor do desenho para azul
	glColor3f(0.0f, 0.0f, 1.0f);

	// Função da GLUT para fazer o desenho de cones sólido
	// com a cor corrente
	
	//cone referente ao corpo do avião
	glPushMatrix();
	glutSolidCone(1.0, 9.0, 20, 4); 
    glPopMatrix();

    //cone referente ao bico do avião
   	glPushMatrix(); 
  	glRotatef(180, 1,0,0);
	glutSolidCone(1, 3, 50, 20); 
    glPopMatrix();
    
    //cone referente a uma asa
   	glPushMatrix(); 
  	glRotatef(70, 0,1,0);
	glutSolidCone(1,7, 50, 20); 
    glPopMatrix();
    
    //cone referente a outra asa
	glPushMatrix(); 
  	glRotatef(-70, 0,1,0);
	glutSolidCone(1,7, 50, 20); 
    glPopMatrix();
    
    //cone referente a parte da cauda de um lado
   	glPushMatrix(); 
	glTranslatef(0, 0, 7);
  	glRotatef(-70, 0,1,0);
	glutSolidCone(0.3, 3 , 60, 1); 
    glPopMatrix();
    
    //cone referente a parte da cauda do outro lado
   	glPushMatrix(); 
	glTranslatef(0, 0, 7);
  	glRotatef(70, 0,1,0);
	glutSolidCone(0.3, 3 , 60, 1); 
    glPopMatrix();
    
    //cone referente a parte de cima da cauda 
   	glPushMatrix(); 
	glTranslatef(0, 0, 7);
  	glRotatef(-70, 1,0,0);
	glutSolidCone(0.3, 2 , 60, 1); 
    glPopMatrix();
    
	// Executa os comandos OpenGL
	glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual
void PosicionaObservador(void)
{
	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
	DefineIluminacao();
	// Posiciona e orienta o observador
	glTranslatef(-obsX,-obsY,-obsZ);
	glRotatef(rotX,1,0,0);
	glRotatef(rotY,0,1,0);
	glRotatef(rotZ,0,0,1);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
	gluPerspective(angle,fAspect,0.5,500);

	PosicionaObservador();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void Teclado (unsigned char tecla, int x, int y)
{
	if(tecla==27) // ESC ?
		exit(0);
}

// Função callback para tratar eventos de teclas especiais
void TeclasEspeciais (int tecla, int x, int y)  
{
    
     
	switch (tecla)
	{
		case GLUT_KEY_HOME:	if(angle>=10)  angle -=5;
							break;
		case GLUT_KEY_END:	if(angle<=150) angle +=5;
							break;
		case GLUT_KEY_RIGHT:{
                             glRotatef(rotX, 1, 0, 0);
                             rotX++;
	                         break;
                            }
  		case GLUT_KEY_LEFT:{
                             glRotatef(rotY, 0, 1, 0);
                             rotY++;
	                         break;
                            }
        
        case GLUT_KEY_DOWN:{
                             glRotatef(rotZ, 0, 0, 1);
                             rotZ++;
	                         break;
                            }
	}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

// Função callback para eventos de botões do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
	if(state==GLUT_DOWN)
	{
		// Salva os parâmetros atuais
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

// Função callback para eventos de movimento do mouse
#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	10.0
void GerenciaMovim(int x, int y)
{
	// Botão esquerdo ?
	if(bot==GLUT_LEFT_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica ângulos
		rotY = rotY_ini - deltax/SENS_ROT;
		rotX = rotX_ini - deltay/SENS_ROT;
	}
	// Botão direito ?
	else if(bot==GLUT_RIGHT_BUTTON)
	{
        int deltax = x_ini - x;
		int deltay = y_ini - y;
		// Calcula diferença
		int deltaz = deltax - deltay;
	  
		// E modifica distância do observador
		obsZ = obsZ_ini + deltaz/SENS_OBS;
	}
	// Botão do meio ?
	else if(bot==GLUT_MIDDLE_BUTTON)
	{
		// Calcula diferenças
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		// E modifica posições
		obsX = obsX_ini + deltax/SENS_TRANSL;
		obsY = obsY_ini - deltay/SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
     
	// Inicializa a variável que especifica o ângulo da projeção
	// perspectiva
	angle=10;
    
	// Inicializa as variáveis usadas para alterar a posição do 
	// observador virtual
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	obsX = obsY = 0;
	obsZ = 150;    
}

// Função Principal 
int main(void)
{
	// Define o modo de operação da GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
 
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5,5); 
    
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(450,450); 
 
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Desenho de um avião 3D com iluminação, construido a partir de cones");
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
  
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para tratamento das teclas normais 
	glutKeyboardFunc (Teclado);

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc (TeclasEspeciais);
     
	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(GerenciaMouse);
	 
	// Registra a função callback para eventos de movimento do mouse	
	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();
 
	return 0;
}
