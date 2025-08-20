#include "stdafx.h"
#include "Player.h"
#include "Game.h"
Player::Player()
{
	//アニメーショングリップをロードする
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	//モデルを初期化する
	m_modelRender.Init("Assets/modelData/unityChan.tkm",m_animationClips,enAnimationClip_Num,enModelUpAxisY);
	m_characterController.Init(25.0f, 75.0f, m_position);
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

Player::~Player()
{
	
}

void Player::Update()
{
	Move();
	Rotation();
	ManageState();
	PlayAnimation();
	if (m_position.y < -1200.0f) {
		m_game->deth = true;
	}
	m_modelRender.Update();
}

void Player::Move()
{
	//xzの移動速度を0.0fにする。
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得。
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;
	//ダッシュ
	float moveSpeedMultiplier = 360.0f;  // 通常移動速度
	if (g_pad[0]->IsPress(enButtonX)) {
		moveSpeedMultiplier = 720.0f;    // Xボタンでダッシュ速度
	}
	//左スティックの入力量と120.0fを乗算。
	right *= stickL.x * moveSpeedMultiplier;
	forward *= stickL.y * moveSpeedMultiplier;

	//移動速度にスティックの入力量を加算する。
	m_moveSpeed += right + forward;

	

	
	// 地面に付いていたら。
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;         // 重力をリセット
		m_jumpCount = 0;              // ジャンプ回数リセット
	}

	// Aボタンが押されたら。
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_jumpCount < m_maxJumpCount)
		{
			m_moveSpeed.y = 360.0f;   // ジャンプさせる
			m_jumpCount++;            // ジャンプ回数加算
		}
	}

	// 地面に付いていなかったら。
	if (!m_characterController.IsOnGround())
	{
		m_moveSpeed.y -= 12.0f;        // 重力を加える
	}




	//キャラクターコントローラーを使って座標を移動させる。
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//絵描きさんに座標を教える。
	m_modelRender.SetPosition(m_position);

}

void Player::Rotation()
{
	//xかzの移動速度があったら(スティックの入力があったら)。
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//キャラクターの方向を変える。
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える。
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{
	//地面に付いていなかったら
	if (m_characterController.IsOnGround() == false)
	{
		//ステートを(ジャンプ中)にする
		playerState = 1;
		return;
	}
	//地面に付いていたら
	//xかｚの移動処理があったら
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (g_pad[0]->IsPress(enButtonX)) {
			playerState =3;    // Xボタンでダッシュ中
		}
		else
		{
			playerState = 2;
		}
	}
	
	//ｘとｙの移動速度が無かったら
	else
	{
		//ステートを0にする
		playerState = 0;
	}
}

//アニメーション再生
void Player::PlayAnimation()
{
	switch (playerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;
	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;
	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;
	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;
	}
}
void Player::Render(RenderContext& renderContext)
{
	m_modelRender.Draw(renderContext);
}