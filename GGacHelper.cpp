//
// Created by css on 6/27/21.
//

#include "GGacHelper.h"

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
						table[i] = VKEY::_UNKNOWN;
					}
					for (vint i = 48; i < 57; i++)
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
				return table[keycode];
			}

		}

	}

}