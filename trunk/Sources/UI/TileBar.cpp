#ifdef EDITOR
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

#include "TileBar.h"

#include <vector>
#include <utility>
#include <cassert>

#include "../NEngine/Sprite.h"
#include "../NEngine/SpriteLoader.h"
#include "../NEngine/SpriteFactory.h"
#include "../NEngine/Renderer.h"

#include "../Engine/AnimatedSprite.h"
#include "../Game/Tile.h"
#include "../Utils/Logger.h"

#include "../NEngine/Exceptions/ConstructionFailedException.h"

#include "../globals.h"

TileBar :: TileBar(NE::SpriteLoader* const pSL, NE::SpriteFactory* const pSF, std::vector<View*>& listTiles, const USize2& windowSize)
:windowSize(windowSize)
{
	unsigned int barHeight = 64;
	unsigned int maximumX = 0;
	
	
	pBarSprite = pSF->createSpriteFromColour(Colour(0x00000080),USize2(windowSize.width,barHeight));
    if ( pBarSprite == NULL )
    {
        ConstructionFailedException("TileBar");
        return;
    }

	// Search the maximum positionX to know the size of the vector
	for ( std::vector<View*>::const_iterator itTile = listTiles.begin() ; itTile != listTiles.end() ; ++itTile )
	{
		if ( static_cast<int>(maximumX) < (*itTile)->positionX )
			maximumX = static_cast<unsigned int>((*itTile)->positionX);
	}
	assert(maximumX+1<=listTiles.size());
	// Resize the vectore to contain the good number of elements
	for ( unsigned int i = 0 ; i < maximumX+1 ; i++ )
	{
		viewList.push_back(std::vector<View*>());
	}

	// Load all the animation needed by the TileBar
	for ( std::vector<View*>::iterator itTile = listTiles.begin() ; itTile != listTiles.end() ; ++itTile )
	{
		int abstractPositionX = (*itTile)->positionX;
			
		(*itTile)->positionX = TILE_BAR_XMARGIN * (1 + (*itTile)->positionX * 2) + 32 * (*itTile)->positionX;

		viewList[abstractPositionX].push_back(*itTile);
	}

	// Load the cursor
	pBarCursor = pSL->loadSpriteFromFile("./data/gfx/tilebar_cursor.png");

	// Load the arrows
	pBarArrows = new AnimatedSprite(pSL->loadSpriteFromFile("./data/gfx/tilebar_arrows.png"),USize2(45,45),300);

	// Final settings
	counterMovementAnim = 0;
	limit =  (viewList[0][0]->getSprite()->getSize().width + TILE_BAR_XMARGIN*2) * viewList.size();
	positionY = windowSize.height;
	state = TBS_Closed;
	currentX = 5;
	currentY = 0;
	// Speed
	stepX = windowSize.width / 80;
	stepY = windowSize.height / 60;

	LDebug << "TileBar created";
}

TileBar :: ~TileBar(void)
{
	delete pBarArrows;

	for ( std::vector<std::vector<View*> >::const_iterator itListView = viewList.begin() ; itListView != viewList.end() ; ++itListView )
	{
		for ( std::vector<View*>::const_iterator itPView = itListView->begin() ; itPView != itListView->end() ; ++itPView )
		{
			delete (*itPView);
		}
	}

	LDebug << "TileBar deleted";
}

void TileBar ::  moveLeft()
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: moveLeft()";
		counterMovementAnim = TILE_DEFAULT_WIDTH + TILE_BAR_XMARGIN * 2;

		state = TBS_MoveLeft;
	
		currentX--;
		if ( currentX < 0 )
		{
			currentX = viewList.size() - 1;
		}
	}
}

void TileBar ::  moveRight()
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: moveRight()";
		
		counterMovementAnim = TILE_DEFAULT_WIDTH + TILE_BAR_XMARGIN * 2;

		state = TBS_MoveRight;
	
		currentX++;
		if ( currentX >= static_cast<int>(viewList.size()) )
		{
			currentX = 0;
		}
	}
}

void TileBar :: moveUp(void)
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: moveUp()";

		currentY++;
	}
}

void TileBar :: moveDown(void)
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: moveDown()";

		currentY--;
	}
}

void TileBar :: open(void)
{
	if ( state == TBS_Closed )
	{
		LDebug << "TileBar :: open()";

		state = TBS_Opening;
	}
}

void TileBar :: move(const NE::InputManager::ArrowsDirection direction)
{
	switch(direction)
	{
		case NE::InputManager::AD_UP:
			moveUp();
			break;
		case NE::InputManager::AD_DOWN:
			moveDown();
			break;
		case NE::InputManager::AD_LEFT:
			moveLeft();
			break;
		case NE::InputManager::AD_RIGHT:
			moveRight();
			break;
		// Remove warnings (we don't mind about the others directions)
		default:
			break;
	}
}

void TileBar :: close(void)
{
	if ( state == TBS_Opened )
	{
		LDebug << "TileBar :: close()";

		state = TBS_Closing;
	}
}

