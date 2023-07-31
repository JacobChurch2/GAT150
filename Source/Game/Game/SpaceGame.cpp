#include "SpaceGame.h"
#include "Player.h"
#include "Framework/Actor.h"
#include "Enemy.h"
#include "Framework/Game.h"

#include "Framework/Scene.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "Render/Text.h"
#include "Render/ModelManager.h"
#include "Framework/Emitter.h"

bool SpaceGame::Initialize()
{
	// create font / text objects
	m_font = std::make_shared<kda::Font> ("ggtype.ttf", 24);
	m_scoreText = std::make_unique<kda::Text>(m_font);
	m_scoreText->Create(kda::g_renderer, "Score 0000", kda::Color{ 1, 1, 1, 1 });

	m_titleText = std::make_unique<kda::Text>(m_font);
	m_titleText->Create(kda::g_renderer, "Create Your Own Bullet Hell", kda::Color{ 1, 1, 1, 1 });

	m_gameoverText = std::make_unique<kda::Text>(m_font);
	m_gameoverText->Create(kda::g_renderer, "Game Over", kda::Color{ 1, 1, 1, 1 });

	m_hpText = std::make_unique<kda::Text>(m_font);
	m_hpText->Create(kda::g_renderer, "HP: ", kda::Color{ 1, 1, 1, 1 });
	
	//load Audio
	kda::g_audioSystem.AddAudio("Laser_shot", "Laser_Shoot.wav");
	kda::g_audioSystem.AddAudio("Explosion", "Explosion.wav");
	kda::g_audioSystem.AddAudio("Music", "Music.wav");

	//Scene
	m_Scene = std::make_unique<kda::Scene>();

	return true;
}

void SpaceGame::Shutdown()
{
}

void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		kda::g_audioSystem.PlayOneShot("Music", true);
		break;
	case SpaceGame::eState::StartLevel:
		m_Scene->RemoveAll();
	{
		std::unique_ptr<Player> player = std::make_unique<Player>(10.0f, kda::Pi, kda::Transform{ { 400, 300 }, 0, 6 }, kda::g_manager.get("Ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		player->SetDamping(0.9f);
		m_Scene->Add(move(player));
	}
		m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kda::randomf(50.0f, 75.0f), kda::Pi, kda::Transform{ { kda::random(800), kda::random(600)}, kda::randomf(kda::TwoPi), 6}, kda::g_manager.get("Enemy.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_Scene->Add(move(enemy));

			AddPoints(100);
		}

		break;

	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives == 0) m_state = eState::GameOver;
		else m_state = eState::PlayerDead;
		break;
	case SpaceGame::eState::PlayerDead:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_state = eState::StartLevel;
		}
		break;
	case SpaceGame::eState::GameOver:
		m_stateTimer -= dt;
		if (m_stateTimer, +0) {
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(kda::g_renderer, std::to_string(m_score), {1,1,1,1});
	m_hpText->Create(kda::g_renderer, "HP: " + std::to_string(m_hp), { 1,1,1,1 });

	m_Scene->Update(dt);
}

void SpaceGame::Draw(kda::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 150, 300);
	}

	if (m_state == eState::GameOver)
	{
		m_gameoverText->Draw(renderer, 300, 300);
	}

	if (m_state == eState::Game || m_state == eState::GameOver || m_state == eState::PlayerDeadStart || m_state == eState::PlayerDead) {
		m_scoreText->Draw(renderer, 40, 40);
		m_hpText->Draw(renderer, 650, 550);
	}
	m_Scene->Draw(renderer);
}
