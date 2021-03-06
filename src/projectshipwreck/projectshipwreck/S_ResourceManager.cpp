#include "S_ResourceManager.h"
using namespace ProjectShipwreckHighClass;

void S_ResourceManager::LoadImage(e_Image key, string filename) {
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;

	try {
		loadedImage = IMG_Load(filename.c_str());
		if(loadedImage == NULL) {
			throw "<RessourceManager::LoadImage>: Cannot find image. Maybe a wrong filename?";
		}

		optimizedImage = SDL_DisplayFormat(loadedImage);
		if(optimizedImage == NULL) {
			throw "<RessourceManager::LoadImage>: cannot optimize image";
		}
	}
	catch (char* strException) {
		cerr << "Error: " << strException << endl;
	}

	this->Pictures.insert(make_pair(key, optimizedImage)); // Save picture to a map together with a key file to access it

	// Free used space
	loadedImage = NULL;
	optimizedImage = NULL;
	SDL_FreeSurface( loadedImage );
	SDL_FreeSurface( optimizedImage );
}


void S_ResourceManager::LoadMusic(e_Audio key, string filename) {
	Mix_Music* loadedMusic = NULL;

	try {
		loadedMusic = Mix_LoadMUS(filename.c_str());
		if(loadedMusic == NULL) {
			throw "<RessourceManager::LoadMusic>: Cannot find soundfile. Maybe a wrong fielname?";
		}
	}
	catch (char* strException) {
		cerr << "Error: " << strException << endl;
	}

	this->Music.insert(make_pair(key, loadedMusic));
}


void S_ResourceManager::LoadSound(e_Audio key, string filename) {
	Mix_Chunk* loadedSound = NULL;

	try {
		loadedSound = Mix_LoadWAV(filename.c_str());
		if(loadedSound == NULL) {
			throw "<RessourceManager::LoadSound>: Cannot find soundfile. Maybe a wrong filename?";
		}
	}
	catch (char* strException) {
		cerr << "Error: " << strException << endl;
	}

	this->Sounds.insert(make_pair(key, loadedSound));
}


void S_ResourceManager::LoadFont(string filename, int size) {
	try {
		this->font = TTF_OpenFont(filename.c_str(), size);
		if(font == NULL) {
			throw "<RessourceManager::LoadFont>: Cannot find font. Maybe a wrong filename?";
		}
	}
	catch (char* strException) {
		cerr << "Error: " << strException << endl;
	}
}


void S_ResourceManager::ApplyPicture(int positionX, int positionY, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
	SDL_Rect Offset; // Used to store the x in y position in a SDL_Rect because SDL_BlitSurface only takes SDL_Rect

	Offset.x = positionX;
	Offset.y = positionY;

	try {
		if(SDL_BlitSurface(source, clip, destination, &Offset) == -1) { // Show the loaded picture on the screen
			throw "<RessourceManager::ApplySurface>: unable to blit surface";
		} 
	}
	catch (char* strException) {
		cerr << "Error: " << strException << endl;
	}
}


void S_ResourceManager::LoadContent() {
	cout << "Loading pictures..." << endl;
	LoadImage(key_background, "background.jpg");

	cout << "Loading music..." << endl;
	//LoadMusic();

	cout << "Loading sound files..." << endl;
	//LoadSound();

	cout << "Loading fonts..." << endl;
	//LoadFont();
}


void S_ResourceManager::Clean() {
	if(this->Pictures.size() > 0) {
		for(this->pictures_it = this->Pictures.begin(); this->pictures_it != this->Pictures.end(); ++this->pictures_it) {
			this->pictures_it->second = NULL;
			SDL_FreeSurface(this->pictures_it->second);
			this->pictures_it->second = NULL;
		}
	}

	if(this->Music.size() > 0) {
		for(this->music_it = this->Music.begin(); this->music_it != Music.end(); ++this->music_it) {
			this->music_it->second = NULL;
			Mix_FreeMusic(this->music_it->second);
			this->music_it->second = NULL;
		}
	}

	if(this->Sounds.size() > 0) {
		for(this->sounds_it = this->Sounds.begin(); this->sounds_it != Sounds.end(); ++this->sounds_it) {
			this->sounds_it->second = NULL;
			Mix_FreeChunk(this->sounds_it->second);
			this->sounds_it->second = NULL;
		}
	}

	this->Pictures.clear();
	this->Music.clear();
	this->Sounds.clear();

	//Close the font
    TTF_CloseFont( font );
    
    //Quit SDL_mixer
    Mix_CloseAudio();
    
    //Quit SDL_ttf
    TTF_Quit();
    
    //Quit SDL
    SDL_Quit();
}