#pragma once

class Player;
class UI:public IGameObject
{
public:
	UI(){};
	~UI();
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
	/// 文字表示処理
	/// </summary>
	void Font();

private:
	//Vector3 m_fontPos = Vector3::Zero;				//持続時間の座標
	//Vector3 m_spritePos = Vector3::Zero;			//持続時間アイコンの座標
	FontRender m_fontRender;						//持続時間表示
	FontRender m_fontRender1;						//炎の塊残数表示
	SpriteRender m_spriteRender;					//持続時間アイコン
	SpriteRender m_spriteRender1;					//炎の塊アイコン
	Player* m_player = nullptr;						//プレイヤー
};

