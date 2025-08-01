#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Transform.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystems.h"
#include "Audio/AudioSystem.h"
#include "Math/Vector3.h"
#include "Framework/Actor.h"
#include "Framework/Scene.h"
#include "Engine.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>


int main(int argc, char* argv[]) {
    //Font stuff


	//initialize engine
	viper::GetEngine().Initialize();

    //initialize game
    std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();
    
    SDL_Event e;
    bool quit = false;

    //create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getReal() * 1280, viper::random::getReal() * 1024 });
    }
//    vec2 v(30, 40);


	//iniialize sounds
	viper::GetEngine().GetAudio().AddSound("bass.wav", "bass");
	viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
	viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");
	viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
	viper::GetEngine().GetAudio().AddSound("cowbell.wav", "cowbell");
    viper::GetEngine().GetAudio().AddSound("laserShoot.wav", "laser");
    viper::GetEngine().GetAudio().AddSound("machineGun.wav", "machineGun");
    viper::GetEngine().GetAudio().AddSound("shotGun.wav", "shotGun");
    viper::GetEngine().GetAudio().AddSound("nuke.wav", "nuke");
    

    //std::vector<viper::vec2> points;
    //MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
		viper::GetEngine().Update();
		game->Update(viper::GetEngine().GetTime().GetDeltaTime());

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
        }

        //draw
        viper::vec3 color{ 0,0,0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        //model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10.0f);
		//model.Draw(renderer, transform);
		game->Draw(viper::GetEngine().GetRenderer());


        viper::vec2 speedz{ -140.0f, 0.0f };
        float length = speedz.Length();

        for (auto& star : stars) {
			star += speedz * viper::GetEngine().GetTime().GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getInt(256), viper::random::getInt(256), viper::random::getInt(256));
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }

        for(int i = 0; i < stars.size(); i++)

            viper::GetEngine().GetRenderer().Present();
    }
   
	game->Shutdown();
    game.release();
	viper::GetEngine().Shutdown();

        return 0;
}