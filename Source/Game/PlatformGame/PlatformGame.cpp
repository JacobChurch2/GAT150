#include "PlatformGame.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "Render/Text.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"

bool PlatformGame::Initialize() {

	//Load audio
	kda::g_audioSystem.AddAudio("hit", "Audio/Laser_Shoot.wav");
	kda::g_audioSystem.AddAudio("music", "Audio/Music.wav");

	//Scene
	m_scene = std::make_unique<kda::Scene>();
	m_scene->Load("Scenes/PlatformScene.json");
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Initialize();

	//add events
	EVENT_SUBSCRIBE("AddPoints", PlatformGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

	return true;
}

void PlatformGame::Shutdown() {

}

void PlatformGame::Update(float dt) {

	switch (m_state)
	{
	case PlatformGame::eState::Title:
		/*if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}*/
	{
		/*auto actor = INSTANTIATE(Actor, "Crate");
		actor->transform.position = { kda::random(kda::g_renderer.GetWidth()), 100 };
		actor->Initialize();
		m_scene->Add(std::move(actor));*/
	}
		break;
	case PlatformGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		kda::g_audioSystem.PlayOneShot("music", true);
		break;
	case PlatformGame::eState::StartLevel:
		m_scene->RemoveAll();
		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:
		break;
	case eState::PlayerDeadStart:
		break;
	case PlatformGame::eState::PlayerDead:
		break;
	case PlatformGame::eState::GameOver:
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void PlatformGame::Draw(kda::Renderer& renderer) {
	m_scene->Draw(renderer);
}

void PlatformGame::AddPoints(const kda::Event& event)
{
	m_score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const kda::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDeadStart;
}
