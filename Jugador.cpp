#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "Jugador.h"
#include "imageManager.h"


using namespace std;
using namespace sf;

Jugador::Jugador() {

	cargarTextura();//Carga las texturas del Jugador.

	cantidadAscenso = 0; //El el número de piso dónde se encuentra el Personaje.

}

void Jugador::cargarTextura() { //Carga las texturas del Jugador.

	img_mgr.addResourceDirectory("Recursos/Imagenes/"); //Define el directorio donde está la Textura.

	s_Jugador.setTexture(img_mgr.getImage("jumper.PNG"));//Se carga la textura del Jugador.
	s_Jugador.setPosition(370, 465);//Se define el tamaño del Sprite del Jugador.

}

void Jugador::actualizarSalto() {//Es el salto del personaje.

	if (cantidadAscenso <= 5) { // si todavia no saltaste todo lo que debias saltar... va del piso 0 al 5
		if (teclaSaltoPresionada && !saltoEnProceso) {
			saltoEnProceso = true;
			enAscenso = true;
			cantidadAscenso++;//incremento de a un piso si se puede saltar
		}
	}

	if (saltoEnProceso) {

		if (s_Jugador.getPosition().y <= posicion_Y - (ascenso_max_Y * cantidadAscenso)) {//el ascenso máximo por el piso (para que varíe el valor de Y)
			enAscenso = false;
			saltoEnProceso = false;//en algún momento el proceso tiene que finalizar
		}

		if (enAscenso) {

			s_Jugador.setPosition(s_Jugador.getPosition().x, s_Jugador.getPosition().y - 4);//cantidadAscenso);
		}
	}
}