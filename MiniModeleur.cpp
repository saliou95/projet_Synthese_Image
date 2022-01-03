
//#include "../utilstexture/sdlglutils.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>
#include "shader.hpp"
#include <string.h>
#include "Primtv.h"
#include "Tore.h"
#include "Arbre.h"

#include <GL/glui.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>
using namespace glm;
using namespace std;


// initialisations

void genereVBO();
void deleteVBO();
void traceObjet(Primtv montore);
void affichage();
void clavier(unsigned char,int,int);
void mouse(int, int, int, int);
void mouseMotion(int, int);
void reshape(int,int);
void drawString(const char *str, int x, int y, float color[4], void *font);
void showInfo();
void interface();
void ajouterPrimtv();

void afficherArbre(GLUI *panneDroit);
void afficheAjout(GLUI* panneGauche);
void *font = GLUT_BITMAP_8_BY_13; // pour afficher des textes 2D sur l'ecran
// variables globales pour OpenGL
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;
float cameraAngleX;
float cameraAngleY;
float cameraDistance=0.;
float aspectRatio;
int complexiter1=10,complexiter2=10;
GLfloat ToreRayon=1,Torerayon=0.1;
// variables Handle d'opengl 
//--------------------------
GLuint programID;   // handle pour le shader
GLuint MatrixIDMVP,MatrixIDView,MatrixIDModel,MatrixIDPerspective;    // handle pour la matrice MVP
GLuint VBO_sommets,VBO_normales, VBO_indices,VBO_UVtext,VAO;
GLuint locCameraPosition ;
GLuint locmaterialShininess ;
GLuint locmaterialSpecularColor;
GLuint locLightPosition ;
GLuint locLightIntensities;//a.k.a the color of the light
GLuint locLightAttenuation;
GLuint locLightAmbientCoefficient;

// location des VBO
//------------------
GLuint indexVertex=0, indexUVTexture=2, indexNormale=3 ;

//variable pour paramétrage eclairage
//--------------------------------------
vec3 cameraPosition(0.,0.,3.);
// le matériau
//---------------
GLfloat materialShininess=3.;
vec3 materialSpecularColor(1.,.1,1);  // couleur du materiau

// la lumière
//-----------
vec3 LightPosition(1.,0.,.5);
vec3 LightIntensities(1.,1.,1.);// couleur la lumiere
GLfloat LightAttenuation =1.;
GLfloat LightAmbientCoefficient=.1;

glm::mat4 MVP;    
glm::mat4 MVP2;   // justement la voilà
glm::mat4 Model, View, Projection;    // Matrices constituant MVP

int screenHeight = 500;
int screenWidth = 500;


//interface graphique variables//
int main_window;
GLUI *panneDroit, *panneGauche, *panneBas;
GLUI_RadioGroup* courantPrimtv;
GLUI_Spinner *ToreR,*Torer,*Complexiter1,*Complexiter2;







Tore montore;
Arbre a;
int nbPrimtv=0;


 GLUI_Rollout *arbre ,*ajout;
 
 int primtvCourant; 
 int nbPrivDiff=1;
 int show;

