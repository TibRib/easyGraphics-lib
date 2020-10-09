#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <GL/freeglut.h>
#include "displayTools.h"

#ifndef M_PI
	#define M_PI 3.141592653
#endif

void rotation(float angle, bool axeX, bool axeY, bool axeZ){
	glRotatef((GLfloat) angle, (GLfloat) axeX, (GLfloat) axeY, (GLfloat) axeZ);
}

void translation(float x, float y, float z){
	glTranslatef((GLfloat) x, (GLfloat) y, (GLfloat) z);
}

void drawLine(float x1, float y1, float x2, float y2){
	glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
}

void draw3DLine(float x1, float y1, float x2, float y2, float z1, float z2) {
	glBegin(GL_LINES);
	glVertex3f(x1, y1,z1);
	glVertex3f(x2, y2, z2);
	glEnd();
}

void drawCircle(float r, float x, float y, int segments)
{
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < segments; i++)
    {
        float theta = (2*M_PI*i)/ segments;

        float vx = r * cos(theta);
        float vy = r * sin(theta);

        glVertex2f(x + vx, y + vy);

    }
    glEnd();
}

void drawDiscus(float r, float x, float y, int segments)
{
    glBegin(GL_POLYGON);
    for(int i = 0; i < segments; i++)
    {
        float theta = (2*M_PI*i)/ segments;

        float vx = r * cos(theta);
        float vy = r * sin(theta);

        glVertex2f(x + vx, y + vy);

    }
    glEnd();
}

void drawString(const char *chaine, float taille, float x, float y)
{
	float scale = taille * 1. / 120;
	glPushMatrix();
	glTranslatef(x - (tailleChaine(chaine, taille)/2), y, 0);
	glScalef(scale, scale, scale);
	for (int i = 0; i < strlen(chaine); i++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, chaine[i]);
	}
	glPopMatrix();

}

float tailleChaine(const char *chaine, float taille)
{
	return glutStrokeLength(GLUT_STROKE_ROMAN, (const unsigned char*)chaine)* taille * 1. / 120;
}

void drawFillRectangle(float x1, float y1, float x2, float y2){
	glBegin(GL_QUADS);
		glVertex2f(x1, y1);
		glVertex2f(x2, y1);
		glVertex2f(x2, y2);
		glVertex2f(x1, y2);
	glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	glBegin(GL_TRIANGLES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
		glVertex2f(x3, y3);
	glEnd();
}

void drawHollowRectangle(float x1, float y1, float x2, float y2){
	glBegin(GL_LINE_STRIP);
			glVertex2f(x1, y1);
			glVertex2f(x1, y2);
			glVertex2f(x2, y2);
			glVertex2f(x2, y1);
			glVertex2f(x1, y1);
		glEnd();
}

void draw3DCylinder(float radius, float height, int slices) {
		GLUquadricObj* quadratic;
		quadratic = gluNewQuadric();
		gluCylinder(quadratic, radius,radius, height, slices, slices);
		gluDeleteQuadric(quadratic);
		drawDiscus(radius, 0, 0, slices);
		glTranslatef(0, 0, height);
		drawDiscus(radius, 0,0, slices);
		glTranslatef(0, 0, -height);
}

void drawCube(float posx, float posy, float posz, float lx, float ly, float lz) {

	glPushMatrix();
	glTranslatef(posx, posy, posz);
	float x = lx, y = ly, z = lz;

	//X designe la largeur sur x;
	//Y designe la longueur sur y;
	//Z designe la position sur z;
	// BACK
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(x, -y, z);
	glTexCoord2f(1,1);
	glVertex3f(x, y, z);
	glTexCoord2f(0, 1);
	glVertex3f(-x, y, z);
	glTexCoord2f(0, 0);
	glVertex3f(-x, -y, z);
	glEnd();

	// FRONT
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(x, -y, -z);
	glTexCoord2f(1, 1);
	glVertex3f(x, y, -z);
	glTexCoord2f(0, 1);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0, 0);
	glVertex3f(-x, -y, -z);
	glEnd();

	// RIGHT
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(x, -y, -z);
	glTexCoord2f(1, 0);
	glVertex3f(x, y, -z);
	glTexCoord2f(1, 1);
	glVertex3f(x, y, z);
	glTexCoord2f(0, 1);
	glVertex3f(x, -y, z);
	glEnd();

	// LEFT
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1);
	glVertex3f(-x, -y, z);
	glTexCoord2f(1, 1);
	glVertex3f(-x, y, z);
	glTexCoord2f(1, 0);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0,0);
	glVertex3f(-x, -y, -z);
	glEnd();

	// TOP
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(x, y, z);
	glTexCoord2f(1, 0);
	glVertex3f(x, y, -z);
	glTexCoord2f(0,0);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0,1);
	glVertex3f(-x, y, z);
	glEnd();

	//  BOTTOM
	glBegin(GL_QUADS);
	glTexCoord2f(1, 0);
	glVertex3f(x, -y, -z);
	glTexCoord2f(1, 1);
	glVertex3f(x, -y, z);
	glTexCoord2f(0, 1);
	glVertex3f(-x, -y, z);
	glTexCoord2f(0,0);
	glVertex3f(-x, -y, -z);
	glEnd();

	glPopMatrix();
}

