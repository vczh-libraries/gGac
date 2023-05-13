//
// Created by roodkcab on 6/27/21.
//

#include "GGacInputService.h"
#include "../GGacHelper.h"
#include "../Services/GGacCallbackService.h"
#include "../Lib/Keybinder.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			void handler (const char *keystring, int id) {
				dynamic_cast<GGacCallbackService*>(GetCurrentController()->CallbackService())->InvokeGlobalShortcutKeyActivated(id);
			}

			GGacInputService::GGacInputService(TimerFunc _timer)
				:usedHotKeys(0),
				 keyNames(146),
				 timer(_timer)
			{
				InitKeyMapping();
				keybinder_init();
			}

			WString GGacInputService::GetKeyNameInternal(VKEY code)
			{
				if ((vint)code < 8) return L"?";
				guint32 scanCode = gdk_keyval_to_unicode(static_cast<guint>(code));
				switch ((vint)code) {
					case GDK_KEY_Insert:
					case GDK_KEY_Delete:
					case GDK_KEY_Home:
					case GDK_KEY_End:
					case GDK_KEY_Page_Up:
					case GDK_KEY_Page_Down:
					case GDK_KEY_Left:
					case GDK_KEY_Right:
					case GDK_KEY_Up:
					case GDK_KEY_Down:
						scanCode |= 1 << 24;
						break;
					case GDK_KEY_Clear:
					case GDK_KEY_Shift_L:
					case GDK_KEY_Shift_R:
					case GDK_KEY_Control_L:
					case GDK_KEY_Control_R:
					case GDK_KEY_Alt_L:
					case GDK_KEY_Alt_R:
						return L"?";
				}
				gchar* name = gdk_keyval_name(scanCode);
				Glib::ustring result = name ? name : "?";
				//g_free(name);
				return atow(result.c_str());
			}

			void GGacInputService::InitKeyMapping()
			{
				for (vint i = 0; i < keyNames.Count(); i++)
				{
					keyNames[i] = GetKeyNameInternal((VKEY)i);
					if (keyNames[i] != L"?")
					{
						//std::wcout << keyNames[i].Buffer() << " " << i << std::endl;
						keys.Set(keyNames[i], (VKEY)i);
					}
				}
			}

			bool GGacInputService::StartGDKTimer()
			{
				if (IsTimerEnabled())
					timer();
				return true;
			}

			void GGacInputService::StartTimer()
			{
				Glib::signal_timeout().connect(sigc::mem_fun(*this, &GGacInputService::StartGDKTimer), 16);
				isTimerEnabled = true;
			}

			void GGacInputService::StopTimer()
			{
				isTimerEnabled = false;
			}

			bool GGacInputService::IsTimerEnabled()
			{
				return isTimerEnabled;
			}

			bool GGacInputService::IsKeyPressing(vl::presentation::VKEY code)
			{
				return false;
			}

			bool GGacInputService::IsKeyToggled(vl::presentation::VKEY code)
			{
				return false;
			}

			vl::WString GGacInputService::GetKeyName(vl::presentation::VKEY code)
			{
				if (0 <= (vint)code && (vint)code < keyNames.Count())
				{
					return keyNames[(vint)code];
				}
				else
				{
					return L"?";
				}
			}

			vl::presentation::VKEY GGacInputService::GetKey(const vl::WString &name)
			{
				vint index = keys.Keys().IndexOf(name);
				return index == -1 ? VKEY::KEY_UNKNOWN : keys.Values()[index];
			}

			vint GGacInputService::RegisterGlobalShortcutKey(bool ctrl, bool shift, bool alt, VKEY code)
			{
				++usedHotKeys;
				WString accelstr = L"";
				if (ctrl) accelstr += L"<Control>";
				if (shift) accelstr += L"<Shift>";
				if (alt) accelstr += L"<Alt>";
				accelstr += wlower(this->GetKeyName(code));
				keybinder_bind(wtoa(accelstr).Buffer(), handler, (int)usedHotKeys);
				return usedHotKeys;
			}

			bool GGacInputService::UnregisterGlobalShortcutKey(vint id)
			{
				if (id <= usedHotKeys) {
					keybinder_unbind((int)id, handler);
					return true;
				}
				return false;
			}
		}

	}

}