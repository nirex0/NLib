// © 2018 NIREX ALL RIGHTS RESERVED

#include "..\..\Header Files\Core\NLogicalBound.h"

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

	NBinding* NLogicalBound::Function(void) const
	{
		return m_annex;
	}

	NBinding* NLogicalBound::Function(NBinding intake)
	{
		m_annex = &intake;
		return m_annex;
	}

	void NLogicalBound::operator=(NBinding rhs)
	{
		m_annex = &rhs;
	}

	void NLogicalBound::operator()(void)
	{
		NBinding current;
		if (m_annex)
		{
			current = *m_annex;
			current(m_binding);
		}
	}

	void NLogicalBound::Run(void)
	{
		NBinding current;
		if (m_annex)
		{
			current = *m_annex;
			current(m_binding);
		}
	}
}
