#pragma once

#include "stdafx.h"

enum class EComponentType : INT8
{
	Base = -1,
	Transform,
	Camera,
	Renderer,
};

class JSComponentBase abstract
{
protected:
	explicit JSComponentBase() {}
public:
	virtual ~JSComponentBase() {}

	class JSObjectBase* m_pOwner;

#pragma region Override
	static EComponentType GetType() { return EComponentType::Base; }
	static shared_ptr<JSComponentBase> Create() { return nullptr; }
	virtual void InitComponent() {}
	virtual void UpdateComponent() = 0;
#pragma endregion
};

class JSObjectBase
{
protected:
	explicit JSObjectBase() : m_bEnable(true) {}
public:
	virtual ~JSObjectBase() {}

protected:
	typedef unordered_map<EComponentType, shared_ptr<JSComponentBase>> COMPONENT;
	COMPONENT m_mapComponent;
	bool m_bEnable;

	virtual bool InitObject() { return true; }
	virtual void ReleaseObject() { m_mapComponent.clear(); }

public:
	static shared_ptr<JSObjectBase> Create() { shared_ptr<JSObjectBase> value(new JSObjectBase()); return value; }

	virtual void Update() { if (!m_bEnable) return; for (auto iterator : m_mapComponent) iterator.second->UpdateComponent(); }
	bool IsEnable() { return m_bEnable; }

	template <typename T> shared_ptr<T> AddComponent(shared_ptr<T> _component = nullptr);

	template <typename T> shared_ptr<T> GetComponent();
};

template<typename T>
inline shared_ptr<T> JSObjectBase::AddComponent(shared_ptr<T> _component)
{
	auto comp = m_mapComponent.find(T::GetType());
	if (comp != m_mapComponent.end())
		return NULL;

	if (!_component)
		_component = T::Create();

	_component->m_pOwner = this;
	m_mapComponent.insert(COMPONENT::value_type(T::GetType(), _component));
	_component->InitComponent();

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