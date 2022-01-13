#include <GL/glew.h>
#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif






#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif 
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
//#include <SDL2/SDL.h>

#include <vector>
#include "shader.hpp"

//************************************************

typedef struct {
        //coordonnées x, y et z du sommet
        GLfloat x;
        GLfloat y;
        GLfloat z;
} Sommet ;
//vector pour stocker les sommets du cube et leur couleur
 std::vector<Sommet> position ={ Sommet{-0.2,-0.3,0.5},Sommet{0.2,-0.3,0.5},Sommet{0.5,-0.5,-0.5},Sommet{-0.5,-0.5,-0.5},Sommet{-0.2,0.3,0.5},Sommet{0.2,0.3,0.5},Sommet{0.5,0.5,-0.5},Sommet{-0.5,0.5,-0.5}
 };
 // (-.5,-.5,-.5) et (.5, .5 ,.5)
//AFAIRE 2 définir un cube entre (-.5,-.5,-.5) et (.5, .5 ,.5)



//Tableau pour stocker les indices des sommets par face pour le cube
std::vector<GLuint> indices={0,1,5,4,1,2,6,5,2,3,7,6,3,0,4,7,0,3,2,1,4,5,6,7};
    //AFAIRE 3 définir les 6 faces quadrangulaires


// initialise à 0 = pas d’indice
GLuint vbo=0 ;
GLuint ibo = 0;
GLuint vao = 0;
GLuint IdProgram = 0;
GLuint VShader = 0;
GLuint FShader = 0;

void genererVBOVAO(void)
{
    //AFAIRE 4
  // initialisé à 0 = pas d’indice
glGenBuffers(1, &vbo);    // et met dans la variable vbo le handle du vbo

// Setup the current VBO
glBindBuffer(GL_ARRAY_BUFFER, vbo);  // on dit avec quel buffer on va travailler (openGL = machine à états)
// Send data to GPU: Fill the currently designated VBO with the buffer of data
glBufferData(GL_ARRAY_BUFFER, position.size()*sizeof(Sommet), &position[0], GL_STATIC_DRAW );
// Good practice to set the current VBO to 0 (=disable VBO) after its use
glBindBuffer(GL_ARRAY_BUFFER, 0);





glGenBuffers(1, &ibo); 
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLint),&indices[0] , GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);



// Create an empty VAO identifiant
glGenVertexArrays(1,&vao);// Setup the current VAO
glBindVertexArray(vao);     // on dit avec quel vao on va travailler// Indicate the VBO we will refer to in the next lines
glBindBuffer(GL_ARRAY_BUFFER, vbo);// Activate the use of the variable at index layout=0 in the shader
glEnableVertexAttribArray( 0 );// Define the memory model of this VBO: here contiguous triplet of floating values (x y z) at index layout=0 in the shader
glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );// attache le tableau d’indices.
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // 1 seul par VAO// As a good practice, disable VBO and VAO after their use
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

}

void prepareProgammeShader(void)
{
// vous avez de la chance ce n'est pas AFAIRE 6
     IdProgram = LoadShaders( "shader.vert", "shader.frag");
}

void dessinerCube(void)
{
    // on spécifie avec quel shader on veut afficher 
    glUseProgram(IdProgram);// on active le VAO
    glBindVertexArray(vao); // on appelle la fonction dessin 
    glDrawElements(GL_QUADS,  sizeof(indices), GL_UNSIGNED_INT, 0);// on désactive le VAO
    glBindVertexArray(0);    // on desactive les VAO
}

char presse;
int anglex,angley,x,y,xold,yold;

/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
//********************************************

//********************************************
int main ( int argc, char** argv )
{
    // initialize SDL video
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(500,500);
  glutCreateWindow("cube");
  glEnable(GL_DEPTH_TEST);



     // ATTENTION ne pas oublier l'initialisation de GLEW
     GLenum err = glewInit() ;

     //info version oenGL / GLSL :
     // AFAIRE 1 : récupérer les infos sur la cater version d'openGL/GLSL
std::cout << std::endl<< "***** Info GPU *****" << std::endl;
std::cout << "Fabricant : " << glGetString (GL_VENDOR) << std::endl;
std::cout << "Carte graphique: " << glGetString (GL_RENDERER) << std::endl;
std::cout << "Version : " << glGetString (GL_VERSION) << std::endl; 
std::cout << "Version GLSL : " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl 
  << std::endl;

     prepareProgammeShader();
     genererVBOVAO();

    // program main loop
    bool done = false;
  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);

  glMatrixMode( GL_PROJECTION );
     glLoadIdentity();
   gluPerspective(60 ,1,.1,30.);


  /* Entree dans la boucle principale glut */
  glutMainLoop();



    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}


void affichage()
{
  int i,j;
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Dessin du cube
    dessinerCube() ;

    //Repère (fait à l'ancienne
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
        glColor3f(0.0,1.0,0.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
        glColor3f(0.0,0.0,1.0);
        glVertex3f(0, 0,0.0);
        glVertex3f(0, 0,1.0);
    glEnd();


  //On echange les buffers
    glutSwapBuffers();
}



void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}





void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}



void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold); 
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }
    
    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }
