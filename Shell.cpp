#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "imageManager.h"
#include "Shell.h"

using namespace std;
using namespace sf;


Shell::Shell(int c) { //Define el color y la posición inicial de los Shells.

	t_color = new Texture();

	switch (c) {

	case 0: t_color->loadFromFile("Recursos\\Imagenes\\shell_amarillo.PNG");
		color = new Sprite(*t_color);
		color->setScale(-1.f, 1.f);
		color->setPosition(800, 50);
		break;

	case 1: t_color->loadFromFile("Recursos\\Imagenes\\shell_azul.PNG");
		color = new Sprite(*t_color);
		color->setScale(-1.f, 1.f);
		color->setPosition(770, 50);
		break;

	case 2: t_color->loadFromFile("Recursos\\Imagenes\\shell_verde.PNG");
		color = new Sprite(*t_color);
		color->setScale(-1.f, 1.f);
		color->setPosition(740, 50);
		break;

	case 3: t_color->loadFromFile("Recursos\\Imagenes\\shell_rojo.PNG");
		color = new Sprite(*t_color);
		color->setScale(-1.f, 1.f);
		color->setPosition(710, 50);
		break;
	}
}


void Shell::posNuevas(int x, Sprite y) { //Posiciona los Shells.

	switch (x) {

	case 0:
		color->setScale(1.f, 1.f);
		color->setPosition(90, 50);
		break;

	case 1:
		color->setScale(1.f, 1.f);
		color->setPosition(60, 50);
		break;

	case 2:
		color->setScale(1.f, 1.f);
		color->setPosition(30, 50);
		break;

	case 3:
		color->setScale(1.f, 1.f);
		color->setPosition(0, 50);
		break;
	}
}


void Shell::posNuevas2(int x, Sprite y) { //Idem.

	switch (x) {

	case 0:
		color->setScale(1.f, 1.f);
		color->setPosition(90, 126);
		break;

	case 1:
		color->setScale(1.f, 1.f);
		color->setPosition(60, 126);
		break;

	case 2:
		color->setScale(1.f, 1.f);
		color->setPosition(30, 126);
		break;

	case 3:
		color->setScale(1.f, 1.f);
		color->setPosition(0, 126);
		break;
	}
}


void Shell::posNuevas3(int x, Sprite y) { //Idem.

	switch (x) {

	case 0:
		color->setScale(1.f, 1.f);
		color->setPosition(90, 201);
		break;

	case 1:
		color->setScale(1.f, 1.f);
		color->setPosition(60, 201);
		break;

	case 2:
		color->setScale(1.f, 1.f);
		color->setPosition(30, 201);
		break;

	case 3:
		color->setScale(1.f, 1.f);
		color->setPosition(0, 201);
		break;
	}
}

void Shell::posNuevas4(int x, Sprite y) { //Idem.

	switch (x) {

	case 0:
		color->setScale(1.f, 1.f);
		color->setPosition(90, 276);
		break;

	case 1:
		color->setScale(1.f, 1.f);
		color->setPosition(60, 276);
		break;

	case 2:
		color->setScale(1.f, 1.f);
		color->setPosition(30, 276);
		break;

	case 3:
		color->setScale(1.f, 1.f);
		color->setPosition(0, 276);
		break;
	}
}

void Shell::posNuevas5(int x, Sprite*& y) { //Idem.

	switch (x) {

	case 0:
		color->setScale(1.f, 1.f);
		color->setPosition(90, 427);

		break;
	case 1:

		color->setScale(1.f, 1.f);
		color->setPosition(60, 427);

		break;
	case 2:
		color->setScale(1.f, 1.f);
		color->setPosition(30, 427);
		break;

	case 3:
		color->setScale(1.f, 1.f);
		color->setPosition(0, 427);
		break;

	}
}

void Shell::pos1(int x, Sprite *& y) { //Idem.

	switch (x) {

	case 0: 
		color->setScale(-1.f, 1.f);
		color->setPosition(800, 125);

		break;
	case 1: 

		color->setScale(-1.f, 1.f);
		color->setPosition(770, 125);

		break;
	case 2:
		color->setScale(-1.f, 1.f);
		color->setPosition(740, 125);
		break;

	case 3:
		color->setScale(-1.f, 1.f);
		color->setPosition(710, 125);
		break;
	}
}


void Shell::pos2(int x, Sprite*& y) { //Idem.

	switch (x) {

	case 0:
		color->setScale(-1.f, 1.f);
		color->setPosition(800, 201);
		break;

	case 1:
		color->setScale(-1.f, 1.f);
		color->setPosition(770, 201);
		break;

	case 2:
		color->setScale(-1.f, 1.f);
		color->setPosition(740, 201);
		break;

	case 3:
		color->setScale(-1.f, 1.f);
		color->setPosition(710, 201);
		break;
	}
}


void Shell::pos3(int x, Sprite*& y) { //Idem.

	switch (x) {

	case 0:
		color->setScale(-1.f, 1.f);
		color->setPosition(800, 352);
		break;

	case 1:
		color->setScale(-1.f, 1.f);
		color->setPosition(770, 352);
		break;

	case 2:
		color->setScale(-1.f, 1.f);
		color->setPosition(740, 352);
		break;

	case 3:
		color->setScale(-1.f, 1.f);
		color->setPosition(710, 352);
		break;
	}
}