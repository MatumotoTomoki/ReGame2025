#pragma once
class Player;
class Game;
class Item :public IGameObject
{
public:
	Item();
	~Item();
	void Render(RenderContext& rc);
	void Update();
	void Rotation();
	void Move();
	Quaternion rot;
	ModelRender m_modelRender;
	Player* BattleCharacter;
	Vector3 m_position;
	Game* game;
};

