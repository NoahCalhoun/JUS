#include "stdafx.h"
#include "Transform.h"

JSTransform::JSTransform()
	: JSComponentBase()
	, m_matWorld(JSMATRIX::Identity())
	, m_vScale(JSVECTOR::One())
	, m_qRotation(JSVECTOR::Zero())
	, m_vPosition(JSVECTOR::Zero())
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

JSVECTOR JSTransform::MatrixToEuler(const JSMATRIX & _matrix)
{
	JSMATRIX matWorld = _matrix;
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

	return JSVECTOR(pitch, yaw, roll);
}

JSVECTOR JSTransform::QuaternionToEuler(const JSVECTOR & _quaternion)
{
	float quatX = _quaternion.f[0];
	float quatY = _quaternion.f[1];
	float quatZ = _quaternion.f[2];
	float quatW = _quaternion.f[3];

	float sqw = quatW * quatW;
	float sqx = quatX * quatX;
	float sqy = quatY * quatY;
	float sqz = quatZ * quatZ;

	float x = (asinf(2.f * (quatW * quatX - quatY * quatZ)));
	float y = (atan2f(2.f * (quatX * quatZ + quatW * quatY), (-sqx - sqy + sqz + sqw)));
	float z = (atan2f(2.f * (quatX * quatY + quatW * quatZ), (-sqx + sqy - sqz + sqw)));

	return JSVECTOR(x, y, z);
}

void JSTransform::SetScale(const float & _scale)
{
	m_vScale = JSVECTOR::One() * _scale;
}

void JSTransform::SetPosition(const JSVECTOR & _position)
{
	m_vPosition = _position;
}

void JSTransform::SetRotation(const JSVECTOR & _rotation)
{
	m_qRotation = XMQuaternionRotationRollPitchYaw(_rotation.f[0], _rotation.f[1], _rotation.f[2]);
}

void JSTransform::Scaling(const float & _scale)
{
	m_vScale *= _scale;
}

void JSTransform::Translate(const JSVECTOR & _vector)
{
	m_vPosition += _vector;
}

void JSTransform::RotateByBasis(EBasisVectorType _type, const float & _angle)
{
	JSVECTOR quatRot;
	quatRot = XMQuaternionRotationAxis(GetBasis(_type).v, _angle);
	m_qRotation *= quatRot;
}

void JSTransform::RotateByAxis(const JSVECTOR & _axis, const float & _angle)
{
	JSVECTOR quatRot;
	quatRot = XMQuaternionRotationAxis(_axis.v, _angle);
	m_qRotation *= quatRot;
}

const JSMATRIX* JSTransform::GetWorld()
{
	return &m_matWorld;
}

const JSVECTOR* JSTransform::GetScale()
{
	return &m_vScale;
}

const JSVECTOR* JSTransform::GetPosition()
{
	return &m_vPosition;
}

const JSVECTOR* JSTransform::GetRotation()
{
	return &m_qRotation;
}

const JSVECTOR JSTransform::GetBasis(EBasisVectorType _type)
{
	JSVECTOR returnVector;
	returnVector = XMVector3Normalize(m_matWorld.r[(int)_type]);
	return returnVector;
}

const float JSTransform::GetAngle(EBasisVectorType _type)
{
	return MatrixToEuler(m_matWorld).f[(int)_type];
}

void JSTransform::GenerateWorldMatrix()
{
	JSMATRIX matScale;
	JSMATRIX matRot;
	JSMATRIX matTrans;

	matScale = XMMatrixScalingFromVector(m_vScale);
	matRot = XMMatrixRotationQuaternion(m_qRotation.v);
	matTrans = XMMatrixTranslationFromVector(m_vPosition);

	//m_matWorld = XMMatrixScalingFromVector(m_vScale) * XMMatrixRotationQuaternion(m_qRotation.v) * XMMatrixTranslationFromVector(m_vPosition);
	m_matWorld = matScale * matRot * matTrans;
}
