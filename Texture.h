#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdbool.h>

GLuint TexLoad(const char* path);
void TexBind(GLuint tex, bool filtered);
bool checkLoaded(GLuint *myTexture);
void TexEnd(void);