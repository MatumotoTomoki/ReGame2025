#include "stdafx.h"
#include "Title.h"
#include"Game.h"
#include"Loading.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
Title::Title()
{
	spriteRender.Init("Assets/sprite/Title.dds", 1920.0f, 1080.0f);
	//タイトルのBGMを読み込む。
	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/Title.wav");
	//タイトルのBGMを再生する。
	titleBGM = NewGO<SoundSource>(0);
	titleBGM->Init(0);
	titleBGM->Play(true);
	//文字を設定する
	fonRender.SetText(L"Yボタンを押してGameStart");
	fonRender.SetPosition({ -220.0f,-200.0f,0.0f });
	fonRender.SetColor(1.0f,1.0f,1.0f,1.0f);
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/kettteionn.wav");
}

Title::~Title()
{
	//タイトルのBGMを削除する。
	DeleteGO(titleBGM);
}

void Title::Update()
{
	static bool isFastBlink = false;
	static int blinkTimer = 0;
	float maxColor = 1.0f;
	float enptGhost = 0.0f;
	float color = 1.0f;

	float colorStep = isFastBlink ? 0.05f : 0.006f;
	if (m_color >= maxColor)
	{
		m_color = 1.0f;
	}
	if (m_color <= enptGhost)
	{
		m_color = 0.0f;
	}
	if (m_color < maxColor and m_colorSteto == false)
	{
		m_color += colorStep;
	}
	if (m_color >= maxColor)
	{
		m_colorSteto = true;
	}
	if (m_colorSteto == true)
	{
		m_color -= colorStep;
		if (m_color <= 0.4f)
		{
			m_colorSteto = false;
		}
	}
	fonRender.SetColor({ m_color,m_color,m_color,m_color });
	
	
	if (!isFastBlink && g_pad[0]->IsTrigger(enButtonY))
	{
		isFastBlink = true;
		blinkTimer = 60;
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(5);
		se->Play(false);
		se->SetVolume(3.5f);
	}

	// 高速点滅中かつ時間経過したらゲームへ遷移
	if (isFastBlink && --blinkTimer <= 0)
	{
		NewGO<Loading>(0);
		DeleteGO(this);
	}

}

void Title::Render(RenderContext& rc)
{
	spriteRender.Draw(rc);
	fonRender.Draw(rc);
}