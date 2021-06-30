//
// Created by css on 6/27/21.
//

#include "GGacCallbackService.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			bool GGacCallbackService::InstallListener(INativeControllerListener *listener)
			{
				return true;
			}

			bool GGacCallbackService::UninstallListener(INativeControllerListener *listener)
			{
				return true;
			}

			void GGacCallbackService::InvokeGlobalTimer()
			{

			}

			void GGacCallbackService::InvokeClipboardUpdated()
			{

			}

			void GGacCallbackService::InvokeNativeWindowCreated(INativeWindow* window)
			{

			}

			void GGacCallbackService::InvokeNativeWindowDestroyed(INativeWindow* window)
			{

			}
		}

	}

}