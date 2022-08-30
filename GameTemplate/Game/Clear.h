#pragma once

class Player;

class Clear : public IGameObject
{
public:
	Clear() {};
	~Clear();
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

	void FullFillClearCondition();
	

private:
	/// <summary>
	/// 到達エフェクトの再生
	/// </summary>
	void PlayArriveEffect();
	/// <summary>
	/// 効果音の再生
	/// </summary>
	void PlaySE();

	Vector3 m_position = Vector3::Zero;					//座標
	Vector3 m_lightPos = Vector3::Zero;					//ポイントライトの座標
	Player* m_player = nullptr;							//プレイヤー
	std::vector< PointLight*> m_lightArray;				//ポイントライト
	PointLight* m_light = nullptr;						//ポイントライトのポインタ
	bool m_clearFlag = 0;								//クリア条件を満たしているか
	EffectEmitter* m_effectEmitter = nullptr;			//取得前の炎エフェクト
};

