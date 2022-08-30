#include "stdafx.h"
#include "UI.h"
#include "Player.h"

namespace
{
	const float SPRITE_SIZE = 128.0f;
}

UI::~UI()
{

}

bool UI::Start()
{
	//炎の持続時間アイコン
	m_spriteRender.Init("Assets/sprite/UI/fire.dds", SPRITE_SIZE, SPRITE_SIZE);
	m_spriteRender.SetPosition({ -890.0f,470.0f,0.0f });
	//炎の塊アイコン
	m_spriteRender1.Init("Assets/sprite/UI/fireball.dds", SPRITE_SIZE, SPRITE_SIZE);
	m_spriteRender1.SetPosition({ 750.0f,470.0f,0.0f });
	//プレイヤーの検索
	m_player = FindGO<Player>("player");

	return true;
}

void UI::Update()
{
	Font();
	m_spriteRender.Update();
	m_spriteRender1.Update();
}

void UI::Font()
{
	wchar_t wcsbuf[256];

	//炎の持続時間
	swprintf_s(wcsbuf, 256, L"%.0f", m_player->GetFireTimer());
	m_fontRender.SetText(wcsbuf);
	m_fontRender.SetPosition({ -800.0f,480.0f,0.0f });
	//m_fontRender.SetScale(1.5f);
	//炎の塊の残数
	swprintf_s(wcsbuf, 256, L"x %02d", m_player->GetFireBallNum());
	m_fontRender1.SetText(wcsbuf);
	m_fontRender1.SetPosition({ 800.0f,480.0f,0.0f });
	//m_fontRender1.SetScale(1.5f);

}

void UI::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_fontRender1.Draw(rc);
	m_spriteRender.Draw(rc);
	m_spriteRender1.Draw(rc);
}