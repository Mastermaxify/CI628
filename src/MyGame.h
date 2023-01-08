#ifndef __MY_GAME_H__
#define __MY_GAME_H__

#include <iostream>
#include <vector>
#include <string>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_render.h"
#include "SDL_ttf.h"
#include <chrono>
#include "SDL_audio.h"

static struct GameData {
    int player1Y = 0;
    int player2Y = 0;
    int ballX = 0;
    int ballY = 0;
} game_data;

class MyGame {

    private:
        SDL_Rect player1 = { 200, 0, 20, 60 };
        SDL_Rect player2 = { 580, 0, 20, 60 };

        SDL_Rect score1 = { 160, 130, 800, 600 };
        SDL_Rect score2 = { 560, 130, 800, 600 };

        SDL_Rect ball = { 0, 0, 10, 10 };

        SDL_Rect back = { 0, 0, 800, 600 };
        SDL_Rect back2 = { -400, -400, 1600, 1600 };

        std::chrono::steady_clock::time_point time;

        float angle = 0;

        SDL_AudioDeviceID device;
 
        SDL_AudioSpec hitBatSound;
        Uint32 hitBatSoundLength;
        Uint8* hitBatSoundBuffer;

        SDL_AudioSpec hitWallSound;
        Uint32 hitWallSoundLength;
        Uint8* hitWallSoundBuffer;

        SDL_Texture* ballTexture;
        SDL_Texture* batTexture;
        SDL_Texture* score1Texture;
        SDL_Texture* score2Texture;
        SDL_Texture* backTexture;
        SDL_Texture* starTexture;

        SDL_Renderer* renderer;
        

    public:
        MyGame(SDL_Renderer* renderer);

        std::vector<std::string> messages;

        void on_receive(std::string message, std::vector<std::string>& args);
        void send(std::string message);
        void input(SDL_Event& event);
        void update();
        void render(SDL_Renderer* renderer);


};

#endif