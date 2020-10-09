exemple : exemple.o displayTools.o Texture.o utils.o
	gcc -o exemple exemple.o displayTools.o Texture.o utils.o -lglut -lGL -lGLU -lX11 -lm -lSOIL

exemple.o : exemple.c displayTools.h easyGraphics.h
	gcc -c -Wall exemple.c

utils.o : utils.c easyGraphics.h displayTools.h 
	gcc -c -Wall utils.c

displayTools.o : displayTools.c displayTools.h Texture.h
	gcc -c -Wall displayTools.c

Texture.o : Texture.c Texture.h
	gcc -c -Wall Texture.c

clean : *.o
	rm *.o && echo "\nfichiers de build nettoyés"

