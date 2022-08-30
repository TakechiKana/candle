#pragma once
#include "Level2DRender/Level2DRender.h"

class Player;
class Title;
class Game;
class Fade;

class Result:public IGameObject
{
public:
	/// <summary>
	/// 結果ステート
	/// </summary>
	enum EnResultState {
		enResultState_GameOver,
		enResultState_GameClear
	};

public:
	Result() {};
	~Result();
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
	/// <param name="rc">レンダーコンテキスト</param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ゲームクリアの設定
	/// </summary>
	void SetClearState()
	{
		m_resultState = enResultState_GameClear;
	}
	/// <summary>
	/// タイトルかゲームを生成する
	/// </summary>
	void CreateNewClass(bool flag);

private:
	/// <summary>
	/// ボタン選択
	/// </summary>
	enum EnSelectButton
	{
		enSelectButton_Title,
		enSelectButton_Button1
	};
private:
	/// <summary>
	/// タイトルボタンステート
	/// </summary>
	void TitleState();
	/// <summary>
	/// ボタン１ステート
	/// </summary>
	void Button1State();
	/// <summary>
	/// ステート管理
	/// </summary>
	void ManageState();

	SpriteRender m_spriteRender;							//ゲームオーバー、クリア画像
	SpriteRender m_spriteRender1;							//タイトルへ画像
	SpriteRender m_spriteRender2;							//やり直し、次へ画像
	SpriteRender m_selectRender;							//選択中画像

	EnResultState m_resultState = enResultState_GameOver;	//結果ステート
	EnSelectButton m_buttonState = enSelectButton_Button1;	//ボタンステート
	Vector3 m_titleButtonPos = Vector3::Zero;				//タイトルボタン座標
	Vector3 m_button1Pos = Vector3::Zero;					//次へボタン、やりなおしボタン座標
	Vector3 m_clearPos = Vector3::Zero;						//ゴール地点の座標
	EffectEmitter* m_effectEmitter = nullptr;				//エフェクトのポインタ
	Player* m_player = nullptr;								//プレイヤー
	Title* m_title = nullptr;								//タイトル
	Game* m_game = nullptr;									//ゲーム
	Fade* m_fade = nullptr;									//フェード
	Level2DRender m_level2DRender;							//レベル2D
	float m_alpha = 0.0f;									//画像の透明度
	bool m_isFade = false;									//フェード中
};

