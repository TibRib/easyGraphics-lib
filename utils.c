#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
#include "easyGraphics.h"

void propertiesInit(void);
void displayFunc(void);
void updateFunc(int g);
void updateDisplayFunc(int g);
void updateFPS(void);
void MouseClick(int button, int state, int x, int y);
void MouseMotion(int x, int y);
void MousePassive(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);
void KeyboardSpecial(int key, int x, int y);
void ReshapeWindow(int width, int height);

static int steps_per_sec = 60;
static int frame_per_sec = 60;

struct fonctions{
    void (*affichage)(void);
    void (*update)(float delta);
    void (*inputClavier)(unsigned char key);
    void (*inputSouris)(int x, int y);
} fonctions;

int init_time, final_time, frame_count = 0;
char fps_buffer[12];


int graphicsInit(const char* nomFenetre, int largeur, int hauteur, int *argcptr, char *argv[]){	
	glutInit(argcptr, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);

	glutInitWindowSize(largeur, hauteur);
	glutInitWindowPosition(0,0);

	glutCreateWindow(nomFenetre);

    //Display func.
	glutDisplayFunc(displayFunc);

    propertiesInit();

    return 0;
}

void definisUpdateParSeconde(int nb){
	steps_per_sec = nb;
}
void definisFrameParSeconde(int nb){
	frame_per_sec = nb;
	frame_count = 0;
}

void definisFonctions(void* affichage, void* update, void* clavier, void* souris){
    fonctions.affichage = affichage;
    fonctions.update = update;
    fonctions.inputClavier = clavier;
    fonctions.inputSouris = souris;

    //Physics update
	glutTimerFunc(1000 / 60, updateFunc, 0);
    //Display update
	glutTimerFunc(1000 / 60, updateDisplayFunc, 0);

	//Mouse btns (boutons)
	glutMouseFunc(MouseClick);

	//Mouse clicked motion
	glutMotionFunc(MouseMotion);

	//Mouse passive motion
	glutPassiveMotionFunc(MousePassive);

	//Keyboard Input
	glutKeyboardFunc(Keyboard);

	//Release of keys
	glutKeyboardUpFunc(KeyboardUp);

	//Keyboard special symbols
	glutSpecialFunc(KeyboardSpecial);

	//Display func.
	glutDisplayFunc(displayFunc);

	//Resize func.
	glutReshapeFunc(ReshapeWindow);
}

/* Attention : Appeler cette fonction après toute declaration du main */
void lanceBoucle(void){
	glutMainLoop();
}


void propertiesInit(void) {
	/*Glut and Window properties */
	glClearColor(1.f, 1.f, 1.f, 1.f);

	glClearDepth(1.0f);

	glShadeModel(GL_FLAT);

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Renormalize scaled normals so that lighting still works properly.
	glEnable(GL_NORMALIZE);

	//Enable colors while illuminated
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	//Texture parameters
	//repetition
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//Enabling Anti-aliasing (multi sampling technique)
	glEnable(GL_MULTISAMPLE);

}


void draw2D(float lF, float hF) {
	//2D- Overlay
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//gluOrtho2D(0, lF, 0, hF);
	glOrtho(0, lF, 0, hF, -1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//Draws 3d animation depending on a certain object position
void draw3D(int fov, float scene_width, float scene_height) {
	//3D Init mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Perspective cavaliere
	gluPerspective(60, (double)scene_width / scene_height, 1, 100000);
	//Orthographic perspective
	//glOrtho(0,scene_width,0,scene_height,1,10000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void debut3D(int fov, int largeur, int hauteur){
    glPushMatrix();
	draw3D(fov,largeur, hauteur);
	glEnable(GL_DEPTH_TEST);
}

void regardeVers(OBJ3D maPosition, OBJ3D cible){
    gluLookAt(maPosition.x, maPosition.y, maPosition.z, cible.x, cible.y, cible.z, 0, 1, 0);
}

void fin3D(void){
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);

    glPopMatrix();
}

void debut2D(int largeur, int hauteur){
    glPushMatrix();
	glPushMatrix();
	glLoadIdentity();
    //ZOOM
	const float zoom = 1.0f;
	int width,height;
    if( zoom > 1.0f ){
        width = largeur / zoom;
        height = hauteur / zoom;
    }
    else{
        width = largeur;
        height = hauteur;
    }
	draw2D(width, height);
	glDisable(GL_DEPTH_TEST);
}

void fin2D(){
    glPopMatrix();
    glPopMatrix();
}

void displayFunc(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(fonctions.affichage != NULL){
        fonctions.affichage();
    }

    glutSwapBuffers();
}

void updateFunc(int g) {
    if(fonctions.update != NULL){
        fonctions.update((float) 1000/steps_per_sec);
    }

	glutTimerFunc(1000 / steps_per_sec, updateFunc, 0);
}

void updateDisplayFunc(int g) {
	glutPostRedisplay();
	updateFPS();

	glutTimerFunc(1000 / frame_per_sec, updateDisplayFunc, 0);
}

void updateFPS(void) {
	frame_count++;
	final_time = time(NULL);
	if (final_time - init_time > 1)
	{
		int fpscalculated = frame_count / (final_time - init_time);
		sprintf(fps_buffer, "FPS : %d\n", fpscalculated);
		frame_count = 0;
		init_time = final_time;
	}
}

void afficheFPS(void){
    changeColor(0, 0, 0);
	drawString(fps_buffer, 18, 60, 20);
}

void ReshapeWindow(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, (GLdouble) width, 0, (GLdouble) height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	printf("Fenetre redimensionnee : %d %d\n",width,height);
}

void KeyboardUp(unsigned char key, int x, int y){}
void KeyboardSpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		break;

	case GLUT_KEY_RIGHT:
		break;

	case GLUT_KEY_UP:
		break;

	case GLUT_KEY_DOWN:
		break;
	}
}

void Keyboard(unsigned char key, int x, int y){
    if(fonctions.inputClavier != NULL)
        fonctions.inputClavier(key);
}

void MouseClick(int button, int state, int x, int y) {
	int gfxY = glutGet(GLUT_WINDOW_HEIGHT) -y ;
	if (state == GLUT_DOWN){ }
	else
	{ //Bouton relache
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			if(fonctions.inputSouris != NULL){
                fonctions.inputSouris(x,gfxY);
            }
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	}
}

void MouseMotion(int x, int y) {}
void MousePassive(int x, int y) {}



//Fonctions de creation de structures
OBJ3D vec3(float x, float y, float z){
    OBJ3D obj;
    obj.x = x;
    obj.y = y;
    obj.z = z;
    return obj;
}

OBJ2D vec2(float x, float y){
    OBJ2D obj;
    obj.x = x;
    obj.y = y;
    return obj;
}
