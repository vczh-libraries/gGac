//
// Created by css on 6/28/21.
//

#include "GuiFocusRectangleElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiFocusRectangleElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					cr->set_source_rgba(1.0, 1.0, 1.0, 1.0);
					cr->rectangle(bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
					cr->stroke();
				}

			}

		}

	}

}