#ifndef __GAME_H__
#define __GAME_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010-2011  Alexandre LAURENT

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

website: http://code.google.com/p/openawars/
e-mail: lw.demoscene@gmail.com
**/
#endif

#include <map>
#include <string>

#include "Game/GameState.h"

#include "NEngine/InputManager.h"

#include "Types/Vec2.h"

#include "Engine/Library.h"
#include "Engine/Theme.h"

namespace NE { class NEngine; }
namespace NE { class Renderer; }

class Map;
class Camera;
class Cursor;

struct MenuView;
class MenuBox;
class ConstructBox;

class Game : public GameState
{
	enum GameState
	{
		GS_VISU,
		GS_CONSTRUCTION,
		GS_SELECT,
		GS_MENU,
        
        GS_MOVE
	};

private:

	Map* pMap;
	Camera* pCamera;
	Cursor* pCursor;					/*!< The cursor */

	// UI
	std::map<std::string, ConstructBox*> constructionBoxes;	/*!< Library of construct box determined by their names */

	MenuBox* pMBMenu;			/*!< menu for the user */

	GameState gState;			/*!< Actual state of the game */
    UVec2 selectedUnitPosition; /*!< Position of the unit selected (the one to move or to control) */

public:
	Game();
	~Game();

	bool load(NE::NEngine* pNE);
	bool loadMap(const Library<Theme>* const pThemes, const std::string& name);
	
	bool draw(NE::Renderer* pRenderer, unsigned int time);
	bool update(NE::InputManager::ArrowsDirection direction, NE::InputManager::Buttons buttons, unsigned int time);
};

/*! \class Game Game.h "Game/GameState/Game.h"
 *  \brief Game state displaying the game
 */

/*! \fn Game::Game()
 */

/*! \fn Game::~Game()
 */

/*! \fn bool Game::init()
 * \brief Init the Game Engine
 * \return true if all goes right
 */

/*! \fn bool Game::loadMap(const std::string& mapName)
 * \brief load a map in the game
 * \param mapName the name of the map to load
 * \return true if all goes right
 */

/*! \fn bool Game::run(void)
 * \brief Start the game main loop
 * \return true if all goes fine
 */

#endif
