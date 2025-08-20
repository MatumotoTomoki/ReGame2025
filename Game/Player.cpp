#include "stdafx.h"
#include "Player.h"
#include "Game.h"
Player::Player()
{
	//�A�j���[�V�����O���b�v�����[�h����
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	m_animationClips[enAnimationClip_Run].SetLoopFlag(true);

	//���f��������������
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
	//xz�̈ړ����x��0.0f�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾�B
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();
	//y�����ɂ͈ړ������Ȃ��B
	forward.y = 0.0f;
	right.y = 0.0f;
	//�_�b�V��
	float moveSpeedMultiplier = 360.0f;  // �ʏ�ړ����x
	if (g_pad[0]->IsPress(enButtonX)) {
		moveSpeedMultiplier = 720.0f;    // X�{�^���Ń_�b�V�����x
	}
	//���X�e�B�b�N�̓��͗ʂ�120.0f����Z�B
	right *= stickL.x * moveSpeedMultiplier;
	forward *= stickL.y * moveSpeedMultiplier;

	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z����B
	m_moveSpeed += right + forward;

	

	
	// �n�ʂɕt���Ă�����B
	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;         // �d�͂����Z�b�g
		m_jumpCount = 0;              // �W�����v�񐔃��Z�b�g
	}

	// A�{�^���������ꂽ��B
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		if (m_jumpCount < m_maxJumpCount)
		{
			m_moveSpeed.y = 360.0f;   // �W�����v������
			m_jumpCount++;            // �W�����v�񐔉��Z
		}
	}

	// �n�ʂɕt���Ă��Ȃ�������B
	if (!m_characterController.IsOnGround())
	{
		m_moveSpeed.y -= 12.0f;        // �d�͂�������
	}




	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	m_position = m_characterController.Execute(m_moveSpeed, 1.0f / 60.0f);

	//�G�`������ɍ��W��������B
	m_modelRender.SetPosition(m_position);

}

void Player::Rotation()
{
	//x��z�̈ړ����x����������(�X�e�B�b�N�̓��͂���������)�B
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		//�L�����N�^�[�̕�����ς���B
		m_rotation.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������B
		m_modelRender.SetRotation(m_rotation);
	}
}

void Player::ManageState()
{
	//�n�ʂɕt���Ă��Ȃ�������
	if (m_characterController.IsOnGround() == false)
	{
		//�X�e�[�g��(�W�����v��)�ɂ���
		playerState = 1;
		return;
	}
	//�n�ʂɕt���Ă�����
	//x�����̈ړ���������������
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (g_pad[0]->IsPress(enButtonX)) {
			playerState =3;    // X�{�^���Ń_�b�V����
		}
		else
		{
			playerState = 2;
		}
	}
	
	//���Ƃ��̈ړ����x������������
	else
	{
		//�X�e�[�g��0�ɂ���
		playerState = 0;
	}
}

//�A�j���[�V�����Đ�
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