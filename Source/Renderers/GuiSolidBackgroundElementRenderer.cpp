//
// Created by css on 6/27/21.
//

#include "GuiSolidBackgroundElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

                IMPLEMENT_ELEMENT_RENDERER(GuiSolidBackgroundElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					Color c = element->GetColor();
					cr->set_source_rgba(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f);

					switch(element->GetShape().shapeType)
					{
						case ElementShapeType::RoundRect:
						case ElementShapeType::Rectangle:
							cr->rectangle(bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
                            cr->fill();
							break;

						case ElementShapeType::Ellipse:
							cr->arc(bounds.x1 + bounds.Width() / 2, bounds.y1 + bounds.Width() / 2, bounds.Width() / 2, -3.1415926, 3.1415926);
							cr->fill();
							break;
					}

				}

			}

		}

	}

}