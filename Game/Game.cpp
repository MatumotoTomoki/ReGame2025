#include "stdafx.h"
#include "Game.h"
#include"Player.h"
#include"Background.h"
#include"GameCamera.h"
#include"Item.h"
#include"GameClear.h"
#include"GameOver.h"
#include "nature/SkyCube.h"
#include "sound/SoundEngine.h"
Game::Game()
{
	itemCount = 0;
	deth = false;

	BattleCharacter= NewGO<Player>(0, "BattleCharacter");
	 BattleCharacter-> m_game = this;

	 background= NewGO<Background>(0, " background");

	 gamecamera = NewGO<GameCamera>(0, "gamecamera");

	 Item* item1 = NewGO<Item>(0, "item");
	 item1->m_position = { 0.0f,25.0f,1100.0f };
	 item1->game = (this);
	 Item* item2 = NewGO<Item>(0, "item");
	 item2->m_position = { 0.0f,240.0f,2460.0f };
	 item2->game = (this);
	 Item* item3 = NewGO<Item>(0, "item");
	 item3->m_position = { 0.0f,740.0f,3950.0f };
	 item3->game = (this);
	 Item* item4 = NewGO<Item>(0, "item");
	 item4->m_position = { 0.0f,-870.0f,4100.0f };
	 item4->game = (this);
	 Item* item5 = NewGO<Item>(0, "item");
	 item5->m_position = { 0.0f,-380.0f,6500.0f };
	 item5->game = (this);
	 g_soundEngine->ResistWaveFileBank(4, "Assets/sound/GameBgm.wav");
	 gamebgm = NewGO<SoundSource>(0);
	 gamebgm->Init(4);
	 gamebgm->Play(true);
	 InitSky();
}

Game::~Game()
{
	//プレイヤーを削除する。
	DeleteGO(BattleCharacter);
	//ゲームカメラを削除する。
	DeleteGO(gamecamera);
	//背景を削除する。
	DeleteGO(background);	
	//ゲームBGMを削除する。
	DeleteGO(gamebgm);
}

void Game::InitSky()
{
	// 現在の空を破棄。
	DeleteGO(m_skyCube);

	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetType((EnSkyCubeType)m_skyCubeType);
	// 環境光の計算のためのIBLテクスチャをセットする。
	g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
}



bool Game::Start()
{
	return true;
}

void Game::Update()
{
	if (itemCount == 5) {
		NewGO<GameClear>(0, "gameclear");
		DeleteGO(this);
	}
	if (deth == true) {
		NewGO<GameOver>(0, "gameover");
		DeleteGO(this);
	}
}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}