#include <iostream>
#include "Core/Core.h"
#include "Render/Render.h"
#include "Render/Model.h"
#include "Framework/Actor.h"
#include "Player.h"
#include "Enemy.h"
#include "Framework/Scene.h"
#include "Render/ModelManager.h"
#include "Render/ParticleSystem.h"
#include "Framework/Emitter.h"
#include "Render/Texture.h"

#include "SpaceGame.h"

#include <vector>
#include <chrono>
#include <thread>
#include <memory>

using namespace std;

class Star
{
public:
	Star(const kda::Vector2& pos, const kda::Vector2& vel) : m_pos{ pos }, m_vel{ vel } {}

	void Update(int height, int width)
	{
		m_pos += m_vel * kda::g_time.GetDeltaTime();

		if (m_pos.x >= height) m_pos.x = 0;
		if (m_pos.y >= width) m_pos.y = 0;
	}

	void Draw(kda::Renderer renderer) 
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kda::Vector2 m_pos;
	kda::Vector2 m_vel;
};

int main(int argc, char* argv[])
{
	INFO_LOG("Hello World");

	//engine setup
	kda::MemoryTracker::Initialize();

	kda::seedRandom((unsigned int)time(nullptr));
	kda::setFilePath("assets");

	kda::g_renderer.Initialize();
	kda::g_renderer.CreateWindow("CSC196", 800, 600);

	kda::g_inputSystem.Initialize();
	kda::g_audioSystem.Initialize();

	unique_ptr<SpaceGame>game = make_unique<SpaceGame>();
	game->Initialize();

	kda::vec2 v{5, 5};
	v.Normalize();

	//stars
	vector<Star> stars;
	for (int i = 0; i < 1000; i++) {
		kda::Vector2 pos(kda::Vector2(kda::randomf((float)kda::g_renderer.getWidth()), kda::randomf((float)kda::g_renderer.getHeight())));
		kda::Vector2 vel(kda::randomf(100, 500), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	// create texture
	shared_ptr<kda::Texture> texture = make_shared<kda::Texture>();
	texture->Create(kda::g_renderer, "ship2.png");

	
	//main game loop
	bool quit = false;
	while (!quit) {

		//update engine
		kda::g_time.Tick();
		kda::g_inputSystem.Update();
		kda::g_audioSystem.Update();
		kda::g_particleSystem.Update(kda::g_time.GetDeltaTime());

		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//update game
		game->Update(kda::g_time.GetDeltaTime());


		//draw
		kda::g_renderer.SetColor(0,0,0, 255);
		kda::g_renderer.BeginFrame();
		//text->Draw(kda::g_renderer, 400, 300);
		kda::g_renderer.DrawTexture(texture.get(), 200.0f, 200.0f, 0.0f);

		for (auto& star : stars)
		{
			star.Update(kda::g_renderer.getWidth(), kda::g_renderer.getHeight());
		
			kda::g_renderer.SetColor(kda::random(0, 254), kda::random(0, 254), kda::random(0, 254), 255);
			
			star.Draw(kda::g_renderer);
		}

		game->Draw(kda::g_renderer);
		kda::g_particleSystem.Draw(kda::g_renderer);

		kda::g_renderer.EndFrame();

	}

	stars.clear();

	return 0;
}