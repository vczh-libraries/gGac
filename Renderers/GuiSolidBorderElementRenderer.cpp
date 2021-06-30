//
// Created by css on 6/27/21.
//

#include "GuiSolidBorderElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiSolidBorderElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					Color c = element->GetColor();
					cr->set_source_rgba(c.r, c.g, c.b, c.a);

					switch(element->GetShape().shapeType)
					{
						case ElementShapeType::RoundRect:
						case ElementShapeType::Rectangle:
							cr->rectangle(bounds.x1, bounds.y1, bounds.x2 - bounds.x1, bounds.y2 - bounds.y1);
							cr->stroke();
							break;

						case ElementShapeType::Ellipse:
							/*cr->arc();
							cr->stroke();*/
							break;
					}
				}

			}

		}

	}

}
