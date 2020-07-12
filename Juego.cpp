#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cstdlib>
#include "Juego.h"
#include "Shell.h"
#include "imageManager.h"

using namespace std;
using namespace sf;

Juego::Juego(Vector2f ResolucionPantalla, String TituloDelJuego) {

	VentanaJuego = new RenderWindow(VideoMode(ResolucionPantalla.x, ResolucionPantalla.y), TituloDelJuego);  //Resolucionde la pantalla y el título de la ventana.
	VentanaJuego->setFramerateLimit(60); //Limito los FPS.
	VentanaJuego->setMouseCursorVisible(false); //Escondo el mouse.

	font.loadFromFile("GILB.ttf"); //Cargo la fuente a utilizar.
	textoContador.setFont(font); //Define la fuente a utilizar.
	textoContador.setCharacterSize(20);//Define el tamaño de la letra.
	textoContador.setOutlineColor(sf::Color::Black);//Define el color del borde del texto.
	textoContador.setOutlineThickness(2);//Define el grosor del borde del texto.

	ShellObtenidoEnPop = NULL; //Hago que el Shell obtenido en Pop sea NULL.
	pilaEnemigo = NULL; //Hago que la Pila de Enemigos sea NULL.

	primerShellCola1 = NULL; //Hago que el Primer Shell de la Cola 1 sea NULL.
	ultimoShellCola1 = NULL; //Hago que el ultimo Shell de la cola 1 sea NULL.

	primerShellCola2 = NULL; //Hago que el Primer Shell de la Cola 2 sea NULL.
	ultimoShellCola2 = NULL; //Hago que el ultimo Shell de la cola 2 sea NULL.

	primerShellCola3 = NULL; //Hago que el Primer Shell de la Cola 3 sea NULL.
	ultimoShellCola3 = NULL; //Hago que el ultimo Shell de la cola 3 sea NULL.

	cargarSonidos(); //Cargo los sonidos.
	CargarGraficos(); //cargo los gráficos.

	GameOn = true; //Permite que el juego inicie.

	LoadPila(pilaEnemigo); //Cargo la Pila 1.
	LoadPila(pilaEnemigo3); //Cargo la Pila 3.
	LoadPila(pilaEnemigo5); //Cargo la Pila 4.

	LoadCola(primerShellCola1,ultimoShellCola1); //Cargo la Cola 1.
	LoadCola2(primerShellCola2, ultimoShellCola2); //Cargo la Cola 2.
	LoadCola(primerShellCola3, ultimoShellCola3); //Cargo la Cola 3.

	acomodarPila3(); //Acomodo la Pila 3.
	acomodarPila5(); //Acomodo la Pila 5.

	acomodarCola(); //Acomodo la Cola 1.
	acomodarCola2(); //Acomodo la Cola 2.
	acomodarCola(); //Acomodo la Cola 3

	LoopJuego(); //Loop principal del Juego.
}

