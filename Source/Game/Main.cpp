#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Core/Random.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystems.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    srand(std::time(0));
    viper::Renderer renderer;
    viper::Time time;

    renderer.Initialize();
    renderer.CreateWinow("Viper Engine", 1200, 1024);

    viper::InputSystem input;
	input.Initialize();

    SDL_Event e;
    bool quit = false;

    //create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
    }
//    vec2 v(30, 40);

    std::vector<viper::vec2> points;
    //MAIN LOOP
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        input.Update();
        if (input.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }
        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = input.GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }

        renderer.SetColor(0, 0, 0);
        renderer.Clear();
        for (int i = 0; i < (int)points.size() - 1; i++) {
            // set color or random color
			renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }


		/*input.Update();
        if(input.GetKeyReleased(SDL_SCANCODE_A)) {
            std::cout << "pressed\n";
		}

        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            std::cout << "Mouse pressed\n";
        }

		viper::vec2 mouse = input.GetMousePosition();
		std::cout << mouse.x << " " << mouse.y << std::endl;*/

        //renderer.SetColor(0,0,0);
        


       /* viper::vec2 speed{ -140.0f, 0.0f };
        float length = speed.Length();

        for (auto& star : stars) {
			star += speed * time.GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);
        }

        for(int i = 0; i < stars.size(); i++)*/

        //for (int i = 0; i < 100; i++) {
            //renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            //renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
            

            //renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            //renderer.DrawPoint(v.x, v.y);
            //renderer.DrawPoint(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);

        //}
        renderer.Present();
    }
    renderer.Shutdown();

        return 0;
}