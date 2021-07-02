//
// Created by css on 6/27/21.
//

#include "GGacCallbackService.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			using namespace collections;
			List<INativeControllerListener *> listeners;

			bool GGacCallbackService::InstallListener(INativeControllerListener *listener)
			{
				if (listeners.Contains(listener))
				{
					return false;
				}
				else
				{
					listeners.Add(listener);
					return true;
				}
			}

			bool GGacCallbackService::UninstallListener(INativeControllerListener *listener)
			{
				if (listeners.Contains(listener))
				{
					listeners.Remove(listener);
					return true;
				}
				else
				{
					return false;
				}
			}

			void GGacCallbackService::InvokeGlobalTimer()
			{
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->GlobalTimer();
				}
			}

			void GGacCallbackService::InvokeClipboardUpdated()
			{
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->ClipboardUpdated();
				}
			}

			void GGacCallbackService::InvokeNativeWindowCreated(INativeWindow* window)
			{
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->NativeWindowCreated(window);
				}
			}

			void GGacCallbackService::InvokeNativeWindowDestroyed(INativeWindow* window)
			{
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->NativeWindowDestroying(window);
				}
			}

		}

	}

}