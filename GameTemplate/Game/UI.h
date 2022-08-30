#pragma once

class Player;
class UI:public IGameObject
{
public:
	UI(){};
	~UI();
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
	/// �����\������
	/// </summary>
	void Font();

private:
	//Vector3 m_fontPos = Vector3::Zero;				//�������Ԃ̍��W
	//Vector3 m_spritePos = Vector3::Zero;			//�������ԃA�C�R���̍��W
	FontRender m_fontRender;						//�������ԕ\��
	FontRender m_fontRender1;						//���̉�c���\��
	SpriteRender m_spriteRender;					//�������ԃA�C�R��
	SpriteRender m_spriteRender1;					//���̉�A�C�R��
	Player* m_player = nullptr;						//�v���C���[
};

