//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACCONTROLLERLISTENER_H
#define GGAC_GGACCONTROLLERLISTENER_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacControllerListener : public Object, public INativeControllerListener
			{
			public:
				void GlobalTimer() override;
				void ClipboardUpdated() override;
				void NativeWindowCreated(INativeWindow *window) override;
				void NativeWindowDestroying(INativeWindow *window) override;
			};

		}

	}

}

#endif //GGAC_GGACCONTROLLERLISTENER_H
