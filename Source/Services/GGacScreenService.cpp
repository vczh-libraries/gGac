//
// Created by css on 6/27/21.
//

#include "GGacScreenService.h"

#include "../GGacHelper.h"
#include "../GGacWindow.h"

namespace vl {
	namespace presentation {
		namespace gtk {

			GGacScreen::GGacScreen(Glib::RefPtr<Gdk::Monitor> _monitor):
					monitor(_monitor)
			{
			}

			NativeRect GGacScreen::GetBounds()
			{
				Gdk::Rectangle r;
				return NativeRect(0, 0, monitor->get_width_mm(), monitor->get_height_mm());
			}

			NativeRect GGacScreen::GetClientBounds()
			{
				return GetBounds();
			}

			WString GGacScreen::GetName()
			{
				return L"";
			}

			bool GGacScreen::IsPrimary()
			{
                return true;
				//return monitor->is_primary();
			}

			double GGacScreen::GetScalingX()
			{
				return monitor->get_scale_factor() * 1.0;
			}

			double GGacScreen::GetScalingY()
			{
				return monitor->get_scale_factor() * 1.0;
			}

			void GGacScreenService::RefreshScreenInformation()
			{
				monitors.Clear();
				auto display = Gdk::Display::get_default();
				auto monitors = display->get_monitors();
                //monitors.Add(Ptr(new GGacScreen(display->get_monitor(i))));
			}

			vint GGacScreenService::GetScreenCount()
			{
				return monitors.Count();
			}

			INativeScreen* GGacScreenService::GetScreen(vint index)
			{
				return monitors[index].Obj();
			}

			INativeScreen* GGacScreenService::GetScreen(INativeWindow* window)
			{
                return 0;
				/*auto nativeWindow = dynamic_cast<GGacWindow*>(window)->GetNativeWindow();
				if (nativeWindow && nativeWindow->get_window())
				{
					int num = nativeWindow->get_screen()->get_monitor_at_window(nativeWindow->get_window());
					if (num >= 0)
					{
						return monitors[num].Obj();
					}
				}
				return 0;*/
			}
		}
	}
}