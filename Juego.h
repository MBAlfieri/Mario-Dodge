#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "Jugador.h"
#include "Shell.h"
#include "imageManager.h"

using namespace std;
using namespace sf;

//----------------------------------------Clase "Juego". Basicamente maneja el funcionamiento del juego.

class Juego {

private:
	RenderWindow* VentanaJuego; //Es la ventana del juego.

	bool GameOn; //Bool para el funcionamiento del juego principal.
	bool BadEnd = false; //Bool para mostrar el GameOver.
	bool GoodEnd = false; //Bool para mostrar la condicion de victoria.

	Sprite s_Fondo; //Sprite del fondo.
	Sprite s_Puerta; //Sprite de la puerta.
	Sprite s_GameOver; //Sprite de la pantalla de GameOver.
	Sprite s_GoodEnd; //Sprite de la pantalla de victoria.

	Shell* pilaEnemigo; //Pila n�mero 1.
	Shell* pilaEnemigo2; //Pila n�mero 2.
	Shell* pilaEnemigo3; //Pila n�mero 3.
	Shell* pilaEnemigo4; //Pila n�mero 4.
	Shell* pilaEnemigo5; //Pila n�mero 5.
	Shell* pilaEnemigo6; //Pila n�mero 6.

	Sprite* ShellObtenidoEnPop; //Shell obtenido en Pop n�mero 1.
	Sprite* ShellObtenidoEnPop2; //Shell obtenido en Pop n�mero 2.
	Sprite* ShellObtenidoEnPop3; //Shell obtenido en Pop n�mero 3.

	Shell* primerShellCola1; //Primer Shell de la Cola 1.
	Shell* ultimoShellCola1; //Ultimo Shell de la Cola 1.

	Shell* primerShellCola2; //Primer Shell de la Cola 2.
	Shell* ultimoShellCola2; //Ultimo Shell de la Cola 2.

	Shell* primerShellCola3; //Primer Shell de la Cola 3.
	Shell* ultimoShellCola3; //Ultimo Shell de la Cola 3.

	Sprite* ShellRemovido; //Shell removido de la Cola 1.
	Sprite* ShellRemovido2; //Shell removido de la Cola 2.
	Sprite* ShellRemovido3; //Shell removido de la Cola 3.

	sf::SoundBuffer b_hit; //Buffer del Sonido de golpe.
	sf::Sound s_hit; //Sonido de golpe.

	sf::SoundBuffer b_fanfare; //Buffer del sonido de Victoria.
	sf::Sound s_fanfare; //Sonido de Victoria.

	sf::SoundBuffer b_GameOver; //Buffer del sonido de GameOver.
	sf::Sound GameOver; //Sonido de GameOver.

	Music musica; //M�sica del juego.

	imageManager img_mgr;//Se crea una instancia del objeto imageManager
	Jugador Jugador1; //Instancia de la Clase Jugador.

	bool BoolPilaEnemigo2 = false; //Sirve para condicionar el Update de la Pila 2.
	bool BoolPilaEnemigo3 = false; //Sirve para condicionar el Update de la Pila 3.
	bool BoolPilaEnemigo4 = false; //Sirve para condicionar el Update de la Pila 4.

	int depositarShell = 4; //Ubicaci�n d�nde se depositar�n los Shells en la Pila 1.
	int depositarShell2 = -1; //Ubicaci�n d�nde se depositar�n los Shells en la Pila 2.

	int depositarShell3 = 4; //Ubicaci�n d�nde se depositar�n los Shells en la Pila 3.
	int depositarShell4 = -1; //Ubicaci�n d�nde se depositar�n los Shells en la Pila 4.

	int depositarShell5 = 4; //Ubicaci�n d�nde se depositar�n los Shells en la Pila 5.
	int depositarShell6 = -1; //Ubicaci�n d�nde se depositar�n los Shells en la Pila 6.

	const int tiempoJuego = 30; //Tiempo que dura el juego.
	float tiempoInicio; //Inicio del tiempo.
	float tiempoFin; //Fin del tiempo.

	sf::Text textoContador; //Es el texto del contador de tiempo.
	sf::Clock reloj; //Es el reloj del juego.

	String Stringnumero; //String que contiene el texto.
	Font font; //Es la fuente del texto.


public:

	Juego(Vector2f ResolucionPantalla, String TituloJuego);  //Resolucionde la pantalla y el t�tulo de la ventana.

	void CargarGraficos(); //Cargo los gr�ficos.
	void dibujar(); //Muestro en pantalla los gr�ficos.

	void LoopJuego(); //Loop principal del juego.

	void UpdatePila(); //Update de la Pila 1 y 2.
	void UpdatePila2(); //Update de la Pila 3 y 4.
	void UpdatePila3(); //Update de la Pila 5 y 6.

	void PushShell(Shell*& pila, int x); //Funci�n para el Push.
	void PopShell(Shell*& pila, Sprite*& shell); //Funci�n para el Pop.
	void LoadPila(Shell*& pila); //Sirve para cargar las Pilas.

	void setdepositarShells() { depositarShell -= 1; }; //Cambio la ubicaci�n d�nde se depositar�n los Shells en la Pila 1.
	void setdepositarShells2() { depositarShell2 += 1; }; //Cambio la ubicaci�n d�nde se depositar�n los Shells en la Pila 2.
	void setdepositarShells3() { depositarShell3 -= 1; }; //Cambio la ubicaci�n d�nde se depositar�n los Shells en la Pila 3.
	void setdepositarShells4() { depositarShell4 += 1; }; //Cambio la ubicaci�n d�nde se depositar�n los Shells en la Pila 4
	void setdepositarShells5() { depositarShell5 -= 1; }; //Cambio la ubicaci�n d�nde se depositar�n los Shells en la Pila 5.
	void setdepositarShells6() { depositarShell6 += 1; }; //Cambio la ubicaci�n d�nde se depositar�n los Shells en la Pila 6.

	void acomodarPila3(); //Acomodo la Pila 3.
	void acomodarPila5(); //Acomodo la Pila 5.

	void acomodarCola(); //Acomodo la Cola 1.
	void acomodarCola2(); //Acomodo la Cola 2.
	void acomodarCola3(); //Acomodo la Cola 3.

	void UpdateCola(); //Update de la Cola 1.
	void UpdateCola2(); //Update de la Cola 2.
	void UpdateCola3();//Update de la Cola 3.

	void InsertarShell(int x, Shell*& primero, Shell*& ultimo); //Inserto los Shells a la Cola.
	void RemoverShell(Shell*& primero, Shell*& ultimo, Sprite*& shellremovido); //Remuevo un Shell de la Cola.

	void LoadCola(Shell*& primero, Shell*& ultimo); //Cargo la Cola.
	void LoadCola2(Shell*& primero, Shell*& ultimo); //Cargo la Cola, en otra posici�n.

	void actualizarContador(); //Actualizo el contador de tiempo.

	void cargarSonidos(); //Cargo los sonidos.

};
