#ifndef __NE_SPRITELOADER_H__
#define __NE_SPRITELOADER_H__

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

#include <map>
#include <string>

namespace NE
{
	class Sprite;
	class Scaler;

	class SpriteLoader
	{
    private:
    
        std::map<std::string, Sprite*> spritesBank;  /*!< Bank saving the Sprite loaded */
        
        Scaler* pScaler;                            /*!< Scaler to use after loading the Sprite */
        
    protected:
        virtual Sprite* loadSprite(const std::string& fileName)=0;
        
	public:
		virtual ~SpriteLoader(void);

		Sprite* loadSpriteFromFile(const std::string& fileName);
        
        void setSpriteScaler(Scaler* pScaler) { this->pScaler = pScaler; }
	};
}

/*! \class NE::SpriteLoader SpriteLoader.h "NEngine/SpriteLoader.h"
 *  \brief SpriteLoader interface
 *
 * The SpriteLoader class gives an interface to implement new platform specific Sprite loading functions.
 * To save loading time, the loader is using a bank to keep the Sprite already loaded. The second advantage of this, is that the memory deallocation has not to be done by the user.
 */

/*! \fn virtual Sprite* NE::SpriteLoader::loadSprite(const std::string& fileName)=0
 * \brief load a Sprite from a file
 * \param fileName the name of the file to load
 * \return a pointer to the newly loaded Sprite
*/

/*! \fn virtual NE::SpriteLoader::~SpriteLoader(void)
 */

/*! \fn virtual Sprite* NE::SpriteLoader::loadSpriteFromFile(const std::string& fileName)=0
 * \brief load a Sprite from a file, or return the corresponding Sprite if already loaded
 * \param fileName the name of the file to load
 * \return a pointer to the newly loaded Sprite
*/

#endif
