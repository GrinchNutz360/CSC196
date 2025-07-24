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
#include "Game/Actor.h"



#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	//initialize engines
    srand(std::time(0));
    viper::Renderer renderer;
    viper::Time time;

    renderer.Initialize();
    renderer.CreateWinow("Viper Engine", 1200, 1024);

    viper::InputSystem input;
	input.Initialize();

    // create audio system
    viper::AudioSystem audio;
	audio.Initialize();

    std::vector<viper::vec2> points{
        { 5, 0 },
        { -2, 3 },
        { 0, 0 },
        { -2, -3 },
        { 5, 0}
    };

    viper::Model* model = new viper::Model{ points, {0,0,1} };

    std::vector<viper::Actor> actors;
    for (int i = 0; i < 10; i++) {
        viper::Transform transform{ {viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024}, 0, 10};
	    viper::Actor actor{ transform, model };
        actors.push_back(actor);
    }
    
    SDL_Event e;
    bool quit = false;

    //create stars
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
    }
//    vec2 v(30, 40);


	//iniialize sounds
	audio.AddSound("bass.wav", "bass");
	audio.AddSound("snare.wav", "snare");
	audio.AddSound("open-hat.wav", "open-hat");
	audio.AddSound("clap.wav", "clap");
	audio.AddSound("cowbell.wav", "cowbell");
    

    //std::vector<viper::vec2> points;
    //MAIN LOOP
    while (!quit) {
        time.Tick();
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        if( input.GetKeyPressed(SDL_SCANCODE_ESCAPE)) {
            quit = true;
		}
        

		//update audio system
        audio.Update();
        /*if (input.GetKeyPressed(SDL_SCANCODE_B)) {audio.PlaySound("bass");}
        if (input.GetKeyPressed(SDL_SCANCODE_S)) {audio.PlaySound("snare");}
        if (input.GetKeyPressed(SDL_SCANCODE_O)) {audio.PlaySound("open-hat");}
        if (input.GetKeyPressed(SDL_SCANCODE_C)) {audio.PlaySound("clap");}
        if (input.GetKeyPressed(SDL_SCANCODE_K)) {audio.PlaySound("cowbell");}*/


        //if (input.GetKeyDown(SDL_SCANCODE_A)) transform.rotation -= viper::math::degToRad(90 * time.GetDeltaTime());
        //if (input.GetKeyDown(SDL_SCANCODE_D)) transform.rotation += viper::math::degToRad(90 * time.GetDeltaTime());
        float speed = 200;

        viper::vec2 direction { 0,0 };
        if (input.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1; //speed * time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1; // speed* time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1; //speed* time.GetDeltaTime();
        if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1; //speed* time.GetDeltaTime();
		
        if (direction.LengthSqr() > 0) {
            direction = direction.Normalized();
            for (auto& actor : actors) {
                actor.GetTransform().position += (direction * speed) * time.GetDeltaTime();

            }
            //actor.GetTransform().position += (direction * speed) * time.GetDeltaTime();
        }

        //update engines
        input.Update();
        if (input.GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
            points.push_back(input.GetMousePosition());
        }
        if (input.GetMouseButtonDown(viper::InputSystem::MouseButton::Left)) {
            viper::vec2 position = input.GetMousePosition();
            if (points.empty()) points.push_back(position);
            else if ((position - points.back()).Length() > 10) points.push_back(position);
        }


        //draw
        viper::vec3 color{ 0,0,0 };

        renderer.SetColor(color.r, color.g, color.b);
        renderer.Clear();

        //model.Draw(renderer, input.GetMousePosition(), time.GetTime(), 10.0f);
		//model.Draw(renderer, transform);
        for (auto& actor : actors) {
		    actor.Draw(renderer);

        }


        for (int i = 0; i < (int)points.size() - 1; i++) {
            // set color or random color
			renderer.SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
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

        


        viper::vec2 speedz{ -140.0f, 0.0f };
        float length = speedz.Length();

        for (auto& star : stars) {
			star += speedz * time.GetDeltaTime();

            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            renderer.SetColor((uint8_t)viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);
        }

        for(int i = 0; i < stars.size(); i++)

        //for (int i = 0; i < 100; i++) {
            //renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            //renderer.DrawLine(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024, viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);
            

            //renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            //renderer.DrawPoint(v.x, v.y);
            //renderer.DrawPoint(viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024);

        renderer.Present();
    }
    renderer.Shutdown();
    audio.Shutdown();

        return 0;
}