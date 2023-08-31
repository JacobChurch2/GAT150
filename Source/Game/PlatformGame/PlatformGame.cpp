#include "PlatformGame.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "Render/Text.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"
#include "Player.h"
#include "Enemy.h"

bool PlatformGame::Initialize() {
	//Load audio
	kda::g_audioSystem.AddAudio("hit", "Audio/Explosion.wav");
	kda::g_audioSystem.AddAudio("music", "Audio/Music.wav");

	//Scene
	m_scene = std::make_unique<kda::Scene>();
	m_scene->Load("Scenes/PlatformScene.json");
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Initialize();

	//deactivate every actor
	m_scene->ActivateAll(false);
	

	//add events
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);
	EVENT_SUBSCRIBE("OnEndLevel", PlatformGame::OnEndLevel);

	return true;
}

void PlatformGame::Shutdown() {

}

void PlatformGame::Update(float dt) {

	switch (m_state)
	{
	case PlatformGame::eState::Title:
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
		}
		m_scene->GetActorByName("Title")->active = true;
		m_scene->GetActorByName("Background")->active = true;
		break;
	case PlatformGame::eState::StartGame:
		m_scene->GetActorByName("Title")->active = false;
		m_state = eState::StartLevel;
		kda::g_audioSystem.PlayOneShot("music", true);
		break;
	case PlatformGame::eState::StartLevel:
		//Activating the right actors
		m_scene->GetActorByName("Timer")->active = true;
		m_scene->GetActorByName("HPText")->active = true;
		m_scene->ActivateAllWithTag("Ground", true);
		{
		auto Grape = INSTANTIATE(Actor, "Grape");
		Grape->Initialize();
		m_scene->Add(std::move(Grape));

		auto Bat = INSTANTIATE(Enemy, "Enemy");
		Bat->transform = kda::Transform{ {1600, 32},0, 1 };
		Bat->Initialize();
		m_scene->Add(std::move(Bat));

		auto Player = INSTANTIATE(Player, "Player");
		Player->Initialize();
		m_scene->Add(std::move(Player));
		}

		//moving things the the right spot
		m_scene->GetActorByName("Timer")->transform = kda::Transform{ {64, 32},0, 1 };

		m_state = eState::Game;
		break;
	case PlatformGame::eState::Game:
		//Timer
		m_gameTimer += dt;
		m_scene->GetActorByName("Timer")->GetComponent<kda::TextRenderComponent>()->SetText(std::to_string((int) floor(m_gameTimer)));
		m_scene->GetActorByName("HPText")->GetComponent<kda::TextRenderComponent>()->SetText(std::to_string(m_scene->GetActor<kda::Player>()->getHP()));
		break;
	case PlatformGame::eState::PlayerDead:
		m_scene->ActivateAll(false);
		m_scene->GetActorByName("Enemy")->destroyed = true;
		m_scene->GetActorByName("Grape")->destroyed = true;
		m_scene->GetActorByName("Player")->destroyed = true;
		m_scene->GetActorByName("Background")->active= true;
		m_state = eState::StartLevel;
		break;
	case PlatformGame::eState::YouWin:
		m_scene->GetActorByName("Player")->active = false;
		m_scene->GetActorByName("Enemy")->active = false;
		m_scene->ActivateAllWithTag("Ground", false);
		m_scene->GetActorByName("HPText")->active = false;
		m_scene->GetActorByName("YouWin")->active = true;
		m_scene->GetActorByName("Timer")->GetComponent<kda::TextRenderComponent>()->SetText(std::to_string(m_gameTimer));
		m_scene->GetActorByName("Timer")->transform = kda::Transform{ {800, 350},0, 1 };
		break;
	default:
		break;
	}
	m_scene->Update(dt);
}

void PlatformGame::Draw(kda::Renderer& renderer) {
	m_scene->Draw(renderer);
}

void PlatformGame::OnPlayerDead(const kda::Event& event)
{
	m_state = eState::PlayerDead;
}

void PlatformGame::OnEndLevel(const kda::Event& event)
{
	m_state = eState::YouWin;
}
