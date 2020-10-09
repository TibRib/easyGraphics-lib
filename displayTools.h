#include <GL/freeglut.h>
#include "Texture.h"

/*Structure de coordonnees */
typedef struct OBJ3D {
	float x;
	float y;
	float z;
}OBJ3D;

typedef struct OBJ2D {
	float x;
	float y;
}OBJ2D;


#define PLEIN GLU_FILL
#define SILHOUETTE GLU_SILHOUETTE
#define LIGNES GLU_LINE
#define POINTS GLU_POINT


//Fonctions de dessin 2D
void drawCircle(float r, float x, float y, int segments);
void drawDiscus(float r, float x, float y, int segments);
void drawString(const char *chaine, float taille, float x, float y);
void drawHollowRectangle(float x1, float y1, float x2, float y2);
void drawFillRectangle(float x1, float y1, float x2, float y2);
void drawLine(float x1, float y1, float x2, float y2);
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3);
void draw3DCylinder(float radius, float height, int slices);
void drawExtrudedObject(const OBJ2D* vertices, int nbvertices, float height);
void drawTexturedRectangle(float x1, float y1, float x2, float y2);
void drawImage(GLuint tex, float x1, float y1, float x2, float y2, bool filtered);

//Others
void changeColor(int r, int g, int b);
void lineWidth(float value);
double rad2deg(double value);
float tailleChaine(const char* chaine, float taille);

//Fonctions de dessin 3D
void drawSphere(float posx, float posy, float posz, float rayon, float prec, GLenum style);
void draw3DLine(float x1, float y1, float x2, float y2, float z1, float z2);
void drawGrid(int rayon, float step, bool faceZ);
void drawRepere(float unitaire);
void drawCube(float posx, float posy, float posz, float lx, float ly, float lz);

void translation(float x, float y, float z);
void rotation(float angle, bool axeX, bool axeY, bool axeZ);
