#pragma once
#include "sound/SoundSource.h"

class Player;

class Fire : public IGameObject
{
public:
	Fire() {};
	~Fire();
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(Vector3& pos)
	{
		m_position = pos;
	}

private:
	/// <summary>
	/// 取る前の炎の塊エフェクト
	/// </summary>
	void PlayFireEffect(bool flag);
	/// <summary>
	/// エフェクトの再生
	/// </summary>
	void PlayGetEffect();
	/// <summary>
	/// 効果音の再生
	/// </summary>
	void PlaySE();

	Vector3 m_position = Vector3::Zero;					//座標
	Vector3 m_lightPos = Vector3::Zero;					//ポイントライトの座標
	Player* m_player = nullptr;							//プレイヤー
	std::vector< PointLight*> m_lightArray;				//ポイントライト
	PointLight* m_light = nullptr;						//ポイントライトのポインタ
	bool m_fireFlag = 1;								//取得前の炎エフェクト用フラグ
	EffectEmitter* m_effectEmitter = nullptr;			//取得前の炎エフェクト
	SoundSource* m_sound = nullptr;						//取得音
};

