#include "displayTools.h"

int graphicsInit(const char* nomFenetre, int largeur, int hauteur, int *argcptr, char *argv[]);
void definisFonctions(void* affichage, void* update, void* clavier, void* souris);

void debut3D(int fov, int largeur, int hauteur);
void fin3D(void);
void debut2D(int largeur, int hauteur);
void fin2D(void);

void afficheFPS(void);
void definisUpdateParSeconde(int nb);
void definisFrameParSeconde(int nb);

void lanceBoucle();

void regardeVers(OBJ3D maPosition, OBJ3D cible);
OBJ3D vec3(float x, float y, float z);
OBJ2D vec2(float x, float y);