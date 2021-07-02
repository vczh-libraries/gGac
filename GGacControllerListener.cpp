//
// Created by css on 6/27/21.
//

#include "GGacControllerListener.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			void GGacControllerListener::GlobalTimer()
			{
			}

			void GGacControllerListener::ClipboardUpdated()
			{
			}

			void GGacControllerListener::NativeWindowCreated(vl::presentation::INativeWindow *window)
			{
				Ptr<GGacWindowListener> listener = MakePtr<GGacWindowListener>(window);
				window->InstallListener(listener.Obj());
				nativeWindowListeners.Add(window, listener);
			}

			void GGacControllerListener::NativeWindowDestroying(vl::presentation::INativeWindow *window)
			{
				Ptr<GGacWindowListener> listener = nativeWindowListeners.Get(window);
				nativeWindowListeners.Remove(window);
				window->UninstallListener(listener.Obj());
			}

		}

	}

}