#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_modelRender.Init("Assets/modelData/background/stage1.tkm");
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rot);
	m_modelRender.SetScale(m_scale);

	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_modelRender.Update();

}

void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