void Juego::LoopJuego() { //Inicia el Loop principal del Juego.

	tiempoInicio = reloj.getElapsedTime().asSeconds() + tiempoJuego; //Inicia el reloj.
	musica.play(); //Reproduzco la música.
	s_hit.setVolume(95); //Le cambio el volumen a la música,

	while (GameOn == true) { //Inicia el juego.

//-----------------------------------------------------------------Eventos.
		sf::Event event; //Instancia de Evento.
		while (VentanaJuego->pollEvent(event)) { 

			if (event.type == sf::Event::Closed) { //Permite cerrar la ventana.
				VentanaJuego->close();
			}

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) { //Detecta si se presiona la Barra Espaciadora para saltar.
				Jugador1.setTeclaSaltoPresionadaTrue();
			}

			else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space) {//Detecta si no se presiona la Barra Espaciadora para saltar.
				Jugador1.setTeclaSaltoPresionadaFalse();
			}}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {//Hace que el personaje se mueva hacia la izquierda.
				Jugador1.setPositionYDer();
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {//Hace que el personaje se mueva hacia la derecha
				Jugador1.setPositionYIzq();
			}

		FloatRect colisionPersonaje = Jugador1.getSprite().getGlobalBounds(); //Define los bounds de la colisión del Personaje.
		FloatRect colisionPuerta = s_Puerta.getGlobalBounds(); //Define los bounds de la colisión de la Puerta.

			if (colisionPersonaje.intersects(colisionPuerta)) { //Si el Personaje colisiona con la Puerta.
				GoodEnd = true; //Se define el final bueno.
				GameOn = false; //Se termina el juego principal.
				musica.stop(); //Se detiene la música principal.
				s_fanfare.play(); //Se reproduce la música de victoria.
			}

			if (ShellObtenidoEnPop != NULL) { //Si el Shell Obtenido en Pop 1 no es NULL.

		FloatRect colisionShell = ShellObtenidoEnPop->getGlobalBounds(); //Define los bounds del Shell.

			if (colisionPersonaje.intersects(colisionShell)) { //Si el personaje colisiona con un Shell.

				Jugador1.setAscenso(); //Se cae el personaje. 
				Jugador1.setCaida(); //Idem.
				s_hit.play(); //Suena el sonido del golpe.
			}
		}

			if (ShellObtenidoEnPop2 != NULL) { //Si el Shell Obtenido en Pop 2 no es NULL.

		FloatRect colisionShell = ShellObtenidoEnPop2->getGlobalBounds(); //Define los bounds del Shell.

			if (colisionPersonaje.intersects(colisionShell)) { //Si el personaje colisiona con un Shell.

				Jugador1.setAscenso(); //Se cae el personaje.
				Jugador1.setCaida(); //Idem.
				s_hit.play(); //Suena el sonido del golpe.
			}
		}

			if (ShellObtenidoEnPop3 != NULL) { //Si el Shell Obtenido en Pop 3 no es NULL.

		FloatRect colisionShell = ShellObtenidoEnPop3->getGlobalBounds(); //Define los bounds del Shell.

			if (colisionPersonaje.intersects(colisionShell)) { //Si el personaje colisiona con un Shell.

				Jugador1.setAscenso(); //Se cae el personaje.
				Jugador1.setCaida(); //Idem
				s_hit.play(); //Suena el sonido del golpe.
			}
		}

			if (ShellRemovido != NULL) { //Si el Shell removido 1 no es NULL.

		FloatRect colisionShell = ShellRemovido->getGlobalBounds(); //Define los bounds del Shell.

			if (colisionPersonaje.intersects(colisionShell)) { //Si el personaje colisiona con un Shell.

				Jugador1.setAscenso(); //Se cae el personaje.
				Jugador1.setCaida(); //Idem
				s_hit.play(); //Suena el sonido del golpe.
			}
		}

			if (ShellRemovido2 != NULL) {//Si el Shell removido 2 no es NULL.

		FloatRect colisionShell = ShellRemovido2->getGlobalBounds(); //Define los bounds del Shell.

			if (colisionPersonaje.intersects(colisionShell)) { //Si el personaje colisiona con un Shell.

				Jugador1.setAscenso(); //Se cae el personaje.
				Jugador1.setCaida(); //Idem
				s_hit.play();  //Suena el sonido del golpe.
			}
		}

			if (ShellRemovido3 != NULL) { //Si el Shell 3 removido no es NULL.

		FloatRect colisionShell = ShellRemovido3->getGlobalBounds(); //Define los bounds del Shell.

			if (colisionPersonaje.intersects(colisionShell)) {

				Jugador1.setAscenso(); //Se cae el personaje.
				Jugador1.setCaida(); //Idem
				s_hit.play(); //Suena el sonido del golpe.
			}
		}

		Jugador1.actualizarSalto(); //Es el salto del personaje.

//-----------------------------------------------------------------Updates.

		UpdatePila(); //Update de la Pila 1.
		UpdatePila2(); //Update de la Pila 2.
		UpdatePila3(); //Update de la Pila 3.

		UpdateCola(); //Update de la Cola 1.
		UpdateCola2(); //Update de la Cola 2.
		UpdateCola3(); //Update de la Cola 3.

//-----------------------------------------------------------------Dibujo en pantalla.

		VentanaJuego->clear(); //Limpia la pantalla.

		actualizarContador(); //Es el reloj.

		dibujar(); //Dibuja en la pantalla los elementos.

		VentanaJuego->display();//Se muestra en la ventana lo dibujado.

	}

//-----------------------------------------------------------------Condición de derrota.

	while(GameOn == false && BadEnd == true) {  //Si se termina el juego y se obtiene el final malo.

		VentanaJuego->clear(); //Limpia la pantalla.

		VentanaJuego->draw(s_GameOver); //Dibujo la pantalla de GameOver.

		VentanaJuego->display(); //Muestro la pantalla de GameOver.
	}

//-----------------------------------------------------------------Condición de victoria.

	while (GameOn == false && GoodEnd == true) { //Si se termina el juego y se obtiene el final bueno.
	
		VentanaJuego->clear(); //Limpia la pantalla.

		VentanaJuego->draw(s_GoodEnd); //Dibujo la pantalla de victoria.

		VentanaJuego->display(); //Muestro la pantalla de victoria.
	}

}

