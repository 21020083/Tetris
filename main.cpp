#include"SDL_mixer.h"
#include"SDL_image.h"
#include<vector>
#include <stdio.h>
#include<string>
#include"playground.h"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 640
#define speed 0,2
using namespace std;
enum dir {NONE,UP,LEFT,DOWN,RIGHT,SPACE}key;
SDL_Color WHITE{255,255,255};
SDL_Color RED{255,0,0};
Uint32 delay=1300;
Shape shapes[7]={
    {{177, 85, 217}, // L BLOCK
    {1,5,4,9}
     ,0,0,4},
     {{255, 52, 38}, // Z BLOCK
    {0,5,1,6}
     ,0,0,4},
     {{0, 255, 255}, // I BLOCK
    {4,5,6,7}
     ,0,0,4},
     {{0, 200, 43}, // J BLOCK
    {0,5,4,6}
     ,0,0,4},
     {{255, 255, 80}, // O BLOCK
    {0,5,1,4}
     ,0,0,4},
     {{0, 0, 255}, // S BLOCK
    {1,5,4,2}
     ,0,0,4},
     {{255,155,41}, // T BLOCK
    {1,5,4,6}
     ,0,0,4}
};
void Shape::spawn()
    {
        srand(time(0));
        *this=shapes[rand()%7];
    }
void ScoreBoard::update()
    {
        next_piece.spawn();
    }
bool running = false;
bool m_running=true;
int score=0;
bool game=true;
int line=0;
void ScoreBoard::create(SDL_Renderer* renderer)
    {
        gameScore.set_font("Heartbit-Bold.otf");
        SDL_Rect rect{400,100,140,75};
        gameScore.set_pos(rect);
        gameScore.set_text("SCORE: "+to_string(score));
        gameScore.createText(renderer);

        Line.set_font("Heartbit-Bold.otf");
        rect={400,170,140,75};
        Line.set_pos(rect);
        Line.set_text("LINE: "+to_string(line));
        Line.createText(renderer);

        Next_Piece.set_font("Heartbit-Bold.otf");
        rect={400,300,180,75};
        Next_Piece.set_pos(rect);
        Next_Piece.set_text("NEXT PIECE: ");
        Next_Piece.createText(renderer);
    }
struct SoundEffects
{
    Mix_Chunk* mSoundEffect;
    Mix_Music* mus;
    SoundEffects()
    {
        int audio_rate = 44100;
        Uint16 audio_format = AUDIO_S16SYS;
        int audio_channels = 2;
        int audio_buffers = 2048;

        if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
            exit(-1);
        }
    }
  ~SoundEffects()
  {
        Mix_Quit();

  }

  void addSoundEffect(const char* path)
  {
       mSoundEffect = Mix_LoadWAV(path);

        if (mSoundEffect == nullptr)
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init audio: %s", Mix_GetError());
  }
  void addMusic(const char* path)
  {
    mus = Mix_LoadMUS(path);
  }
  void playSoundEffect ()
    {
        Mix_Volume(2,20);
        Mix_PlayChannel(2, mSoundEffect, 0);
  }
  void playMusic()
  {
    Mix_VolumeMusic(20);
    Mix_PlayMusic(mus,-1);
  }
};
SoundEffects se;
struct Menu
{

    TextObject Play,Exit;
    int x,y;
    void create(SDL_Renderer* renderer)
    {
        Play.set_font("Heartbit-Bold.otf");
        SDL_Rect rect{255,170,130,75};
        Play.set_pos(rect);
        Play.set_text("PLAY");
        Play.createText(renderer);

        Exit.set_font("Heartbit-Bold.otf");
        rect={255,270,125,75};
        Exit.set_pos(rect);
        Exit.set_text("EXIT");
        Exit.createText(renderer);
    }
     void show(SDL_Renderer* renderer)
    {
        Play.draw(renderer);
        Exit.draw(renderer);
    }
    void update(SDL_Event m_event,SDL_Renderer* renderer)
    {
        while(m_running){
            create(renderer);
            while(SDL_PollEvent(&m_event))
            {
                if(m_event.type == SDL_QUIT)
                    m_running= false;
                switch(m_event.type)
                {
                    case SDL_MOUSEMOTION:
                        x=m_event.motion.x;
                        y=m_event.motion.y;
                        if(x>=Play.pos.x && x<=Play.pos.x+Play.pos.w && y>=Play.pos.y && y<=Play.pos.y+Play.pos.h){
                            Play.setcolor(RED);
                            Play.createText(renderer);
                        }
                        else{
                            Play.setcolor(WHITE);
                            Play.createText(renderer);
                        }
                        if(x>=Exit.pos.x && x<=Exit.pos.x+Exit.pos.w && y>=Exit.pos.y && y<=Exit.pos.y+Exit.pos.h){
                            Exit.setcolor(RED);
                            Exit.createText(renderer);
                        }
                        else{
                            Exit.setcolor(WHITE);
                            Exit.createText(renderer);
                        }
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        x=m_event.motion.x;
                        y=m_event.motion.y;
                        if(x>=Play.pos.x && x<=Play.pos.x+Play.pos.w && y>=Play.pos.y && y<=Play.pos.y+Play.pos.h){
                            running=1;
                            m_running=0;
                        }
                        if(x>=Exit.pos.x && x<=Exit.pos.x+Exit.pos.w && y>=Exit.pos.y && y<=Exit.pos.y+Exit.pos.h){
                            game=0;
                            m_running=0;
                        }
            }

        }
        show(renderer);
        SDL_RenderPresent(renderer);
    }
    }


};

