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

#include <iostream>

#include <SDL/SDL.h>

#include "Engine/Window.h"

#include "Utils/Logger.h"

int main(int argc, char** argv)
{
	(void)argc;
	(void)argv;

	// Starting SDL
	if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
	{
		LError << "Error while initializing SDL -> SDL_INIT_VIDEO";
		return 1;
	}

	{
		Window win;
		std::vector<ResolutionInfo> riList;

		win.getResolutionsAvailable(false,riList);

		// Window test
		win.openWindow(640,480,32,false,false);
		SDL_Delay(1000);
		win.changeResolution(800,600,32,false,true);
		SDL_Delay(1000);
		win.changeResolution(640,480,32,true,false);
		SDL_Delay(1000);
		win.changeResolution(800,600,32,true,true);
		SDL_Delay(1000);
		win.changeResolution(812,200,32,true,false);
		SDL_Delay(1000);
	}

	// Bye bye SDL
	SDL_Quit();

	Logger::deleteLogger();

	return 0;
}