#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace
{
	const float CAMERA_FAR = 10000.0f;
	const float TARGET_Y = 100.0f;
}

bool GameCamera::Start()
{
	//カメラの初期設定
	m_toCameraPos.Set(0.0f, 200.0f, -300.0f);
	g_camera3D->SetFar(CAMERA_FAR);

	//プレイヤーの検索
	m_player = FindGO<Player>("player");

	return true;
}

void GameCamera::UpdatePositionAndTarget()
{
	//注視点の計算
	Vector3 target = m_player->GetPosition();
	//Y座標を少し上げる
	target.y += TARGET_Y;

	//視点を計算する
	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(target);
}

void GameCamera::Update()
{
	UpdatePositionAndTarget();
	//カメラの更新
	g_camera3D->Update();
}