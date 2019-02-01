// © 2019 NIREX ALL RIGHTS RESERVED

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
	class NAPI NAsyncWorker : public NObject
	{
	public:
		NAsyncWorker();
		~NAsyncWorker();

		NRegistry* WorkRegistry(void) const;
		NRegistry* DoneRegistry(void) const;

		NRegistry* WorkRegistry(NRegistry* intake);
		NRegistry* DoneRegistry(NRegistry* intake);

		void RunWorkerAsync(void);
		void RunWorkerAsyncSafe(void);
		bool IsRunning(void);

	private:
		bool WorkThread(std::thread& out);

	private:
		std::thread* thr;

		bool m_isRunning;
		NRegistry* m_WorkRegistry;
		NRegistry* m_DoneRegistry;
	};
}

#endif // !_W_ASYNCWORKER_H_
