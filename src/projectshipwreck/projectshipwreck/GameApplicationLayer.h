#ifndef GAMEAPPLICATIONLAYER_H_
#define GAMEAPPLICATIONLAYER_H_

/////////////////////////////////////////////////////////////////////////////////////////////
// In dieser Klasse wird der MainLoop des Spiels als Funktion gespeichert. Sie ist also	   //
//  die einzige Klasse, die der Main bekannt ist. Weiter Funktionen sind das Speichern des //
// events f�r den Eventhandler.In der Main wird ein Objekt dieser Klasse als MainGameSource//													   //
// gespeichert.																			   //
/////////////////////////////////////////////////////////////////////////////////////////////

#include "S_Resourcemanager.h"
#include "S_EventHandler.h"
#include "S_GameModes.h"
#include "Update.h"
#include "SaveAndLoad.h"

namespace ProjectShipwreckHighClass
{

	class GameApplicationLayer
	{
	private:
		SDL_Event GameMainEvent;// Das Hauptevent des SPiels, dass an den Eventhandler als Parameter �bergeben wird
		bool b_GameShutDown;// Bool ist zust�ndig f�r das Herunterfahren des Spiels
		ProjectShipwreckLowClass::Update * p_GameUpdateSource;
	public:
		GameApplicationLayer():b_GameShutDown(false){p_GameUpdateSource = new ProjectShipwreckLowClass::Update();}//Der Konstruktor der GameApplicationKlasse, er tut eigentlich nichts
		~GameApplicationLayer(){delete p_GameUpdateSource;}//Der Dekonstruktor der GameApplicationKlasse, er tut eigentlich nichts
		GameApplicationLayer(const GameApplicationLayer &){p_GameUpdateSource = new ProjectShipwreckLowClass::Update();}// Der Kopierkonstruktor der Klasse GameAppliactionLayer
		GameApplicationLayer & operator=(const GameApplicationLayer &){p_GameUpdateSource = new ProjectShipwreckLowClass::Update();}
		void main_Loop();// Diese Funktion beinh�lt den �bergeordneten Verlauf des Spiels, das Spiel wird darin ausgef�hrt
		void initialize_GameResources();// Initialisiert alle Game relevanten Datein, lie�t Spielerdaten ein und l�d eventuelle Spielst�nde
		void close_GameResources();// Sicheres Schlie�en der Applikation


	};

}


#endif


//------------------------------------------------------END OF FILE--------------------------------------------------------------------------------------