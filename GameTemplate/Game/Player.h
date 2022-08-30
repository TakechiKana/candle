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
	/// ����������
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc">�����_�[�R���e�L�X�g</param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();
	/// <summary>
	/// ��]����
	/// </summary>
	void Rotation();
	/// <summary>
	/// �X�e�[�g�J��
	/// </summary>
	void TransitionState();
	/// <summary>
	/// �X�e�[�g�Ǘ�
	/// </summary>
	void ManageState();
	/// <summary>
	/// �ҋ@�X�e�[�g
	/// </summary>
	void IdleState();
	/// <summary>
	/// �����X�e�[�g
	/// </summary>
	void WalkState();
	/// <summary>
	/// �W�����v�X�e�[�g
	/// </summary>
	void JumpState();
	/// <summary>
	/// �_�E���X�e�[�g
	/// </summary>
	void DownState();
	/// <summary>
	/// �N���A�X�e�[�g
	/// </summary>
	void ClearState();
	/// <summary>
	/// �������Ԃ̏���
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
	/// ���W�ݒ�
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]�̐ݒ�
	/// </summary>
	/// <param name="rot">��]</param>
	void SetRotation(Quaternion rot)
	{
		m_rot = rot;
	}
	/// <summary>
	/// �g�嗦�̐ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(Vector3 scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// ���W�擾
	/// </summary>
	const Vector3 GetPosition()
	{
		return m_position;
	}
	/// <summary>
	/// ��]�擾
	/// </summary>
	const Quaternion GetQuaternion()
	{
		return m_rot;
	}
	/// <summary>
	/// �g�嗦�̎擾
	/// </summary>
	const Vector3 GetScale()
	{
		return m_scale;
	}
	/// <summary>
	/// ���̎������Ԃ̎擾
	/// </summary>
	/// <returns></returns>
	const float GetFireTimer()
	{
		return m_fireTimer;
	}
	/// <summary>
	/// �A�C�e�����E�������ɁA���̎������Ԃ𑝂₷
	/// </summary>
	/// <param name="fireTimer">���Z���鎞��</param>
	void PlusFireTimer(float fireTimer)
	{
		m_fireTimer += fireTimer;
	}
	/// <summary>
	/// ���̉�̐�
	/// </summary>
	/// <param name="flag">0->���Z�A1->���Z</param>
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
	/// ���̉�̐����擾
	/// </summary>
	/// <returns></returns>
	const int GetFireBallNum()
	{
		return m_fireBallNum;
	}
	/// <summary>
	/// �S�[�����W�̐ݒ�
	/// </summary>
	/// <param name="pos">�S�[���̍��W</param>
	void SetClearPosition(Vector3& pos)
	{
		m_clearPos = pos;
	}
	/// <summary>
	/// �N���A�n�_�ɓ��B������
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
	/// �A�j���[�V�����Đ�
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

	std::vector< PointLight*> m_lightArray;				//�|�C���g���C�g
	PointLight* m_light = nullptr;						//�|�C���g���C�g�̃|�C���^
	Vector3 m_position = Vector3::Zero;					//���W
	Vector3 m_lightPos = Vector3::Zero;					//�|�C���g���C�g�̍��W
	Vector3 m_clearPos = Vector3::Zero;					//�S�[�����W
	Vector3 m_scale = Vector3::One;						//�g�嗦
	Quaternion m_rot = Quaternion::Identity;			//��]
	EnPlayerState m_playerState = enPlayerState_Idle;	//�X�e�[�g
	ModelRender m_modelRender;							//���f��
	CharacterController m_charaCon;						//�L�����R��

	AnimationClip m_animationClips[enAnimationClip_Num]; //�A�j���[�V�����N���b�v

	Vector3 m_moveSpeed = Vector3::Zero;				//�ړ����x
	Vector3 m_oldSpeed = Vector3::Zero;					//1�t���[���O�̈ʒu
	bool m_isJump = false;								//�W�����v�t���O
	bool m_isDown = false;								//�_�E���t���O
	bool m_isPlayingAnimation = true;					//�A�j���[�V�������I�������
	float m_timer = 0.0f;								//�Z�s�A�p
	float m_fireTimer = 0.0f;							//�������Ă��鎞��
	int m_fireBallNum = 0;								//���̉�̐�
	EffectEmitter* m_effectEmitter = nullptr;			//���G�t�F�N�g
	SoundSource* m_stepSound = nullptr;					//����
	SoundSource* m_downSound = nullptr;					//�_�E���̉�
	SoundSource* m_jumpSound = nullptr;					//�W�����v��
	Sepia m_sepia;										//�Z�s�A
};

