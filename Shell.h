#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "imageManager.h"

using namespace std;
using namespace sf;

//----------------------------------------Clase "Shell". Maneja la posición y el color de los Shells.

class Shell
{
private:
	friend class Juego; //Clase amiga Juego.
	Texture* t_color; //Textura del Shell.
	Sprite* color; //Sprite del Shell.

public:
	Shell(int c);

	void posNuevas(int x, Sprite y); //Posiciona los Shells.
	void posNuevas2(int x, Sprite y); //Idem
	void posNuevas3(int x, Sprite y);//Idem
	void posNuevas4(int x, Sprite y);//Idem
	void posNuevas5(int x, Sprite*& y);//Idem

	void pos1(int x, Sprite*& y);//Idem
	void pos2(int x, Sprite*& y);//Idem
	void pos3(int x, Sprite*& y);//Idem

	Shell* siguienteShell; //Es el Shell siguiente.

};

