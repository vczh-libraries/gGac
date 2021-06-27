//
// Created by css on 6/27/21.
//

#include "GGacScreenService.h"

#include "../GGacHelper.h"
#include "../GGacWindow.h"

namespace vl {
	namespace presentation {
		namespace gtk {

			GGacScreen::GGacScreen(GdkMonitor* _screen):
					screen(_screen)
			{
			}

			NativeRect GGacScreen::GetBounds()
			{
				GdkRectangle r = {0};
				gdk_monitor_get_workarea(screen, &r);
				return NativeRect(r.x, r.y, r.x + r.width, r.y + r.height);
			}

			NativeRect GGacScreen::GetClientBounds()
			{
				return GetBounds();
			}

			WString GGacScreen::GetName()
			{
				return L"?";
			}

			bool GGacScreen::IsPrimary()
			{
				return screen == gdk_display_get_primary_monitor(gdk_display_get_default());
			}

			double GGacScreen::GetScalingX()
			{
				return 2.0;
			}

			double GGacScreen::GetScalingY()
			{
				return 2.0;
			}

			GGacScreenService::GGacScreenService()
			{
				RefreshScreenInformation();
			}

			void GGacScreenService::RefreshScreenInformation()
			{
				screens.Clear();
				GdkDisplay *display = gdk_display_get_default();
				int n = gdk_display_get_n_monitors(display);
				for (int i = 0; i < n; i++) {
					screens.Add(new GGacScreen(gdk_display_get_monitor(display, i)));
				}
			}

			vint GGacScreenService::GetScreenCount()
			{
				return screens.Count();
			}

			INativeScreen* GGacScreenService::GetScreen(vint index)
			{
				return screens[index].Obj();
			}

			INativeScreen* GGacScreenService::GetScreen(INativeWindow* window)
			{
				GGacWindow* gWin = dynamic_cast<GGacWindow*>(window);
				return 0;
			}
		}
	}
}