#pragma once
class Game;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& renderContext);
	void Move();//�ړ�����
	void Rotation();//��]����
	void ManageState();//�X�e�[�g�Ǘ�
	void PlayAnimation();//�A�j���[�V�����̍Đ�
	//�������烁���o�[�ϐ�
	enum EnAnimationClip //�A�j���[�V����
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];//�A�j���[�V�����N���b�v�B
	ModelRender m_modelRender; //���f�������_�[
	Vector3 m_position; //���W
	CharacterController m_characterController;//�L�����N�^�[�R���g���[���[�B
	Vector3 m_moveSpeed;//�ړ����x�B
	Quaternion m_rotation;//�N�H�[�^�j�I���B
	Game* m_game;
	int playerState = 0;//�v���C���[�̃X�e�[�g�i��ԁj��\���ϐ��B
	int m_jumpCount = 0;
	int m_maxJumpCount = 2;
	int itemCount = 0;//�A�C�e���̏W�߂������J�E���g����
};

