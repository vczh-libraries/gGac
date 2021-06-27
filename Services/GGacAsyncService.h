//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACASYNCSERVICE_H
#define GGAC_GGACASYNCSERVICE_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacAsyncService : public INativeAsyncService
			{
			public:
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
