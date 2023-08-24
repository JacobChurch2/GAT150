#include "Render/Render.h"
#include "Core/Core.h"
//#include "../../Engine/Core/Math/Vector2.h"
#include "Framework/Framework.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsSystem.h"
#include "PlatformGame.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <memory>
#include <array>
#include <map>
#include <functional>

using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("Hello World!")

	kda::MemoryTracker::Initialize();
	kda::seedRandom((unsigned int)time(nullptr));
	kda::setFilePath("Assets/PlatformGame");

	//Initialize game engine
	kda::g_audioSystem.Initialize();
	kda::g_renderer.Initialize();
	kda::g_renderer.CreateWindow("CSC196", 800, 600);
	kda::g_inputSystem.Initialize();
	kda::PhysicsSystem::Instance().Initialize();

	unique_ptr<PlatformGame> game = make_unique<PlatformGame>();
	game->Initialize();

	// Main game loop
	bool quit = false;
	while (!quit) {

		//update engine
		kda::g_audioSystem.Update();
		kda::g_time.tick();
		kda::g_inputSystem.Update();
		kda::g_particleSystem.Update(kda::g_time.getDeltaTime());
		kda::PhysicsSystem::Instance().Update(kda::g_time.getDeltaTime());

		//escape
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		//Update Game
		game->Update(kda::g_time.getDeltaTime());

		//Draw Game
		kda::g_renderer.SetColor(0, 0, 0, 255);
		kda::g_renderer.BeginFrame();

		game->Draw(kda::g_renderer);
		kda::g_particleSystem.Draw(kda::g_renderer);

		kda::g_renderer.EndFrame();
	}

	return 0;

}