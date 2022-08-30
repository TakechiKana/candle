#include "stdafx.h"
#include "Fire.h"
#include "Player.h"

#include "sound/SoundEngine.h"

//EffectEmitter
#include "graphics/effect/EffectEmitter.h"

namespace
{
	const float DISTANCE = 70.0f;
	const float FIRETIMER = 20.0f;
	const float LIGHT_POW_PARAM = 5.0f;
	const float LIGHT_RANGE = 300.0f;
	const float LIGHT_POS_Y = 150.0f;
}

Fire::~Fire()
{
	for (auto ptLig : m_lightArray) {
		delete ptLig;
	}
}

bool Fire::Start()
{
	//取得音初期化
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/fire/get.wav");

	//炎の塊の取得エフェクト
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/fireparticle.efk");

	//炎の塊エフェクト
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fireball1.efk");
	//エフェクトを発生させる。
	m_effectEmitter = NewGO<EffectEmitter>(0);
	//ResistEffect関数で指定した番号を指定する。
	m_effectEmitter->Init(0);
	//大きさを設定する。
	m_effectEmitter->SetScale(Vector3::One * 11.0f);
	Vector3 effectPosition = m_position;
	//座標を少し上にする。
	effectPosition.y += 30.0f;
	//座標を設定する。
	m_effectEmitter->SetPosition(effectPosition);
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

	//プレイヤーを検索
	m_player = FindGO<Player>("player");

	return true;
}

void Fire::Update()
{
	if (m_player->GetPlayerState() == Player::enPlayerState_Down)
	{
		DeleteGO(this);
	}
	//ポイントライトの座標
	m_lightPos = m_position;
	m_lightPos.y += LIGHT_POS_Y;
	m_light->SetPosition(m_lightPos);
	//ポイントライトの更新
	m_light->Update();

	////炎の塊エフェクト
	//PlayFireEffect(1);

	if (m_effectEmitter != nullptr) {
		if (m_effectEmitter->IsPlay() == false)
		{
			//エフェクトを発生させる。
			m_effectEmitter = NewGO<EffectEmitter>(0);
			//ResistEffect関数で指定した番号を指定する。
			m_effectEmitter->Init(0);
			//大きさを設定する。
			m_effectEmitter->SetScale(Vector3::One * 11.0f);
			Vector3 effectPosition = m_position;
			//座標を少し上にする。
			effectPosition.y += 30.0f;
			//座標を設定する。
			m_effectEmitter->SetPosition(effectPosition);
			//エフェクトを再生する。
			m_effectEmitter->Play();
		}
	}
	

	//プレイヤーと炎までのベクトル
	Vector3 diff = m_player->GetPosition() - m_position;
	//二点間のベクトルが一定の距離になったら
	if (diff.Length() <= DISTANCE)
	{
		//PlayFireEffect(0);
		//取得エフェクト再生
		PlayGetEffect();
		//効果音再生
		PlaySE();
		//炎の持続時間を加算する
		m_player->PlusFireTimer(FIRETIMER);
		//炎の塊の数を減らす
		m_player->SetFireBallNum(1);
		//自クラスを削除
		DeleteGO(this);
	}
}

void Fire::PlayFireEffect(bool flag)
{
	if (!m_player->GetPlayerState() == Player::enPlayerState_Down)
	{
		DeleteGO(this);
	}

	if (!flag)
	{
		//エフェクトを発生させる。
		m_effectEmitter = NewGO<EffectEmitter>(0);
		//ResistEffect関数で指定した番号を指定する。
		m_effectEmitter->Init(0);
		//大きさを設定する。
		m_effectEmitter->SetScale(Vector3::One * 11.0f);
		Vector3 effectPosition = m_position;
		//座標を少し上にする。
		effectPosition.y += 30.0f;
		//座標を設定する。
		m_effectEmitter->SetPosition(effectPosition);
		//エフェクトを再生する。
		m_effectEmitter->Play();
	}

	if (!flag)
	{
		if (m_effectEmitter->IsPlay())
		{
			m_effectEmitter->Stop();
		}
		return;
	}
	if (m_effectEmitter != nullptr) {
		if (m_effectEmitter->IsPlay() == false)
		{
			//エフェクトを発生させる。
			m_effectEmitter = NewGO<EffectEmitter>(0);
			//ResistEffect関数で指定した番号を指定する。
			m_effectEmitter->Init(0);
			//大きさを設定する。
			m_effectEmitter->SetScale(Vector3::One * 11.0f);
			Vector3 effectPosition = m_position;
			//座標を少し上にする。
			effectPosition.y += 30.0f;
			//座標を設定する。
			m_effectEmitter->SetPosition(effectPosition);
			//エフェクトを再生する。
			m_effectEmitter->Play();
		}
	}
}

void Fire::PlaySE()
{
	m_sound = NewGO<SoundSource>(0);
	m_sound->Init(2);
	m_sound->Play(false);
	m_sound->SetVolume(0.3f);

}

void Fire::PlayGetEffect()
{
	//エフェクトを発生させる。
	EffectEmitter* effectEmitter1 = NewGO<EffectEmitter>(0);
	//ResistEffect関数で指定した番号を指定する。
	effectEmitter1->Init(1);
	//大きさを設定する。
	effectEmitter1->SetScale(Vector3::One * 11.0f);
	Vector3 effectPosition = m_position;
	//座標を少し上にする。
	effectPosition.y += 30.0f;
	//座標を設定する。
	effectEmitter1->SetPosition(effectPosition);
	//エフェクトを再生する。
	effectEmitter1->Play();
}