void Juego::dibujar() { //Muestro en pantalla los gráficos.

	VentanaJuego->draw(s_Fondo); //Fondo del juego.

	VentanaJuego->draw(s_Puerta); //Es la puerta.

	VentanaJuego->draw(Jugador1.getSprite()); //Es el jugador.

	VentanaJuego->draw(textoContador); //Es el texto del reloj.


//-----------------------------------------------------------------Dibujando los Shells.

//-----------------------------------------------------------------Pila 1.

	if (ShellObtenidoEnPop != NULL) //Si el Shell obtenido en Pop 1 no es Null.
	{
		VentanaJuego->draw(*ShellObtenidoEnPop); //Se dibuja el Shell Obtenido en Pop 1.
	}

	if (pilaEnemigo != NULL) //Si la Pila de Enemigos 1 no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo->color); //Se dibuja la Pila 1.
	}

	if (pilaEnemigo != NULL && pilaEnemigo->siguienteShell != NULL) //Si la Pila de Enemigos 1 y el Shell siguiente no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo->siguienteShell->color); //Se dibuja los Shells siguientes.
	}

	if (pilaEnemigo != NULL && pilaEnemigo->siguienteShell != NULL && pilaEnemigo->siguienteShell->siguienteShell != NULL) //Si la Pila de Enemigos 1 y los Shells siguientes no son NULL. 
	{
		VentanaJuego->draw(*pilaEnemigo->siguienteShell->siguienteShell->color); //Se dibujan los Shells siguientes.
	}

//-----------------------------------------------------------------Pila 2.

	if (pilaEnemigo2 != NULL) //Si la Pila de Enemigos 2 no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo2->color); //Se dibuja la Pila 2.
	}

	if (pilaEnemigo2 != NULL && pilaEnemigo2->siguienteShell != NULL) //Si la Pila de Enemigos 2 y el Shell siguiente no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo2->siguienteShell->color); //Se dibuja los Shells siguientes.
	}

	if (pilaEnemigo2 != NULL && pilaEnemigo2->siguienteShell != NULL && pilaEnemigo2->siguienteShell->siguienteShell != NULL) //Si la Pila de Enemigos 2 y los Shells siguientes no son NULL. 
	{
		VentanaJuego->draw(*pilaEnemigo2->siguienteShell->siguienteShell->color); //Se dibujan los Shells siguientes.
	}

//-----------------------------------------------------------------Pila 3.	

	if (ShellObtenidoEnPop2 != NULL) //Si el Shell obtenido en Pop 2 no es Null.
	{
		VentanaJuego->draw(*ShellObtenidoEnPop2); //Se dibuja el Shell Obtenido en Pop 2.
	}

	if (pilaEnemigo3 != NULL) //Si la Pila de Enemigos 3 no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo3->color); //Se dibuja la Pila 3.
	}

	if (pilaEnemigo3 != NULL && pilaEnemigo3->siguienteShell != NULL) //Si la Pila de Enemigos 3 y el Shell siguiente no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo3->siguienteShell->color); // Se dibuja los Shells siguientes.
	}

	if (pilaEnemigo3 != NULL && pilaEnemigo3->siguienteShell != NULL && pilaEnemigo3->siguienteShell->siguienteShell != NULL)  //Si la Pila de Enemigos 3 y los Shells siguientes no son NULL.
	{
		VentanaJuego->draw(*pilaEnemigo3->siguienteShell->siguienteShell->color); //Se dibujan los Shells siguientes.
	}

//-----------------------------------------------------------------Pila 4.	

	if (pilaEnemigo4 != NULL) //Si la Pila de Enemigos 4 no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo4->color); //Se dibuja la Pila 4.
	}

	if (pilaEnemigo4 != NULL && pilaEnemigo4->siguienteShell != NULL) //Si la Pila de Enemigos 4 y el Shell siguiente no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo4->siguienteShell->color); //Se dibuja los Shells siguientes.
	}

	if (pilaEnemigo4 != NULL && pilaEnemigo4->siguienteShell != NULL && pilaEnemigo4->siguienteShell->siguienteShell != NULL)  //Si la Pila de Enemigos 4 y los Shells siguientes no son NULL.
	{
		VentanaJuego->draw(*pilaEnemigo4->siguienteShell->siguienteShell->color); //Se dibujan los Shells siguientes.
	}

//-----------------------------------------------------------------Pila 5.	

	if (ShellObtenidoEnPop3 != NULL) //Si el Shell obtenido en Pop 3 no es Null.
	{
		VentanaJuego->draw(*ShellObtenidoEnPop3); //Se dibuja el Shell Obtenido en Pop 3.
	}

	if (pilaEnemigo5 != NULL) //Si la Pila de Enemigos 5 no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo5->color); //Se dibuja la Pila 5.
	}

	if (pilaEnemigo5 != NULL && pilaEnemigo5->siguienteShell != NULL) //Si la Pila de Enemigos 5 y el Shell siguiente no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo5->siguienteShell->color); //Se dibuja los Shells siguientes.
	}

	if (pilaEnemigo5 != NULL && pilaEnemigo5->siguienteShell != NULL && pilaEnemigo5->siguienteShell->siguienteShell != NULL) //Si la Pila de Enemigos 5 y los Shells siguientes no son NULL.
	{
		VentanaJuego->draw(*pilaEnemigo5->siguienteShell->siguienteShell->color); //Se dibujan los Shells siguientes.
	}

