#include "stdafx.h"
#include "Item.h"
#include"Player.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include"Game.h"
Item::Item()
{
	m_modelRender.Init("Assets/modelData/Item.tkm");
	BattleCharacter = FindGO<Player>("BattleCharacter");
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/tokutenn.wav");
}

Item::~Item()
{

}

void Item:: Update()
{
	Rotation();
	Move();
	m_modelRender.Update();
	Vector3 diff = BattleCharacter->m_position - m_position;
	if (diff.Length() <= 120.0f)
	{
		//カウントを+１する
		game->itemCount += 1;
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(3.5f);
		DeleteGO(this);
	}
	if (game->deth == true) {
		DeleteGO(this);
	}
}

void Item::Rotation()
{
	rot.AddRotationDegY(100.0f);

	m_modelRender.SetRotation(rot);
}

void Item::Move()
{
	m_modelRender.SetPosition(m_position);
}

void Item::Render(RenderContext& rc)
{
	//モデルを描画する。
	m_modelRender.Draw(rc);
}