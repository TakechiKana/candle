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
	/// ���ʃX�e�[�g
	/// </summary>
	enum EnResultState {
		enResultState_GameOver,
		enResultState_GameClear
	};

public:
	Result() {};
	~Result();
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
	/// <param name="rc">�����_�[�R���e�L�X�g</param>
	void Render(RenderContext& rc);
	/// <summary>
	/// �Q�[���N���A�̐ݒ�
	/// </summary>
	void SetClearState()
	{
		m_resultState = enResultState_GameClear;
	}
	/// <summary>
	/// �^�C�g�����Q�[���𐶐�����
	/// </summary>
	void CreateNewClass(bool flag);

private:
	/// <summary>
	/// �{�^���I��
	/// </summary>
	enum EnSelectButton
	{
		enSelectButton_Title,
		enSelectButton_Button1
	};
private:
	/// <summary>
	/// �^�C�g���{�^���X�e�[�g
	/// </summary>
	void TitleState();
	/// <summary>
	/// �{�^���P�X�e�[�g
	/// </summary>
	void Button1State();
	/// <summary>
	/// �X�e�[�g�Ǘ�
	/// </summary>
	void ManageState();

	SpriteRender m_spriteRender;							//�Q�[���I�[�o�[�A�N���A�摜
	SpriteRender m_spriteRender1;							//�^�C�g���։摜
	SpriteRender m_spriteRender2;							//��蒼���A���։摜
	SpriteRender m_selectRender;							//�I�𒆉摜

	EnResultState m_resultState = enResultState_GameOver;	//���ʃX�e�[�g
	EnSelectButton m_buttonState = enSelectButton_Button1;	//�{�^���X�e�[�g
	Vector3 m_titleButtonPos = Vector3::Zero;				//�^�C�g���{�^�����W
	Vector3 m_button1Pos = Vector3::Zero;					//���փ{�^���A���Ȃ����{�^�����W
	Vector3 m_clearPos = Vector3::Zero;						//�S�[���n�_�̍��W
	EffectEmitter* m_effectEmitter = nullptr;				//�G�t�F�N�g�̃|�C���^
	Player* m_player = nullptr;								//�v���C���[
	Title* m_title = nullptr;								//�^�C�g��
	Game* m_game = nullptr;									//�Q�[��
	Fade* m_fade = nullptr;									//�t�F�[�h
	Level2DRender m_level2DRender;							//���x��2D
	float m_alpha = 0.0f;									//�摜�̓����x
	bool m_isFade = false;									//�t�F�[�h��
};

