#pragma once

#include "graphics/postEffect/PostEffectComponentBase.h"

namespace nsK2Engine {
	class Sepia : public PostEffectComponentBase
	{
	public:
		Sepia();
		~Sepia();
		/// <summary>
		/// 描画。
		/// </summary>
		/// <param name="rc">レンダ―コンテキスト。</param>
		/// <param name="mainRenderTarget">メインレンダ―ターゲット。</param>
		void OnRender(RenderContext& rc, RenderTarget& mainRenderTarget) override;
		/// <summary>
		/// 初期化。
		/// </summary>
		void OnInit(
			RenderTarget& mainRenderTarget,
			RenderTarget& zprepassRenderTarget,
			RenderTarget& normalRenderTarget,
			RenderTarget& metallicSmoothRenderTarget,
			RenderTarget& albedoRenderTarget) override;
		/// <summary>
		/// ポストエフェクトを実行した結果となるテクスチャを取得。
		/// </summary>
		/// <returns></returns>
		Texture& GetResultTexture() override
		{
			return m_finRt.GetRenderTargetTexture();
		}
		/// <summary>
		/// ポストの結果の画像をメインレンダリングターゲットにコピーする？
		/// </summary>
		/// <returns></returns>
		bool IsCopyResultTextureToMainRenderTarget() const override
		{
			return true;
		}
		/// <summary>
		/// α値を設定する。
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
		Sprite m_finSprite;							// 最終合成用のスプライト。
		RenderTarget m_finRt;						// 最終合成レンダリングターゲット。
		SCB_1 m_cb1;
	};
}