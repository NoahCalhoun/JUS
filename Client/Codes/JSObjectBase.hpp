#pragma once

#include "stdafx.h"

enum class EComponentType : INT8
{
	Base = -1,
	Transform,
};

class JSComponentBase abstract
{
protected:
	explicit JSComponentBase() {}
public:
	virtual ~JSComponentBase() {}

	shared_ptr<class JSObjectBase> m_pOwner;
	virtual void UpdateComponent() = 0;

	static EComponentType GetType() { return EComponentType::Base; }
};

class JSObjectBase abstract
{
protected:
	explicit JSObjectBase() {}
public:
	virtual ~JSObjectBase() { if (m_pSelf) m_pSelf.reset(); }

protected:
	typedef unordered_map<EComponentType, shared_ptr<JSComponentBase>> COMPONENT;
	COMPONENT m_mapComponent;

	virtual bool InitObject() { return false; }
	virtual void ReleaseObject() { m_mapComponent.clear(); }

public:
	shared_ptr<JSObjectBase> m_pSelf;

	//template <typename T> static shared_ptr<T> Create();

	virtual void Update() { for (auto iterator : m_mapComponent) iterator.second->UpdateComponent(); }

	template <typename T> shared_ptr<T> AddComponent(shared_ptr<T> _component = nullptr);

	template <typename T> shared_ptr<T> GetComponent();
};

//template<typename T>
//inline shared_ptr<T> JSObjectBase::Create()
//{
//	shared_ptr<T> pObject(new T);
//	if (auto baseObject = dynamic_pointer_cast<JSObjectBase>(pObject))
//	{
//		baseObject->m_pSelf = baseObject;
//		baseObject->Begin();
//		return pObject;
//	}
//	else
//	{
//		pObject.reset();
//		return NULL;
//	}
//}

template<typename T>
inline shared_ptr<T> JSObjectBase::AddComponent(shared_ptr<T> _component)
{
	auto comp = m_mapComponent.find(T::GetType());
	if (comp != m_mapComponent.end())
		return NULL;

	if (!_component)
		_component = T::Create();

	_component->m_pOwner = m_pSelf;
	_component->InitComponent();
	m_mapComponent.insert(COMPONENT::value_type(T::GetType(), _component));

	return _component;
}

template<typename T>
inline shared_ptr<T> JSObjectBase::GetComponent()
{
	auto value = m_mapComponent.find(T::GetType());
	if (value == m_mapComponent.end())
		return NULL;

	return dynamic_pointer_cast<T>(value->second);
}