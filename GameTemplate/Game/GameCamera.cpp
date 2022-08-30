#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

namespace
{
	const float CAMERA_FAR = 10000.0f;
	const float TARGET_Y = 100.0f;
}

bool GameCamera::Start()
{
	//�J�����̏����ݒ�
	m_toCameraPos.Set(0.0f, 200.0f, -300.0f);
	g_camera3D->SetFar(CAMERA_FAR);

	//�v���C���[�̌���
	m_player = FindGO<Player>("player");

	return true;
}

void GameCamera::UpdatePositionAndTarget()
{
	//�����_�̌v�Z
	Vector3 target = m_player->GetPosition();
	//Y���W�������グ��
	target.y += TARGET_Y;

	//���_���v�Z����
	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(target);
}

void GameCamera::Update()
{
	UpdatePositionAndTarget();
	//�J�����̍X�V
	g_camera3D->Update();
}