bool TileBar :: draw(const NE::Renderer& r, const unsigned int time)
{
	bool isOk = true;

	IVec2 barPosition( 0 , positionY);

	LDebug << "TileBar :: draw()";

	if ( state != TBS_Closed )
	{
		isOk &= r.drawSurface(barPosition,*pBarSprite);
	}
	
	if ( state == TBS_Opened || state == TBS_MoveLeft || state == TBS_MoveRight )
	{
        unsigned int spriteWidth = viewList[currentX][0]->getSprite()->getSize().width;
		unsigned int selectedTileXPosition = windowSize.width / 2 - spriteWidth / 2;
		unsigned int xOffset = 0;
		if ( currentX-1 >= 0 )
		{
			xOffset = (windowSize.width / 2 - spriteWidth / 2) - viewList[currentX-1][0]->positionX;
		}
		else
		{
			xOffset = (windowSize.width / 2 - spriteWidth / 2) - viewList[viewList.size()-1][0]->positionX;
		}
		IVec2 cursorPosition(windowSize.width / 2 - pBarCursor->getSize().width/2, positionY + TILE_BAR_HEIGHT / 2 - pBarCursor->getSize().height/2);

		// Display the Tiles
		for ( unsigned int i = 0 ; i < viewList.size() ; i++ )	// TILE_NB_DRAWN + 1 because we are drawing one extra tile, to avoid some nasty effect when sliding
		{
			// Calculation of the offset for sprite with higher size than normal Tile (e.g.: Mountains)
			unsigned int yOffset = viewList[i%viewList.size()][currentY%viewList[i%viewList.size()].size()]->getSprite()->getSize().height - TILE_DEFAULT_HEIGHT;

			IVec2 tilePosition(viewList[i%viewList.size()][0]->positionX, positionY + TILE_BAR_YMARGIN *2);
			// Offset, because we are drawing one before the first visible
			tilePosition.x -= TILE_BAR_XMARGIN *2 + viewList[i%viewList.size()][0]->getSprite()->getSize().width;

			if ( state == TBS_Opened )
			{
				// The currently selected sprite will be centered in the cursor
				if ( static_cast<int>(i) == currentX )
				{
					tilePosition.x = windowSize.width / 2 - viewList[i%viewList.size()][0]->getSprite()->getSize().width / 2;
				}

				// The following sprite after the selected one have to be offseted to continue the TileBar correctly
				if ( tilePosition.x > static_cast<int>(selectedTileXPosition) )
				{
					tilePosition.x += xOffset;
				}
			}

			// Apply offset for the sprite with non standard size
			tilePosition.y -= yOffset;

			// Remove little bug that one sprite is visible on the bound left
			if ( state != TBS_Opened || tilePosition.x > 0 )
			{
				isOk &= viewList[i%viewList.size()][currentY%viewList[i%viewList.size()].size()]->getSprite()->draw(r,tilePosition,time);
			}
		}

		// Draw the cursor
		isOk &= r.drawSurface(cursorPosition,*pBarCursor);
		// Draw the arrow if needed
		if ( viewList[currentX].size() > 1 && state == TBS_Opened )
		{
			isOk &= pBarArrows->draw(r,cursorPosition);
		}
	}

	return isOk;
}

void TileBar :: update(const unsigned int time)
{
#ifdef VERBOSE
	LDebug << "TileBar :: update()";
#endif

	switch (state)
	{
		case TBS_Closing:
			positionY+=stepY;
			if ( positionY >= windowSize.height )
			{
				state = TBS_Closed;
			}
			break;
		case TBS_Opening:
			positionY-=stepY;
			if ( positionY <= windowSize.height - 64 )
			{
				state = TBS_Opened;
			}
			break;
		case TBS_MoveRight:
			if ( counterMovementAnim > static_cast<int>(stepX) )
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						(*itASprites)->positionX-=stepX;
					}
				}
				counterMovementAnim-=stepX;
			}
			else
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						(*itASprites)->positionX-=counterMovementAnim;
					}
				}
				counterMovementAnim-=counterMovementAnim;
			}

			if ( counterMovementAnim <= 0 )
			{
				// Final check to move the sprites from back to front
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						if ( (*itASprites)->positionX < 0 )
						{
							(*itASprites)->positionX = (limit - (TILE_BAR_XMARGIN + (*itASprites)->getSprite()->getSize().width));
						}
					}
				}
				state = TBS_Opened;
			}
			break;
		case TBS_MoveLeft:
			if ( counterMovementAnim > static_cast<int>(stepX) )
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						(*itASprites)->positionX+=stepX;
					}
				}

				counterMovementAnim-=stepX;
			}
			else
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						(*itASprites)->positionX+=counterMovementAnim;
					}
				}
				counterMovementAnim-=counterMovementAnim;
			}

			if ( counterMovementAnim <= 0 )
			{
				for ( std::vector<std::vector<View*> >::iterator itVectorASprites = viewList.begin() ; itVectorASprites != viewList.end() ; ++itVectorASprites )
				{
					for ( std::vector<View*>::iterator itASprites = itVectorASprites->begin() ; itASprites != itVectorASprites->end() ; ++itASprites )
					{
						if ( (*itASprites)->positionX > static_cast<int>(limit) )
						{
							(*itASprites)->positionX -= limit;
						}
					}
				}

				state = TBS_Opened;
			}
			break;
		// Remove warnings (static case)
		case TBS_Opened:
		case TBS_Closed:
			break;
	}
}

#endif // EDITOR
