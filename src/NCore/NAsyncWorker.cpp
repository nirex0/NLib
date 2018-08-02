// © 2018 NIREX ALL RIGHTS RESERVED

#include "NAsyncWorker.h"

namespace NLib
{
	NAsyncWorker::NAsyncWorker()
	{
		thr = new std::thread();
		m_WorkRegistry = new NRegistry();
		m_DoneRegistry = new NRegistry();
	}

	NAsyncWorker::~NAsyncWorker()
	{
		delete thr;
		delete m_WorkRegistry;
		delete m_DoneRegistry;
	}

	NRegistry* NAsyncWorker::WorkRegistry(void) const
	{
		return m_WorkRegistry;
	}

	NRegistry* NAsyncWorker::DoneRegistry(void) const
	{
		return m_DoneRegistry;
	}

	NRegistry* NAsyncWorker::WorkRegistry(NRegistry* intake)
	{
		m_WorkRegistry = intake;
		return m_WorkRegistry;
	}

	NRegistry* NAsyncWorker::DoneRegistry(NRegistry* intake)
	{
		m_DoneRegistry = intake;
		return m_DoneRegistry;
	}

	void NAsyncWorker::RunWorkerAsync(void)
	{
		if (WorkThread(*thr))
		{
			thr->detach();
		}
		m_DoneRegistry->Run(this, new NAsyncArgs());
	}

	void NAsyncWorker::RunWorkerAsyncSafe(void)
	{
		if (!m_isRunning)
		{
			if (WorkThread(*thr))
			{
				thr->detach();
			}
			m_DoneRegistry->Run(this, new NAsyncArgs());
		}
	}

	bool NAsyncWorker::IsRunning(void)
	{
		return m_isRunning;
	}

	bool NAsyncWorker::WorkThread(std::thread& out)
	{
		for (const auto& p : m_WorkRegistry->Container())
		{
			out = std::thread([=] { (*p)(this, new NAsyncArgs()); });
		}
		return true;
	}
}