void drawRepere(float unitaire) {
	//trace du repere x,y,z de meme vecteur unitaire
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(unitaire, 0, 0);
	glEnd();
	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, unitaire, 0);
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, unitaire);
	glEnd();
}

/*Dessine une grille plane d'une certaine taille et de carreaux uniformes */
//Parametre supplementaire: faceZ : tourne la grille pour faire face à l'axe Z (utilisation en 2D)
void drawGrid(int rayon, float step, bool faceZ) {
	glPushMatrix();
	if(faceZ) glRotatef(90.f, 1.0f, 0, 0);
	glBegin(GL_LINES);
	for (GLfloat i = -rayon; i <= rayon; i += step) {
		glVertex3f(i, 0, rayon);
		glVertex3f(i, 0, -rayon);
		glVertex3f(rayon, 0, i);
		glVertex3f(-rayon, 0, i);
	}
	glEnd();

	glPopMatrix();
}


void drawSphere(float posx, float posy, float posz, float rayon, float prec, GLenum style) {
	glPushMatrix();
	glTranslatef(posx, posy, posz);

	GLUquadric* params = gluNewQuadric();
	gluQuadricTexture(params, GLU_TRUE);
	gluQuadricDrawStyle(params, style);
	gluSphere(params, rayon, prec, prec);
	gluDeleteQuadric(params);
	
	glPopMatrix();
}

void changeColor(int r, int g, int b) {
	glColor3f((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f);
}

void lineWidth(float value) {
	glLineWidth(10.0f);
}

double rad2deg(double value) {
	return value * 180 / (3.14);
}

void draw2DObject(const OBJ2D* vertices, int nbvertices) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < nbvertices; i++) {
		glVertex2f(vertices[i].x, vertices[i].y);
	}
	glEnd();
}

void drawTexturedRectangle(float x1, float y1, float x2, float y2) {
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex2f(x1, y1);
	glTexCoord2i(1, 0); glVertex2f(x2, y1);
	glTexCoord2i(1, 1); glVertex2f(x2, y2);
	glTexCoord2i(0, 1); glVertex2f(x1, y2);
	glEnd();
}

void drawImage(GLuint tex, float x1, float y1, float x2, float y2, bool filtered){
	TexBind(tex, filtered);
	drawTexturedRectangle(x1,y1,x2,y2);
	TexEnd();
}

void drawExtrudedObject(const OBJ2D* vertices, int nbvertices, float height) {
	int vxsize = nbvertices - 1;
	int i;
	//BACK (z = height)
	glTranslatef(0, 0, -height);
	draw2DObject(vertices, nbvertices);
	//FRONT ( z = height)
	glTranslatef(0, 0, 2*height);
	draw2DObject(vertices, nbvertices);

	glTranslatef(0, 0, -height);

	//SIDES
	glBegin(GL_QUADS);
	for (i = 0; i < vxsize - 1; i++) {
		glVertex3f(vertices[i].x, vertices[i].y, -height);
		glVertex3f(vertices[i].x, vertices[i].y, height);
		glVertex3f(vertices[i + 1].x, vertices[i + 1].y, height);
		glVertex3f(vertices[i + 1].x, vertices[i + 1].y, -height);
	}
	glEnd();
}