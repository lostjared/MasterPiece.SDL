
#include"theheader.h"
// From an another game I wrote, minor changes


enum { D_DOWN = 1, D_UP = 2 };
enum { STARTX = 185 , STARTY = 95 };
enum { BLOCK_BLACK = 0, BLOCK_YELLOW, BLOCK_ORANGE, BLOCK_LTBLUE, BLOCK_DBLUE, BLOCK_PURPLE, BLOCK_PINK,BLOCK_GRAY,BLOCK_RED,BLOCK_GREEN,BLOCK_CLEAR, BLOCK_FADE };

// the game object
const int BR  = 5;
void getcords(int r, int c, int& rx, int& ry) {
    if (r < 0 || r >= 17 || c < 0 || c >= 8)
    {
        rx = -1;
        ry = -1;
        return;
    }
    rx = STARTX + (c * 32);
    ry = STARTY + (r * 16);
}
// contains the game grid
// which is were the game play occours
class Game  {
    
    public:
    
    bool paused;
    
    // games tile matrix
    class TileMatrix {
        
        public:
        
        struct GameData {
            
            unsigned long score;
            int lines;
            int speed;
            int lineamt;
            
            
            inline GameData()
            {
                newgame();
            }
            
            inline void newgame()
            {
                score = 0;
                lines = 0;
                speed = 20;
                lineamt = 0;
            }
            
            inline void addline()
            {
                lines++;
                score += 6;
                lineamt++;
                
                if(lineamt >= linenum)
                {
                    lineamt = 0;
                    speed = speed - 4;
                    if(speed < 4)
                    {
                        speed = 5;
                    }
                }
                
                //				shandle.sounds[1].Play();
                
            }
        };
        
        struct GameBlock {
            
            
            struct Color {
                int c1,c2,c3;
                
                inline void randcolor()
                {
                    c1 = rand()%10;
                    c2 = rand()%10;
                    c3 = rand()%10;
                    if(c1 == 0) { c1++; }
                    if(c2 == 0) { c2++; }
                    if(c3 == 0) { c3++; }
                    
                    
                    // were all the same
                    if(c1 == c2 && c1 == c3)
                    {
                        randcolor();// try again
                        return;
                    }
                }
                
                inline void copycolor(Color* c)
                {
                    c1 = c->c1;
                    c2 = c->c2;
                    c3 = c->c3;
                }
                
                // shift the colors up and down (true & false)
                inline void shiftcolor(bool dir)
                {
                    int ic1;
                    int ic2;
                    int ic3;
                    ic1 = c1;
                    ic2 = c2;
                    ic3 = c3;
                    
                    if(dir)
                    {
                        c1 = ic3;
                        c2 = ic1;
                        c3 = ic2;
                    }
                    else
                    {
                        c1 = ic2;
                        c2 = ic3;
                        c3 = ic1;
                    }
                }
                
            };
            
            Color color;
            Color nextcolor;
            
            int x,y;
            
            inline GameBlock()
            {
                color.randcolor();
                nextcolor.randcolor();
            }
            
            inline void NextBlock()
            {
                color.copycolor(&nextcolor);
                nextcolor.randcolor();
                x = 3;
                y = 0;
                
            }
            
            inline void MoveDown()
            {
                if( y < 16 )
                {
                    
                    y++;
                    
                }
            }
            
            inline void MoveLeft()
            {
                if(x > 0)
                {
                    x--;
                }
            }
            
            inline void MoveRight()
            {
                if(x < 7)
                {
                    x++;
                }
            }
            
            
        };
        
        GameData Game;
        GameBlock block;
        // breathing room
        int Tiles[17 + BR][8 + BR];
        
        inline void cleartiles()
        {
            
            
            for(int i = 0; i < 17; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if( i <= 16 && j <= 7)
                        Tiles[i][j] = 0;
                }
            }
            
        }
        
        // initilize the matrix, for a new game
        inline void init_matrix()
        {
            cleartiles();
            Game.newgame();
            block.NextBlock();
            
        }
        
        inline void setblock()
        {
            if ( block.y <= 0 )
            {
                gameover();
                //mxhwnd.setScreen(HIGHSCORES);
            }
            
            Tiles[ block.y ] [ block.x ] = block.color.c1;
            Tiles[ block.y+1 ] [ block.x ] = block.color.c2;
            Tiles[ block.y+2 ] [ block.x ] = block.color.c3;
            block.NextBlock();
            
        }
        
        // constructor
        
        inline TileMatrix()
        {
            cleartiles();
        }
        
        static const int FLASH_STEPS = 3;

