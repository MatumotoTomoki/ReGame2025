#include "stdafx.h"
#include "Background.h"

Background::Background()
{
	m_modelRender.Init("Assets/modelData/stage.tkm");
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
}

Background::~Background()
{

}

void Background::Render(RenderContext& rc)
{
	//���f����`�悷��B
	m_modelRender.Draw(rc);
}