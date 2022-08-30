#pragma once
#include "sound/SoundSource.h"
#include "graphics/postEffect/Sepia.h"
class Result;
class Game;

class Player : public IGameObject
{
public:
	enum EnPlayerState
	{
		enPlayerState_Idle,
		enPlayerState_Walk,
		enPlayerState_Jump,
		enPlayerState_Down,
		enPlayerState_Clear
	};
public:
	Player() {};
	~Player();
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
	/// 描画処理
	/// </summary>
	/// <param name="rc">レンダーコンテキスト</param>
	void Render(RenderContext& rc);
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();
	/// <summary>
	/// 回転処理
	/// </summary>
	void Rotation();
	/// <summary>
	/// ステート遷移
	/// </summary>
	void TransitionState();
	/// <summary>
	/// ステート管理
	/// </summary>
	void ManageState();
	/// <summary>
	/// 待機ステート
	/// </summary>
	void IdleState();
	/// <summary>
	/// 歩きステート
	/// </summary>
	void WalkState();
	/// <summary>
	/// ジャンプステート
	/// </summary>
	void JumpState();
	/// <summary>
	/// ダウンステート
	/// </summary>
	void DownState();
	/// <summary>
	/// クリアステート
	/// </summary>
	void ClearState();
	/// <summary>
	/// 持続時間の処理
	/// </summary>
	void CountFireTimer();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const bool IsEnableMove()
	{
		return m_playerState != enPlayerState_Clear
			&& m_playerState != enPlayerState_Down;
	}

	/// <summary>
	/// 座標設定
	/// </summary>
	/// <param name="pos">座標</param>
	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">回転</param>
	void SetRotation(Quaternion rot)
	{
		m_rot = rot;
	}
	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(Vector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// 座標取得
	/// </summary>
	const Vector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// 回転取得
	/// </summary>
	const Quaternion GetQuaternion()
	{
		return m_rot;
	}
	/// <summary>
	/// 拡大率の取得
	/// </summary>
	const Vector3 GetScale()
	{
		return m_scale;
	}
	/// <summary>
	/// 炎の持続時間の取得
	/// </summary>
	/// <returns></returns>
	const float GetFireTimer()
	{
		return m_fireTimer;
	}
	/// <summary>
	/// アイテムを拾った時に、炎の持続時間を増やす
	/// </summary>
	/// <param name="fireTimer">加算する時間</param>
	void PlusFireTimer(float fireTimer)
	{
		m_fireTimer += fireTimer;
	}
	/// <summary>
	/// 炎の塊の数
	/// </summary>
	/// <param name="flag">0->加算、1->減算</param>
	void SetFireBallNum(bool flag)
	{
		switch (flag)
		{
		case 0:
			m_fireBallNum += 1;
			break;
		case 1:
			m_fireBallNum -= 1;
			break;
		default:
			break;
		}
	}
	/// <summary>
	/// 炎の塊の数を取得
	/// </summary>
	/// <returns></returns>
	const int GetFireBallNum()
	{
		return m_fireBallNum;
	}
	/// <summary>
	/// ゴール座標の設定
	/// </summary>
	/// <param name="pos">ゴールの座標</param>
	void SetClearPosition(Vector3& pos)
	{
		m_clearPos = pos;
	}
	/// <summary>
	/// クリア地点に到達したか
	/// </summary>
	void SetClearState()
	{
		m_playerState = enPlayerState_Clear;
	}

	const EnPlayerState GetPlayerState()
	{
		return m_playerState;
	}

	const bool IsPlayAnimation()
	{
		return m_isPlayingAnimation;
	}


private:
	/// <summary>
	/// アニメーション再生
	/// </summary>
	void PlayAnimation();

	enum EnAnimationClips
	{
		enAnimationClip_Idle,
		enAnimationClip_Walk,
		enAnimationClip_Jump,
		enAnimationClip_Down,
		enAnimationClip_Clear,
		enAnimationClip_Num
	};

	std::vector< PointLight*> m_lightArray;				//ポイントライト
	PointLight* m_light = nullptr;						//ポイントライトのポインタ
	Vector3 m_position = Vector3::Zero;					//座標
	Vector3 m_lightPos = Vector3::Zero;					//ポイントライトの座標
	Vector3 m_clearPos = Vector3::Zero;					//ゴール座標
	Vector3 m_scale = Vector3::One;						//拡大率
	Quaternion m_rot = Quaternion::Identity;			//回転
	EnPlayerState m_playerState = enPlayerState_Idle;	//ステート
	ModelRender m_modelRender;							//モデル
	CharacterController m_charaCon;						//キャラコン

	AnimationClip m_animationClips[enAnimationClip_Num]; //アニメーションクリップ

	Vector3 m_moveSpeed = Vector3::Zero;				//移動速度
	Vector3 m_oldSpeed = Vector3::Zero;					//1フレーム前の位置
	bool m_isJump = false;								//ジャンプフラグ
	bool m_isDown = false;								//ダウンフラグ
	bool m_isPlayingAnimation = true;					//アニメーションが終わったか
	float m_timer = 0.0f;								//セピア用
	float m_fireTimer = 0.0f;							//炎がついている時間
	int m_fireBallNum = 0;								//炎の塊の数
	EffectEmitter* m_effectEmitter = nullptr;			//炎エフェクト
	SoundSource* m_stepSound = nullptr;					//足音
	SoundSource* m_downSound = nullptr;					//ダウンの音
	SoundSource* m_jumpSound = nullptr;					//ジャンプ音
	Sepia m_sepia;										//セピア
};

