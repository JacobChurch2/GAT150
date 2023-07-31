#pragma once
#include "Framework/Game.h"
#include "Render/Text.h"

class SpaceGame : public kda::Game
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDeadStart,
		PlayerDead,
		GameOverStart,
		GameOver
	};
public:


	// Inherited via Game
	virtual bool Initialize() override;

	virtual void Shutdown() override;

	virtual void Update(float dt) override;

	virtual void Draw(kda::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 10;

	float m_stateTimer = 0;

	std::shared_ptr<kda::Font> m_font;
	std::unique_ptr<kda::Text> m_scoreText;
	std::unique_ptr<kda::Text> m_titleText;
	std::unique_ptr<kda::Text> m_gameoverText;
	std::unique_ptr<kda::Text> m_hpText;
};