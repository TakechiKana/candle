#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera() {};
	~GameCamera() {};
	/// <summary>
	/// ����������
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// �X�V����
	/// </summary>
	/// <returns></returns>
	void Update();
	/// <summary>
	/// �J�����̍��W�ƒ����_�̏���
	/// </summary>
	void UpdatePositionAndTarget();

private:
	Vector3 m_toCameraPos = Vector3::Zero;			//���_���璍���_�܂ł̂׃N�g��
	Player* m_player = nullptr;						//�v���C���[
};

