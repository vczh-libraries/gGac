//
// Created by css on 6/27/21.
//

#include "GGacHelper.h"
#include <gdk/gdkkeysyms.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			VKEY GdkEventKeyCodeToGacKeyCode(unsigned short keycode)
			{
				static VKEY table[128];
				if (table[0] != VKEY::_UNKNOWN)
				{
					for (vint i = 0; i < 128; i++)
					{
						table[i] = VKEY(i);
					}
					for (vint i = 48; i < 58; i++)
					{
						int s = i - 48;
						table[i] = (VKEY)((int)VKEY::_0 + s);
					}
					for (vint i = 65; i <= 90; i++)
					{
						int s = i - 65;
						table[i] = (VKEY)((int)VKEY::_A + s);
						table[i + 32] = (VKEY)((int)VKEY::_A + s);
					}
				}
				if (keycode <= 128)
				{
					return table[keycode];
				}
				else if (keycode > 128)
				{
					switch (keycode)
					{
					case GDK_KEY_Return:
						return VKEY::_RETURN;
					case GDK_KEY_Tab:
						return VKEY::_TAB;
					case GDK_KEY_Caps_Lock:
						return VKEY::_CAPITAL;
					case GDK_KEY_Shift_L:
						return VKEY::_SHIFT;
					case GDK_KEY_Shift_R:
						return VKEY::_RSHIFT;
					case GDK_KEY_Control_L:
						return VKEY::_CONTROL;
					case GDK_KEY_Control_R:
						return VKEY::_RCONTROL;
					case GDK_KEY_Escape:
						return VKEY::_ESCAPE;
					case GDK_KEY_Delete:
						return VKEY::_DELETE;
					case GDK_KEY_BackSpace:
						return VKEY::_BACK;
					case GDK_KEY_Left:
						return VKEY::_LEFT;
					case GDK_KEY_Right:
						return VKEY::_RIGHT;
					case GDK_KEY_Up:
						return VKEY::_UP;
					case GDK_KEY_Down:
						return VKEY::_DOWN;
					}
					return VKEY::_UNKNOWN;
				}
			}

		}

	}

}