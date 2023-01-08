#include "MyGame.h"

void MyGame::on_receive(std::string cmd, std::vector<std::string>& args) {
    if (cmd == "GAME_DATA") {
        // we should have exactly 4 arguments
        if (args.size() == 4) {
            game_data.player1Y = stoi(args.at(0));
            game_data.player2Y = stoi(args.at(1));
            game_data.ballX = stoi(args.at(2));
            game_data.ballY = stoi(args.at(3));
        }


    } 
    
    else if (cmd == "BALL_HIT_BAT1" || cmd == "BALL_HIT_BAT2") {

        SDL_QueueAudio(device, hitBatSoundBuffer, hitBatSoundLength);
        SDL_PauseAudioDevice(device, 0);

    }

    else if (cmd == "HIT_WALL_LEFTGAME_DATA" || cmd == "HIT_WALL_RIGHTGAME_DATA" || cmd == "HIT_WALL_UP" || cmd == "HIT_WALL_DOWN") {
        

        SDL_QueueAudio(device, hitWallSoundBuffer, hitWallSoundLength);
        SDL_PauseAudioDevice(device, 0);

    }

    else if (cmd == "SCORES") {

        TTF_Init();


        TTF_Font* sans = TTF_OpenFont("assets/SIMSUN.ttf", 48);

        std::cout << TTF_GetError();

        SDL_Color white = { 255, 255, 255 };
        SDL_Surface* image = TTF_RenderText_Solid(sans, args[0].c_str(), white);

        score1.w = image->w;
        score1.h = image->h;

        SDL_DestroyTexture(score1Texture);

        score1Texture = SDL_CreateTextureFromSurface(renderer, image);

        SDL_FreeSurface(image);
        
        image = TTF_RenderText_Solid(sans, args[1].c_str(), white);

        score2.w = image->w;
        score2.h = image->h;

        SDL_DestroyTexture(score2Texture);

        score2Texture = SDL_CreateTextureFromSurface(renderer, image);

        SDL_FreeSurface(image);
    }

    else {
        std::cout << "Received: " << cmd << std::endl;

        for (int i = 0; i < args.size(); i++)
        { 
            std::cout << "Server said: " << args[i] << std::endl;
        }
        
    }
}

void MyGame::send(std::string message) {
    messages.push_back(message);
}

void MyGame::input(SDL_Event& event) {
    switch (event.key.keysym.sym) {
        case SDLK_w:
            send(event.type == SDL_KEYDOWN ? "W_DOWN" : "W_UP");
            break;

        case SDLK_s:
            send(event.type == SDL_KEYDOWN ? "S_DOWN" : "S_UP");
            break;
    }
}

MyGame::MyGame(SDL_Renderer* renderer){
    SDL_Surface* image = IMG_Load("assets/BALL.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);



    ballTexture = texture;

    SDL_FreeSurface(image);
    
    
    image = IMG_Load("assets/BAT.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);

    batTexture = texture;

    SDL_FreeSurface(image);

    image = IMG_Load("assets/BACK.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);

    backTexture = texture;

    SDL_FreeSurface(image);

    image = IMG_Load("assets/GRID.png");
    texture = SDL_CreateTextureFromSurface(renderer, image);

    starTexture = texture;

    SDL_FreeSurface(image);

    this->renderer = renderer;

    TTF_Init();


    TTF_Font* sans = TTF_OpenFont("assets/SIMSUN.ttf", 48);

    std::cout << TTF_GetError();

    

    SDL_Color white = { 255, 255, 255 };
    image = TTF_RenderText_Solid(sans,"0", white);

    score1Texture = SDL_CreateTextureFromSurface(renderer, image);

    score1.w = image->w;
    score1.h = image->h;

    SDL_FreeSurface(image);

    image = TTF_RenderText_Solid(sans, "0", white);

    score2Texture = SDL_CreateTextureFromSurface(renderer, image);

    score2.w = image->w;
    score2.h = image->h;

    SDL_FreeSurface(image);

    time = std::chrono::steady_clock::now();

    SDL_LoadWAV("assets/hit_bat.wav", &hitBatSound, &hitBatSoundBuffer, &hitBatSoundLength);
    SDL_LoadWAV("assets/hit_wall.wav", &hitWallSound, &hitWallSoundBuffer, &hitWallSoundLength);

    device = SDL_OpenAudioDevice(NULL, 0, &hitWallSound, NULL, 0);
}

void MyGame::update() {
    player1.y = game_data.player1Y;
    player2.y = game_data.player2Y;

    ball.x = game_data.ballX;
    ball.y = game_data.ballY;

    std::chrono::steady_clock::time_point newTime = std::chrono::steady_clock::now();

    std::chrono::duration<double> deltaTime;

    deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(newTime - time);

    time = newTime;

    angle = angle + deltaTime.count();
}

void MyGame::render(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(renderer, 254, 254, 254, 254);
    SDL_RenderCopy(renderer, batTexture, NULL, &player1);
    SDL_RenderCopy(renderer, batTexture, NULL, &player2);
    SDL_RenderCopy(renderer, ballTexture, NULL, &ball);
    SDL_RenderCopy(renderer, score1Texture, NULL, &score1);
    SDL_RenderCopy(renderer, score2Texture, NULL, &score2);
    SDL_RenderCopy(renderer, backTexture, NULL, &back);

    SDL_RenderCopyEx(renderer, starTexture, NULL, &back2, angle, NULL, SDL_FLIP_NONE);

}
