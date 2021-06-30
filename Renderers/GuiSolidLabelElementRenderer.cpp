//
// Created by css on 6/27/21.
//

#include "GuiSolidLabelElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiSolidLabelElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
				}

			}

		}

	}

}