//-----------------------------------------------------------------Pila 6.	

	if (pilaEnemigo6 != NULL) //Si la Pila de Enemigos 6 no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo6->color); //Se dibuja la Pila 4.
	}

	if (pilaEnemigo6 != NULL && pilaEnemigo6->siguienteShell != NULL) //Si la Pila de Enemigos 5 y el Shell siguiente no es NULL.
	{
		VentanaJuego->draw(*pilaEnemigo6->siguienteShell->color); //Se dibuja los Shells siguientes.
	}

	if (pilaEnemigo6 != NULL && pilaEnemigo6->siguienteShell != NULL && pilaEnemigo6->siguienteShell->siguienteShell != NULL) //Si la Pila de Enemigos 5 y los Shells siguientes no son NULL.
	{
		VentanaJuego->draw(*pilaEnemigo6->siguienteShell->siguienteShell->color); //Se dibujan los Shells siguientes.
	}

//-----------------------------------------------------------------Cola 1.

	if (ShellRemovido != NULL) // Si el Shell removido 1 no es NULL.
	{
		VentanaJuego->draw(*ShellRemovido); //Se dibuja el Shell removido.
	}

	if (primerShellCola1 != NULL) //Si el Primer Shell de la Cola 1 no es NULL.
	{
		VentanaJuego->draw(*primerShellCola1->color); //Se dibuja el Primer Shell.
	}

	if (primerShellCola1 != NULL && primerShellCola1->siguienteShell != NULL) //Si el Primer Shell de la Cola 1 y el Shell siguiente no son NULL.
	{
		VentanaJuego->draw(*primerShellCola1->siguienteShell->color); //Se dibuja los Shells siguientes.
	}

	if (primerShellCola1 != NULL && primerShellCola1->siguienteShell->siguienteShell != NULL) //Si el Primer Shell de la Cola 1 y los Shells siguientes no son NULL.
	{
		VentanaJuego->draw(*primerShellCola1->siguienteShell->siguienteShell->color); //Se dibujan los Shells siguientes.
	}

//-----------------------------------------------------------------Cola 2.

	if (ShellRemovido2 != NULL) //Si el Shell removido 2 no es NULL.
	{
		VentanaJuego->draw(*ShellRemovido2); //Se dibuja el Shell removido.
	}

	if (primerShellCola2 != NULL) //Si el Primer Shell de la Cola 2 no es NULL.
	{
		VentanaJuego->draw(*primerShellCola2->color); //Se dibuja el Primer Shell.
	}

	if (primerShellCola2 != NULL && primerShellCola2->siguienteShell != NULL) //Si el Primer Shell de la Cola 2 y el Shell siguiente no son NULL.
	{
		VentanaJuego->draw(*primerShellCola2->siguienteShell->color); //Se dibuja los Shells siguientes.
	}

	if (primerShellCola2 != NULL && primerShellCola2->siguienteShell->siguienteShell != NULL) //Si el Primer Shell de la Cola 2 y los Shells siguientes no son NULL.
	{
		VentanaJuego->draw(*primerShellCola2->siguienteShell->siguienteShell->color); //Se dibujan los Shells siguientes.
	}

//-----------------------------------------------------------------Cola 3.

	if (ShellRemovido3 != NULL) //Si el Shell removido 3 no es NULL.
	{
		VentanaJuego->draw(*ShellRemovido3); //Se dibuja el Shell removido.
	}

	if (primerShellCola3 != NULL) //Si el Primer Shell de la Cola 3 no es NULL.
	{
		VentanaJuego->draw(*primerShellCola3->color); //Se dibuja el Primer Shell.
	}

	if (primerShellCola3 != NULL && primerShellCola3->siguienteShell != NULL) //Si el Primer Shell de la Cola 3 y el Shell siguiente no son NULL.
	{
		VentanaJuego->draw(*primerShellCola3->siguienteShell->color); //Se dibuja los Shells siguientes.
	}

	if (primerShellCola3 != NULL && primerShellCola3->siguienteShell->siguienteShell != NULL) //Si el Primer Shell de la Cola 3 y los Shells siguientes no son NULL.
	{
		VentanaJuego->draw(*primerShellCola3->siguienteShell->siguienteShell->color);//Se dibujan los Shells siguientes.
	}

}

