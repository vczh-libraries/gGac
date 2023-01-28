//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GGACASYNCSERVICE_H
#define GGAC_GGACASYNCSERVICE_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacAsyncService : public INativeAsyncService
			{
			protected:
				struct TaskItem
				{
					Semaphore*              semaphore;
					Func<void()>            proc;

					TaskItem();
					TaskItem(Semaphore* _semaphore, const Func<void()>& _proc);
					~TaskItem();
				};

				class DelayItem: public Object, public INativeDelay
				{
				public:
					DelayItem(GGacAsyncService* _service, const Func<void()>& _proc, bool _executeInMainThread, vint milliseconds);
					~DelayItem();

					GGacAsyncService*      service;
					Func<void()>            proc;
					ExecuteStatus           status;
					DateTime                executeTime;
					bool                    executeInMainThread;

					ExecuteStatus           GetStatus() override;
					bool                    Delay(vint milliseconds) override;
					bool                    Cancel() override;
				};

				collections::List<TaskItem>             taskItems;
				collections::List<Ptr<DelayItem>>       delayItems;
				SpinLock                                taskListLock;
				vint                                    mainThreadId;

			public:
				GGacAsyncService();
				~GGacAsyncService();

				void ExecuteAsyncTasks();
				bool IsInMainThread(INativeWindow *window) override;
				void InvokeAsync(const Func<void()> &proc) override;
				void InvokeInMainThread(INativeWindow *window, const Func<void()> &proc) override;
				bool InvokeInMainThreadAndWait(INativeWindow *window, const Func<void()> &proc, vint milliseconds) override;
				Ptr<INativeDelay> DelayExecute(const Func<void()> &proc, vint milliseconds) override;
				Ptr<INativeDelay> DelayExecuteInMainThread(const Func<void()> &proc, vint milliseconds) override;
			};

		}

	}

}

#endif //GGAC_GGACASYNCSERVICE_H
