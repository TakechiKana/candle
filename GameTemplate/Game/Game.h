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
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
	/// <summary>
	/// ���C�e�B���O
	/// </summary>
	void Lighting();

private:
	ModelRender m_modelRender;
	Vector3 m_pos;
	PhysicsStaticObject m_physicsStaticObject;
	std::vector< Fire*> m_fires;			//�|�C���g���C�g

	Player* m_player = nullptr;				//Player�N���X
	BackGround* m_bg = nullptr;				//BackGround�N���X
	GameCamera* m_gamecam = nullptr;		//GameCamera�N���X
	Fire* m_fire = nullptr;					//Fire�N���X
	UI* m_ui = nullptr;						//UI�N���X
	Result* m_result = nullptr;				//Result�N���X
	Fade* m_fade = nullptr;					//Fade�N���X
	Clear* m_clear = nullptr;				//Clear�N���X
	LevelRender m_levelRender;
};

