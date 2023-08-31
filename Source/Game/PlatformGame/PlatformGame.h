#pragma once
#include "Framework/Game.h"
#include "Framework/Event/EventManager.h"
#include "Render/Text.h"

class PlatformGame : public kda::Game, kda::IEventListener
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		PlayerDeadStart,
		GameOver,
		GameOverStart,
		YouWin
	};

public:
	virtual bool Initialize() override;
	virtual void Shutdown() override;
	virtual void Update(float dt) override;
	virtual void Draw(kda::Renderer& renderer) override;

	void SetState(eState state) { m_state = state; }
	void OnPlayerDead(const kda::Event& event);
	void OnEndLevel(const kda::Event& event);

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;

	float m_stateTimer = 3;
	float m_gameTimer = 0;

	std::shared_ptr<kda::Font> m_font;
	std::shared_ptr<kda::Text> m_TimerText;
};