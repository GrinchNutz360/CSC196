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
    // Test getInt() variants
    std::cout << "Integer Functions:\n";
    std::cout << "getInt(): " << viper::random::getInt() << "\n";
    std::cout << "getInt(): " << viper::random::getInt() << "\n";
    std::cout << "getInt(10): " << viper::random::getInt(10) << "\n";
    std::cout << "getInt(10): " << viper::random::getInt(10) << "\n";
    std::cout << "getInt(5, 15): " << viper::random::getInt(5, 15) << "\n";
    std::cout << "getInt(5, 15): " << viper::random::getInt(5, 15) << "\n";
    std::cout << "getInt(-10, 10): " << viper::random::getInt(-10, 10) << "\n\n";

    // Test getReal() variants with float
    std::cout << "Float Functions:\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "getReal<float>(): " << viper::random::getReal<float>() << "\n";
    std::cout << "getReal<float>(): " << viper::random::getReal<float>() << "\n";
    std::cout << "getReal<float>(5.0f): " << viper::random::getReal<float>(5.0f) << "\n";
    std::cout << "getReal<float>(2.5f, 7.5f): " << viper::random::getReal<float>(2.5f, 7.5f) << "\n";
    std::cout << "getReal<float>(-1.0f, 1.0f): " << viper::random::getReal<float>(-1.0f, 1.0f) << "\n\n";

    // Test getReal() variants with double
    std::cout << "Double Functions:\n";
    std::cout << std::setprecision(10);
    std::cout << "getReal<double>(): " << viper::random::getReal<double>() << "\n";
    std::cout << "getReal<double>(100.0): " << viper::random::getReal<double>(100.0) << "\n";
    std::cout << "getReal<double>(0.0, 2.0): " << viper::random::getReal<double>(0.0, 2.0) << "\n\n";

    // Test getBool()
    std::cout << "Boolean Functions:\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << "getBool(): " << std::boolalpha << viper::random::getBool() << "\n";
    }
    std::cout << "\n";

    //Font stuff

	//initialize engine
	viper::GetEngine().Initialize();

    viper::Font* font = new viper::Font();
    font->Load("ArcadeClassic.ttf", 50);
    viper::Text* text = new viper::Text(font);
    text->Create(viper::GetEngine().GetRenderer(), "Score:", viper::vec3{1, 1, 1});

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

        if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
        }

        //draw
        viper::vec3 color{ 0,0,0 };

        viper::GetEngine().GetRenderer().SetColor(color.r, color.g, color.b);
        viper::GetEngine().GetRenderer().Clear();

        text->Draw(viper::GetEngine().GetRenderer(), 40.0f, 40.0f);

        //model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10.0f);
		//model.Draw(renderer, transform);
		game->Draw();


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
   

	viper::GetEngine().Shutdown();

        return 0;
}