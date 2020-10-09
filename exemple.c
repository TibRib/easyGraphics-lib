#include <stdio.h>
#include <stdlib.h>
#include "easyGraphics.h"

/* Const */
#define WWIDTH 640
#define WHEIGHT 480

/*Prototypes */
void display(void);

static unsigned int image;

int main(int argc, char *argv[])
{
    graphicsInit("ma fenetre", WWIDTH, WHEIGHT, &argc, argv);
    image = TexLoad("image.png");
    definisFonctions(display,NULL,NULL,NULL);
    lanceBoucle();
    
	return 0;
}

void display(void) {

    debut2D(WWIDTH, WHEIGHT);
    fin2D();

}
