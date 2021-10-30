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
					table[0] = VKEY::KEY_UNKNOWN;
					for (vint i = 48; i < 58; i++)
					{
						//0-9
						int s = i - 48;
						table[i] = (VKEY)((int)VKEY::KEY_0 + s);
					}
					for (vint i = 65; i <= 90; i++)
					{
						//a-zA-Z
						int s = i - 65;
						table[i] = (VKEY)((int)VKEY::KEY_A + s);
						table[i + 32] = (VKEY)((int)VKEY::KEY_A + s);
					}
					//!@#$%^&*()-=[]\;',./_+{}|:"<>?
					table[GDK_KEY_exclam] = VKEY::KEY_1;
					table[GDK_KEY_at] = VKEY::KEY_2;
					table[GDK_KEY_numbersign] = VKEY::KEY_3;
					table[GDK_KEY_dollar] = VKEY::KEY_4;
					table[GDK_KEY_percent] = VKEY::KEY_5;
					table[GDK_KEY_asciicircum] = VKEY::KEY_6;
					table[GDK_KEY_ampersand] = VKEY::KEY_7;
					table[GDK_KEY_asterisk] = VKEY::KEY_8;
					table[GDK_KEY_parenleft] = VKEY::KEY_9;
					table[GDK_KEY_parenright] = VKEY::KEY_0;
					table[GDK_KEY_minus] = VKEY::KEY_OEM_MINUS;
					table[GDK_KEY_underscore] = VKEY::KEY_OEM_MINUS;
					table[GDK_KEY_equal] = VKEY::KEY_OEM_PLUS;
					table[GDK_KEY_plus] = VKEY::KEY_OEM_PLUS;
					table[GDK_KEY_bracketleft] = VKEY::KEY_OEM_6;
					table[GDK_KEY_braceleft] = VKEY::KEY_OEM_6;
					table[GDK_KEY_bracketright] = VKEY::KEY_OEM_4;
					table[GDK_KEY_braceright] = VKEY::KEY_OEM_4;
					table[GDK_KEY_colon] = VKEY::KEY_OEM_1;
					table[GDK_KEY_semicolon] = VKEY::KEY_OEM_1;
					table[GDK_KEY_quotedbl] = VKEY::KEY_OEM_7;
					table[GDK_KEY_quoteleft] = VKEY::KEY_OEM_7;
					table[GDK_KEY_quoteright] = VKEY::KEY_OEM_7;
					table[GDK_KEY_period] = VKEY::KEY_OEM_PERIOD;
					table[GDK_KEY_greater] = VKEY::KEY_OEM_PERIOD;
					table[GDK_KEY_comma] = VKEY::KEY_OEM_COMMA;
					table[GDK_KEY_less] = VKEY::KEY_OEM_COMMA;
					table[GDK_KEY_question] = VKEY::KEY_OEM_2;
					table[GDK_KEY_slash] = VKEY::KEY_OEM_2;
					table[GDK_KEY_backslash] = VKEY::KEY_OEM_5;
					table[GDK_KEY_bar] = VKEY::KEY_OEM_5;
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