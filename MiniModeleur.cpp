
//#include "../utilstexture/sdlglutils.h"
#define GLM_ENABLE_EXPERIMENTAL
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
#include "Groupe.h"
#include "Tore.h"
#include "Sphere.h"
#include "Cube.h"
#include "Cylindre.h"
#include "Arbre.h"
#include <GL/glui.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>
using namespace glm;
using namespace std;


// initialisations des fonctions principales

void genereVBO(); // Elle génère les VBO d'une primitive
void deleteVBO(); // Trace la primitive via le VAO
void traceObjet(Primtv primtv);
void affichage(); // Cette fonction affiche la ou les primitives en fonction du groupe selectionné ou de la primitive selectionnée.
void clavier(unsigned char,int,int); // Gestion des évenements de saisis du clavier
void mouse(int, int, int, int); // Gestion des évenements de clic de la souris
void mouseMotion(int, int); // Gestion des évenements de la souris
void reshape(int,int);
void drawString(const char *str, int x, int y, float color[4], void *font);
void showInfo();
void interface(); // S'occupe du rendu de l'interface graphique
void ajouterPrimtv(); // S'occupe de l'ajout d'une primitive i au groupe courant (groupe séléctionné)

void afficherArbre(GLUI *panneDroit);     // Affiche dans l'interface graphique le panneau droit (Panneau de gestion des Groupes et Primitive)
void afficheAjout(GLUI* panneGauche);     // Affiche dans l'interface graphique le panneau gauche (Panneau d'ajout de primitives)
void afficheTransformations(GLUI* panneBas);  // Affiche dans l'interface graphique le panneau bas (Panneau de gestion des transformation de Primitive)
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
int Cycomplexiter1=10,Cycomplexiter2=10;
GLfloat CylindreRayon=0.5;
GLfloat ToreRayon=1,Torerayon=0.1;
GLfloat SphereRayon = 1.0, SpherePas = 30;
GLfloat CubeLongueur = 1.0, CubeLargeur = 1;

