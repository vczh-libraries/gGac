//
// Created by css on 6/27/21.
//

#include "GGacControllerListener.h"
#include "Renderers/GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			void GGacControllerListener::GlobalTimer()
			{
				/*auto window = GetCurrentController()->WindowService()->GetMainWindow();
				auto view = GetGGacWindowListener(window)->GetGGacView();*/
				for (vint i = 0; i < nativeWindowListeners.Count(); i++)
				{
					auto view = nativeWindowListeners.Values()[i]->GetGGacView();
					view->queue_draw();
				}
			}

			void GGacControllerListener::ClipboardUpdated()
			{
			}

			void GGacControllerListener::NativeWindowCreated(vl::presentation::INativeWindow *window)
			{
				Ptr<GGacWindowListener> listener = Ptr(new GGacWindowListener(window));
				window->InstallListener(listener.Obj());
				nativeWindowListeners.Add(window, listener);
			}

			void GGacControllerListener::NativeWindowDestroying(vl::presentation::INativeWindow *window)
			{
				Ptr<GGacWindowListener> listener = nativeWindowListeners.Get(window);
				nativeWindowListeners.Remove(window);
				window->UninstallListener(listener.Obj());
			}

			Ptr<GGacWindowListener> GGacControllerListener::GetGGacWindowListener(INativeWindow* window)
			{
				vint index = nativeWindowListeners.Keys().IndexOf(window);
				return index == -1 ? nullptr : nativeWindowListeners.Values().Get(index);
			}

		}

	}

}