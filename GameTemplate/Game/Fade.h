#pragma once
class Fade:public IGameObject
{
public:
	Fade() {};
	~Fade();
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
	/// <param name="">�����_�[�R���e�L�X�g</param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �t�F�[�h���n�߂�
	/// </summary>
	void StartFadeOut()
	{
		m_fadeState = enFadeState_FadeOut;
	}
	/// <summary>
	/// �t�F�[�h���I���
	/// </summary>
	void StartFadeIn()
	{
		m_fadeState = enFadeState_FadeIn;
	}
	/// <summary>
	/// �t�F�[�h����
	/// </summary>
	/// <returns></returns>
	bool IsFade()
	{
		if (m_alpha >= 0.5f && m_fadeState == enFadeState_Idle)
		{
			return true;
		}
		return false;
	}

	bool CanFlashSprite()
	{
		if (m_alpha > 0.5f)
		{
			return true;
		}
		return false;
	}

private:
	enum EnFadeState
	{
		enFadeState_FadeIn,
		enFadeState_FadeOut,
		enFadeState_Idle
	};

	SpriteRender m_spriteRender;						//�X�v���C�g�����_�[
	SpriteRender m_spriteRender1;						//�X�v���C�g�����_�[
	EnFadeState m_fadeState = enFadeState_Idle;			//�X�e�[�g
	float m_alpha = 0.0f;								//�S�̂̃��l
	float m_alpha1 = 0.0f;								//���[�h���摜�̃��l
};

