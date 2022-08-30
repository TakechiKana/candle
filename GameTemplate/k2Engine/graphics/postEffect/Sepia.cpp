#include "k2EnginePreCompile.h"
#include "Sepia.h"

namespace nsK2Engine {

	Sepia::Sepia()
	{

	}

	Sepia::~Sepia()
	{

	}

	void Sepia::OnInit(
		RenderTarget& mainRenderTarget,
		RenderTarget& zprepassRenderTarget,
		RenderTarget& normalRenderTarget,
		RenderTarget& metallicSmoothRenderTarget,
		RenderTarget& albedoRenderTarget
	) {

		m_finRt.Create(
			mainRenderTarget.GetWidth(),
			mainRenderTarget.GetHeight(),
			1,
			1,
			mainRenderTarget.GetColorBufferFormat(),
			DXGI_FORMAT_UNKNOWN
		);

		m_cb1.alphaNum = 0.0f;

		SpriteInitData initData;
		initData.m_width = mainRenderTarget.GetWidth();
		initData.m_height = mainRenderTarget.GetHeight();
		initData.m_colorBufferFormat[0] = mainRenderTarget.GetColorBufferFormat();
		initData.m_fxFilePath = "Assets/shader/postEffect/sepia.fx";
		initData.m_psEntryPoinFunc = "PSOut";
		initData.m_expandConstantBuffer = &m_cb1;
		initData.m_expandConstantBufferSize = sizeof(m_cb1);
		initData.m_textures[0] = &mainRenderTarget.GetRenderTargetTexture();

		m_finSprite.Init(initData);
	}

	void Sepia::OnRender(RenderContext& rc, RenderTarget& mainRenderTarget)
	{
		g_graphicsEngine->BeginGPUEvent("Sepia");

		// 最終合成。
		// レンダリングターゲットとして利用できるまで待つ
		rc.WaitUntilToPossibleSetRenderTarget(m_finRt);
		// レンダリングターゲットを設定
		rc.SetRenderTargetAndViewport(m_finRt);
		// 最終合成。
		m_finSprite.Draw(rc);
		// レンダリングターゲットへの書き込み終了待ち
		rc.WaitUntilFinishDrawingToRenderTarget(m_finRt);

		g_graphicsEngine->EndGPUEvent();
	}
}