#pragma once

#include "graphics/postEffect/PostEffectComponentBase.h"

namespace nsK2Engine {
	class Sepia : public PostEffectComponentBase
	{
	public:
		Sepia();
		~Sepia();
		/// <summary>
		/// �`��B
		/// </summary>
		/// <param name="rc">�����_�\�R���e�L�X�g�B</param>
		/// <param name="mainRenderTarget">���C�������_�\�^�[�Q�b�g�B</param>
		void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) override;
		/// <summary>
		/// �������B
		/// </summary>
		void OnInit(
			RenderTarget& mainRenderTarget,
			RenderTarget& zprepassRenderTarget,
			RenderTarget& normalRenderTarget,
			RenderTarget& metallicSmoothRenderTarget,
			RenderTarget& albedoRenderTarget) override;
		/// <summary>
		/// �|�X�g�G�t�F�N�g�����s�������ʂƂȂ�e�N�X�`�����擾�B
		/// </summary>
		/// <returns></returns>
		Texture& GetResultTexture() override
		{
			return m_finRt.GetRenderTargetTexture();
		}
		/// <summary>
		/// �|�X�g�̌��ʂ̉摜�����C�������_�����O�^�[�Q�b�g�ɃR�s�[����H
		/// </summary>
		/// <returns></returns>
		bool IsCopyResultTextureToMainRenderTarget() const override
		{
			return true;
		}
		/// <summary>
		/// ���l��ݒ肷��B
		/// </summary>
		/// <param name="alphaNum"></param>
		void SetAlphaNum(float alphaNum)
		{
			m_cb1.alphaNum = alphaNum;
		}

	private:
		struct SCB_1 {
			float alphaNum;
		};
		Sprite m_finSprite;							// �ŏI�����p�̃X�v���C�g�B
		RenderTarget m_finRt;						// �ŏI���������_�����O�^�[�Q�b�g�B
		SCB_1 m_cb1;
	};
}