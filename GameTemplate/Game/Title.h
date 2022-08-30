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
	void Render(RenderContext& rc);

public:
	ModelRender m_modelRender;					//���f�������_�[
	SpriteRender m_spriteRender;				//�X�v���C�g�����_�[
	SpriteRender m_spriteRender1;				//�X�v���C�g�����_�[�P
	SpriteRender m_spriteRender2;				//�X�v���C�g�����_�[�Q
	std::vector< PointLight*> m_lightArray;		//�|�C���g���C�g�z��
	PointLight* m_ptLight = nullptr;			//�|�C���g���C�g
	Vector3 m_modelPos = Vector3::Zero;			//���f���̍��W
	Vector3 m_toCameraPos = Vector3::Zero;		//�����_�܂ł̃x�N�g��
	Vector2 m_spritePos = Vector2::Zero;		//�摜���W
	Game* m_game = nullptr;						//�Q�[��
	Fade* m_fade = nullptr;						//�t�F�[�h
	SoundSource* m_bgm = nullptr;				//BGM
	SoundSource* m_sound = nullptr;				//�v���C��
	Level2DRender m_level2DRender;				//���x��2D
	float m_alpha = 1.0f;						//���l
	float m_volume = 0.0f;
	bool m_fadeOut = 0;							//���̃N���X���t�F�[�h�A�E�g����
};

