#include "mx.h"

extern mxHwnd mxhwnd;
extern mxPaint paint;
extern mxFont font;
extern int linenum;

extern const char* getPath(const char*);
extern void gameover();

#include"mx.h"
#include<cstring>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>
using namespace std;

#ifndef _WIN32
#include<unistd.h>
#endif

#define INTRO 1
#define START 2
#define OPTIONS 3
#define CREDITS 4
#define GAME 5
#define HIGHSCORES 6
