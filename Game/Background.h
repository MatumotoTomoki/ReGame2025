#pragma once
class Background : public IGameObject
{
public:
	Background();
	~Background();
	void Render(RenderContext& rc);
	ModelRender m_modelRender;
	PhysicsStaticObject physicsStaticObject;
};

