#pragma once

class Player;

class Clear : public IGameObject
{
public:
	Clear() {};
	~Clear();
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

	void FullFillClearCondition();
	

private:
	/// <summary>
	/// ���B�G�t�F�N�g�̍Đ�
	/// </summary>
	void PlayArriveEffect();
	/// <summary>
	/// ���ʉ��̍Đ�
	/// </summary>
	void PlaySE();

	Vector3 m_position = Vector3::Zero;					//���W
	Vector3 m_lightPos = Vector3::Zero;					//�|�C���g���C�g�̍��W
	Player* m_player = nullptr;							//�v���C���[
	std::vector< PointLight*> m_lightArray;				//�|�C���g���C�g
	PointLight* m_light = nullptr;						//�|�C���g���C�g�̃|�C���^
	bool m_clearFlag = 0;								//�N���A�����𖞂����Ă��邩
	EffectEmitter* m_effectEmitter = nullptr;			//�擾�O�̉��G�t�F�N�g
};

