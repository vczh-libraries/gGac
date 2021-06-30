//
// Created by css on 6/28/21.
//

#include "GuiInnerShadowElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiInnerShadowElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
				}

			}

		}

	}

}