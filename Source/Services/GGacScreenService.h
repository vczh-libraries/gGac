//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GGACSCREENSERVICE_H
#define GGAC_GGACSCREENSERVICE_H

#include "GacUI.h"
#include <gtkmm.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacScreen : public Object, public INativeScreen
			{
				friend class GGacScreenService;
			protected:
				Glib::RefPtr<Gdk::Monitor>    monitor;

			public:
				GGacScreen(Glib::RefPtr<Gdk::Monitor> monitor);

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
				collections::List<Ptr<GGacScreen>> 	monitors;
				HandleRetriver 						handleRetriver;

			public:
				void                    RefreshScreenInformation();
				vint                    GetScreenCount() override;
				INativeScreen*          GetScreen(vint index) override;
				INativeScreen*          GetScreen(INativeWindow* window) override;
			};

		}

	}

}

#endif //GGAC_GGACSCREENSERVICE_H
