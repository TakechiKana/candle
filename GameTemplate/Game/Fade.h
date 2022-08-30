#pragma once
class Fade:public IGameObject
{
public:
	Fade() {};
	~Fade();
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="">レンダーコンテキスト</param>
	void Render(RenderContext& rc);
	/// <summary>
	/// フェードを始める
	/// </summary>
	void StartFadeOut()
	{
		m_fadeState = enFadeState_FadeOut;
	}
	/// <summary>
	/// フェードを終わる
	/// </summary>
	void StartFadeIn()
	{
		m_fadeState = enFadeState_FadeIn;
	}
	/// <summary>
	/// フェード中か
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

	SpriteRender m_spriteRender;						//スプライトレンダー
	SpriteRender m_spriteRender1;						//スプライトレンダー
	EnFadeState m_fadeState = enFadeState_Idle;			//ステート
	float m_alpha = 0.0f;								//全体のα値
	float m_alpha1 = 0.0f;								//ロード中画像のα値
};

