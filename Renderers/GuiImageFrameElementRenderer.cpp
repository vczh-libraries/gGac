//
// Created by css on 6/28/21.
//

#include "GuiImageFrameElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiImageFrameElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
				}

			}

		}

	}

}