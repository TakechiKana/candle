#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class GameCamera;
class Fire;
class UI;
class Result;
class Fade;
class Clear;

class Game : public IGameObject
{
public:
	Game() {};
	~Game();
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
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ライティング
	/// </summary>
	void Lighting();

private:
	ModelRender m_modelRender;
	Vector3 m_pos;
	PhysicsStaticObject m_physicsStaticObject;
	std::vector< Fire*> m_fires;			//ポイントライト

	Player* m_player = nullptr;				//Playerクラス
	BackGround* m_bg = nullptr;				//BackGroundクラス
	GameCamera* m_gamecam = nullptr;		//GameCameraクラス
	Fire* m_fire = nullptr;					//Fireクラス
	UI* m_ui = nullptr;						//UIクラス
	Result* m_result = nullptr;				//Resultクラス
	Fade* m_fade = nullptr;					//Fadeクラス
	Clear* m_clear = nullptr;				//Clearクラス
	LevelRender m_levelRender;
};

