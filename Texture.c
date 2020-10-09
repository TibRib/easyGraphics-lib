#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Texture.h"

GLuint TexLoad(const char* path) {
    GLuint tex2d =  SOIL_load_OGL_texture
    (
        path,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    checkLoaded(&tex2d);
    return tex2d;
}

void TexBind(GLuint tex, bool filtered) {
    glEnable(GL_TEXTURE_2D);
    glColor3f(1.f, 1.f, 1.f);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    if(filtered){
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else{
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}

void TexEnd(void){
    glDisable(GL_TEXTURE_2D);
}

bool checkLoaded(GLuint *myTexture) {
    if (*myTexture == 0)
    {
        printf("Erreur de chargement d'image :\n  SOIL :: %s \n",SOIL_last_result());
        return false;
    }
    return true;
}