#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera() {};
	~GameCamera() {};
	/// <summary>
	/// 初期化処理
	/// </summary>
	/// <returns></returns>
	bool Start();
	/// <summary>
	/// 更新処理
	/// </summary>
	/// <returns></returns>
	void Update();
	/// <summary>
	/// カメラの座標と注視点の処理
	/// </summary>
	void UpdatePositionAndTarget();

private:
	Vector3 m_toCameraPos = Vector3::Zero;			//視点から注視点までのべクトル
	Player* m_player = nullptr;						//プレイヤー
};

