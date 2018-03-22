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

	static D3DXVECTOR3 MatrixToEuler(const D3DXMATRIX& _matrix);
	static D3DXVECTOR3 QuaternionToEuler(const D3DXQUATERNION& _quaternion);
	static D3DXVECTOR3 ZeroVector;
	static D3DXVECTOR3 OneVector;
	static D3DXMATRIX IdentityMatrix;

	void SetScale(const float& _scale);
	void SetPosition(const D3DXVECTOR3& _position);
	void SetRotation(const D3DXVECTOR3& _rotation);

	void Scaling(const float& _scale);
	void Translate(const D3DXVECTOR3& _vector);
	void RotateByBasis(EBasisVectorType _type, const float& _angle);
	void RotateByAxis(const D3DXVECTOR3& _axis, const float& _angle);

	const D3DXMATRIX* GetWorld();
	const D3DXVECTOR3* GetScale();
	const D3DXVECTOR3* GetPosition();
	const D3DXQUATERNION* GetRotation();
	const D3DXVECTOR3 GetBasis(EBasisVectorType _type);
	const float GetAngle(EBasisVectorType _type);

	void GenerateWorldMatrix();

private:
	D3DXMATRIX m_matWorld;
	D3DXVECTOR3 m_vScale;
	D3DXQUATERNION m_qRotation;
	D3DXVECTOR3 m_vPosition;
};