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
	//�N���A���W�G�t�F�N�g
	EffectEngine::GetInstance()->ResistEffect(2, u"Assets/effect/clear.efk");
	//�擾�G�t�F�N�g
	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/clearParticle.efk");
	//�N���A���̓o�^
	g_soundEngine->ResistWaveFileBank(6, "Assets/sound/clear/clear.wav");

	//�v���C���[������
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

	//�|�C���g���C�g�̍��W
	m_lightPos = m_position;
	m_lightPos.y += LIGHT_POS_Y;
	m_light->SetPosition(m_position);
	//�|�C���g���C�g�̍X�V
	m_light->Update();

	if (m_effectEmitter != nullptr) {
		if (m_effectEmitter->IsPlay() == false)
		{
			//�G�t�F�N�g�𔭐�������B
			m_effectEmitter = NewGO<EffectEmitter>(0);
			//ResistEffect�֐��Ŏw�肵���ԍ����w�肷��B
			m_effectEmitter->Init(2);
			//�傫����ݒ肷��B
			m_effectEmitter->SetScale(Vector3::One * 11.0f);
			//���W��ݒ肷��B
			m_effectEmitter->SetPosition(m_position);
			//�G�t�F�N�g���Đ�����B
			m_effectEmitter->Play();
		}
	}


	//�v���C���[�Ɖ��܂ł̃x�N�g��
	Vector3 diff = m_player->GetPosition() - m_position;
	//��_�Ԃ̃x�N�g�������̋����ɂȂ�����
	if (diff.Length() <= DISTANCE)
	{
		m_effectEmitter->Stop();
		//�擾�G�t�F�N�g�Đ�
		PlayArriveEffect();
		//���ʉ��Đ�
		PlaySE();
		//�v���C���[���N���A�X�e�[�g�ɂ���
		m_player->SetClearState();
		//���N���X���폜
		DeleteGO(this);
	}
}

void Clear::FullFillClearCondition()
{
	//�G�t�F�N�g�𔭐�������B
	m_effectEmitter = NewGO<EffectEmitter>(0);
	//ResistEffect�֐��Ŏw�肵���ԍ����w�肷��B
	m_effectEmitter->Init(2);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(Vector3::One * 11.0f);

	//���W��ݒ肷��B
	m_effectEmitter->SetPosition(m_position);
	//�G�t�F�N�g���Đ�����B
	m_effectEmitter->Play();


	//�|�C���g���C�g�̃I�u�W�F�N�g�����B
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
	//�G�t�F�N�g�𔭐�������B
	EffectEmitter* effectEmitter1 = NewGO<EffectEmitter>(0);
	//ResistEffect�֐��Ŏw�肵���ԍ����w�肷��B
	effectEmitter1->Init(3);
	//�傫����ݒ肷��B
	effectEmitter1->SetScale(Vector3::One * 11.0f);
	Vector3 effectPosition = m_position;
	//���W��������ɂ���B
	effectPosition.y += 10.0f;
	//���W��ݒ肷��B
	effectEmitter1->SetPosition(effectPosition);
	//�G�t�F�N�g���Đ�����B
	effectEmitter1->Play();
}