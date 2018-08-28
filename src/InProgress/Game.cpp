#include "Game.h"

void Game::Start(void) {

	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(1920,1080,32), "SpaceGameThing");
	_gameState = Game::Playing;
	
	while (!IsExiting()) {
		GameLoop();
	}

	_mainWindow.close();
}
bool Game::IsExiting() {

	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop() {

	sf::Event currentEvent;
	while(_mainWindow.GetEvent(currentEvent)) {
		
		switch (_gameState) {
		
			case Game::Playing:
				{
					_mainWindow.clear();
			
					_mainWindow.display();

					if (currentEvent.Type == sf::Event::Closed)
						_gameState = Game::Exiting;
				break;
				}
		}
	}
}


Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;	
