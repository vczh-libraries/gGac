//
// Created by css on 6/27/21.
//

#include "GGacInputService.h"
#include "../GGacHelper.h"
#include <gtkmm.h>


namespace vl {

	namespace presentation {

		namespace gtk {

			GGacInputService::GGacInputService(TimerFunc _timer)
					:timer(_timer)
			{
				InitKeyMapping();
			}

			void GGacInputService::InitKeyMapping()
			{
				memset(asciiLowerMap, 0, sizeof(wchar_t) * 256);
				memset(asciiUpperMap, 0, sizeof(wchar_t) * 256);

				asciiLowerMap[(int)VKEY::KEY_0] = L'0';
				asciiLowerMap[(int)VKEY::KEY_1] = L'1';
				asciiLowerMap[(int)VKEY::KEY_2] = L'2';
				asciiLowerMap[(int)VKEY::KEY_3] = L'3';
				asciiLowerMap[(int)VKEY::KEY_4] = L'4';
				asciiLowerMap[(int)VKEY::KEY_5] = L'5';
				asciiLowerMap[(int)VKEY::KEY_6] = L'6';
				asciiLowerMap[(int)VKEY::KEY_7] = L'7';
				asciiLowerMap[(int)VKEY::KEY_8] = L'8';
				asciiLowerMap[(int)VKEY::KEY_9] = L'9';
				asciiLowerMap[(int)VKEY::KEY_OEM_1] = L';';
				asciiLowerMap[(int)VKEY::KEY_OEM_6] = L'[';
				asciiLowerMap[(int)VKEY::KEY_OEM_4] = L']';
				asciiLowerMap[(int)VKEY::KEY_OEM_7] = L'\'';
				asciiLowerMap[(int)VKEY::KEY_OEM_COMMA] = L',';
				asciiLowerMap[(int)VKEY::KEY_OEM_PERIOD] = L'.';
				asciiLowerMap[(int)VKEY::KEY_OEM_2] = L'/';
				asciiLowerMap[(int)VKEY::KEY_OEM_5] = L'\\';
				asciiLowerMap[(int)VKEY::KEY_OEM_MINUS] = L'-';
				asciiLowerMap[(int)VKEY::KEY_OEM_PLUS] = L'=';
				asciiLowerMap[(int)VKEY::KEY_OEM_3] = L'`';
				asciiLowerMap[(int)VKEY::KEY_SPACE] = L' ';
				asciiLowerMap[(int)VKEY::KEY_RETURN] = (int)VKEY::KEY_RETURN;
				asciiLowerMap[(int)VKEY::KEY_ESCAPE] = (int)VKEY::KEY_ESCAPE;
				asciiLowerMap[(int)VKEY::KEY_BACK] = (int)VKEY::KEY_BACK;
				for(int i=(int)VKEY::KEY_A; i<=(int)VKEY::KEY_Z; ++i)
					asciiLowerMap[i] = L'a' + (i-(int)VKEY::KEY_A);
				for(int i=(int)VKEY::KEY_NUMPAD0; i<(int)VKEY::KEY_NUMPAD9; ++i)
					asciiLowerMap[i] = L'0' + (i-(int)VKEY::KEY_NUMPAD0);

				asciiUpperMap[(int)VKEY::KEY_0] = L')';
				asciiUpperMap[(int)VKEY::KEY_1] = L'!';
				asciiUpperMap[(int)VKEY::KEY_2] = L'@';
				asciiUpperMap[(int)VKEY::KEY_3] = L'#';
				asciiUpperMap[(int)VKEY::KEY_4] = L'$';
				asciiUpperMap[(int)VKEY::KEY_5] = L'%';
				asciiUpperMap[(int)VKEY::KEY_6] = L'^';
				asciiUpperMap[(int)VKEY::KEY_7] = L'&';
				asciiUpperMap[(int)VKEY::KEY_8] = L'*';
				asciiUpperMap[(int)VKEY::KEY_9] = L'(';
				asciiUpperMap[(int)VKEY::KEY_OEM_1] = L':';
				asciiUpperMap[(int)VKEY::KEY_OEM_6] = L'{';
				asciiUpperMap[(int)VKEY::KEY_OEM_4] = L'}';
				asciiUpperMap[(int)VKEY::KEY_OEM_7] = L'\"';
				asciiUpperMap[(int)VKEY::KEY_OEM_COMMA] = L'<';
				asciiUpperMap[(int)VKEY::KEY_OEM_PERIOD] = L'>';
				asciiUpperMap[(int)VKEY::KEY_OEM_2] = L'?';
				asciiUpperMap[(int)VKEY::KEY_OEM_5] = L'|';
				asciiUpperMap[(int)VKEY::KEY_OEM_MINUS] = L'_';
				asciiUpperMap[(int)VKEY::KEY_OEM_PLUS] = L'+';
				asciiUpperMap[(int)VKEY::KEY_OEM_3] = L'~';
				asciiUpperMap[(int)VKEY::KEY_SPACE] = L' ';
				asciiUpperMap[(int)VKEY::KEY_RETURN] = (int)VKEY::KEY_RETURN;
				asciiUpperMap[(int)VKEY::KEY_ESCAPE] = (int)VKEY::KEY_ESCAPE;
				asciiUpperMap[(int)VKEY::KEY_BACK] = (int)VKEY::KEY_BACK;
				for(int i=(int)VKEY::KEY_A; i<=(int)VKEY::KEY_Z; ++i)
					asciiUpperMap[i] = L'A' + (i-(int)VKEY::KEY_A);
				for(int i=(int)VKEY::KEY_NUMPAD0; i<(int)VKEY::KEY_NUMPAD9; ++i)
					asciiLowerMap[i] = L'0' + (i-(int)VKEY::KEY_NUMPAD0);
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
				return vl::WString();
			}

			vl::presentation::VKEY GGacInputService::GetKey(const vl::WString &name)
			{
				return VKEY::KEY_RCONTROL;
			}

			bool GGacInputService::ConvertToPrintable(NativeWindowCharInfo &info, GdkEvent *event)
			{
				info.ctrl = event->key.state & GDK_CONTROL_MASK;
				info.shift = event->key.state & GDK_SHIFT_MASK;
				info.alt = event->key.state & GDK_MOD1_MASK;
				info.capslock = event->key.state & GDK_LOCK_MASK;

				if (info.ctrl || info.alt)
					return false;

				int code = (int)GdkEventKeyCodeToGacKeyCode(event->key.keyval);
				if(code >= 256)
					return false;

				info.code = asciiLowerMap[code];
				if (info.capslock || info.shift)
				{
					info.code = asciiUpperMap[code];
				}

				return info.code != 0;
			}
		}

	}

}