void Juego::CargarGraficos() { //Carga los gráficos del juego.

	img_mgr.addResourceDirectory("Recursos/Imagenes/"); //Define el directorio donde están las imágenes.

	s_Fondo.setTexture(img_mgr.getImage("fondo_plataformas.PNG"));//Se carga la textura del Fondo.

	s_Puerta.setTexture(img_mgr.getImage("puerta.PNG"));//Se carga la textura de la puerta,.
	s_Puerta.setPosition(250, 26); //Se posiciona la puerta.

	s_GameOver.setTexture(img_mgr.getImage("game_over.PNG"));//Se carga la textura de la pantalla de GameOver.

	s_GoodEnd.setTexture(img_mgr.getImage("win.PNG")); //Se carga la textura de la pantalla de victoria.
}

void Juego::cargarSonidos() { //Carga los sonidos.

	b_hit.loadFromFile("Hit.WAV"); //Cargo el sonido del golpe.
	s_hit.setBuffer(b_hit); //Cargo el Buffer.

	b_fanfare.loadFromFile("Win.WAV");//Cargo el sonido de Victoria.
	s_fanfare.setBuffer(b_fanfare);//Cargo el Buffer.

	b_GameOver.loadFromFile("GameOver.WAV");//Cargo el sonido de GameOver.
	GameOver.setBuffer(b_GameOver);//Cargo el Buffer.

	musica.openFromFile("OST.WAV");//Cargo la música.

}

void Juego::acomodarPila3() { //Posiciono la Pila 3.

	if (pilaEnemigo3 != NULL)
	{
		pilaEnemigo3->pos1(3, pilaEnemigo3->color);
	}

	if (pilaEnemigo3 != NULL && pilaEnemigo3->siguienteShell != NULL)
	{
		pilaEnemigo3->siguienteShell->pos1(2, pilaEnemigo3->siguienteShell->color);
		pilaEnemigo3->siguienteShell->siguienteShell->pos1(1, pilaEnemigo3->siguienteShell->siguienteShell->color);
		pilaEnemigo3->siguienteShell->siguienteShell->siguienteShell->pos1(0, pilaEnemigo3->siguienteShell->siguienteShell->siguienteShell->color);
	}
}

void Juego::acomodarPila5() {  //Posiciono la Pila 5.

	if (pilaEnemigo5 != NULL)
	{
		pilaEnemigo5->pos2(3, pilaEnemigo5->color);
	}

	if (pilaEnemigo5 != NULL && pilaEnemigo5->siguienteShell != NULL)
	{
		pilaEnemigo5->siguienteShell->pos2(2, pilaEnemigo5->siguienteShell->color);
		pilaEnemigo5->siguienteShell->siguienteShell->pos2(1, pilaEnemigo5->siguienteShell->siguienteShell->color);
		pilaEnemigo5->siguienteShell->siguienteShell->siguienteShell->pos2(0, pilaEnemigo5->siguienteShell->siguienteShell->siguienteShell->color);
	}
}

void Juego::acomodarCola() { //Acomodo la Cola 1.

	if (primerShellCola1 != NULL)
	{
		primerShellCola1->posNuevas4(0, *primerShellCola1->color);
	}

	if (primerShellCola1 != NULL && primerShellCola1->siguienteShell != NULL)
	{
		primerShellCola1->siguienteShell->posNuevas4(1, *primerShellCola1->siguienteShell->color);
		primerShellCola1->siguienteShell->siguienteShell->posNuevas4(2, *primerShellCola1->siguienteShell->siguienteShell->color);
		ultimoShellCola1->posNuevas4(3, *primerShellCola1->color);
	}
}

void Juego::acomodarCola2() { //Acomodo la Cola 2.

	if (primerShellCola2 != NULL)
	{
		primerShellCola2->pos3(3, *&primerShellCola2->color);
	}

	if (primerShellCola2 != NULL && primerShellCola2->siguienteShell != NULL)
	{
		primerShellCola2->siguienteShell->pos3(2, *&primerShellCola2->siguienteShell->color);
		primerShellCola2->siguienteShell->siguienteShell->pos3(1, *&primerShellCola2->siguienteShell->siguienteShell->color);
		ultimoShellCola2->pos3(0, *&ultimoShellCola2->color);
	}
}

void Juego::acomodarCola3() { //Acomodo la Cola 3.

	if (primerShellCola3 != NULL)
	{
		primerShellCola3->posNuevas5(3, *&primerShellCola3->color);
	}

	if (primerShellCola3 != NULL && primerShellCola3->siguienteShell != NULL)
	{
		primerShellCola3->siguienteShell->posNuevas5(2, *&primerShellCola3->siguienteShell->color);
		primerShellCola3->siguienteShell->siguienteShell->posNuevas5(1, *&primerShellCola3->siguienteShell->siguienteShell->color);
		primerShellCola3->posNuevas5(0, *&primerShellCola3->color);
	}
}

