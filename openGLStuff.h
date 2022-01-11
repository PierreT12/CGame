#include "MainPlayers.h"
#include "Attack.h"
#include "MapGen.h"

#ifdef OPENGLSTUFF_CPP
#define extern 
#endif

void endOpenGLDrawing();
void startOpenGLDrawing(MainPlayers* playerOne, MainPlayers* playerTwo, GL_Window* window, MapGen* POneMap, MapGen* PTwoMap);
void startOpenGLDrawingStartScreen(Sprite* background, Sprite* title);
void startOpenGLDrawingGameOverScreen(Sprite* background, Score* playerOneScore, Score* playerTwoScore, Sprite* winner);
void initOpenGLDrawing( GL_Window *window, Keys *keys, float backRed, float backGreen, float backBlue);

extern GL_Window*	g_window;
extern Keys*		g_keys;

#undef extern