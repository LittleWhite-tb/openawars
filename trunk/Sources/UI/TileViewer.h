#ifndef __TILEVIEWER_H__
#define __TILEVIEWER_H__

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

#include "Game/GameState/GameObjects/Tile.h"

#include "Types/Size2.h"
#include "Types/Vec2.h"

namespace NE { class Sprite; }
namespace NE { class Renderer; }

class Theme;
class AnimatedSprite;
class Font;

class Tile;
class UnitTemplate;

class TileViewer
{
private:

	Font* pFont;				/*!< the font to use */
	AnimatedSprite* pBackground;		/*!< the sprite for the background */
	AnimatedSprite* pTileSprite;	/*!< the tile to display in the UI */

	std::string title;				/*!< the title to display */
	std::string tileName;			/*!< the name for the tile to display */

	USize2 windowSize;				/*!< The window size */
	IVec2 position;					/*!< the UI position */

public:
	TileViewer(const Theme* pTheme, const USize2& windowSize);
	~TileViewer();

	void setTile(const Tile* pTile);
	void setTile(const UnitTemplate* pUnitTemplate);

	void setTitle(const std::string& title) { this->title = title; }

	void putOnLeft(void);
	void putOnRight(void);

	bool draw(const NE::Renderer& r, const unsigned int time);
};

/*! \class TileViewer TileViewer.h "Engine/TileViewer.h"
 *  \brief viewer for Tile for the editor to indicate which tile is selected
 *
 *	We can:
 *		- Change the title
 *		- Change the position ( on left or right of the screen )
 *		- Change the tile
 */

/*! \fn TileViewer::TileViewer(NE::SpriteLoader* const pSL, const std::string& fileNameBackground, const std::string& fileNameFont, const USize2& windowSize)
 * Will load the font and the background
 * \param pSL The SpriteLoader to use to load the background
 * \param fileNameBackground The file for the background
 * \param fileNameFont The file for the font
 * \param windowSize the size of the window (used as reference to place the viewer)
 */

/*! \fn TileViewer::~TileViewer(void)
 */

/*! \fn void TileViewer::setTile(AnimatedSprite* const pTileSprite, const std::string tileName)
 * \brief Set the tile to display
 * \param pTileSprite the new sprite to display
 * \param tileName the name of the tile to display
 */

/*! \fn void TileViewer::setTitle(const std::string& title)
 * \brief Set a new title to display
 * \param title the new title
 */

/*! \fn void TileViewer::putOnLeft(void)
 * \brief Set the UI on the left of the screen
 */

/*! \fn void TileViewer::putOnRight(void)
 * \brief Set the UI on the right of the screen
 */

/*! \fn bool TileViewer::draw(const NE::Renderer& r)
 * draw the UI
 * \param r the NE::Renderer to use to draw the viewer
 * \return true if all goes right
 */

#endif