void Juego::PushShell(Shell*& pila, int x ) //Función para el Push.
{
	Shell* newShell = new Shell(x);
	newShell->siguienteShell = pila;
	pila = newShell;

}

void Juego::PopShell(Shell*& pila, Sprite*& shell) //Función para el Pop.
{
	Shell* aux = pila;
	shell = aux->color;
	pila = aux->siguienteShell;
	delete aux;
}

void Juego::LoadPila(Shell*& pila) //Sirve para cargar las Pilas.
{
	PushShell(pila, 0);
	PushShell(pila, 1);
	PushShell(pila, 2);
	PushShell(pila, 3);

}

void Juego::InsertarShell(int x, Shell*& primero, Shell*& ultimo) { //Inserto los Shells a la Cola.

	Shell* newShell = new Shell(x);
	newShell->siguienteShell = NULL;
	if (primero == NULL)
	{
		primero = newShell;
	}
	else
	{
		ultimo->siguienteShell = newShell;
	}
	ultimo = newShell;
}

void Juego::RemoverShell(Shell*& primero, Shell*& ultimo, Sprite*& shellremovido) //Remuevo un Shell de la Cola.
{
	shellremovido = primero->color;
	Shell* aux = primero;

	if (primero == ultimo)
	{
		primero = NULL;
		ultimo = NULL;
	}
	else
	{
		primero = primero->siguienteShell;
	}
	delete aux;
}

void Juego::LoadCola(Shell*& primero, Shell*& ultimo) //Cargo la Cola.
{
	InsertarShell(0, primero, ultimo);
	InsertarShell(1, primero, ultimo);
	InsertarShell(2, primero, ultimo);
	InsertarShell(3, primero, ultimo);
}

void Juego::LoadCola2(Shell*& primero, Shell*& ultimo) //Cargo la Cola, en otra posición.
{
	InsertarShell(3, primero, ultimo);
	InsertarShell(2, primero, ultimo);
	InsertarShell(1, primero, ultimo);
	InsertarShell(0, primero, ultimo);
}

void Juego::actualizarContador() { //Es el contador/reloj.

	tiempoFin = reloj.getElapsedTime().asSeconds();

	int seconds = ((int)(tiempoInicio - tiempoFin));

	if (seconds >= 0) { //Muestra el tiempo
		char buffer[20];
		sprintf_s(buffer, "Tiempo: %i", seconds);
		textoContador.setString(buffer);
	}

	else { //Si se termina el tiempo, se pierde el juego.
		musica.stop();
		GameOver.play();
		GameOn = false;
		BadEnd = true;
	}
}

//----------------------------------------------------------------Updates. Todas funcionan de manera similar, así que la explicación se encontrarán en las primeras, nada más. :P

//-----------------------------------------------------------------Pilas.

void Juego::UpdatePila() //Update de la Pila 1 y 2.
{

//-----------------------------------------------------------------Pila 1.

	if (ShellObtenidoEnPop == NULL && pilaEnemigo != NULL && BoolPilaEnemigo2 == false)
	{
		PopShell(pilaEnemigo, ShellObtenidoEnPop); //Realizo el pop.
		setdepositarShells(); //Cambio la ubicación dónde se depositarán los Shells en la Pila 1.
	}

	else if (ShellObtenidoEnPop != NULL && ShellObtenidoEnPop->getPosition().x > 0 && BoolPilaEnemigo2 == false) //Muevo el Shell horizontalmente.
	{
		ShellObtenidoEnPop->setPosition(ShellObtenidoEnPop->getPosition().x - 8, ShellObtenidoEnPop->getPosition().y);
	}

	if (ShellObtenidoEnPop != NULL && ShellObtenidoEnPop->getPosition().x < 85 && BoolPilaEnemigo2 == false) //Si se llega al limite de la pantalla, borro el Shell y realizo un Push.
	{
		PushShell(pilaEnemigo2, depositarShell); //Realizo el Push.
		pilaEnemigo2->posNuevas(depositarShell, *ShellObtenidoEnPop); //Posiciono los Shells cuando llegan al otro lado.
		ShellObtenidoEnPop = NULL; //El Shell se vuelve NULL para que pueda salir el siguiente.
	}

//-----------------------------------------------------------------Pila 2.

	if (ShellObtenidoEnPop == NULL && pilaEnemigo2 != NULL && depositarShell == 0)
	{
		setdepositarShells2();
		PopShell(pilaEnemigo2, ShellObtenidoEnPop);
		BoolPilaEnemigo2 = true;
	}

	else if (ShellObtenidoEnPop != NULL && ShellObtenidoEnPop->getPosition().x < 800 && BoolPilaEnemigo2 == true)
	{
		ShellObtenidoEnPop->setPosition(ShellObtenidoEnPop->getPosition().x + 8, ShellObtenidoEnPop->getPosition().y);
	}

	if (ShellObtenidoEnPop != NULL && ShellObtenidoEnPop->getPosition().x > 750 && BoolPilaEnemigo2 == true)
	{
		PushShell(pilaEnemigo, depositarShell2);
		ShellObtenidoEnPop = NULL;

		if (depositarShell2 == 3) { //Una vez que se depositaron todos los Shells posibles, esto permite que arranque de nuevo el Loop, inicializando todo de nuevo.

			BoolPilaEnemigo2 = false;
			depositarShell = 4;
			depositarShell2 = -1;
		}
	}
}

