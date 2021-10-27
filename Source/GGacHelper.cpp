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
				if (table[0] != VKEY::KEY_UNKNOWN)
				{
					for (vint i = 0; i < 128; i++)
					{
						table[i] = VKEY(i);
					}
					for (vint i = 48; i < 58; i++)
					{
						int s = i - 48;
						table[i] = (VKEY)((int)VKEY::KEY_0 + s);
					}
					for (vint i = 65; i <= 90; i++)
					{
						int s = i - 65;
						table[i] = (VKEY)((int)VKEY::KEY_A + s);
						table[i + 32] = (VKEY)((int)VKEY::KEY_A + s);
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
						return VKEY::KEY_RETURN;
					case GDK_KEY_Tab:
						return VKEY::KEY_TAB;
					case GDK_KEY_Caps_Lock:
						return VKEY::KEY_CAPITAL;
					case GDK_KEY_Shift_L:
						return VKEY::KEY_SHIFT;
					case GDK_KEY_Shift_R:
						return VKEY::KEY_RSHIFT;
					case GDK_KEY_Control_L:
						return VKEY::KEY_CONTROL;
					case GDK_KEY_Control_R:
						return VKEY::KEY_RCONTROL;
					case GDK_KEY_Escape:
						return VKEY::KEY_ESCAPE;
					case GDK_KEY_Delete:
						return VKEY::KEY_DELETE;
					case GDK_KEY_BackSpace:
						return VKEY::KEY_BACK;
					case GDK_KEY_Left:
						return VKEY::KEY_LEFT;
					case GDK_KEY_Right:
						return VKEY::KEY_RIGHT;
					case GDK_KEY_Up:
						return VKEY::KEY_UP;
					case GDK_KEY_Down:
						return VKEY::KEY_DOWN;
					}
				}
				return VKEY::KEY_UNKNOWN;
			}

		}

	}

}