#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "imageManager.h"

using namespace std;
using namespace sf;

//----------------------------------------Clase "Jugador". Maneja el movimiento del personaje.

class Jugador {
private:

	Sprite s_Jugador; //Sprite del Jugador
	imageManager img_mgr;//Se crea una instancia del objeto imageManager
	const int posicion_Y = 465; //Posicion del personaje en Y.
	const int ascenso_max_Y = 75; //Límite del salto del personaje en Y.
	bool teclaSaltoPresionada = false; //Maneja los elementos del salto del Personaje.
	bool enAscenso = false;// Idem.
	bool saltoEnProceso = false; //Idem.
	int cantidadAscenso;//Son los pisos que puede subir el Personaje.

public:
	Jugador();
	Sprite getSprite() { return s_Jugador; }; //Devuelve el Sprite del Jugador.
	void cargarTextura(); //Carga las texturas del Jugador.
	void setTeclaSaltoPresionadaTrue() { teclaSaltoPresionada = true; } //Define si se presionó o no la tecla de salto.
	void setTeclaSaltoPresionadaFalse() { teclaSaltoPresionada = false; }//Iden
	void setPositionYIzq() { s_Jugador.setPosition(s_Jugador.getPosition().x + 8, s_Jugador.getPosition().y);  s_Jugador.setScale(-1.f, 1.f); }; //Hará que el Jugador se mueva a la izquierda.
	void setPositionYDer() { s_Jugador.setPosition(s_Jugador.getPosition().x - 8, s_Jugador.getPosition().y); s_Jugador.setScale(1.f, 1.f); }; //Hará que el Jugador se mueva a la derecha.
	void actualizarSalto(); //Update del salto.
	void setAscensoNuevoY(int ascY) { ascenso_max_Y <= ascY; } //Es el ascenso del personaje.
	void setPosY(int posY) { posicion_Y <= posY; } //Posicion en Y del Personaje
	void setAscenso() { cantidadAscenso = 0; } //Hace que el Personaje vuelva al nivel 0.
	void setCaida() { s_Jugador.setPosition(370, 465); } //Define dónde caerá el personaje.

};
