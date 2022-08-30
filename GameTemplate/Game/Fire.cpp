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
	//�擾��������
	g_soundEngine->ResistWaveFileBank(2, "Assets/sound/fire/get.wav");

	//���̉�̎擾�G�t�F�N�g
	EffectEngine::GetInstance()->ResistEffect(1, u"Assets/effect/fireparticle.efk");

	//���̉�G�t�F�N�g
	EffectEngine::GetInstance()->ResistEffect(0, u"Assets/effect/fireball1.efk");
	//�G�t�F�N�g�𔭐�������B
	m_effectEmitter = NewGO<EffectEmitter>(0);
	//ResistEffect�֐��Ŏw�肵���ԍ����w�肷��B
	m_effectEmitter->Init(0);
	//�傫����ݒ肷��B
	m_effectEmitter->SetScale(Vector3::One * 11.0f);
	Vector3 effectPosition = m_position;
	//���W��������ɂ���B
	effectPosition.y += 30.0f;
	//���W��ݒ肷��B
	m_effectEmitter->SetPosition(effectPosition);
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

	//�v���C���[������
	m_player = FindGO<Player>("player");

	return true;
}

void Fire::Update()
{
	if (m_player->GetPlayerState() == Player::enPlayerState_Down)
	{
		DeleteGO(this);
	}
	//�|�C���g���C�g�̍��W
	m_lightPos = m_position;
	m_lightPos.y += LIGHT_POS_Y;
	m_light->SetPosition(m_lightPos);
	//�|�C���g���C�g�̍X�V
	m_light->Update();

	////���̉�G�t�F�N�g
	//PlayFireEffect(1);

	if (m_effectEmitter != nullptr) {
		if (m_effectEmitter->IsPlay() == false)
		{
			//�G�t�F�N�g�𔭐�������B
			m_effectEmitter = NewGO<EffectEmitter>(0);
			//ResistEffect�֐��Ŏw�肵���ԍ����w�肷��B
			m_effectEmitter->Init(0);
			//�傫����ݒ肷��B
			m_effectEmitter->SetScale(Vector3::One * 11.0f);
			Vector3 effectPosition = m_position;
			//���W��������ɂ���B
			effectPosition.y += 30.0f;
			//���W��ݒ肷��B
			m_effectEmitter->SetPosition(effectPosition);
			//�G�t�F�N�g���Đ�����B
			m_effectEmitter->Play();
		}
	}
	

	//�v���C���[�Ɖ��܂ł̃x�N�g��
	Vector3 diff = m_player->GetPosition() - m_position;
	//��_�Ԃ̃x�N�g�������̋����ɂȂ�����
	if (diff.Length() <= DISTANCE)
	{
		//PlayFireEffect(0);
		//�擾�G�t�F�N�g�Đ�
		PlayGetEffect();
		//���ʉ��Đ�
		PlaySE();
		//���̎������Ԃ����Z����
		m_player->PlusFireTimer(FIRETIMER);
		//���̉�̐������炷
		m_player->SetFireBallNum(1);
		//���N���X���폜
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
		//�G�t�F�N�g�𔭐�������B
		m_effectEmitter = NewGO<EffectEmitter>(0);
		//ResistEffect�֐��Ŏw�肵���ԍ����w�肷��B
		m_effectEmitter->Init(0);
		//�傫����ݒ肷��B
		m_effectEmitter->SetScale(Vector3::One * 11.0f);
		Vector3 effectPosition = m_position;
		//���W��������ɂ���B
		effectPosition.y += 30.0f;
		//���W��ݒ肷��B
		m_effectEmitter->SetPosition(effectPosition);
		//�G�t�F�N�g���Đ�����B
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
			//�G�t�F�N�g�𔭐�������B
			m_effectEmitter = NewGO<EffectEmitter>(0);
			//ResistEffect�֐��Ŏw�肵���ԍ����w�肷��B
			m_effectEmitter->Init(0);
			//�傫����ݒ肷��B
			m_effectEmitter->SetScale(Vector3::One * 11.0f);
			Vector3 effectPosition = m_position;
			//���W��������ɂ���B
			effectPosition.y += 30.0f;
			//���W��ݒ肷��B
			m_effectEmitter->SetPosition(effectPosition);
			//�G�t�F�N�g���Đ�����B
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
	//�G�t�F�N�g�𔭐�������B
	EffectEmitter* effectEmitter1 = NewGO<EffectEmitter>(0);
	//ResistEffect�֐��Ŏw�肵���ԍ����w�肷��B
	effectEmitter1->Init(1);
	//�傫����ݒ肷��B
	effectEmitter1->SetScale(Vector3::One * 11.0f);
	Vector3 effectPosition = m_position;
	//���W��������ɂ���B
	effectPosition.y += 30.0f;
	//���W��ݒ肷��B
	effectEmitter1->SetPosition(effectPosition);
	//�G�t�F�N�g���Đ�����B
	effectEmitter1->Play();
}