bool checkCollisionY(Shape s){
    for(int i=0;i<4;i++){
        int dy=s.pos[i]/4;
        if(s.y+dy*block_size>=SCREEN_HEIGHT)
            return true;
    }
    return false;
}
bool checkCollisionX(Shape s){
    for(int i=0;i<4;i++){
        int dx=s.pos[i]%4;
        if(s.x+dx*block_size<0 || s.x+dx*block_size>9*block_size)
            return true;
    }
    return false;
}
bool canrotate(Shape s,playground p){
            Shape s1= s;
            s1.rotate();
            if(!checkCollisionX(s1) && !checkCollisionY(s1) && p.canMove(s1))
                return true;
            return false;

}




Uint32 timeStep;
SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
playground p;
Shape s;
ScoreBoard Board;

void fall(Shape&s ,playground& p)
{
    if ( SDL_GetTicks() >= timeStep + delay ){
        timeStep = SDL_GetTicks();
        s.y += block_size;
        if (!p.canMove(s) || checkCollisionY(s))
            {
            s.y-=block_size;
            p.lock(s,renderer);
            s=Board.next_piece;
            s.x=0;
            s.y=0;
            Board.update();
            }
    }
}
void drop(Shape &s,playground &p)
{
    while(p.canMove(s))

        {
            s.y+=block_size;
            s.draw(renderer);
        }

    s.y-=block_size;
    p.lock(s,renderer);
    s=Board.next_piece;
    s.x=0;
    s.y=0;
    Board.update();

}
void checkLevel()
{
    if(score>=1000 && score<= 1500)
    {
        delay = 900;
    }
    if(score<=2000 && score >1500)
        delay = 600;
}




void update(){
    switch(key){
    case UP:{
        if(canrotate(s,p))
            s.rotate();
        break;
    }
    case LEFT:{
            s.x-=block_size;
        if(checkCollisionX(s) || !p.canMove(s))
            s.x+=block_size;
        break;}
    case DOWN:{
        s.y+=block_size;
        if(checkCollisionY(s)||!p.canMove(s)){
            s.y-=block_size;
            p.lock(s,renderer);
            s=Board.next_piece;
            s.x=0;
            s.y=0;
            Board.update();

        }
        break;
    }
    case RIGHT:{
            s.x+=block_size;
            if(!p.canMove(s)||checkCollisionX(s))
              s.x-=block_size;
        break;
            }

    case SPACE:
        drop(s,p);
        break;

    default:
        break;
    }
    fall(s,p);
    key=NONE;
    if(p.checkRows())
    {
        se.playSoundEffect();
        score+=100;
        line+=1;
    }
    if(p.checkGameEnd(s))
    {
        running = false;
        m_running = true;
    }
    checkLevel();
};
void cleargame(playground&p)
{
    p.init();
    score=0;
    line=0;
}
int main(int argc, char** argv){
    p.init();
    s=shapes[rand()%7];
if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }
     if( TTF_Init() == -1 )
        {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return 1;
      }
    ;
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }
        se.addSoundEffect("line.wav");
        se.addMusic("sound_bgm.mp3");
        Board.next_piece=shapes[rand()%7];
        timeStep = SDL_GetTicks();
    while(game){
        SDL_Event m_event;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        Menu menu;
        menu.create(renderer);
        menu.update(m_event,renderer);
        int fps=60;
        int desired_delta=1000/fps;
        SDL_Event e;
        while(running){
            int startloop=SDL_GetTicks();
            if(!Mix_PlayingMusic())
                se.playMusic();
            while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
                game=false;
            }
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                    case SDLK_UP:
                        key=UP;
                        break;

                    case SDLK_DOWN:
                        key=DOWN;
                        break;

                    case SDLK_LEFT:
                        key=LEFT;
                        break;

                    case SDLK_RIGHT:
                        key=RIGHT;
                        break;

                    case SDLK_SPACE:
                        key = SPACE;
                        break;
                }
            }

            }
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            p.draw(renderer);
            s.draw(renderer);
            update();
            Board.create(renderer);
            Board.show(renderer);
            int delta=SDL_GetTicks()-startloop;
            if(delta<desired_delta)
                SDL_Delay(desired_delta-delta);
            SDL_RenderPresent(renderer);
        }
        cleargame(p);
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window=nullptr;
    renderer=nullptr;
    TTF_Quit();
    SDL_Quit();
    return 0;
}

