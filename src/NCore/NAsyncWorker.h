// © 2018 NIREX ALL RIGHTS RESERVED

#ifndef _N_ASYNCWORKER_H_
#define _N_ASYNCWORKER_H_

#include "NObject.h"
#include "NRegistry.h"
#include "NAsyncArgs.h"
#include "NDefines.h"

#include <chrono>
#include <mutex>
#include <thread>
#include <future>

namespace NLib
{
	class NAsyncWorker : public NObject
	{
	public:
		NAPI NAsyncWorker();
		NAPI ~NAsyncWorker();

		// Getters
		NAPI NRegistry* WorkRegistry(void) const;
		NAPI NRegistry* DoneRegistry(void) const;

		// Setters
		NAPI NRegistry* WorkRegistry(NRegistry* intake);
		NAPI NRegistry* DoneRegistry(NRegistry* intake);

		// Functions
		NAPI void RunWorkerAsync(void);
		NAPI void RunWorkerAsyncSafe(void);
		NAPI bool IsRunning(void);

	private:
		NAPI bool WorkThread(std::thread& out);

	private:
		std::thread thr;
		std::mutex m_MutexLock;

		bool m_isRunning;
		NRegistry* m_WorkRegistry;
		NRegistry* m_DoneRegistry;
	};
}

#endif // !_W_ASYNCWORKER_H_
