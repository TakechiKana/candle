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
	//���ʉ�������
	g_soundEngine->ResistWaveFileBank(3, "Assets/sound/candle/step.wav");
	g_soundEngine->ResistWaveFileBank(4, "Assets/sound/candle/jump.wav");
	g_soundEngine->ResistWaveFileBank(5, "Assets/sound/candle/down.wav");

	//�A�j���[�V�����N���b�v�̏�����
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

	//���f���̏�����
	m_modelRender.Init("Assets/modelData/candle/candle.tkm",m_animationClips,enAnimationClip_Num);
	//m_position.y = 600.0f;
	m_modelRender.SetPosition(m_position);
	//�L�����R��������
	m_charaCon.Init(10.0f, 50.0f, m_position);
	//�������Ԃ̏����ݒ�
	m_fireTimer = FIRETIMER;

	//�|�C���g���C�g�̃I�u�W�F�N�g�����B
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
	//�ړ�����
	Move();
	//��]����
	Rotation();
	//�X�e�[�g�Ǘ�
	ManageState();
	//���̎������Ԃ̏���
	CountFireTimer();
	//�A�j���[�V�����̍Đ�
	PlayAnimation();

	//�|�C���g���C�g�̍��W
	m_lightPos = m_position;
	m_lightPos.y += LIGHT_YPOS;
	//�|�C���g���C�g���ړ�
	m_light->SetPosition(m_lightPos);
	m_light->Update();

	//���f���̍X�V
	m_modelRender.Update();
	

}

void Player::CountFireTimer()
{
	if (!IsEnableMove())
	{
		return;
	}
	//�������Ԃ�0�ɂȂ�����
	if (m_fireTimer <= 0.0f)
	{
		m_fireTimer = 0.0f;
		return;
	}
	//�������Ԃ����炵�Ă���
	m_fireTimer -= g_gameTime->GetFrameDeltaTime();
}

void Player::TransitionState()
{
	//�����邩�������Ԃ�0�ɂȂ�����
	if (m_position.y <= DOWN_YPOS ||
		m_fireTimer <= 0.0f)
	{
		m_isDown = 1;
		//�_�E��
		m_playerState = enPlayerState_Down;
		//�֐��𔲂���
		return;
	}
	//�n�ʂɂ��Ă��Ȃ��Ƃ�
	if (!m_charaCon.IsOnGround())
	{
		m_playerState = enPlayerState_Jump;
		//�֐��𔲂���
		return;
	}
	//�ړ����x������Ƃ�
	if (fabsf(m_moveSpeed.x) > 0.01f
		|| fabsf(m_moveSpeed.z) > 0.01f)
	{
		m_playerState = enPlayerState_Walk;
		return;
	}

	//��L�̏����ɓ��Ă͂܂�Ȃ��Ƃ�
	m_playerState = enPlayerState_Idle;
}

void Player::ManageState()
{
	switch (m_playerState)
	{
		//�ҋ@�X�e�[�g�̎�
	case enPlayerState_Idle:
		IdleState();
		break;
		//�����X�e�[�g�̎�
	case enPlayerState_Walk:
		WalkState();
		break;
		//�W�����v�X�e�[�g�̎�
	case enPlayerState_Jump:
		JumpState();
		break;
		//�_�E���X�e�[�g�̎�
	case enPlayerState_Down:
		DownState();
		//�N���A�X�e�[�g�̎�
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
			//���ʉ����Đ�����B
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
		//���ʉ����Đ�����B
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
		//���ʉ����Đ�����B
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
	//�_�E�������瓮�����Ȃ�
	if (!IsEnableMove())
	{
		if (m_charaCon.IsOnGround() || m_position.y <= DOWN_YPOS)
		{
			return;
		}
	}
	//���t���[�����x��0�ɂ���
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	Vector3 stickL;

	//���X�e�B�b�N�̓��͗ʂ��v�Z
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	
	
	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���B
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//y�����ɂ͈ړ������Ȃ��B
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

	

	//�L�����R�����n�ʂɂ��Ă���Ƃ�
	if (m_charaCon.IsOnGround())
	{
		////�d�͂𖳂����B
		//m_moveSpeed.y = 0.0f;

		//A�{�^���������ꂽ��B
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
	//�L�����R�����g���Ĉړ�
	m_position = m_charaCon.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());

	if (m_charaCon.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
	}
	//���f���ɍ��W��ݒ肷��
	m_modelRender.SetPosition(m_position);

}

void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) < 0.001f
		&& fabsf(m_moveSpeed.z) < 0.001f) {
		return;
	}
	//atan2�֐���p���ă��W�A���P�ʂ̊p�x�����߂�B
	float angle = atan2(-m_moveSpeed.x, m_moveSpeed.z);
	//���߂��p�x��ݒ肷��B
	m_rot.SetRotationY(-angle);

	//��]��ݒ肷��B
	m_modelRender.SetRotation(m_rot);

	Vector3 forward;

	//�v���C���[�̐��ʃx�N�g�����v�Z����B
	forward = Vector3::AxisZ;
	m_rot.Apply(forward);
}

void Player::PlayAnimation()
{
	switch (m_playerState) {
		//�v���C���[�X�e�[�g��Idle��������B
	case enPlayerState_Idle:
		//Idle
		m_modelRender.PlayAnimation(enAnimationClip_Idle, 0.3f);
		break;
		//�v���C���[�X�e�[�g��Walk��������B
	case enPlayerState_Walk:
		//Walk
		m_modelRender.PlayAnimation(enAnimationClip_Walk, 0.3f);
		//�v���C���[�X�e�[�g��Jump��������B
	case enPlayerState_Jump:
		//Down
		m_modelRender.PlayAnimation(enAnimationClip_Jump, 0.3f);
		break;

		break;
		//�v���C���[�X�e�[�g��Down��������B
	case enPlayerState_Down:
		//Down
		m_modelRender.PlayAnimation(enAnimationClip_Down, 0.3f);
		break;
		//�v���C���[�X�e�[�g��Clear��������B
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