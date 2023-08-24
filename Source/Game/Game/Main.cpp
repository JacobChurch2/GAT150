#include "Render/Render.h"
#include "Core/Core.h"
#include "Player.h"
#include "Enemy.h"
#include "SpaceGame.h"
#include "../../Engine/Core/Math/Vector2.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsSystem.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <array>
#include <map>
#include <functional>

using namespace std;

class Star {
public:
	Star(const kda::Vector2& pos, const kda::Vector2& vel) :
		m_pos{pos},
		m_vel{vel}
	{}

	void Update(int width, int height) {
		m_pos += m_vel * kda::g_time.getDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

public:
	kda::Vector2 m_pos;
	kda::Vector2 m_vel;
};

int main(int argc, char* argv[]) 
{
	INFO_LOG("Hello World!")

	kda::MemoryTracker::Initialize();
	kda::seedRandom((unsigned int)time(nullptr));
	kda::setFilePath("Assets/SpaceGame");

	//Initialize game engine
	kda::g_audioSystem.Initialize();
	kda::g_renderer.Initialize();
	kda::g_renderer.CreateWindow("CSC196", 800, 600);
	kda::g_inputSystem.Initialize();
	kda::PhysicsSystem::Instance().Initialize();

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	kda::vec2 v{5, 5};
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kda::Vector2 pos(kda::random(kda::g_renderer.GetWidth()), kda::random(kda::g_renderer.GetHeight()));
		kda::Vector2 vel(kda::randomf(100, 500), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	kda::Transform transform{{400, 300}, 0, 3};
	kda::vec2 position{ 400, 300};

	float speed = 200;
	//float turnRate = kda::DegreesToRadians(180);

	// Main game loop
	bool quit = false;
	while (!quit) {

		kda::g_audioSystem.Update();
		kda::g_time.tick();
		kda::g_inputSystem.Update();
		kda::g_particleSystem.Update(kda::g_time.getDeltaTime());
		kda::PhysicsSystem::Instance().Update(kda::g_time.getDeltaTime());

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)){
			kda::g_audioSystem.PlayOneShot("hit");
		}

		//Update Game
		game->Update(kda::g_time.getDeltaTime());

		//Draw Game
		kda::g_renderer.SetColor(0, 0, 0, 255);
		kda::g_renderer.BeginFrame();

		game->Draw(kda::g_renderer);

		for (auto& star : stars) {

			star.Update(kda::g_renderer.GetWidth(), kda::g_renderer.GetHeight());

			kda::g_renderer.SetColor(kda::random(0, 254), kda::random(0, 254), kda::random(0, 254), 255);
			kda::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);


		}
		kda::g_particleSystem.Draw(kda::g_renderer);
		
		kda::g_renderer.EndFrame();
	}


	stars.clear();


	return 0;

}