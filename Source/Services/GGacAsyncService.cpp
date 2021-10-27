//
// Created by css on 6/27/21.
//

#include "GGacAsyncService.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			using namespace collections;

			GGacAsyncService::TaskItem::TaskItem()
			:semaphore(0)
			{
			}

			GGacAsyncService::TaskItem::TaskItem(Semaphore* _semaphore, const Func<void()>& _proc)
			:semaphore(_semaphore),
			proc(_proc)
			{
			}

			GGacAsyncService::TaskItem::~TaskItem()
			{
			}

			GGacAsyncService::DelayItem::DelayItem(GGacAsyncService* _service, const Func<void()>& _proc, bool _executeInMainThread, vint milliseconds)
			:service(_service),
			proc(_proc),
			status(INativeDelay::Pending),
			executeTime(DateTime::LocalTime().Forward(milliseconds)),
			executeInMainThread(_executeInMainThread)
			{
			}

			GGacAsyncService::DelayItem::~DelayItem()
			{
			}

			INativeDelay::ExecuteStatus GGacAsyncService::DelayItem::GetStatus()
			{
				return status;
			}

			bool GGacAsyncService::DelayItem::Delay(vint milliseconds)
			{
				SPIN_LOCK(service->taskListLock)
				{
					if (status == INativeDelay::Pending)
					{
						executeTime = DateTime::LocalTime().Forward(milliseconds);
						return true;
					}
				}
				return false;
			}

			bool GGacAsyncService::DelayItem::Cancel()
			{
				SPIN_LOCK(service->taskListLock)
				{
					if (status == INativeDelay::Pending)
					{
						if (service->delayItems.Remove(this))
						{
							status = INativeDelay::Canceled;
							return true;
						}
					}
				}
				return false;
			}

			///

			GGacAsyncService::GGacAsyncService()
			:mainThreadId(Thread::GetCurrentThreadId())
			{
			}

			GGacAsyncService::~GGacAsyncService()
			{
			}

			void GGacAsyncService::ExecuteAsyncTasks()
			{
				DateTime now = DateTime::LocalTime();
				Array<TaskItem> items;
				List<Ptr<DelayItem>> executableDelayItems;

				SPIN_LOCK(taskListLock)
				{
					CopyFrom(items, taskItems);
					taskItems.RemoveRange(0, items.Count());
					for (vint i = delayItems.Count()-1; i>=0 ;i--)
					{
						Ptr<DelayItem> item = delayItems[i];
						if (now.filetime >= item->executeTime.filetime)
						{
							item->status = INativeDelay::Executing;
							executableDelayItems.Add(item);
							delayItems.RemoveAt(i);
						}
					}
				}

				for (auto item : items)
				{
					item.proc();
					if (item.semaphore)
					{
						item.semaphore->Release();
					}
				}

				for (auto item : executableDelayItems)
				{
					if (item->executeInMainThread)
					{
						item->proc();
						item->status = INativeDelay::Executed;
					}
					else
					{
						InvokeAsync([=]()
						{
							item->proc();
							item->status = INativeDelay::Executed;
						});
					}
				}
			}

			bool GGacAsyncService::IsInMainThread(INativeWindow* window)
			{
				return Thread::GetCurrentThreadId() == mainThreadId;
			}

			void GGacAsyncService::InvokeAsync(const Func<void()>& proc)
			{
				ThreadPoolLite::Queue(proc);
			}

			void GGacAsyncService::InvokeInMainThread(INativeWindow* window, const Func<void()>& proc)
			{
				SPIN_LOCK(taskListLock)
				{
					TaskItem item(0, proc);
					taskItems.Add(item);
				}
			}

			bool GGacAsyncService::InvokeInMainThreadAndWait(INativeWindow* window, const Func<void()>& proc, vint milliseconds)
			{
				Semaphore* semaphore = new Semaphore();
				semaphore->Create(0, 1);

				TaskItem item(semaphore, proc);
				SPIN_LOCK(taskListLock)
				{
					taskItems.Add(item);
				}

				return semaphore->Wait();
			}

			Ptr<INativeDelay> GGacAsyncService::DelayExecute(const Func<void()>& proc, vint milliseconds)
			{
				Ptr<DelayItem> delay;
				SPIN_LOCK(taskListLock)
				{
					delay = new DelayItem(this, proc, false, milliseconds);
					delayItems.Add(delay);
				}
				return delay;
			}

			Ptr<INativeDelay> GGacAsyncService::DelayExecuteInMainThread(const Func<void()>& proc, vint milliseconds)
			{
				Ptr<DelayItem> delay;
				SPIN_LOCK(taskListLock)
				{
					delay = new DelayItem(this, proc, true, milliseconds);
					delayItems.Add(delay);
				}
				return delay;
			}

		}

	}
}