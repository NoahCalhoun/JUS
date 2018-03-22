#include "stdafx.h"
#include "Transform.h"

D3DXVECTOR3 JSTransform::ZeroVector = D3DXVECTOR3(0, 0, 0);
D3DXVECTOR3 JSTransform::OneVector = D3DXVECTOR3(1, 1, 1);
D3DXMATRIX JSTransform::IdentityMatrix = D3DXMATRIX(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

JSTransform::JSTransform()
	: JSComponentBase()
	, m_matWorld(IdentityMatrix)
	, m_vScale(OneVector)
	, m_qRotation(0, 0, 0, 1)
	, m_vPosition(ZeroVector)
{
}

JSTransform::~JSTransform()
{
}

shared_ptr<JSTransform> JSTransform::Create()
{
	shared_ptr<JSTransform> value(new JSTransform());
	return value;
}

void JSTransform::UpdateComponent()
{
	GenerateWorldMatrix();
}

D3DXVECTOR3 JSTransform::MatrixToEuler(const D3DXMATRIX & _matrix)
{
	D3DXMATRIX	matWorld = _matrix;
	D3DXVec3Normalize((D3DXVECTOR3*)matWorld.m[0], (D3DXVECTOR3*)matWorld.m[0]);
	D3DXVec3Normalize((D3DXVECTOR3*)matWorld.m[1], (D3DXVECTOR3*)matWorld.m[1]);
	D3DXVec3Normalize((D3DXVECTOR3*)matWorld.m[2], (D3DXVECTOR3*)matWorld.m[2]);

	float yaw, pitch, roll;

	pitch = asinf(matWorld.m[2][1]);
	while (pitch > D3DX_PI / 2.f || pitch < -1 * D3DX_PI / 2.f)
	{
		//need to check Error
		if (pitch > D3DX_PI / 2.f)
			pitch -= (D3DX_PI * 2.f);
		else if (pitch < -1 * D3DX_PI / 2.f)
			pitch += (D3DX_PI * 2.f);
	}

	auto critical = matWorld.m[0][1] == 0 && matWorld.m[1][1] == 0;
	yaw = critical ? 0.f : atan2f(-1 * matWorld.m[2][0], matWorld.m[2][2]);
	roll = critical ? atan2f(matWorld.m[1][0], matWorld.m[0][0]) : atan2f(-1 * matWorld.m[0][1], matWorld.m[1][1]);

	return D3DXVECTOR3(pitch, yaw, roll);
}

D3DXVECTOR3 JSTransform::QuaternionToEuler(const D3DXQUATERNION & _quaternion)
{
	float sqw = _quaternion.w * _quaternion.w;
	float sqx = _quaternion.x * _quaternion.x;
	float sqy = _quaternion.y * _quaternion.y;
	float sqz = _quaternion.z * _quaternion.z;

	float x = (asinf(2.f * (_quaternion.w * _quaternion.x - _quaternion.y * _quaternion.z)));
	float y = (atan2f(2.f * (_quaternion.x * _quaternion.z + _quaternion.w * _quaternion.y), (-sqx - sqy + sqz + sqw)));
	float z = (atan2f(2.f * (_quaternion.x * _quaternion.y + _quaternion.w * _quaternion.z), (-sqx + sqy - sqz + sqw)));

	return D3DXVECTOR3(x, y, z);
}

void JSTransform::SetScale(const float & _scale)
{
	m_vScale = OneVector * _scale;
}

void JSTransform::SetPosition(const D3DXVECTOR3 & _position)
{
	m_vPosition = _position;
}

void JSTransform::SetRotation(const D3DXVECTOR3 & _rotation)
{
	D3DXQuaternionRotationYawPitchRoll(&m_qRotation, _rotation.y, _rotation.x, _rotation.z);
}

void JSTransform::Scaling(const float & _scale)
{
	m_vScale *= _scale;
}

void JSTransform::Translate(const D3DXVECTOR3 & _vector)
{
	m_vPosition += _vector;
}

void JSTransform::RotateByBasis(EBasisVectorType _type, const float & _angle)
{
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationAxis(&quatRot, &GetBasis(_type), _angle);
	m_qRotation *= quatRot;
}

void JSTransform::RotateByAxis(const D3DXVECTOR3 & _axis, const float & _angle)
{
	D3DXQUATERNION quatRot;
	D3DXQuaternionRotationAxis(&quatRot, &_axis, _angle);
	m_qRotation *= quatRot;
}

const D3DXMATRIX* JSTransform::GetWorld()
{
	return &m_matWorld;
}

const D3DXVECTOR3* JSTransform::GetScale()
{
	return &m_vScale;
}

const D3DXVECTOR3* JSTransform::GetPosition()
{
	return &m_vPosition;
}

const D3DXQUATERNION* JSTransform::GetRotation()
{
	return &m_qRotation;
}

const D3DXVECTOR3 JSTransform::GetBasis(EBasisVectorType _type)
{
	D3DXVECTOR3 returnVector;
	D3DXVec3Normalize(&returnVector, (D3DXVECTOR3*)m_matWorld.m[(int)_type]);
	return returnVector;
}

const float JSTransform::GetAngle(EBasisVectorType _type)
{
	return ((float*)MatrixToEuler(m_matWorld))[(int)_type];
}

void JSTransform::GenerateWorldMatrix()
{
	D3DXMATRIX matScale;
	D3DXMATRIX matRot;
	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);
	D3DXMatrixRotationQuaternion(&matRot, &m_qRotation);

	m_matWorld = matScale * matRot * matTrans;
}
