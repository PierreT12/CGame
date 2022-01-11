#define OPENGLSTUFF_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>		
#include "glut.h"
#include "openglframework.h"
#include "openglstuff.h"






void initOpenGLDrawing( GL_Window *window, Keys *keys, float backRed, float backGreen, float backBlue)
{
	glClearColor(backRed, backGreen, backGreen, 0.0f);			// Background Color
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);			// Enable Alpha Blending
	glEnable(GL_BLEND);											// Enable Blending
	glEnable(GL_TEXTURE_2D);									// Enable Texture Mapping
	glEnable(GL_CULL_FACE);										// Remove Back Face
	
	g_window	= window;
	g_keys		= keys;
}
void endOpenGLDrawing()
{
	glFlush();
}

//Draws all Start Screen Sprites
void startOpenGLDrawingStartScreen(Sprite* background, Sprite* title)
{
	glClear(GL_COLOR_BUFFER_BIT);

	background->render();
	title->render();


	glLoadIdentity();
}

//Draws all Game Over Screen Sprites
void startOpenGLDrawingGameOverScreen(Sprite* background, Score* playerOneScore, Score* playerTwoScore, Sprite* winner)
{
	glClear(GL_COLOR_BUFFER_BIT);

	background->render();


	playerOneScore->render();
	playerTwoScore->render();

	winner->render();

	glLoadIdentity();
}


//How the normal game loop is rendered (This is kinda complicated)
// -The background picture (The one with the mountains)
// -Renders the Map
//		- Floor (Won't be seen)
//		- Sprite that the player sees as the floor
//		- Enemies/Powerups/Hazards
//	- Player Character
// -Scoreboard Plate
// - Actual Score
// - Item Holder

//Draws the main game loop Sprites 
void startOpenGLDrawing(MainPlayers* playerOne, MainPlayers* playerTwo, GL_Window* window, MapGen* POneMap, MapGen* PTwoMap)
{
		// Clear the window
	glClear(GL_COLOR_BUFFER_BIT);

	//We need to shift the viewport to draw the split screen
	for (int i = 0; i < 2; i++)
	{
		if (i == 0)
		{
			
			//Gets the bounds for the camera
			GLdouble left = (playerOne->getSprite()->getPosition()->x - (window->init.width * 2.0));
			GLdouble right = (playerOne->getSprite()->getPosition()->x + (window->init.width * 2.0));
			GLdouble top = (playerOne->getSprite()->getPosition()->y - (window->init.height * 2.0) + 750);
			GLdouble bottom = (playerOne->getSprite()->getPosition()->y + (window->init.height * 2.0));


			//Sets the viewport to the upper part of the screen
			glViewport(0, 400, (GLsizei)(window->init.width), (GLsizei)(window->init.height /2.0));

			glMatrixMode(GL_PROJECTION);										// Select The Projection Matrix
			glLoadIdentity();													// Reset The Projection Matrix

			//Set the camera
			gluOrtho2D(left, right, top, bottom);
			//Loads in the modelview
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			//Always make sure that the background renders in first
			playerOne->GetBackground()->render();

			POneMap->render(playerOne->getSprite());

			playerOne->render();

			playerOne->getScoreBoard()->getSpritePlate()->render();

			playerOne->getScoreBoard()->render();

			playerOne->GetHolder()->render();


		}
		//Does the same for the lower portion of the screen
		if (i == 1)
		{
			//Gets the bounds for the camera
			GLdouble left = (playerTwo->getSprite()->getPosition()->x - (window->init.width * 2.0));
			GLdouble right = (playerTwo->getSprite()->getPosition()->x + (window->init.width * 2.0));
			GLdouble top = (playerTwo->getSprite()->getPosition()->y - (window->init.height * 2.0) + 750);
			GLdouble bottom = (playerTwo->getSprite()->getPosition()->y + (window->init.height * 2.0));


			//Sets the viewport to the lower part of the screen
			glViewport(0, 0, (GLsizei)(window->init.width), (GLsizei)(window->init.height / 2.0));

			glMatrixMode(GL_PROJECTION);										// Select The Projection Matrix
			glLoadIdentity();													// Reset The Projection Matrix
			
			//Set the camera
			gluOrtho2D(left, right, top, bottom);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			playerTwo->GetBackground()->render();


			PTwoMap->render(playerTwo->getSprite());


			playerTwo->render();


			playerTwo->getScoreBoard()->getSpritePlate()->render();

			playerTwo->getScoreBoard()->render();

			playerTwo->GetHolder()->render();

		}

		


		
		
	}


}