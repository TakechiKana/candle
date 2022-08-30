#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround() {};
	void Render(RenderContext& rc);
	/// <summary>
	/// ç¿ïWÇÃê›íË
	/// </summary>
	/// <param name="pos"></param>
	void SetPosition(Vector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ägëÂó¶ÇÃê›íË
	/// </summary>
	/// <param name="scale"></param>
	void SetScale(Vector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// âÒì]ÇÃê›íË
	/// </summary>
	/// <param name="rot"></param>
	void SetRotation(Quaternion rot)
	{
		m_rot = rot;
	}

private:
	Vector3 m_position = Vector3::Zero;
	Vector3 m_scale = Vector3::One;
	Quaternion m_rot = Quaternion::Identity;
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
};

