#pragma once
#include "sound/SoundSource.h"

class Player;

class Fire : public IGameObject
{
public:
	Fire() {};
	~Fire();
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
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(Vector3& pos)
	{
		m_position = pos;
	}

private:
	/// <summary>
	/// ���O�̉��̉�G�t�F�N�g
	/// </summary>
	void PlayFireEffect(bool flag);
	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	void PlayGetEffect();
	/// <summary>
	/// ���ʉ��̍Đ�
	/// </summary>
	void PlaySE();

	Vector3 m_position = Vector3::Zero;					//���W
	Vector3 m_lightPos = Vector3::Zero;					//�|�C���g���C�g�̍��W
	Player* m_player = nullptr;							//�v���C���[
	std::vector< PointLight*> m_lightArray;				//�|�C���g���C�g
	PointLight* m_light = nullptr;						//�|�C���g���C�g�̃|�C���^
	bool m_fireFlag = 1;								//�擾�O�̉��G�t�F�N�g�p�t���O
	EffectEmitter* m_effectEmitter = nullptr;			//�擾�O�̉��G�t�F�N�g
	SoundSource* m_sound = nullptr;						//�擾��
};

