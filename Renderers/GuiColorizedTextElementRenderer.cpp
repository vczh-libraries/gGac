//
// Created by css on 6/28/21.
//

#include "GuiColorizedTextElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiColorizedTextElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
				}

			}

		}

	}

}