//----------------------------------------
void initOpenGL(void)
//----------------------------------------
{
  glCullFace (GL_BACK); // on spécifie queil faut éliminer les face arriere
  glEnable(GL_CULL_FACE); // on active l'élimination des faces qui par défaut n'est pas active
  glEnable(GL_DEPTH_TEST); 
  programID = LoadShaders( "PhongShader.vert", "PhongShader.frag" );
  MatrixIDMVP = glGetUniformLocation(programID, "MVP");
  Projection = glm::perspective( glm::radians(60.f), 1.0f, 1.0f, 1000.0f);
  locCameraPosition = glGetUniformLocation(programID, "cameraPosition");
  locLightPosition = glGetUniformLocation(programID, "light.position");
  locLightIntensities = glGetUniformLocation(programID, "light.intensities");//a.k.a the color of the light
  locLightAttenuation = glGetUniformLocation(programID, "light.attenuation");
  locLightAmbientCoefficient = glGetUniformLocation(programID, "light.ambientCoefficient");
}
void genereVBO (Primtv maprimitive)
{
  
    glGenBuffers(1, &VAO);
    glBindVertexArray(VAO); // ici on bind le VAO , c'est lui qui recupèrera les configurations des VBO glVertexAttribPointer , glEnableVertexAttribArray...

    if(glIsBuffer(VBO_sommets) == GL_TRUE) glDeleteBuffers(1, &VBO_sommets);
    glGenBuffers(1, &VBO_sommets);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sommets);
    glBufferData(GL_ARRAY_BUFFER, maprimitive.getPositions().size()*sizeof(Sommet),&maprimitive.getPositions()[0] , GL_STATIC_DRAW);
    glVertexAttribPointer ( indexVertex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    if(glIsBuffer(VBO_normales) == GL_TRUE) glDeleteBuffers(1, &VBO_normales);
    glGenBuffers(1, &VBO_normales);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_normales);
    glBufferData(GL_ARRAY_BUFFER, maprimitive.getNormales().size()*sizeof(Normale),&maprimitive.getNormales()[0]  , GL_STATIC_DRAW);
    glVertexAttribPointer ( indexNormale, 3, GL_FLOAT, GL_FALSE, 0, (void*)0  );

    if(glIsBuffer(VBO_indices) == GL_TRUE) glDeleteBuffers(1, &VBO_indices);
    glGenBuffers(1, &VBO_indices); // ATTENTIOn IBO doit etre un GL_ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, maprimitive.getFaces().size()*sizeof(Face),&maprimitive.getFaces()[0]  , GL_STATIC_DRAW);
 /*
    if(glIsBuffer(VBO_UVtext) == GL_TRUE) glDeleteBuffers(1, &VBO_UVtext);
    glGenBuffers(1, &VBO_UVtext);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_UVtext);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordTexture),coordTexture , GL_STATIC_DRAW);
    glVertexAttribPointer (indexUVTexture, 2, GL_FLOAT, GL_FALSE, 0,  (void*)0  );
 */
   glEnableVertexAttribArray(indexVertex);
   glEnableVertexAttribArray(indexNormale );
   //glEnableVertexAttribArray(indexUVTexture);
 
   
// une fois la config terminée   
   // on désactive le dernier VBO et le VAO pour qu'ils ne soit pas accidentellement modifié 
 glBindBuffer(GL_ARRAY_BUFFER, 0);
 glBindVertexArray(0);
 
}
//-----------------
void deleteVBO ()
//-----------------
{
    glDeleteBuffers(1, &VBO_sommets);
   glDeleteBuffers(1, &VBO_normales);
  //  glDeleteBuffers(1, &VBO_indices);
 //   glDeleteBuffers(1, &VBO_UVtext);
        glDeleteBuffers(1, &VAO);
}

/* fonction d'affichage */
void affichage()
{

  /* effacement de l'image avec la couleur de fond */
 /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glClearDepth(10.0f);                         // 0 is near, >0 is far
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);

 
     View       = glm::lookAt(   cameraPosition, // Camera is at (0,0,3), in World Space
                                            glm::vec3(0,0,0), // and looks at the origin
                                            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                                             );
     Model = glm::mat4(1.0f);
     Model = glm::translate(Model,glm::vec3(0,0,cameraDistance));
     Model = glm::rotate(Model,glm::radians(cameraAngleX),glm::vec3(1, 0, 0) );
     Model = glm::rotate(Model,glm::radians(cameraAngleY),glm::vec3(0, 1, 0) );
     Model = glm::scale(Model,glm::vec3(.5, .5, .5));
     
     for(int i=0 ;i<a.getTaille();i++)
      {
        Primtv p=a.getPrimtv(i);
        
       if(p.show==1)
       {
              genereVBO(p);
      // cout <<glm::to_string(p.getmodel())<<endl;
      MVP = Projection * View* (Model*p.getmodel());
              traceObjet(p); 
       }
          
      }      
          // trace VBO avec ou sans shader

    //Model = glm::translate(Model,glm::vec3(0,0,cameraDistance));
    //Model = glm::scale(Model,glm::vec3(.2, .2, .2));


    
    /* on force l'affichage du resultat */
      glutPostRedisplay();
      glutSwapBuffers();
}



