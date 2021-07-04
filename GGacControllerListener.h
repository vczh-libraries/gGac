//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACCONTROLLERLISTENER_H
#define GGAC_GGACCONTROLLERLISTENER_H

#include "GacUI.h"
#include "GGacWindowListener.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			using namespace collections;

			class GGacControllerListener : public Object, public INativeControllerListener
			{
			protected:
				Dictionary<INativeWindow*, Ptr<GGacWindowListener>>  nativeWindowListeners;

			public:
				void GlobalTimer() override;
				void ClipboardUpdated() override;
				void NativeWindowCreated(INativeWindow *window) override;
				void NativeWindowDestroying(INativeWindow *window) override;
				Ptr<GGacWindowListener> GetGGacWindowListener(INativeWindow* window);
			};

		}

	}

}

#endif //GGAC_GGACCONTROLLERLISTENER_H
