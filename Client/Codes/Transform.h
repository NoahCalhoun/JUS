#pragma once

#include "JSObjectBase.hpp"

enum class EBasisVectorType : INT8
{
	Right,
	Up,
	Front
};

class JSTransform : public JSComponentBase
{
protected:
	explicit JSTransform();
public:
	virtual ~JSTransform();

public:
	static EComponentType GetType() { return EComponentType::Transform; }
	static shared_ptr<JSTransform> Create();
	virtual void UpdateComponent() override;

	static JSVECTOR MatrixToEuler(const JSMATRIX& _matrix);
	static JSVECTOR QuaternionToEuler(const JSVECTOR& _quaternion);

	void SetScale(const float& _scale);
	void SetPosition(const JSVECTOR& _position);
	void SetRotation(const JSVECTOR& _rotation);

	void Scaling(const float& _scale);
	void Translate(const JSVECTOR& _vector);
	void RotateByBasis(EBasisVectorType _type, const float& _angle);
	void RotateByAxis(const JSVECTOR& _axis, const float& _angle);

	const JSMATRIX* GetWorld();
	const JSVECTOR* GetScale();
	const JSVECTOR* GetPosition();
	const JSVECTOR* GetRotation();
	const JSVECTOR GetBasis(EBasisVectorType _type);
	const float GetAngle(EBasisVectorType _type);

	void GenerateWorldMatrix();

private:
	//D3DXMATRIX m_matWorld;
	//D3DXVECTOR3 m_vScale;
	//D3DXQUATERNION m_qRotation;
	//D3DXVECTOR3 m_vPosition;

	JSMATRIX m_matWorld;
	JSVECTOR m_vScale;
	JSVECTOR m_qRotation;
	JSVECTOR m_vPosition;
};