//-------------------------------------
//Trace le tore 2 via le VAO
void traceObjet(Primtv maprimitive)
//-------------------------------------
{
 // Use  shader & MVP matrix   MVP = Projection * View * Model;
 glUseProgram(programID);

//on envoie les données necessaires aux shaders */
 glUniformMatrix4fv(MatrixIDMVP, 1, GL_FALSE, &MVP[0][0]);
 //glUniformMatrix4fv(MatrixIDView, 1, GL_FALSE,&View[0][0]);
 //glUniformMatrix4fv(MatrixIDModel, 1, GL_FALSE, &Model[0][0]);
 //glUniformMatrix4fv(MatrixIDPerspective, 1, GL_FALSE, &Projection[0][0]);
 glUniform3f(locCameraPosition,cameraPosition.x, cameraPosition.y, cameraPosition.z);
// glUniform1f(locmaterialShininess,materialShininess);
 //glUniform3f(locmaterialSpecularColor,materialSpecularColor.x,materialSpecularColor.y,materialSpecularColor.z);
 glUniform3f(locLightPosition,LightPosition.x,LightPosition.y,LightPosition.z);
 glUniform3f(locLightIntensities,LightIntensities.x,LightIntensities.y,LightIntensities.z);
 glUniform1f(locLightAttenuation,LightAttenuation);
 glUniform1f(locLightAmbientCoefficient,LightAmbientCoefficient);

//pour l'affichage
   glBindVertexArray(VAO); // on active le VAO
   glDrawElements(GL_TRIANGLES,maprimitive.getFaces().size()*sizeof(Face), GL_UNSIGNED_INT, 0);// on appelle la fonction dessin 
   glBindVertexArray(0);    // on desactive les VAO
   glUseProgram(0);         // et le pg

}

void reshape(int w, int h)
{
    // set viewport to be the entire window

  int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
 // glViewport( tx, ty, tw, th );
   glViewport( tx, ty, tw, th );

   // glViewport(tx, ty, (GLsizei)w, (GLsizei)h);// ATTENTION GLsizei important - indique qu'il faut convertir en entier non négatif

    // set perspective viewing frustum
    aspectRatio = (float)w / h;

    Projection = glm::perspective(glm::radians(60.0f),(float)(w)/(float)h, 1.0f, 1000.0f);
}


void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'f': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'e': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 'v' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      materialShininess-=.5;
      glutPostRedisplay();
      break;
    case 'S' : /* Affichage en mode sommets seuls */
      materialShininess+=.5;
      glutPostRedisplay();
      break;
    case 'x' : /* Affichage en mode sommets seuls */
      LightPosition.x-=.2;
      glutPostRedisplay();
      break;
    case 'X' : /* Affichage en mode sommets seuls */
      LightPosition.x+=.2;
      glutPostRedisplay();
      break;
    case 'y' : /* Affichage en mode sommets seuls */
      LightPosition.y-=.2;
      glutPostRedisplay();
      break;
    case 'Y' : /* Affichage en mode sommets seuls */
      LightPosition.y+=.2;
      glutPostRedisplay();
      break;
    case 'z' : /* Affichage en mode sommets seuls */
      LightPosition.z-=.2;
      glutPostRedisplay();
      break;
    case 'Z' : /* Affichage en mode sommets seuls */
      LightPosition.z+=.2;
      glutPostRedisplay();
      break;
    case 'a' : /* Affichage en mode sommets seuls */
      LightAmbientCoefficient-=.1;
      glutPostRedisplay();
      break;
    case 'A' : /* Affichage en mode sommets seuls */
      LightAmbientCoefficient+=.1;
      glutPostRedisplay();
      break;
      
      
 case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}



void mouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if(state == GLUT_UP)
            mouseMiddleDown = false;
    }
}


