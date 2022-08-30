#include "stdafx.h"
#include "Result.h"
#include "Player.h"
#include "Game.h"
#include "Title.h"
#include "Fade.h"

#include "sound/SoundEngine.h"

namespace
{
	const float RESULT_HIGH = 1080.0f;						//結果画像の高さ
	const float RESULT_WIDTH = 1920.0f;						//結果画像の幅
	const float BUTTON_HIGH = 128.0f;						//ボタンの高さ
	const float BUTTON_WIDTH = 256.0f;						//ボタンの幅
	const float ALPHA_MULTI = 2.0f;							//α値に乗算する値
}

Result::~Result()
{

}

bool Result::Start()
{
	//フェードの検索
	m_fade = FindGO<Fade>("fade");

	m_button1Pos = { 0.0f,-240.0f,0.0f };
	m_titleButtonPos = { 0.0f,-340.0f,0.0f };

	//画像初期化
	m_spriteRender.Init("Assets/sprite/result/gameover.dds", RESULT_WIDTH, RESULT_HIGH);
	m_spriteRender.SetPosition(Vector3::Zero);
	//m_spriteRender1.Init("Assets/sprite/result/retry.dds", BUTTON_WIDTH, BUTTON_HIGH);
	//m_spriteRender1.SetPosition(m_button1Pos);
	m_spriteRender2.Init("Assets/sprite/result/titlebuttun.dds", BUTTON_WIDTH, BUTTON_HIGH);
	m_spriteRender2.SetPosition(m_titleButtonPos);
	m_selectRender.Init("Assets/sprite/select.dds", BUTTON_WIDTH, BUTTON_WIDTH);
	m_selectRender.SetPosition(m_titleButtonPos);
	//レベル読み込み

	//m_level2DRender.Init("Assets/level2D/result.casl", [&](Level2DObjectData& objData)
	//	{
	//		//結果
	//		if (objData.EqualObjectName("result") == true)
	//		{
	//			m_spriteRender.SetPosition(objData.position);
	//			return true;
	//		}
	//		//タイトルボタン
	//		if (objData.EqualObjectName("button1") == true)
	//		{
	//			m_spriteRender1.SetPosition(objData.position);
	//			m_button1Pos = objData.position;
	//			return true;
	//		}
	//		//リトライボタン
	//		if (objData.EqualObjectName("retry") == true)
	//		{
	//			m_spriteRender2.SetPosition(objData.position);
	//			m_titleButtonPos = objData.position;
	//			return true;
	//		}
	//		return true;
	//	});
	//このクラスをフェードインさせる
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
		//ゲームクラスの生成
		m_title = NewGO<Title>(0, "title");
		DeleteGO(this);
	}
	//Aボタンを押したら
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		se->Play(false);
		se->SetVolume(0.5f);

		//このクラスをフェードアウトさせる
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
	//		//このクラスをフェードアウトさせる
	//		m_fade->StartFadeOut();
	//		flag = m_fade->IsFade();
	//		if (m_fade->IsFade()) {
	//			m_game = NewGO<Game>(0, "game");
	//			DeleteGO(this);
	//		}
	//		break;
	//	case enSelectButton_Title:
	//		//このクラスをフェードアウトさせる
	//		m_fade->StartFadeOut();
	//		flag = m_fade->IsFade();
	//		if (m_fade->IsFade()) {
	//			m_title = NewGO<Title>(0, "title");
	//			DeleteGO(this);
	//		}
	//		break;
	//	}
	//}
	//α値の計算
	m_alpha += g_gameTime->GetFrameDeltaTime() * ALPHA_MULTI;
	//正弦波を使うことで0.0~1.0を往来させて点滅する。
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