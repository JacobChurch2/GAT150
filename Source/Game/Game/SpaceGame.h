#pragma once
#include "Framework/Game.h"
#include "Render/Text.h"

class SpaceGame : public kda::Game {
	public:
		enum class eState {
			Title,
			StartGame,
			StartLevel,
			Game,
			PlayerDead,
			PlayerDeadStart,
			GameOver,
			GameOverStart
		};

	public:
		virtual bool Initialize() override;
		virtual void Shutdown() override;
		virtual void Update(float dt) override;
		virtual void Draw(kda::Renderer& renderer) override;

		void SetState(eState state) { m_state = state; }

	private:
		eState m_state = eState::Title;
		float m_spawnTimer = 0;
		float m_spawnTime = 3;

		float m_stateTimer = 3;

		std::shared_ptr<kda::Font> m_font;
		std::shared_ptr<kda::Text> m_scoreText;
		std::shared_ptr<kda::Text> m_titleText;
		std::shared_ptr<kda::Text> m_gameOverText;
};