void Juego::UpdatePila2() //Update de la Pila 3 y 4.
{

//-----------------------------------------------------------------Pila 3.

	if (ShellObtenidoEnPop2 == NULL && pilaEnemigo3 != NULL && BoolPilaEnemigo3 == false)
	{
		PopShell(pilaEnemigo3, ShellObtenidoEnPop2);
		setdepositarShells3();
	}
	
	else if (ShellObtenidoEnPop2 != NULL && ShellObtenidoEnPop2->getPosition().x > 0 && BoolPilaEnemigo3 == false)
	{
		ShellObtenidoEnPop2->setPosition(ShellObtenidoEnPop2->getPosition().x - 6, ShellObtenidoEnPop2->getPosition().y);
	}

	if (ShellObtenidoEnPop2 != NULL && ShellObtenidoEnPop2->getPosition().x < 85 && BoolPilaEnemigo3 == false)
	{
		PushShell(pilaEnemigo4, depositarShell3);
		pilaEnemigo4->posNuevas2(depositarShell3, *ShellObtenidoEnPop2);
		ShellObtenidoEnPop2 = NULL;
	}

//-----------------------------------------------------------------Pila 4.

	if (ShellObtenidoEnPop2 == NULL && pilaEnemigo4 != NULL && depositarShell3 == 0)
	{
		setdepositarShells4();
		PopShell(pilaEnemigo4, ShellObtenidoEnPop2);
		BoolPilaEnemigo3 = true;
	}

	else if (ShellObtenidoEnPop2 != NULL && ShellObtenidoEnPop2->getPosition().x < 800 && BoolPilaEnemigo3 == true)
	{
		ShellObtenidoEnPop2->setPosition(ShellObtenidoEnPop2->getPosition().x + 6, ShellObtenidoEnPop2->getPosition().y);
	}

	if (ShellObtenidoEnPop2 != NULL && ShellObtenidoEnPop2->getPosition().x > 750 && BoolPilaEnemigo3 == true)
	{
		PushShell(pilaEnemigo3, depositarShell4);

		if (pilaEnemigo3 != NULL)
		{
			pilaEnemigo3->pos1(depositarShell4, pilaEnemigo3->color);
		}

		ShellObtenidoEnPop2 = NULL;

		if (depositarShell4 == 3) {

			BoolPilaEnemigo3 = false;
			depositarShell3 = 4;
			depositarShell4 = -1;
		}
	}
}

void Juego::UpdatePila3() //Update de la Pila 5 y 6.
{
//-----------------------------------------------------------------Pila 5.

	if (ShellObtenidoEnPop3 == NULL && pilaEnemigo5 != NULL && BoolPilaEnemigo4 == false)
	{
		PopShell(pilaEnemigo5, ShellObtenidoEnPop3);
		setdepositarShells5();
	}

	else if (ShellObtenidoEnPop3 != NULL && ShellObtenidoEnPop3->getPosition().x > 0 && BoolPilaEnemigo4 == false)
	{
		ShellObtenidoEnPop3->setPosition(ShellObtenidoEnPop3->getPosition().x - 9, ShellObtenidoEnPop3->getPosition().y);
	}

	if (ShellObtenidoEnPop3 != NULL && ShellObtenidoEnPop3->getPosition().x < 85 && BoolPilaEnemigo4 == false)
	{
		PushShell(pilaEnemigo6, depositarShell5);
		pilaEnemigo6->posNuevas3(depositarShell5, *ShellObtenidoEnPop3);
		ShellObtenidoEnPop3 = NULL;
	}

//-----------------------------------------------------------------Pila 6.

	if (ShellObtenidoEnPop3 == NULL && pilaEnemigo6 != NULL && depositarShell5 == 0)
	{
		setdepositarShells6();
		PopShell(pilaEnemigo6, ShellObtenidoEnPop3);
		BoolPilaEnemigo4 = true;
	}

	else if (ShellObtenidoEnPop3 != NULL && ShellObtenidoEnPop3->getPosition().x < 800 && BoolPilaEnemigo4 == true)
	{
		ShellObtenidoEnPop3->setPosition(ShellObtenidoEnPop3->getPosition().x + 9, ShellObtenidoEnPop3->getPosition().y);
	}


	if (ShellObtenidoEnPop3 != NULL && ShellObtenidoEnPop3->getPosition().x > 750 && BoolPilaEnemigo4 == true)
	{
		PushShell(pilaEnemigo5, depositarShell6);

		if (pilaEnemigo5 != NULL)
		{
			pilaEnemigo5->pos2(depositarShell6, pilaEnemigo3->color);
		}

		ShellObtenidoEnPop3 = NULL;

		if (depositarShell6 == 3) {

			BoolPilaEnemigo4 = false;
			depositarShell5 = 4;
			depositarShell6 = -1;
		}
	}
}

