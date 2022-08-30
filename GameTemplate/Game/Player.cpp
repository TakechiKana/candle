#include "stdafx.h"
#include "Player.h"
//EffectEmitter
#include "graphics/effect/EffectEmitter.h"
#include "sound/SoundEngine.h"

namespace
{
	const float MOVESPEED = 300.0f;
	const float JUMP_MOVESPEED = 120.0f;
	const float JUMP = 175.0f;
	const float GRAVITY = 300.0f;
	const float FIRETIMER = 40.0f;
	const float DOWN_YPOS = -1000.0f;
	const float LIGHT_YPOS = 100.0f;
	const float LIGHT_RANGE = 1200.0f;
	const float LIGHT_RANGE_MIN = 600.0f;
	const float LIGHT_POW_PARAM = 40.0f;
	const float FIRE_YPOS = 67.0f;
	const float FIRE_RANGE = 20.0f;
	const float FIRE_POW_PARAM = 1.0f;

}

Player::~Player()
{
	for (auto ptLig : m_lightArray) {
		delete ptLig;
	}
}

bool Player::Start()
{
	//効果音初期化
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/candle/step.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/candle/jump.wav");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/candle/down.wav");

	//アニメーションクリップの初期化
	m_animationClips[enAnimationClip_Idle].Load("Assets/animData/candle/idle.tka");
	m_animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Walk].Load("Assets/animData/candle/walk2.tka");
	m_animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Jump].Load("Assets/animData/candle/jump.tka");
	m_animationClips[enAnimationClip_Jump].SetLoopFlag(true);
	m_animationClips[enAnimationClip_Down].Load("Assets/animData/candle/down.tka");
	m_animationClips[enAnimationClip_Down].SetLoopFlag(false);
	m_animationClips[enAnimationClip_Clear].Load("Assets/animData/candle/clear.tka");
	m_animationClips[enAnimationClip_Clear].SetLoopFlag(false);

	//モデルの初期化
	m_modelRender.Init("Assets/modelData/candle/candle.tkm",m_animationClips,enAnimationClip_Num);
	//m_position.y = 600.0f;
	m_modelRender.SetPosition(m_position);
	//キャラコン初期化
	m_charaCon.Init(10.0f, 50.0f, m_position);
	//持続時間の初期設定
	m_fireTimer = FIRETIMER;

	//ポイントライトのオブジェクトを作る。
	m_light = new PointLight;
	m_light->Init();
	m_light->SetColor(Vector3(0.7f, 0.7f, 0.7f));
	m_light->SetAffectPowParam(LIGHT_POW_PARAM);
	m_light->SetRange(LIGHT_RANGE);
	m_light->SetPosition(m_lightPos);
	m_lightArray.push_back(m_light);

	m_stepSound = NewGO<SoundSource>(0);
	m_stepSound->Init(3);


	return true;
}

void Player::Update()
{
	if (m_playerState != enPlayerState_Down)
	{
		m_sepia.SetAlphaNum(0.0f);
	}
	//移動処理
	Move();
	//回転処理
	Rotation();
	//ステート管理
	ManageState();
	//炎の持続時間の処理
	CountFireTimer();
	//アニメーションの再生
	PlayAnimation();

	//ポイントライトの座標
	m_lightPos = m_position;
	m_lightPos.y += LIGHT_YPOS;
	//ポイントライトを移動
	m_light->SetPosition(m_lightPos);
	m_light->Update();

	//モデルの更新
	m_modelRender.Update();
	

}

void Player::CountFireTimer()
{
	if (!IsEnableMove())
	{
		return;
	}
	//持続時間が0になったら
	if (m_fireTimer <= 0.0f)
	{
		m_fireTimer = 0.0f;
		return;
	}
	//持続時間を減らしていく
	m_fireTimer -= g_gameTime->GetFrameDeltaTime();
}

void Player::TransitionState()
{
	//落ちるか持続時間が0になったら
	if (m_position.y <= DOWN_YPOS ||
		m_fireTimer <= 0.0f)
	{
		m_isDown = 1;
		//ダウン
		m_playerState = enPlayerState_Down;
		//関数を抜ける
		return;
	}
	//地面についていないとき
	if (!m_charaCon.IsOnGround())
	{
		m_playerState = enPlayerState_Jump;
		//関数を抜ける
		return;
	}
	//移動速度があるとき
	if (fabsf(m_moveSpeed.x) > 0.01f
		|| fabsf(m_moveSpeed.z) > 0.01f)
	{
		m_playerState = enPlayerState_Walk;
		return;
	}

	//上記の条件に当てはまらないとき
	m_playerState = enPlayerState_Idle;
}

