#ifndef __NENGINE_H__
#define __NENGINE_H__

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

#include "NETypes.h"
#include "../Types/Vec2.h"

#include <string>

struct Colour;
struct Rect;

class NEngine
{
private:

public:
	virtual ~NEngine() {}

	// Windowing
	virtual Window* createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const bool isOpenGL)=0;
	virtual USize2 getWindowSize(const Window* const pWin)=0;
	virtual int getBitsPerPixel(const Window* const pWin)=0;
	virtual void destroyWindow(Window* const pWin)=0;

	virtual bool isCursorVisible(void)const=0;
	virtual void setCursorVisible(const bool mustShowCursor)const=0;
	virtual void setCaption(const std::string& windowName, const std::string& iconName)const=0;

	virtual bool needWindowClosure(void)const=0;

	// Drawing
	virtual USize2 getSurfaceSize(const Surface* const pSurface)=0;

	virtual bool clearScreen(Window* const pWin, const Colour& colour)=0;

	virtual bool drawTile(Window* const pWin, const Rect& tile, const Colour& colour)const=0;
	virtual bool drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface)=0;
	virtual bool drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Colour& mask)=0;
	// virtual bool drawSurface(Window* const pWin, const Rect& destRect, Surface* const pSurface)=0;
	virtual bool drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Rect& srcRect)=0;
	virtual bool drawSurface(Window* const pWin, const IVec2& position, Surface* const pSurface, const Rect& srcRect, const Colour& mask)=0;
};

/*! \class NEngine NEngine.h "NEngine/NEngine.h"
 *  \brief Interface describing how to implement a NEngine for the application
 *
 * By saying this class as interface, it means that it is a virtual pure class.
 * Each inheritency of this class should reimplement all functions described here to give a complete wrapper for the application upper the graphical library
 * The class handle all basics needed by a game application such as:
 *		- Window
 *		- Drawing operations
 *		- Inputs handling
 *		- Pictures loading
 *		- Font management
 */

/*! \fn virtual NEngine::~NEngine()
 */

/*! \fn virtual Window* NEngine::createWindow(const USize2& winSize, const unsigned short bpp, const bool isFullscreen, const bool isOpenGL)=0
 * \brief Create a window where to render
 * \param winSize the size of the window
 * \param bpp the Bits per pixel wanted
 * \param isFullscreen true if the window should be fullscreen
 * \param isOpenGL true if the window should be compatible with OpenGL
 * \return a pointer to the window
 */

/*! \fn virtual USize2 NEngine::getWindowSize(const Window* const pWin)=0
 * \brief Get the size of the Window
 * \param pWin a pointer to the window
 * \return the size of the window
 */

/*! \fn virtual int NEngine::getBitsPerPixel(const Window* const pWin)=0
 * \brief Get the number of bits per pixel of the Window
 * \param pWin a pointer to the window
 * \return the number of bits per pixel
 */

/*! \fn virtual void NEngine::destroyWindow(Window* const pWin)=0
 * \brief Destroy the Window
 * \param pWin pointer on the window to destroy
 */

/*! \fn virtual bool NEngine::isCursorVisible(void)const=0
 * \brief Get if the cursor is visible
 * \return true if the cursor is visible
 */

/*! \fn virtual void NEngine::setCursorVisible(const bool mustShowCursor)const=0
 * \brief Set the visibility of the cursor
 * \param mustShowCursor true if the cursor must be visible
 */

/*! \fn virtual void NEngine::setCaption(const std::string& windowName, const std::string& iconName)const=0
 * \brief Set the name and icon for the Window
 * \param windowName the new name of the window
 * \param iconName the path to the icon
 */

/*! \fn virtual bool NEngine::needWindowClosure(void)const=0
 * \brief Get if the window has to be closes (after the user clicked on the red cross)
 * \return true if the window should be closed
 */

#endif