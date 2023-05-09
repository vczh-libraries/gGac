//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GGACCALLBACKSERVICE_H
#define GGAC_GGACCALLBACKSERVICE_H

#include "GacUI.h"
#include <gtkmm.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacCallbackService : public Object, public INativeCallbackService, public INativeCallbackInvoker
			{
			public:
				bool InstallListener(INativeControllerListener *listener) override;
				bool UninstallListener(INativeControllerListener *listener) override;
				INativeCallbackInvoker *Invoker() override;

				void InvokeGlobalTimer() override;
				void InvokeClipboardUpdated() override;
				void InvokeGlobalShortcutKeyActivated(vint id) override;
				void InvokeNativeWindowCreated(INativeWindow* window) override;
				void InvokeNativeWindowDestroying(INativeWindow* window) override;
			};

		}

	}

}


#endif //GGAC_GGACCALLBACKSERVICE_H
