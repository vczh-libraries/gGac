//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACCALLBACKSERVICE_H
#define GGAC_GGACCALLBACKSERVICE_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacCallbackService : public Object, public INativeCallbackService
			{
			public:
				bool InstallListener(INativeControllerListener *listener) override;
				bool UninstallListener(INativeControllerListener *listener) override;

				void InvokeGlobalTimer();
				void InvokeClipboardUpdated();
				void InvokeNativeWindowCreated(INativeWindow* window);
				void InvokeNativeWindowDestroyed(INativeWindow* window);
			};

		}

	}

}


#endif //GGAC_GGACCALLBACKSERVICE_H
