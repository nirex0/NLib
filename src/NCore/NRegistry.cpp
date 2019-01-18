// © 2018 NIREX ALL RIGHTS RESERVED

#include "NRegistry.h"

namespace NLib
{
	NRegistry::NRegistry()
		: m_count(0)
	{
		m_registered = new std::vector<RegistryAnnex*>();
	}

	NRegistry::NRegistry(const NRegistry& nRegistery)
		: m_count(0)
	{
		for (size_t i = 0; i < nRegistery.m_registered->size(); i++)
		{
			this->Register(*(*nRegistery.m_registered)[i]);
			_InterlockedIncrement(&m_count);
		}
	}

	NRegistry::NRegistry(NRegistry&& nRegistery)
		: m_count(0)
	{
		for (size_t i = 0; i < nRegistery.m_registered->size(); i++)
		{
			this->Register(*(*nRegistery.m_registered)[i]);
			_InterlockedIncrement(&m_count);
		}
	}

	NRegistry::~NRegistry(void) 
	{
		delete m_registered;
	}

	long NRegistry::GetCount(void) const
	{
		return m_count;
	}

	NRegistry* NRegistry::operator()(NObject* sender, NEventArgs* args)
	{
		RegistryAnnex current;
		for (size_t i = 0; i < m_registered->size(); i++)
		{
			if ((*m_registered)[i] != nullptr)
			{
				current = *(*m_registered)[i];
				current(sender, args);
			}
		}
		return this;
	}

	NRegistry* NRegistry::Run(NObject* sender, NEventArgs* args)
	{
		RegistryAnnex current;
		for (size_t i = 0; i < m_registered->size(); i++)
		{
			if ((*m_registered)[i] != nullptr)
			{
				current = *(*m_registered)[i];
				current(sender, args);
			}
		}
		return this;
	}

	NRegistry* NRegistry::Register(RegistryAnnex rhs)
	{
		m_registered->push_back(new RegistryAnnex(rhs));
		_InterlockedIncrement(&m_count);
		return this;
	}

	NRegistry* NRegistry::UnRegister(RegistryAnnex* rhs)
	{
		for (size_t i = 0; i < m_registered->size(); i++)
		{
			if ((*m_registered)[i] == rhs)
			{
				(*m_registered)[i] = nullptr;
				_InterlockedDecrement(&m_count);
			}
		}
		return this;
	}

	NRegistry* NRegistry::operator+=(RegistryAnnex rhs)
	{
		m_registered->push_back(new RegistryAnnex(rhs));
		_InterlockedIncrement(&m_count);
		return this;
	}

	NRegistry* NRegistry::operator-=(RegistryAnnex rhs)
	{
		for (size_t i = 0; i < m_registered->size(); i++)
		{
			if ((*m_registered)[i] == &rhs)
			{
				(*m_registered)[i] = nullptr;
				_InterlockedDecrement(&m_count);
			}
		}
		return this;
	}

	std::vector<RegistryAnnex*> NRegistry::Container(void) const
	{
		return (*m_registered);
	}
}
