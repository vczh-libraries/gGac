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
					cairo_t* context = GetCurrentGGacContextFromRenderTarget();
					Color c = element->GetColor();
					cairo_set_source_rgba(context, c.r, c.g, c.b, c.a);

					switch(element->GetShape().shapeType)
					{
						case ElementShapeType::RoundRect:
						case ElementShapeType::Rectangle:
							cairo_rectangle(context, bounds.x1, bounds.y1, bounds.x2 - bounds.x1, bounds.y2 - bounds.y1);
							cairo_stroke(context);
							break;

						case ElementShapeType::Ellipse:
							/*cairo_translate(context, x + width / 2., y + height / 2.);
							cairo_scale(context, width / 2., height / 2.);
							cairo_arc(context, 0., 0., 1., 0., 2 * M_PI);
							cairo_stroke(context);*/
							break;
					}
				}

			}

		}

	}

}