// std::string NewGroupNom;
char  NewGroupNom[20] = {""};

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
GLUI_Rollout *arbre ,*ajout,*groupe,*primtvs, *ajoutGroup;
GLUI_RadioGroup* courantPrimtv,*courantGroupe;
GLUI_Spinner *ToreR,*Torer,*Complexiter1,*Complexiter2, *SphereR, *SphereP, *SphereS,*CylindreR,*CylindrevertP,*CylindrehorP;
GLUI_EditText *GroupeNom;
GLUI_Translation *trans_x,*trans_y,*trans_z;
GLUI_Scrollbar *rotx,*roty,*rotz;
GLUI_Spinner *scalex, *scaley,*scalez;
GLUI_Spinner *CubeL, * Cubel;
 int primtvCourant,groupeCourant=0; 
 int nbPrivDiff=4;
 int show;
 GLfloat scalx=1,scaly=1,scalz=1;
 GLfloat transx=0, transy=0, transz=0;
 GLfloat vittessetrans=0.0005;
 vec3 traansAll;
 GLfloat rotationx=0,rotationy=0,rotationz=0;
 Arbre a;


 int nbPrimtv=0;


 


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
     //cout <<transx<<endl;

       for(int i=0 ;i<a.getTaille();i++)
      {
        Groupe p=a.getGroupe(i);
        
       if(p.show==1)
       {

         for(int j=0;j<p.getTaille();j++)
         {

           Primtv pp=p.getPrimtv(j);
           if(pp.show==1)
           {
              genereVBO(pp);
            // cout<<"trace"<<pp.nom<<endl;
              MVP = Projection * View* (Model*p.getmodel()*pp.getmodel());
              traceObjet(pp); 
           }
         }
       
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
//Trace la primitive via le VAO
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






      // Fonction d'ajout de primitive dans le groupe de primitive séléctionner
        void ajouterPrimtv(int i)
        {
         // cout <<i<<endl;
         if(i==0)
         {
          Tore tore;
          tore.init(ToreRayon,Torerayon,complexiter1,complexiter2);
           a.addPrimtv(tore,groupeCourant);
         }
        else if(i==1) {
          Sphere sphere;
          sphere.init(SphereRayon,SpherePas);
           a.addPrimtv(sphere,groupeCourant);
         }


        else if(i==2) {
          Cube cube;
          cube.init(CubeLongueur, CubeLargeur);
          a.addPrimtv(cube,groupeCourant);
          }

           else if(i==3) {
          Cylindre c;
          c.init(CylindreRayon, Cycomplexiter1,Cycomplexiter2);
          a.addPrimtv(c,groupeCourant);
          }

         panneDroit->close();

  
     interface();
             }
   

      void ajouterGroup(int id) {
        Groupe groupe(NewGroupNom);
        a.addGroupe(groupe);
        GroupeNom->set_text("");
        panneDroit->close();
        interface();
      }
     
      void defineshow(int i)
       {
          a.Changeshow(i);
          //cout<< a.getPrimtv(i).show<<endl;
              
       }
       void defineshowPrimtv(int j)
       {
              a.ChangeshowPrimtv(groupeCourant,j);
              //cout<< a.getPrimtv(i).show<<endl;
              
       }

      void supprimer(int j)
      {
        if(primtvCourant==0)
        a.removeAllPrimtiv(groupeCourant);
        else
        a.removePrimtv(groupeCourant,primtvCourant-1);
        interface();
      }

void supprimerg(int j)
      {
       a.removeGroupe(groupeCourant);
       groupeCourant=0;
        interface();
      }

      void transformations(int i)
      {
        if(i==1)
        {
            if(primtvCourant==0)
              for(int i=0 ;i<a.getGroupe(groupeCourant).getTaille();i++)
                  a.translaterg(vec3(vittessetrans*transx,vittessetrans*transy,-vittessetrans*transz),groupeCourant);
          
            else
            {
            
                a.translater(vec3(vittessetrans*transx,vittessetrans*transy,-vittessetrans*transz),groupeCourant,primtvCourant-1);
            }
          trans_x->set_x(0.0);
          trans_y->set_y(0.0);
          trans_z->set_z(0.0);
          transx=0;
          transy=0;
          transz=0;
        }
        if(i==2)
        {
             if(primtvCourant==0)
                {
                      a.roterg(rotationx,vec3(1,0,0),groupeCourant);
                      a.roterg(rotationy,vec3(0,1,0),groupeCourant);
                      a.roterg(rotationz,vec3(0,0,1),groupeCourant);
                }
                  
              else
                  {
                      a.roter(rotationx,vec3(1,0,0),groupeCourant,primtvCourant-1);
                      a.roter(rotationy,vec3(0,1,0),groupeCourant,primtvCourant-1);
                      a.roter(rotationz,vec3(0,0,1),groupeCourant,primtvCourant-1);
                  }
        rotx->set_float_val(0);
        roty->set_float_val(0);
        rotz->set_float_val(0);
        rotationx=0;
        rotationy=0;
        rotationz=0;
        
              }

         if(i==3)
        {
          if(primtvCourant==0)
           for(int i=0 ;i<a.getGroupe(groupeCourant).getTaille();i++)
              a.scalerg(vec3(scalx,scaly,scalz),groupeCourant);
              else
              a.scaler(vec3(scalx,scaly,scalz),groupeCourant,primtvCourant-1);
          scalex->set_float_val(1.0);
          scaley->set_float_val(1.0);
          scalez->set_float_val(1.0);
          transx=1;
          transy=1;
          transz=1;
        }

 
      
      }
 void radiochange(int i)
 {
   interface(); 
 }
      void afficherArbre(GLUI *parentremove)

        {
            arbre=new GLUI_Rollout(parentremove, "Arbres", true );
          
            groupe=new GLUI_Rollout(arbre, "Groupes", true );
           
            for(int i=0;i<a.getTaille();i++)
            {     
                show=a.getGroupe(i).show;
                    new GLUI_Checkbox( groupe,a.getGroupe(i).nom.c_str(),&show,i,defineshow);
                    // new GLUI_StaticText( arbre, "" );
            }
            
              new GLUI_StaticText( groupe, "" );
        
            new GLUI_Column( groupe, true );
            courantGroupe= new GLUI_RadioGroup(groupe,&groupeCourant,-1,radiochange);
        
               
              
            for(int i=0;i<a.getTaille();i++)
            {           
                    
              new GLUI_RadioButton(courantGroupe,"");
            }
          //  new GLUI_Column( arbre, true );
           if(a.getTaille()>1)
            new GLUI_Button(groupe, "Supprimer",-1,supprimerg);



 
           primtvs=new GLUI_Rollout(arbre, "Primitives du groupe", true );
         
          
           for(int i=0;i<a.getGroupe(groupeCourant).getTaille();i++)
            {     
                show=a.getGroupe(groupeCourant).getPrimtv(i).show;
                new GLUI_Checkbox( primtvs,a.getGroupe(groupeCourant).getPrimtv(i).nom.c_str(),&show,i,defineshowPrimtv);
                    // new GLUI_StaticText( arbre, "" );
            }
              new GLUI_StaticText( primtvs, "" );
          
         
            new GLUI_Column( primtvs, true );
            courantPrimtv= new GLUI_RadioGroup(primtvs,&primtvCourant);
       
                new GLUI_RadioButton(courantPrimtv,"ALL");
              
         for(int i=0;i<a.getGroupe(groupeCourant).getTaille();i++)
            {           
                    
              new GLUI_RadioButton(courantPrimtv,"");
            }
             
              new GLUI_Column( arbre, true );
            
            new GLUI_Button(primtvs, "Supprimer",-1,supprimer);
          
           
}


// S'occupe du rendu du panneau d'ajout de primitive et de groupe
void afficheAjout(GLUI *parentAdd)
{     
        ajoutGroup=new GLUI_Rollout(parentAdd, "Ajout de groupe", true );
        // for(int i=0; i< a.getTaille();i++) {}
        GroupeNom  = new GLUI_EditText(ajoutGroup, "Nom", NewGroupNom, -3);
        // ajout, "Rayon:",&NewGroupNom
        new GLUI_Button(ajoutGroup, "Ajouter un groupe", -2, ajouterGroup );


        ajout=new GLUI_Rollout(parentAdd, "AjouterPrimitives", true );

        for (int i=0;i< nbPrivDiff;i++)
        {
         if(i==0)
         {
          Complexiter1  =new GLUI_Spinner( ajout, "pas vertt",&complexiter1);
          Complexiter1->set_int_limits(10,200);
          Complexiter2  =new GLUI_Spinner( ajout, "pas horiz",&complexiter2);
          Complexiter2->set_int_limits(10,200);
          ToreR  =new GLUI_Spinner( ajout, "Rayon:",&ToreRayon);
          ToreR->set_float_limits(0.3,1000);
          Torer  =new GLUI_Spinner( ajout, "rayon:",&Torerayon);
          Torer->set_float_limits(0.1,990);
          new GLUI_Button(ajout, "Ajouter un tore", i, ajouterPrimtv );

         }
        if(i==1)
         {
          SphereR  =new GLUI_Spinner( ajout, "Rayon:",&SphereRayon);
          SphereR->set_float_limits(0.3,1000);
          SphereP  =new GLUI_Spinner( ajout, "Pas:",&SpherePas);
          SphereP->set_float_limits(0.1,990);
         
          new GLUI_Button(ajout, "Ajouter une sphere", i, ajouterPrimtv );

         }
         
        if(i==2)
        {
          CubeL =new GLUI_Spinner( ajout, "Longueur:",&CubeLongueur);
          CubeL->set_float_limits(0.3,1000);
          Cubel =new GLUI_Spinner( ajout, "Largeur:",&CubeLargeur);
          Cubel->set_float_limits(0.1,990);
          new GLUI_Button(ajout, "Ajouter un cube", i, ajouterPrimtv );
        }

        if(i==3)
         {
          CylindrevertP  =new GLUI_Spinner( ajout, "pas vertt",&Cycomplexiter1);
          CylindrevertP->set_int_limits(10,200);
          CylindrehorP  =new GLUI_Spinner( ajout, "pas horiz",&Cycomplexiter2);
          CylindrehorP->set_int_limits(10,200);
          CylindreR  =new GLUI_Spinner( ajout, "Rayon:",&CylindreRayon);
          CylindreR->set_float_limits(0.3,1000);
           new GLUI_Button(ajout, "Ajouter un cylindre", i, ajouterPrimtv );
         }
       
        }
}

void afficheTransformations(GLUI* panneBas)
{
GLUI_Spinner *vittesse  =new GLUI_Spinner( panneBas, "Vitesse de translation:",&vittessetrans);
          vittesse->set_float_limits(0.00001,0.1);
        new GLUI_Column( panneBas, false );
trans_x = new GLUI_Translation(panneBas, "Translation X", GLUI_TRANSLATION_X,&transx,1,transformations );
        new GLUI_Column( panneBas, false );
trans_y = new GLUI_Translation(panneBas, "Translation Y", GLUI_TRANSLATION_Y,&transy,1,transformations );
 new GLUI_Column( panneBas, false );
trans_z = new GLUI_Translation(panneBas, "Translation Z", GLUI_TRANSLATION_Z,&transz,1,transformations );
 
 new GLUI_Column( panneBas, false );
rotx= new GLUI_Scrollbar(panneBas, " rotationx",GLUI_SCROLL_HORIZONTAL,&rotationx,2,transformations );
rotx->set_float_limits(-360.,360.);

roty= new GLUI_Scrollbar(panneBas, " rotationy",GLUI_SCROLL_HORIZONTAL,&rotationy,2,transformations );
roty->set_float_limits(-360.,360.);

rotz= new GLUI_Scrollbar(panneBas, " rotationz",GLUI_SCROLL_HORIZONTAL,&rotationz,2,transformations );
rotz->set_float_limits(-360.,360.);
 new GLUI_Column( panneBas, false );
scalex  =new GLUI_Spinner( panneBas, "Scalex:",&scalx,3,transformations);
          scalex->set_float_limits(0.8,1.2);
           new GLUI_Column( panneBas, false );
scaley  =new GLUI_Spinner( panneBas, "ScaleY",&scaly,3,transformations);
          scaley->set_float_limits(0.8,1.2);
           new GLUI_Column( panneBas, false );

scalez  =new GLUI_Spinner( panneBas, "ScaleZ",&scalz,3,transformations);
          scalez->set_float_limits(0.8,1.2);
}


void interface()
{
  GLUI_Master.close_all();
   
    panneDroit= GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_RIGHT );
    panneGauche= GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_LEFT );
    panneBas= GLUI_Master.create_glui_subwindow( main_window, GLUI_SUBWINDOW_BOTTOM );
  
     afficherArbre(panneDroit);
     afficheAjout(panneGauche);
     afficheTransformations(panneBas);
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
  Groupe g1("Default Groupe");

  a.addGroupe(g1);
  interface();

 
  /* Entree dans la boucle principale glut */
  glutMainLoop();

  glDeleteProgram(programID);
  deleteVBO();
  return 0;
}