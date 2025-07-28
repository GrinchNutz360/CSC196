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

#include "Game/Player.h"
#include "Game/SpaceGame.h"

#include <iostream>
#include <vector>
#include <memory>


int main(int argc, char* argv[]) {
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
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
    }
//    vec2 v(30, 40);


	//iniialize sounds
	viper::GetEngine().GetAudio().AddSound("bass.wav", "bass");
	viper::GetEngine().GetAudio().AddSound("snare.wav", "snare");
	viper::GetEngine().GetAudio().AddSound("open-hat.wav", "open-hat");
	viper::GetEngine().GetAudio().AddSound("clap.wav", "clap");
	viper::GetEngine().GetAudio().AddSound("cowbell.wav", "cowbell");
    

    //std::vector<viper::vec2> points;
    //MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
		viper::GetEngine().Update();
		game->Update();

        if( viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}
        

		//update audio system
        /*if (input.GetKeyPressed(SDL_SCANCODE_B)) {audio.PlaySound("bass");}
        if (input.GetKeyPressed(SDL_SCANCODE_S)) {audio.PlaySound("snare");}
        if (input.GetKeyPressed(SDL_SCANCODE_O)) {audio.PlaySound("open-hat");}
        if (input.GetKeyPressed(SDL_SCANCODE_C)) {audio.PlaySound("clap");}
        if (input.GetKeyPressed(SDL_SCANCODE_K)) {audio.PlaySound("cowbell");}*/


        //if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) viper::mattransform.rotation -= viper::math::degToRad(90 * viper::GetEngine().GetTime().GetDeltaTime());
        //if (input.GetKeyDown(SDL_SCANCODE_D)) transform.rotation += viper::math::degToRad(90 * time.GetDeltaTime());
        

        //update engines
      /*  if (input->GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            points.push_back(input->GetMousePosition());
        }
        if (input->GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = input->GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }*/


        //draw
        viper::vec3 color{ 0,0,0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        //model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10.0f);
		//model.Draw(renderer, transform);
		game->Draw();


        viper::vec2 speedz{ -140.0f, 0.0f };
        float length = speedz.Length();

        for (auto& star : stars) {
			star += speedz * viper::GetEngine().GetTime().GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            viper::GetEngine().GetRenderer().DrawPoint(star.x, star.y);
        }

        for(int i = 0; i < stars.size(); i++)

            viper::GetEngine().GetRenderer().Present();
    }
   

	viper::GetEngine().Shutdown();

        return 0;
}