#include "Player.h"
#include "Render/ModelManager.h"
#include "Input/InputSystem.h"
#include "Render/Render.h"
#include "PewPew.h"
#include "Framework/Scene.h"
#include "Game/SpaceGame.h"

void Player::Update(float dt)
{
	Actor::Update(dt);
	//rotation
	float rotate = 0;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kda::g_time.GetDeltaTime();

	//thrust
	float thrust = 0;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = -1;

	//fire pew pew
	bigBulletTimer += dt;
	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE)) 
	{
		//create pew pew
		float rad = GetRadius() + 20;
		kda::vec2 temp {rad, 0.0f};
		temp = temp.Rotate(m_transform.rotation);

		kda::vec2 temp2 {-rad, 0.0f};
		temp2 = temp2.Rotate(m_transform.rotation);

		kda::Transform transform1{temp + m_transform.position, m_transform.rotation + kda::DegreesToRadians(10.0f), 1 };
		std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew> ( 400.0f, transform1, kda::g_manager.get("PlayerBullet.txt"));
		pewPew->m_tag = "Player";
		m_scene->Add(std::move(pewPew));

		kda::Transform transform2{ temp2 + m_transform.position, m_transform.rotation - kda::DegreesToRadians(10.0f), 1 };
		pewPew = std::make_unique<PewPew>(400.0f, transform2, kda::g_manager.get("PlayerBullet.txt"));
		pewPew->m_tag = "Player";
		m_scene->Add(std::move(pewPew));

		kda::g_audioSystem.PlayOneShot("Laser_shot");

		m_game->AddPoints(10);
	}
	else if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_V) && !kda::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_V) && bigBulletTimer >= bigBulletCooldown) {
		float rad = GetRadius() + 100;
		kda::vec2 temp {0.0f, -rad};
		temp = temp.Rotate(m_transform.rotation);

		kda::Transform transform1{temp + m_transform.position, m_transform.rotation + kda::DegreesToRadians(10.0f), 5 };
		std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>(400.0f, transform1, kda::g_manager.get("PlayerBullet.txt"));
		pewPew->m_tag = "Big";
		m_scene->Add(std::move(pewPew));

		kda::g_audioSystem.PlayOneShot("Laser_shot");

		bigBulletTimer = 0;
	}

	if (kda::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kda::g_time.SetTimeScale(.5);
	else kda::g_time.SetTimeScale(1);

	kda::vec2 forward = kda::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust);

	m_transform.position.x = kda::Wrap(m_transform.position.x, (float)kda::g_renderer.getWidth());
	m_transform.position.y = kda::Wrap(m_transform.position.y, (float)kda::g_renderer.getHeight());

}

void Player::OnCollision(Actor* actor)
{
	hp -= 5;

	m_game->m_hp -= 5;

	if (hp <= 0) {
		m_game->SetLives(m_game->GetLives() - 1);
		dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDeadStart);
		m_destroyed = true;

		m_game->m_hp = 100;

		kda::g_audioSystem.PlayOneShot("Explosion");
	}
}
