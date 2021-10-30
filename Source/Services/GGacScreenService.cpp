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
				monitor->get_workarea(r);
				return NativeRect(r.get_x(), r.get_y(), r.get_x() + r.get_width(), r.get_y() + r.get_height());
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
				return monitor->is_primary();
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
				int n = display->get_n_monitors();
				for (int i = 0; i < n; i++)
				{
					monitors.Add(new GGacScreen(display->get_monitor(i)));
				}
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
				auto nativeWindow = dynamic_cast<GGacWindow*>(window)->GetNativeWindow();
				if (nativeWindow && nativeWindow->get_window())
				{
					int num = nativeWindow->get_screen()->get_monitor_at_window(nativeWindow->get_window());
					if (num >= 0)
					{
						return monitors[num].Obj();
					}
				}
				return 0;
			}
		}
	}
}