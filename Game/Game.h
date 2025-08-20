#pragma once



class Player;
class Background;
class GameCamera;
class Item;
class Player;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	void InitSky();
	//ƒƒ“ƒo[•Ï”
	Player* BattleCharacter;
	Background* background;
	GameCamera* gamecamera;
	SoundSource* gamebgm;
	int itemCount = 0;
	bool deth = false;
	
private:
	ModelRender m_modelRender;
	Vector3 m_pos;
	Item* m_item;
	SkyCube* m_skyCube;
	int m_skyCubeType = enSkyCubeType_Night;
};

