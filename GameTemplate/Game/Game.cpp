#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Fire.h"
#include "UI.h"
#include "Result.h"
#include "Fade.h"
#include "Clear.h"

Game::~Game()
{
	DeleteGO(m_bg);
	DeleteGO(m_gamecam);
	DeleteGO(m_ui);
	DeleteGO(m_player);
}

bool Game::Start()
{
	//フェードの検索
	m_fade = FindGO<Fade>("fade");
	//m_modelRender.Init("Assets/modelData/unityChan.tkm");
	
	m_levelRender.Init("Assets/level3D/stage1.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"stage1") == true)
			{
				//背景クラスの生成
				m_bg = NewGO<BackGround>(0, "background");
				//座標、スケール、回転の設定。
				m_bg->SetPosition(objData.position);
				m_bg->SetRotation(objData.rotation);
				m_bg->SetScale(objData.scale);

				return true;
			}
			if (objData.EqualObjectName(L"candle") == true)
			{
				//プレイヤークラスの生成
				m_player = NewGO<Player>(0, "player");
				//座標、スケール、回転の設定。
				m_player->SetPosition(objData.position);
				m_player->SetRotation(objData.rotation);
				m_player->SetScale(objData.scale);

				return true;
			}
			if (objData.EqualObjectName(L"fire") == true)
			{
				m_fire = NewGO<Fire>(0, "fire");
				//座標の設定
				m_fire->SetPosition(objData.position);
				//総数の計算
				m_player->SetFireBallNum(0);

				m_fires.push_back(m_fire);
			}
			if (objData.EqualObjectName(L"clear") == true)
			{
				m_clear = NewGO<Clear>(0, "clear");
				//ゴール地点座標の設定
				m_clear->SetPosition(objData.position);
			}
			return true;
		});

	//カメラの生成
	m_gamecam = NewGO<GameCamera>(0, "gamecamera");
	//UIの生成
	m_ui = NewGO<UI>(0, "ui");
	//このクラスをフェードインさせる
	m_fade->StartFadeIn();

	return true;
}

void Game::Update()
{
	if (m_fade->IsFade())
	{
		m_result = NewGO<Result>(0, "result");
		if (m_player->GetPlayerState() == Player::enPlayerState_Clear)
		{
			m_result->SetClearState();
		}
		DeleteGO(this);
	}
	if (!m_player->IsPlayAnimation())
	{
		m_fade->StartFadeOut();
	}
}

void Game::Lighting()
{

}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}