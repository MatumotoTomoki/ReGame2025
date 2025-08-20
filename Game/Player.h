#pragma once
class Game;
class Player:public IGameObject
{
public:
	Player();
	~Player();
	void Update();
	void Render(RenderContext& renderContext);
	void Move();//移動処理
	void Rotation();//回転処理
	void ManageState();//ステート管理
	void PlayAnimation();//アニメーションの再生
	//ここからメンバー変数
	enum EnAnimationClip //アニメーション
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Run,
		enAnimationClip_Jump,
		enAnimationClip_Num,
	};
	AnimationClip m_animationClips[enAnimationClip_Num];//アニメーションクリップ。
	ModelRender m_modelRender; //モデルレンダー
	Vector3 m_position; //座標
	CharacterController m_characterController;//キャラクターコントローラー。
	Vector3 m_moveSpeed;//移動速度。
	Quaternion m_rotation;//クォータニオン。
	Game* m_game;
	int playerState = 0;//プレイヤーのステート（状態）を表す変数。
	int m_jumpCount = 0;
	int m_maxJumpCount = 2;
	int itemCount = 0;//アイテムの集めた数をカウントする
};

