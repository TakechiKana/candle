#include "stdafx.h"
#include "Clear.h"
#include "Player.h"

//EffectEmitter
#include "graphics/effect/EffectEmitter.h"

namespace
{
	const float DISTANCE = 70.0f;
	const float LIGHT_POW_PARAM = 5.0f;
	const float LIGHT_RANGE = 300.0f;
	const float LIGHT_POS_Y = 150.0f;
}

Clear::~Clear()
{
	for (auto ptLig : m_lightArray) {
		delete ptLig;
	}
}

bool Clear::Start()
{
	//クリア座標エフェクト
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/clear.efk");
	//取得エフェクト
	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/clearParticle.efk");
	//クリア音の登録
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/clear/clear.wav");

	//プレイヤーを検索
	m_player = FindGO<Player>("player");

	return true;
}

void Clear::Update()
{
	if (m_player->GetPlayerState() == Player::enPlayerState_Down)
	{
		DeleteGO(this);
	}
	if (!m_clearFlag)
	{
		if (m_player->GetFireBallNum() == 0)
		{
			FullFillClearCondition();
			m_clearFlag = 1;
		}
		return;
	}

	//ポイントライトの座標
	m_lightPos = m_position;
	m_lightPos.y += LIGHT_POS_Y;
	m_light->SetPosition(m_position);
	//ポイントライトの更新
	m_light->Update();

	if (m_effectEmitter != nullptr) {
		if (m_effectEmitter->IsPlay() == false)
		{
			//エフェクトを発生させる。
			m_effectEmitter = NewGO<EffectEmitter>(0);
			//ResistEffect関数で指定した番号を指定する。
			m_effectEmitter->Init(2);
			//大きさを設定する。
			m_effectEmitter->SetScale(Vector3::One * 11.0f);
			//座標を設定する。
			m_effectEmitter->SetPosition(m_position);
			//エフェクトを再生する。
			m_effectEmitter->Play();
		}
	}


	//プレイヤーと炎までのベクトル
	Vector3 diff = m_player->GetPosition() - m_position;
	//二点間のベクトルが一定の距離になったら
	if (diff.Length() <= DISTANCE)
	{
		m_effectEmitter->Stop();
		//取得エフェクト再生
		PlayArriveEffect();
		//効果音再生
		PlaySE();
		//プレイヤーをクリアステートにする
		m_player->SetClearState();
		//自クラスを削除
		DeleteGO(this);
	}
}

void Clear::FullFillClearCondition()
{
	//エフェクトを発生させる。
	m_effectEmitter = NewGO<EffectEmitter>(0);
	//ResistEffect関数で指定した番号を指定する。
	m_effectEmitter->Init(2);
	//大きさを設定する。
	m_effectEmitter->SetScale(Vector3::One * 11.0f);

	//座標を設定する。
	m_effectEmitter->SetPosition(m_position);
	//エフェクトを再生する。
	m_effectEmitter->Play();


	//ポイントライトのオブジェクトを作る。
	m_light = new PointLight;
	m_light->Init();
	m_light->SetColor(Vector3(0.7f, 0.7f, 0.7f));
	m_light->SetAffectPowParam(LIGHT_POW_PARAM);
	m_light->SetRange(LIGHT_RANGE);
	m_light->SetPosition(m_lightPos);
	m_lightArray.push_back(m_light);

}

void Clear::PlaySE()
{
	SoundSource* se = NewGO<SoundSource>(0);
	se->Init(6);
	se->Play(false);
	se->SetVolume(0.3f);
}

void Clear::PlayArriveEffect()
{
	//エフェクトを発生させる。
	EffectEmitter* effectEmitter1 = NewGO<EffectEmitter>(0);
	//ResistEffect関数で指定した番号を指定する。
	effectEmitter1->Init(3);
	//大きさを設定する。
	effectEmitter1->SetScale(Vector3::One * 11.0f);
	Vector3 effectPosition = m_position;
	//座標を少し上にする。
	effectPosition.y += 10.0f;
	//座標を設定する。
	effectEmitter1->SetPosition(effectPosition);
	//エフェクトを再生する。
	effectEmitter1->Play();
}