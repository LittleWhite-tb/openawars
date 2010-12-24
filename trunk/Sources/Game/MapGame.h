#ifndef __MAPGAME_H__
#define __MAPGAME_H__

#ifndef DOXYGEN_IGNORE_TAG
/**
OpenAWars is an open turn by turn strategic game aiming to recreate the feeling of advance (famicon) wars (c)
Copyright (C) 2010  Alexandre LAURENT

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

#include <string>

#include "Map.h"

#include "Unit.h"

class Renderer;
class SpriteManager;
class Camera;

class MapGame : public Map
{
    struct TileEffect
    {
        bool isHighlight;
        bool isAttackable;
        
        TileEffect():isHighlight(false),isAttackable(false) {}
        void clear(void) { isHighlight = false ; isAttackable = false; }
    };
    
private:
	Unit*** unitMap;			/*!< Map of units logical information */
    TileEffect** effectMap;     /*!< Map containing information for the additionnal effect */
    
    Sprite* pHighlightSprite;   /*!< Sprite used for highlighting the map */
    Sprite* pAttackableSprite;  /*!< Sprite used for highlighting where the player can attack the map */

public:
	MapGame(SpriteManager& sm, const std::string& fileName, const std::string& fileNameHighlight, const std::string& fileNameAttackable);
	~MapGame();

	bool draw(const Renderer& r, const Camera& c, const unsigned int time);

	void enableUnits(void);

	bool setTile(const UVec2& position, const UnitType unitType);
	const Unit* getUnit(const UVec2& position);

    bool move(const UVec2& origPosition, const UVec2& destPosition);
    
    void setMoveHighlight(const UVec2& origPosition, const UnitType ut, const int movement);
    void setAttackableHighLight(const UVec2& origPosition);
    
    void clearHighlight(void);
};

/*! \class MapGame MapGame.h "Game/MapGame.h"
 *  \brief Map implementation for the game
 *
 * This implementation adds a new map containing the information of all units (fuel, life...)
 * The class is reimplementing the draw function (to draw enabled/disabled unit) and 
 * the setTile function (to get logical unit in the unitMap)
 */

/*! \fn MapGame::MapGame(SpriteManager& sm, const std::string& fileName, const std::string& fileNameHighlight, const std::string& fileNameAttackable)
 * Load the map
 * \param sm the SpriteManager to load the sprites
 * \param fileName the name of the file for the map to load
 * \param fileNameHighlight the name of the sprite to load for highlighting the cells
 * \param fileNameAttackable the name of the sprite to load for attackable cells
 */		

/*! \fn MapGame::~MapGame()
 */

/*! \fn bool MapGame::draw(const Camera& c, const unsigned int time)
 * \brief Draw the map
 * \param c The Camera (used to draw the correct part of the Map)
 * \param time the actual time (for animation)
 * \return true if all goes right
 */

/*! \fn void MapGame::enableUnits(void)
 * \brief Enable all units in the map
 */

/*! \fn bool MapGame::setTile(const UVec2& position, const UnitType unitType)
 * \brief Set the Unit at the position
 * Will overwrite the Unit previously contained on the map by the new one.
 * The new Unit is selected following the internal logic of the editor.
 * \param position the position where to change the tile
 * \param unitType the type of the new unit
 * \return true if all goes right
 */

/*! \fn const Unit* MapGame::getUnit(const UVec2& position)
 * \brief Get the Unit at the position
 * \param position the position where to get the unit
 * \return the pointer on the unit
 */

/*! \fn bool MapGame::move(const UVec2& origPosition, const UVec2& destPosition)
 * \brief Move the unit to a new position
 * \param origPosition the position of the unit
 * \param destPosition the position of the unit after moving it
 * \return true if it was possible to move it
 */

/*! \fn void MapGame::setMoveHighlight(const UVec2& origPosition, const UnitType ut, const int movement)
 * \brief Set the move possibility for the unit at the origPosition
 * \param origPosition the position where the unit to move is
 * \param ut the type of the unit to move
 * \param movement the movement length
 */

/*! \fn void MapGame::setAttackableHighLight(const UVec2& origPosition)
 * \brief Set the attack possibility for the unit at the origPosition
 * \param origPosition the position where the unit to move is
 */

/*! \fn void MapGame::clearHighlight(void)
 * \brief Clear the highlight effect on the map
 */

#endif