        inline bool hasFlashing() const
        {
            for(int i = 0; i < 17; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if(Tiles[i][j] < 0)
                        return true;
                }
            }
            return false;
        }

        inline void ProccessBlocks()
        {
            for(int z = 0; z < 8; z++)
            {
                for(int i = 0; i < 16; i++)
                {
                    if(Tiles[i][z] > 0 && Tiles[i+1][z] == 0)
                    {
                        Tiles[i+1][z] = Tiles[i][z];
                        Tiles[i][z] = 0;
                    }
                }
            }
        }
        
        inline void flash_colors()
        {
            for(int i = 0; i < 17; i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    if(Tiles[i][j] < 0)
                    {
                        Tiles[i][j]++;
                        if(Tiles[i][j] >= 0)
                        {
                            Tiles[i][j] = 0; // clear after full flash cycle
                        }
                    }
                }
            }
        }
        
    };
    
    TileMatrix matrix;
    
    
    
    void load()
    {
        // lets load up are graphics
        grid_blocks[0].load(&mxhwnd,getPath("img/block_black.bmp"));
        grid_blocks[1].load(&mxhwnd,getPath("img/block_yellow.bmp"));
        grid_blocks[2].load(&mxhwnd,getPath("img/block_orange.bmp"));
        grid_blocks[3].load(&mxhwnd,getPath("img/block_ltblue.bmp"));
        grid_blocks[4].load(&mxhwnd,getPath("img/block_dblue.bmp"));
        grid_blocks[5].load(&mxhwnd,getPath("img/block_purple.bmp"));
        grid_blocks[6].load(&mxhwnd,getPath("img/block_pink.bmp"));
        grid_blocks[7].load(&mxhwnd,getPath("img/block_gray.bmp"));
        grid_blocks[8].load(&mxhwnd,getPath("img/block_red.bmp"));
        grid_blocks[9].load(&mxhwnd,getPath("img/block_green.bmp"));
        grid_blocks[10].load(&mxhwnd,getPath("img/block_clear.bmp"));
        gbg.load(&mxhwnd,getPath("img/gamebg.bmp"));
        matrix.init_matrix();
        paused = false;
    }
    
    
    void update()
    {
        draw();
        if(paused == true)
        {
            font.printText(20,20, "Game Paused press P To Continue.");
            return;
        }
        SDL_Delay(30);
        logic();
    }
    
    inline void draw()
    {
        gbg.display(0,0);
        drawmatrix();
        drawblock();
        std::ostringstream stream;
        stream << "Score: " << matrix.Game.score;
        font.printText(200,60,stream.str().c_str());
        stream.str("");
        stream << "Tabs: " << matrix.Game.lines;
        font.printText(310,60,stream.str().c_str());
    }
    
    inline void logic()
    {
        static int wait = 0;
        static unsigned int flash_tick = SDL_GetTicks();
        wait++;
        
        if(wait > matrix.Game.speed)
        {
            wait = 0;
            matrix.block.MoveDown();
        }
        
        if(SDL_GetTicks() - flash_tick > 1000)
        {
            matrix.flash_colors();
            flash_tick = SDL_GetTicks();
        }

        if(matrix.hasFlashing())
        {
            // wait until all flashing finish, then let gravity and block logic continue
            return;
        }

        matrix.ProccessBlocks();
        blockProc();
    }
    
    inline void blockProc()
    {
        if(matrix.block.y + 2 >= 16 || matrix.Tiles[matrix.block.y + 3][matrix.block.x] != 0)
        {
            matrix.setblock();
            return;
        }

        bool foundMatch = false;

        for(int i = 0; i < 17; i++)
        {
            for(int j = 0; j < 8 - 2; j++)
            {
                int cur_color = matrix.Tiles[i][j];
                if(cur_color > 0
                   && matrix.Tiles[i][j+1] == cur_color
                   && matrix.Tiles[i][j+2] == cur_color)
                {
                    matrix.Tiles[i][j] = -TileMatrix::FLASH_STEPS;
                    matrix.Tiles[i][j+1] = -TileMatrix::FLASH_STEPS;
                    matrix.Tiles[i][j+2] = -TileMatrix::FLASH_STEPS;
                    matrix.Game.addline();
                    foundMatch = true;
                }
            }
        }

        for(int z = 0; z < 8; z++)
        {
            for(int q = 0; q < 17 - 2; q++)
            {
                int cur_color = matrix.Tiles[q][z];
                if(cur_color > 0
                   && matrix.Tiles[q+1][z] == cur_color
                   && matrix.Tiles[q+2][z] == cur_color)
                {
                    matrix.Tiles[q][z] = -TileMatrix::FLASH_STEPS;
                    matrix.Tiles[q+1][z] = -TileMatrix::FLASH_STEPS;
                    matrix.Tiles[q+2][z] = -TileMatrix::FLASH_STEPS;
                    matrix.Game.addline();
                    foundMatch = true;
                }
            }
        }

        for(int p = 0; p < 8; p++)
        {
            for(int w = 0; w < 17; w++)
            {
                int cur_color = matrix.Tiles[w][p];
                if(cur_color > 0)
                {
                    if(w + 2 < 17 && p + 2 < 8
                       && matrix.Tiles[w+1][p+1] == cur_color
                       && matrix.Tiles[w+2][p+2] == cur_color)
                    {
                        matrix.Tiles[w][p] = -TileMatrix::FLASH_STEPS;
                        matrix.Tiles[w+1][p+1] = -TileMatrix::FLASH_STEPS;
                        matrix.Tiles[w+2][p+2] = -TileMatrix::FLASH_STEPS;
                        matrix.Game.addline();
                        foundMatch = true;
                    }
                    if(w - 2 >= 0 && p - 2 >= 0
                       && matrix.Tiles[w-1][p-1] == cur_color
                       && matrix.Tiles[w-2][p-2] == cur_color)
                    {
                        matrix.Tiles[w][p] = -TileMatrix::FLASH_STEPS;
                        matrix.Tiles[w-1][p-1] = -TileMatrix::FLASH_STEPS;
                        matrix.Tiles[w-2][p-2] = -TileMatrix::FLASH_STEPS;
                        matrix.Game.addline();
                        foundMatch = true;
                    }
                    if(w - 2 >= 0 && p + 2 < 8
                       && matrix.Tiles[w-1][p+1] == cur_color
                       && matrix.Tiles[w-2][p+2] == cur_color)
                    {
                        matrix.Tiles[w][p] = -TileMatrix::FLASH_STEPS;
                        matrix.Tiles[w-1][p+1] = -TileMatrix::FLASH_STEPS;
                        matrix.Tiles[w-2][p+2] = -TileMatrix::FLASH_STEPS;
                        matrix.Game.addline();
                        foundMatch = true;
                    }
                    if(w + 2 < 17 && p - 2 >= 0
                       && matrix.Tiles[w+1][p-1] == cur_color
                       && matrix.Tiles[w+2][p-2] == cur_color)
                    {
                        matrix.Tiles[w][p] = -TileMatrix::FLASH_STEPS;
                        matrix.Tiles[w+1][p-1] = -TileMatrix::FLASH_STEPS;
                        matrix.Tiles[w+2][p-2] = -TileMatrix::FLASH_STEPS;
                        matrix.Game.addline();
                        foundMatch = true;
                    }
                }
            }
        }

        if(foundMatch)
            return;
    }

    // draw the matrix
    inline void drawmatrix()
    {
        
        int STARTPOSX = STARTX;
        int STARTPOSY = STARTY;
        int x = STARTPOSX,y = STARTPOSY;
        
        for(int i = 0; i < 17; i++)
        {
            
            
            for(int j = 0; j < 8; j++)
            {
                if(matrix.Tiles[i][j] > 0)
                    grid_blocks[matrix.Tiles[i][j]].display(x,y);
                else if(matrix.Tiles[i][j] < 0)
                    paint.drawRect(x, y, 32, 16, SDL_MapRGB(mxhwnd.pscr->format, rand()%255, rand()%255, rand()%255));
                x = x + 32;
            }
            x = STARTPOSX;
            y = y + 16;
            // down lower
        }
        
        
        // draw the next block
        int bx = 510; int by = 200;
        
        
        grid_blocks[matrix.block.nextcolor.c1].display(bx,by);
        grid_blocks[matrix.block.nextcolor.c2].display(bx,by+16);
        grid_blocks[matrix.block.nextcolor.c3].display(bx,by+32);
        
        
        
        
    }
    // draw the blocks
    inline void drawblock()
    {
        int bx;
        int by;
        getcords(matrix.block.y,matrix.block.x,bx,by);
        grid_blocks[matrix.block.color.c1].display(bx,by);
        getcords(matrix.block.y+1,matrix.block.x,bx,by);
        grid_blocks[matrix.block.color.c2].display(bx,by);
        getcords(matrix.block.y+2,matrix.block.x,bx,by);
        grid_blocks[matrix.block.color.c3].display(bx,by);
        
        
    }
    // keypress
    inline void keypress(int wParam)
    {
        switch(wParam)
        {
            case SDLK_LEFT:
                if(matrix.block.x >= 1)
                {
                    if(matrix.Tiles[matrix.block.y][matrix.block.x-1] == 0 && matrix.Tiles[matrix.block.y + 1][matrix.block.x-1] == 0 && matrix.Tiles[matrix.block.y + 2][matrix.block.x-1] == 0)
                    {
                        matrix.block.MoveLeft();
                    }
                }
                break;
            case SDLK_RIGHT:
                if(matrix.block.x < 7)
                {
                    if(matrix.Tiles[matrix.block.y][matrix.block.x+1] == 0 && matrix.Tiles[matrix.block.y + 1][matrix.block.x+1] == 0 && matrix.Tiles[matrix.block.y + 2][matrix.block.x+1] == 0)
                    {
                        matrix.block.MoveRight();
                    }
                }
                break;
            case SDLK_DOWN:
                if(matrix.block.y + 2 < 16 && matrix.Tiles[matrix.block.y + 3][matrix.block.x] == 0)
                {
                    matrix.block.MoveDown();
                }
                break;
            case SDLK_UP:
            case 'A':
            case 'a':
                matrix.block.color.shiftcolor(true);
                break;
            case 'S':
            case 's':
                matrix.block.color.shiftcolor(false);
                break;
        }
        
    }
    
    void free()
    {
        for(int q = 0; q <= 10; q++)
            grid_blocks[q].~mxSprite();
        
        gbg.~mxSprite();
    }
    
    private:
    
    mxSprite grid_blocks[11];
    mxSprite gbg;
    
    
    
};
