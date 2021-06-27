//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACSCREENSERVICE_H
#define GGAC_GGACSCREENSERVICE_H

#include "GacUI.h"
#include <gdk/gdk.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacScreen : public Object, public INativeScreen
			{
				friend class GGacScreenService;
			protected:
				GdkMonitor*    screen;

			public:
				GGacScreen(GdkMonitor* screen);

				double 			GetScalingX() override;
				double 			GetScalingY() override;
				NativeRect      GetBounds() override;
				NativeRect      GetClientBounds() override;
				WString         GetName() override;
				bool            IsPrimary() override;
			};

			class GGacScreenService : public Object, public INativeScreenService
			{
				typedef void (*HandleRetriver)(INativeWindow*);

			protected:
				collections::List<Ptr<GGacScreen>> 	screens;
				HandleRetriver 						handleRetriver;

			public:
				GGacScreenService();

				void                    RefreshScreenInformation();
				vint                    GetScreenCount() override;
				INativeScreen*          GetScreen(vint index) override;
				INativeScreen*          GetScreen(INativeWindow* window) override;
			};

		}

	}

}

#endif //GGAC_GGACSCREENSERVICE_H