void mouseMotion(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}







        void ajouterPrimtv(int i)
        {
         // cout <<i<<endl;
         if(i==0)
         {
          Tore tore;
          tore.init(ToreRayon,Torerayon,complexiter1,complexiter1);
           a.addPrimtv(tore);
         }
         panneDroit->close();

  
     interface();
             }
   
     
       void defineshow(int i)
       {
              a.Changeshow(i);
              //cout<< a.getPrimtv(i).show<<endl;
       }
        void afficherArbre(GLUI *parentremove)

        {
          show=0;
          a.reshape();
           Complexiter1  =new GLUI_Spinner( parentremove, "",&complexiter1);
          Complexiter1->set_int_limits(10,200);
            Complexiter2  =new GLUI_Spinner( parentremove, "",&complexiter2);
          Complexiter2->set_int_limits(10,200);
         arbre=new GLUI_Rollout(parentremove, "Arbre", true );

         
         for(int i=0;i<a.getTaille();i++)
         {     
                 new GLUI_Checkbox( arbre,a.getPrimtv(i).nom.c_str(),&show,i,defineshow);
                // new GLUI_StaticText( arbre, "" );
         }
        
         new GLUI_Column( arbre, true );
        courantPrimtv= new GLUI_RadioGroup(arbre,&primtvCourant);
     
             new GLUI_RadioButton(courantPrimtv,"ALL");
           
         for(int i=0;i<a.getTaille();i++)
         {           
                
          new GLUI_RadioButton(courantPrimtv,"");
         }
        new GLUI_Column( arbre, true );
        

         for(int i=0;i<a.getTaille();i++)
         {           
        
         new GLUI_Button(arbre, "Sup");
         }
       

}

void afficheAjout(GLUI *parentAdd)
{

    ajout=new GLUI_Rollout(parentAdd, "AjouterPrimitives", true );

        for (int i=0;i< nbPrivDiff;i++)
        {
         if(i==0)
         {
          ToreR  =new GLUI_Spinner( ajout, "Grand rayon:",&ToreRayon);
          ToreR->set_float_limits(0.3,1000);
          Torer  =new GLUI_Spinner( ajout, "Petit rayon:",&Torerayon);
          Torer->set_float_limits(0.1,990);
          new GLUI_Button(ajout, "Ajouter un tore", i, ajouterPrimtv );

         }
        
        }
}

void interface()
{
  GLUI_Master.close_all();
   
    panneDroit= GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_RIGHT );
    panneGauche= GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_LEFT );
    panneBas= GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
  
     afficherArbre(panneDroit);
     afficheAjout(panneGauche);
    panneDroit->set_main_gfx_window( main_window );
    panneGauche->set_main_gfx_window( main_window );
    panneBas->set_main_gfx_window( main_window );
}


int main(int argc,char **argv)

{
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(screenWidth,screenHeight);
  main_window=glutCreateWindow("Mini Modeleur");

  glutDisplayFunc(affichage);
    GLUI_Master.set_glutReshapeFunc( reshape );  
    GLUI_Master.set_glutKeyboardFunc( clavier );
    GLUI_Master.set_glutSpecialFunc( NULL );
    GLUI_Master.set_glutMouseFunc( mouse );
    glutMotionFunc( mouseMotion );
// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

//info version GLSL
std::cout << "***** Info GPU *****" << std::endl;
    std::cout << "Fabricant : " << glGetString (GL_VENDOR) << std::endl;
    std::cout << "Carte graphique: " << glGetString (GL_RENDERER) << std::endl;
    std::cout << "Version : " << glGetString (GL_VERSION) << std::endl;
    std::cout << "Version GLSL : " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;

	initOpenGL(); 




montore.init(1.,.3,complexiter1,complexiter2);
montore.translater(vec3(1,0,0));
montore.translater(vec3(-2,0,0));
montore.roter(90,vec3(1,0,0));
montore.roter(130,vec3(0,1,0));


a.addPrimtv(montore);



nbPrimtv=a.getTaille();
interface();

 
  /* Entree dans la boucle principale glut */
  glutMainLoop();

  glDeleteProgram(programID);
  deleteVBO();
  return 0;
}