#include "stdafx.h"
#include "Result.h"
#include "Player.h"
#include "Game.h"
#include "Title.h"
#include "Fade.h"

#include "sound/SoundEngine.h"

namespace
{
	const float RESULT_HIGH = 1080.0f;						//���ʉ摜�̍���
	const float RESULT_WIDTH = 1920.0f;						//���ʉ摜�̕�
	const float BUTTON_HIGH = 128.0f;						//�{�^���̍���
	const float BUTTON_WIDTH = 256.0f;						//�{�^���̕�
	const float ALPHA_MULTI = 2.0f;							//���l�ɏ�Z����l
}

Result::~Result()
{

}

bool Result::Start()
{
	//�t�F�[�h�̌���
	m_fade = FindGO<Fade>("fade");

	m_button1Pos = { 0.0f,-240.0f,0.0f };
	m_titleButtonPos = { 0.0f,-340.0f,0.0f };

	//�摜������
	m_spriteRender.Init("Assets/sprite/result/gameover.dds", RESULT_WIDTH, RESULT_HIGH);
	m_spriteRender.SetPosition(Vector3::Zero);
	//m_spriteRender1.Init("Assets/sprite/result/retry.dds", BUTTON_WIDTH, BUTTON_HIGH);
	//m_spriteRender1.SetPosition(m_button1Pos);
	m_spriteRender2.Init("Assets/sprite/result/titlebuttun.dds", BUTTON_WIDTH, BUTTON_HIGH);
	m_spriteRender2.SetPosition(m_titleButtonPos);
	m_selectRender.Init("Assets/sprite/select.dds", BUTTON_WIDTH, BUTTON_WIDTH);
	m_selectRender.SetPosition(m_titleButtonPos);
	//���x���ǂݍ���

	//m_level2DRender.Init("Assets/level2D/result.casl", [&](Level2DObjectData& objData)
	//	{
	//		//����
	//		if (objData.EqualObjectName("result") == true)
	//		{
	//			m_spriteRender.SetPosition(objData.position);
	//			return true;
	//		}
	//		//�^�C�g���{�^��
	//		if (objData.EqualObjectName("button1") == true)
	//		{
	//			m_spriteRender1.SetPosition(objData.position);
	//			m_button1Pos = objData.position;
	//			return true;
	//		}
	//		//���g���C�{�^��
	//		if (objData.EqualObjectName("retry") == true)
	//		{
	//			m_spriteRender2.SetPosition(objData.position);
	//			m_titleButtonPos = objData.position;
	//			return true;
	//		}
	//		return true;
	//	});
	//���̃N���X���t�F�[�h�C��������
	m_fade->StartFadeIn();
	return true;
}

void Result::Update()
{
	if (m_resultState != enResultState_GameOver)
	{
		m_spriteRender.Init("Assets/sprite/result/gameclear.dds", RESULT_WIDTH, RESULT_HIGH);
	}
	if (m_fade->IsFade())
	{
		//�Q�[���N���X�̐���
		m_title = NewGO<Title>(0, "title");
		DeleteGO(this);
	}
	//A�{�^������������
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(0.5f);

		//���̃N���X���t�F�[�h�A�E�g������
		m_fade->StartFadeOut();
	}

	//if (!m_isFade) {
	//	switch (m_buttonState)
	//	{
	//	case enSelectButton_Button1:
	//		m_selectRender.SetPosition(m_button1Pos);
	//		if (g_pad[0]->IsTrigger(enButtonA))
	//		{
	//			m_isFade = 1;
	//		}
	//		if (g_pad[0]->IsTrigger(enButtonDown))
	//		{
	//			m_buttonState = enSelectButton_Title;
	//		}
	//		break;
	//	case enSelectButton_Title:
	//		m_selectRender.SetPosition(m_titleButtonPos);
	//		if (g_pad[0]->IsTrigger(enButtonA))
	//		{
	//			m_isFade = 1;
	//		}
	//		if (g_pad[0]->IsTrigger(enButtonUp))
	//		{
	//			m_buttonState = enSelectButton_Button1;
	//		}
	//		break;
	//	}
	//}
	//else
	//{
	//	bool flag;
	//	switch (m_buttonState)
	//	{
	//	case enSelectButton_Button1:
	//		//���̃N���X���t�F�[�h�A�E�g������
	//		m_fade->StartFadeOut();
	//		flag = m_fade->IsFade();
	//		if (m_fade->IsFade()) {
	//			m_game = NewGO<Game>(0, "game");
	//			DeleteGO(this);
	//		}
	//		break;
	//	case enSelectButton_Title:
	//		//���̃N���X���t�F�[�h�A�E�g������
	//		m_fade->StartFadeOut();
	//		flag = m_fade->IsFade();
	//		if (m_fade->IsFade()) {
	//			m_title = NewGO<Title>(0, "title");
	//			DeleteGO(this);
	//		}
	//		break;
	//	}
	//}
	//���l�̌v�Z
	m_alpha += g_gameTime->GetFrameDeltaTime() * ALPHA_MULTI;
	//�����g���g�����Ƃ�0.0~1.0�����������ē_�ł���B
	m_selectRender.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));

	m_spriteRender.Update();
	//m_spriteRender1.Update();
	m_spriteRender2.Update();
	m_selectRender.Update();

}

void Result::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_selectRender.Draw(rc);
	//m_spriteRender1.Draw(rc);
	m_spriteRender2.Draw(rc);
}