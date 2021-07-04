//
// Created by css on 6/27/21.
//

#include "GuiSoldBackgroundElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiSolidBackgroundElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					Color c = element->GetColor();
					cr->set_source_rgba(c.r, c.g, c.b, c.a);
					cr->fill();

					switch(element->GetShape().shapeType)
					{
						case ElementShapeType::RoundRect:
						case ElementShapeType::Rectangle:
							cr->rectangle(bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
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