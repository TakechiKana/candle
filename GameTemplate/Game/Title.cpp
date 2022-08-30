#include "stdafx.h"
#include "Title.h"
#include "Game.h"
#include "Fade.h"

#include "sound/SoundEngine.h"


namespace
{
	const float LIGHT_YPOS = 100.0f;				//ライトY座標に加算する値
	const float LIGHT_RANGE = 1200.0f;				//ライトの範囲
	const float LIGHT_POW_PARAM = 40.0f;			//ライトの影響率の累乗数
	const float ALPHA_MULTI = 2.0f;					//α値にかける数値
	const float VOLUME_MINUS = 0.01f;				//音量を下げるための定数
	const float VOLUME = 0.6f;						//音量
}

Title::~Title() 
{
	for (auto ptLig : m_lightArray) {
		delete ptLig;
	}
	DeleteGO(m_bgm);
}

bool Title::Start()
{
	//フェードの検索
	m_fade = FindGO<Fade>("fade");

	//カメラの初期設定
	m_toCameraPos.Set(0.0f, 150.0f, -200.0f);
	g_camera3D->SetFar(10000.0f);

	g_soundEngine->ResistWaveFileBank(0, "Assets/sound/title/title.wav");
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/title/play.wav");
	m_volume = VOLUME;
	//BGM再生
	m_bgm = NewGO<SoundSource>(0);
	m_bgm->Init(0);
	m_bgm->Play(true);
	m_bgm->SetVolume(m_volume);

	//モデルの初期化
	m_modelRender.Init("Assets/modelData/title/title.tkm");
	m_modelRender.SetPosition(m_modelPos);

	//画像の初期化
	m_spriteRender.Init("Assets/sprite/title/candle.dds", 1024.0f, 256.0f);
	m_spriteRender1.Init("Assets/sprite/title/play.dds", 512.0f, 256.0f);
	m_spriteRender2.Init("Assets/sprite/select.dds", 512.0f, 512.0f);

	//ライトの座標
	Vector3 lightPos = m_modelPos;
	lightPos.y += LIGHT_YPOS;

	//ポイントライトのオブジェクトを作る。
	m_ptLight = new PointLight;
	m_ptLight->Init();
	m_ptLight->SetColor(Vector3(0.7f, 0.7f, 0.7f));
	m_ptLight->SetAffectPowParam(LIGHT_POW_PARAM);
	m_ptLight->SetRange(LIGHT_RANGE);
	m_ptLight->SetPosition(lightPos);
	m_lightArray.push_back(m_ptLight);

	m_level2DRender.Init("Assets/level2D/title.casl", [&](Level2DObjectData& objData)
		{
			//タイトル
			if (objData.EqualObjectName("candle") == true)
			{
				m_spriteRender.SetPosition(objData.position);
				return true;
			}
			//プレイボタン、選択ボタン
			if (objData.EqualObjectName("play") == true)
			{
				m_spriteRender1.SetPosition(objData.position);
				m_spriteRender2.SetPosition(objData.position);
				return true;
			}
			return true;
		});
	//このクラスをフェードインさせる
	m_fade->StartFadeIn();
	return true;
}

void Title::Update()
{
	if (m_fadeOut)
	{
		if (m_volume <= 0.0f)
		{
			m_volume = 0.0f;
		}
		m_volume -= VOLUME_MINUS;
		m_bgm->SetVolume(m_volume);

	}
	if (m_fade->IsFade())
	{
		//ゲームクラスの生成
		m_game = NewGO<Game>(0, "game");
		DeleteGO(this);
	}
	//Aボタンを押したら
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		m_sound = NewGO<SoundSource>(0);
		m_sound->Init(1);
		m_sound->Play(false);
		m_sound->SetVolume(0.5f);
		//フェードアウト中のフラグを立てる
		m_fadeOut = 1;
		//このクラスをフェードアウトさせる
		m_fade->StartFadeOut();
	}
	//ポイントライトの更新
	m_ptLight->Update();
	//α値の計算
	m_alpha += g_gameTime->GetFrameDeltaTime() * ALPHA_MULTI;
	//正弦波を使うことで0.0~1.0を往来させて点滅する。
	m_spriteRender2.SetMulColor(Vector4(1.0f, 1.0f, 1.0f, fabsf(sinf(m_alpha))));

	Vector3 target = Vector3::Zero;
	//Y座標を少し上げる
	target.y += 10.0f;

	//視点を計算する
	Vector3 pos = target + m_toCameraPos;

	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(target);
	g_camera3D->Update();

	m_modelRender.Update();
	m_spriteRender.Update();
	m_spriteRender1.Update();
	m_spriteRender2.Update();
}

void Title::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
	m_spriteRender.Draw(rc);
	m_spriteRender2.Draw(rc);
	m_spriteRender1.Draw(rc);
}