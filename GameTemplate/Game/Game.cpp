#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "Fire.h"
#include "UI.h"
#include "Result.h"
#include "Fade.h"
#include "Clear.h"

Game::~Game()
{
	DeleteGO(m_bg);
	DeleteGO(m_gamecam);
	DeleteGO(m_ui);
	DeleteGO(m_player);
}

bool Game::Start()
{
	//�t�F�[�h�̌���
	m_fade = FindGO<Fade>("fade");
	//m_modelRender.Init("Assets/modelData/unityChan.tkm");
	
	m_levelRender.Init("Assets/level3D/stage1.tkl", [&](LevelObjectData& objData)
		{
			if (objData.EqualObjectName(L"stage1") == true)
			{
				//�w�i�N���X�̐���
				m_bg = NewGO<BackGround>(0, "background");
				//���W�A�X�P�[���A��]�̐ݒ�B
				m_bg->SetPosition(objData.position);
				m_bg->SetRotation(objData.rotation);
				m_bg->SetScale(objData.scale);

				return true;
			}
			if (objData.EqualObjectName(L"candle") == true)
			{
				//�v���C���[�N���X�̐���
				m_player = NewGO<Player>(0, "player");
				//���W�A�X�P�[���A��]�̐ݒ�B
				m_player->SetPosition(objData.position);
				m_player->SetRotation(objData.rotation);
				m_player->SetScale(objData.scale);

				return true;
			}
			if (objData.EqualObjectName(L"fire") == true)
			{
				m_fire = NewGO<Fire>(0, "fire");
				//���W�̐ݒ�
				m_fire->SetPosition(objData.position);
				//�����̌v�Z
				m_player->SetFireBallNum(0);

				m_fires.push_back(m_fire);
			}
			if (objData.EqualObjectName(L"clear") == true)
			{
				m_clear = NewGO<Clear>(0, "clear");
				//�S�[���n�_���W�̐ݒ�
				m_clear->SetPosition(objData.position);
			}
			return true;
		});

	//�J�����̐���
	m_gamecam = NewGO<GameCamera>(0, "gamecamera");
	//UI�̐���
	m_ui = NewGO<UI>(0, "ui");
	//���̃N���X���t�F�[�h�C��������
	m_fade->StartFadeIn();

	return true;
}

void Game::Update()
{
	if (m_fade->IsFade())
	{
		m_result = NewGO<Result>(0, "result");
		if (m_player->GetPlayerState() == Player::enPlayerState_Clear)
		{
			m_result->SetClearState();
		}
		DeleteGO(this);
	}
	if (!m_player->IsPlayAnimation())
	{
		m_fade->StartFadeOut();
	}
}

void Game::Lighting()
{

}

void Game::Render(RenderContext& rc)
{
	//m_modelRender.Draw(rc);
}