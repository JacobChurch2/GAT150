#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"

#include "Framework/Framework.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "Render/Text.h"
#include "Render/ParticleSystem.h"
#include "Render/Particle.h"

bool SpaceGame::Initialize(){
	//Create fonts/ text objects
	m_font = GET_RESOURCE(kda::Font, "ggtype.ttf", 24);
	m_scoreText = std::make_unique<kda::Text>(GET_RESOURCE(kda::Font, "ggtype.ttf", 24));
	m_scoreText->Create(kda::g_renderer, "0000", kda::Color{ 1, 1, 1, 1 });

	m_gameOverText = std::make_unique<kda::Text>(GET_RESOURCE(kda::Font, "ggtype.ttf", 24));
	m_gameOverText->Create(kda::g_renderer, "GAME OVER", kda::Color{ 1, 1, 1, 1 });

	//Load audio
	kda::g_audioSystem.AddAudio("hit", "Laser_Shoot.wav");
	kda::g_audioSystem.AddAudio("music", "Music.wav");

	//Scene
	m_scene = std::make_unique<kda::Scene>();
	m_scene->Load("Scene.json");
	m_scene->Initialize();

	//add events
	EVENT_SUBSCRIBE("AddPoints", SpaceGame::AddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

	return true;
}

void SpaceGame::Shutdown() {

}

void SpaceGame::Update(float dt){

	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			m_state = eState::StartGame;
			//m_scene->GetActorByName("Background")->active = false;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		kda::g_audioSystem.PlayOneShot("music", true);
		break;
	case SpaceGame::eState::StartLevel:
		m_scene->RemoveAll();
	{
		auto player = INSTANTIATE(Player, "Player");
 		/*std::unique_ptr<Player> player = std::make_unique<Player>(20.0f, kda::pi, kda::Transform{ {400, 300}, 0, 1 });
		player->tag = "Player";
		player->m_game = this;*/

		//create components
		/*auto component = CREATE_CLASS(SpriteComponent);
		component->m_texture = GET_RESOURCE(kda::Texture, "PlayerShip.png", kda::g_renderer);
		player->AddComponent(std::move(component));

		auto physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
		physicsComponent->m_damping = 0.9f;
		player->AddComponent(std::move(physicsComponent));

		auto collisionComponent = CREATE_CLASS(CircleCollisionComponent);
		collisionComponent->m_radius = 30.0f;
		player->AddComponent(std::move(collisionComponent));*/

		player->Initialize();
		m_scene->Add(std::move(player));
	}
	m_state = eState::Game;
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime) {
			m_spawnTimer = 0;

			auto enemy = INSTANTIATE(Enemy, "Enemy");
			/*std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kda::randomf(75.0f, 150.0f), kda::pi, kda::Transform((float)(kda::random(800), kda::random(600)), (float)kda::random((int)(kda::pi2), 1)));
			enemy->tag = "Enemy";
			enemy->m_game = this;

			std::unique_ptr<kda::SpriteComponent> component = std::make_unique<kda::SpriteComponent>();
			component->m_texture = GET_RESOURCE(kda::Texture, "EnemyShip.png", kda::g_renderer);
			enemy->AddComponent(std::move(component));

			auto collisionComponent = std::make_unique<kda::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));*/

			enemy->Initialize();
			m_scene->Add(std::move(enemy));
		}
		break;
	case eState::PlayerDeadStart:
		m_stateTimer = 3;
		if (m_lives <= 0) m_state = eState::GameOver;
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
		if (m_stateTimer <= 0) {
			m_scene->RemoveAll();
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}
	m_scoreText->Create(kda::g_renderer, "Score " + std::to_string(m_score), {1, 1, 1, 1});
	m_scene->Update(dt);
}

void SpaceGame::Draw(kda::Renderer& renderer){
	m_scene->Draw(renderer);

	if (m_state == eState::Title) {
		//m_titleText->Draw(renderer, 400, 300);
		m_scene->GetActorByName("Title")->active = true;
	}
	else 
	{
		m_scene->GetActorByName("Title")->active = false;
	}

	if (m_state == eState::GameOver) {
		m_gameOverText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 20);
}

void SpaceGame::AddPoints(const kda::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const kda::Event& event)
{
	m_state = eState::PlayerDeadStart;
}
