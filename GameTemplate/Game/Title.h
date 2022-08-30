#pragma once

#include "Level2DRender/Level2DRender.h"
#include "sound/SoundSource.h"

class Game;
class Fade;

class Title :public IGameObject
{
public:
	Title() {};
	~Title();
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
	void Render(RenderContext& rc);

public:
	ModelRender m_modelRender;					//モデルレンダー
	SpriteRender m_spriteRender;				//スプライトレンダー
	SpriteRender m_spriteRender1;				//スプライトレンダー１
	SpriteRender m_spriteRender2;				//スプライトレンダー２
	std::vector< PointLight*> m_lightArray;		//ポイントライト配列
	PointLight* m_ptLight = nullptr;			//ポイントライト
	Vector3 m_modelPos = Vector3::Zero;			//モデルの座標
	Vector3 m_toCameraPos = Vector3::Zero;		//注視点までのベクトル
	Vector2 m_spritePos = Vector2::Zero;		//画像座標
	Game* m_game = nullptr;						//ゲーム
	Fade* m_fade = nullptr;						//フェード
	SoundSource* m_bgm = nullptr;				//BGM
	SoundSource* m_sound = nullptr;				//プレイ音
	Level2DRender m_level2DRender;				//レベル2D
	float m_alpha = 1.0f;						//α値
	float m_volume = 0.0f;
	bool m_fadeOut = 0;							//このクラスがフェードアウト中か
};

