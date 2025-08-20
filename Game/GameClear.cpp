#include "stdafx.h"
#include "GameClear.h"
#include"Title.h"

GameClear::GameClear()
{
	spriteRender.Init("Assets/sprite/GameClear.DDS",1920.0f, 1080.0f);
	 g_soundEngine->ResistWaveFileBank(3, "Assets/sound/GameClear.wav");
    SoundSource* bgm = NewGO<SoundSource>(0);
    bgm->Init(3);      
    bgm->Play(false);   
    bgm->SetVolume(3.5f);  // ‰¹—Ê’²®
}

GameClear::~GameClear()
{

}

void GameClear::Update()
{
	if (g_pad[0]->IsTrigger(enButtonX))
	{
		NewGO<Title>(0, "title");
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
}