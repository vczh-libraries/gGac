//
// Created by css on 6/28/21.
//

#include "Gui3DSplitterElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(Gui3DSplitterElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					Color c1 = element->GetColor1();
					cr->set_source_rgba(c1.r, c1.g, c1.b, c1.a);
					cr->stroke();
					Color c2 = element->GetColor2();
					cr->set_source_rgba(c1.r, c1.g, c1.b, c1.a);
					cr->stroke();
				}

			}

		}

	}

}