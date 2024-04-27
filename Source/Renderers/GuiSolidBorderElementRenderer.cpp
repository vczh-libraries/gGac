//
// Created by roodkcab on 6/27/21.
//

#include "GuiSolidBorderElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				void GuiSolidBorderElementRenderer::InitializeInternal()
				{
				}

				void GuiSolidBorderElementRenderer::FinalizeInternal()
				{
				}

				void GuiSolidBorderElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{
				}

				void GuiSolidBorderElementRenderer::OnElementStateChanged()
				{
				}

				void GuiSolidBorderElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					Color c = element->GetColor();
					cr->set_source_rgba(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f);
                    cr->set_line_width(1);

                    auto shape = element->GetShape();
					switch(shape.shapeType)
					{
						case ElementShapeType::RoundRect:
                        {
                            double degrees = M_PI / 180.0;
                            double l = MAX(shape.radiusX, shape.radiusY);
                            double s = MIN(shape.radiusX, shape.radiusY);
                            cr->scale(1, s/l);
                            cr->begin_new_sub_path();
                            cr->arc(bounds.x1 + shape.radiusX + 0.5, bounds.y1 + shape.radiusY, l, 180 * degrees, 270 * degrees);
                            cr->arc(bounds.x2 - shape.radiusX - 0.5, bounds.y1 + shape.radiusY, l, -90 * degrees, 0 * degrees);
                            cr->arc(bounds.x2 - shape.radiusX - 0.5, bounds.y2 - shape.radiusY, l, 0 * degrees, 90 * degrees);
                            cr->arc(bounds.x1 + shape.radiusX + 0.5, bounds.y2 - shape.radiusY, l, 90 * degrees, 180 * degrees);
                            cr->close_path();
                            cr->stroke();
                        }
                        break;

						case ElementShapeType::Rectangle:
							cr->rectangle(bounds.x1 + 0.5, bounds.y1 + 0.5, bounds.Width() - 1, bounds.Height() - 1);
							cr->stroke();
							break;

						case ElementShapeType::Ellipse:
							cr->arc(bounds.x1 + bounds.Width() / 2, bounds.y1 + bounds.Width() / 2, bounds.Width() / 2, -M_PI, M_PI);
							cr->stroke();
							break;
					}
				}

			}

		}

	}

}
