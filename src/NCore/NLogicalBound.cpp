// © 2019 NIREX ALL RIGHTS RESERVED

#include "NLogicalBound.h"

namespace NLib
{
	NLogicalBound::NLogicalBound()
	{
	}

	NLogicalBound::~NLogicalBound()
	{
	}

	bool NLogicalBound::Binding(void) const
	{
		return m_binding;
	}

	bool NLogicalBound::Binding(bool intake)
	{
		m_binding = intake;
		return m_binding;
	}

	BindAnnex* NLogicalBound::Function(void) const
	{
		return m_annex;
	}

	BindAnnex* NLogicalBound::Function(BindAnnex intake)
	{
		m_annex = &intake;
		return m_annex;
	}

	void NLogicalBound::operator=(BindAnnex rhs)
	{
		m_annex = &rhs;
	}

	void NLogicalBound::operator()(void)
	{
		BindAnnex current;
		if (m_annex)
		{
			current = *m_annex;
			current(m_binding);
		}
	}

	void NLogicalBound::Run(void)
	{
		BindAnnex current;
		if (m_annex)
		{
			current = *m_annex;
			current(m_binding);
		}
	}
}