//-----------------------------------------------------------------Colas.

void Juego::UpdateCola() //Update de la Cola 1.
{
	if (ShellRemovido == NULL && primerShellCola1 != NULL) //Si el Shell Removido es NULL y el Primer Shell de la Cola 1 no es NULL.
	{
		RemoverShell(primerShellCola1, ultimoShellCola1, ShellRemovido); //Remuevo el Shell.
	}

	else if (ShellRemovido != NULL && ShellRemovido->getPosition().x < 820) //Muevo el Shell horizontalmente.
	{
		ShellRemovido->setPosition(ShellRemovido->getPosition().x + 7, ShellRemovido->getPosition().y);
	}

	if (ShellRemovido != NULL && ShellRemovido->getPosition().x > 800)
	{
		LoadCola(primerShellCola1, ultimoShellCola1); //Cargo la Cola.

		if (primerShellCola1 != NULL && primerShellCola1->siguienteShell != NULL) //Muevo de lugar los Shells para que vayan rotando.
		{
			primerShellCola1->siguienteShell->posNuevas4(1, *primerShellCola1->siguienteShell->color);
			primerShellCola1->siguienteShell->siguienteShell->posNuevas4(2, *primerShellCola1->siguienteShell->siguienteShell->color);
			primerShellCola1->siguienteShell->siguienteShell->siguienteShell->posNuevas4(3, *primerShellCola1->siguienteShell->siguienteShell->siguienteShell->color);
		}

		delete ShellRemovido; //Elimino el Shell removido.
		ShellRemovido = NULL; //El Shell removido se vuelve Null para que inicie de nuevo el loop.
	}
}

void Juego::UpdateCola2() //Update de la Cola 2.
{
	if (ShellRemovido2 == NULL && primerShellCola2 != NULL)
	{
		RemoverShell(primerShellCola2, ultimoShellCola2, ShellRemovido2);
	}

	else if (ShellRemovido2 != NULL && ShellRemovido2->getPosition().x > -10)
	{
		ShellRemovido2->setPosition(ShellRemovido2->getPosition().x - 9, ShellRemovido2->getPosition().y);
	}

	if (ShellRemovido2 != NULL && ShellRemovido2->getPosition().x < 0)
	{
		LoadCola2(primerShellCola2, ultimoShellCola2);

		if (primerShellCola2 != NULL && primerShellCola2->siguienteShell != NULL)
		{
			primerShellCola2->siguienteShell->pos3(2, *&primerShellCola2->siguienteShell->color);
			primerShellCola2->siguienteShell->siguienteShell->pos3(1, *&primerShellCola2->siguienteShell->siguienteShell->color);
			primerShellCola2->siguienteShell->siguienteShell->siguienteShell->pos3(0, *&primerShellCola2->siguienteShell->siguienteShell->siguienteShell->color);
		}

		delete ShellRemovido2;
		ShellRemovido2 = NULL;
	}
}

void Juego::UpdateCola3() //Update de la Cola 3.
{

	if (ShellRemovido3 == NULL && primerShellCola3 != NULL)
	{
		RemoverShell(primerShellCola3, ultimoShellCola3, ShellRemovido3);
	}

	else if (ShellRemovido3 != NULL && ShellRemovido3->getPosition().x < 820)
	{
		ShellRemovido3->setPosition(ShellRemovido3->getPosition().x + 7, ShellRemovido3->getPosition().y);
	}

	if (ShellRemovido3 != NULL && ShellRemovido3->getPosition().x > 800)
	{
		LoadCola(primerShellCola3, ultimoShellCola3);

		if (primerShellCola3 != NULL && primerShellCola3->siguienteShell != NULL)
		{
			primerShellCola3->siguienteShell->posNuevas5(1, *&primerShellCola3->siguienteShell->color);
			primerShellCola3->siguienteShell->siguienteShell->posNuevas5(2, *&primerShellCola3->siguienteShell->siguienteShell->color);
			primerShellCola3->siguienteShell->siguienteShell->siguienteShell->posNuevas5(3, *&primerShellCola3->siguienteShell->siguienteShell->siguienteShell->color);
		}

		delete ShellRemovido3;
		ShellRemovido3 = NULL;
	}
}