void Player::ManageState()
{
	switch (m_playerState)
	{
		//待機ステートの時
	case enPlayerState_Idle:
		IdleState();
		break;
		//歩きステートの時
	case enPlayerState_Walk:
		WalkState();
		break;
		//ジャンプステートの時
	case enPlayerState_Jump:
		JumpState();
		break;
		//ダウンステートの時
	case enPlayerState_Down:
		DownState();
		//クリアステートの時
	case enPlayerState_Clear:
		ClearState();
	default:
		break;
	}
}

void Player::IdleState()
{
	TransitionState();
}

void Player::WalkState()
{
	if (m_stepSound != nullptr)
	{
		if (!m_stepSound->IsPlaying())
		{
			//効果音を再生する。
			m_stepSound = NewGO<SoundSource>(0);
			m_stepSound->Init(3);
			m_stepSound->Play(false);
			m_stepSound->SetVolume(0.1f);

		}
	}
	TransitionState();
}

void Player::JumpState()
{
	if (m_isJump)
	{
		//効果音を再生する。
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(4);
		se->Play(false);
		se->SetVolume(0.2f);
		m_isJump = 0;
	}

	TransitionState();
}

void Player::DownState()
{
	m_timer += g_gameTime->GetFrameDeltaTime();
	if (m_timer >= 1.0f)
	{
		m_timer = 1.0f;
	}
	m_sepia.SetAlphaNum(m_timer);
	if (m_isDown)
	{
		//効果音を再生する。
		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(5);
		se->Play(false);
		se->SetVolume(0.5f);
		m_isDown = 0;
	}
	if (!m_modelRender.IsPlayingAnimation())
	{
		m_isPlayingAnimation = false;
	}
}

void Player::ClearState()
{
	if (!m_modelRender.IsPlayingAnimation())
	{
		m_isPlayingAnimation = false;
	}
}

void Player::Move()
{
	//ダウンしたら動かさない
	if (!IsEnableMove())
	{
		if (m_charaCon.IsOnGround() || m_position.y <= DOWN_YPOS)
		{
			return;
		}
	}
	//毎フレーム速度を0にする
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 stickL;

	//左スティックの入力量を計算
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	
	
	//カメラの前方向と右方向のベクトルを持ってくる。
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y方向には移動させない。
	forward.y = 0.0f;
	right.y = 0.0f;

	if (m_charaCon.IsOnGround()) {
		m_moveSpeed += right * stickL.x * MOVESPEED;
		m_moveSpeed += forward * stickL.y * MOVESPEED;
	}
	else
	{
		m_moveSpeed += right * stickL.x * JUMP_MOVESPEED;
		m_moveSpeed += forward * stickL.y * JUMP_MOVESPEED;

	}

	

	//キャラコンが地面についているとき
	if (m_charaCon.IsOnGround())
	{
		////重力を無くす。
		//m_moveSpeed.y = 0.0f;

		//Aボタンが押されたら。
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			m_isJump = 1;
			m_charaCon.Jump();
			m_moveSpeed.y = JUMP;
		}
	}
	else
	{
		m_moveSpeed.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
	}
	//キャラコンを使って移動
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	if (m_charaCon.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}
	//モデルに座標を設定する
	m_modelRender.SetPosition(m_position);

}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	//atan2関数を用いてラジアン単位の角度を求める。
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//求めた角度を設定する。
	m_rot.SetRotationY(-angle);

	//回転を設定する。
	m_modelRender.SetRotation(m_rot);

	Vector3 forward;

	//プレイヤーの正面ベクトルを計算する。
	forward = Vector3::AxisZ;
	m_rot.Apply(forward);
}

void Player::PlayAnimation()
{
	switch (m_playerState) {
		//プレイヤーステートがIdleだったら。
	case enPlayerState_Idle:
		//Idle
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.3f);
		break;
		//プレイヤーステートがWalkだったら。
	case enPlayerState_Walk:
		//Walk
		m_modelRender.PlayAnimation(enAnimationClip_Walk, 0.3f);
		//プレイヤーステートがJumpだったら。
	case enPlayerState_Jump:
		//Down
		m_modelRender.PlayAnimation(enAnimationClip_Jump, 0.3f);
		break;

		break;
		//プレイヤーステートがDownだったら。
	case enPlayerState_Down:
		//Down
		m_modelRender.PlayAnimation(enAnimationClip_Down, 0.3f);
		break;
		//プレイヤーステートがClearだったら。
	case enPlayerState_Clear:
		//Down
		m_modelRender.PlayAnimation(enAnimationClip_Clear, 0.3f);
		break;
	default:
		break;
	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}