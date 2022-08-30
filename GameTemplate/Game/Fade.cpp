#include "stdafx.h"
#include "Fade.h"

namespace
{
	const float ALPHA_MULTI = 3.0f;						//�E���摜�̃��l�ɂ����鐔
	const Vector3 POSITION = { 800.0f,-420.0f,0.0f };	//�E���摜�̍��W
}

Fade::~Fade()
{

}

bool Fade::Start()
{
	//�摜�̏�����
	m_spriteRender.Init("Assets/sprite/roding/roding_back.dds",1080.0f, 1920.0f);
	m_spriteRender.SetScale(Vector3::One*3.0f);
	m_spriteRender1.Init("Assets/sprite/roding/roding.dds", 256.0f, 256.0f);
	m_spriteRender1.SetPosition(POSITION);

	return true;
}

void Fade::Update()
{
	switch (m_fadeState)
	{
	case enFadeState_FadeIn:
		m_alpha -= 0.5f * g_gameTime->GetFrameDeltaTime();
		if (m_alpha <= 0.0f) {
			m_alpha = 0.0f;
			m_fadeState = enFadeState_Idle;
		}
		break;
	case enFadeState_FadeOut:
		m_alpha += 0.5f * g_gameTime->GetFrameDeltaTime();
		if (m_alpha >= 1.5f) {
			m_alpha = 1.5f;
			m_fadeState = enFadeState_Idle;
		}
		break;
	case enFadeState_Idle:
		if (CanFlashSprite()) {
			//���l�̌v�Z
			m_alpha1 += g_gameTime->GetFrameDeltaTime() * 10.0f;
			//�����g���g�����Ƃ�0.0~1.0�����������ē_�ł���B
			//m_spriteRender1.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha1))));
		}
		break;
	}

	//m_spriteRender1.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha1))));

	m_spriteRender.Update();
	m_spriteRender1.Update();
}

void Fade::Render(RenderContext& rc)
{
	m_spriteRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_alpha));
	m_spriteRender.Draw(rc);
	m_spriteRender1.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, m_alpha));
	m_spriteRender1.Draw(rc);
}