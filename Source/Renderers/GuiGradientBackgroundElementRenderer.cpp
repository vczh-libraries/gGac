//
// Created by roodkcab on 6/28/21.
//

#include "GuiGradientBackgroundElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				GuiGradientBackgroundElementRenderer::GuiGradientBackgroundElementRenderer()
				{
				}

				GuiGradientBackgroundElementRenderer::~GuiGradientBackgroundElementRenderer()
				{
				}

				void GuiGradientBackgroundElementRenderer::InitializeInternal()
				{

				}

				void GuiGradientBackgroundElementRenderer::FinalizeInternal()
				{

				}

				void GuiGradientBackgroundElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{
					CreateGGacGradient();
				}

				void GuiGradientBackgroundElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();

                    switch (element->GetDirection())
                    {
                        case GuiGradientBackgroundElement::Horizontal:
                            gGradient = Cairo::LinearGradient::create(bounds.x1, bounds.y1, bounds.x2, bounds.y1);
                            break;
                        case GuiGradientBackgroundElement::Vertical:
                            gGradient = Cairo::LinearGradient::create(bounds.x1, bounds.y1, bounds.x1, bounds.y2);
                            break;
                        case GuiGradientBackgroundElement::Slash:
                            gGradient = Cairo::LinearGradient::create(bounds.x2, bounds.y2, bounds.x1, bounds.y1);
                            break;
                        case GuiGradientBackgroundElement::Backslash:
                            gGradient = Cairo::LinearGradient::create(bounds.x1, bounds.y1, bounds.x2, bounds.y2);
                            break;
                    }
                    gGradient->add_color_stop_rgba(0.0, oldColor.key.r / 255.0, oldColor.key.g / 255.0, oldColor.key.b / 255.0, oldColor.key.a / 255.0);
                    gGradient->add_color_stop_rgba(1.0, oldColor.value.r / 255.0, oldColor.value.g / 255.0, oldColor.value.b / 255.0, oldColor.value.a / 255.0);

                    auto shape = element->GetShape();
					switch(shape.shapeType)
					{
                        case ElementShapeType::RoundRect:
                        {
                            cr->set_source(gGradient);
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
                            cr->fill();
                        }
                        break;

						case ElementShapeType::Rectangle:
                        {
							cr->set_source(gGradient);
							cr->rectangle(bounds.x1, bounds.y1, bounds.x2 - bounds.x1, bounds.y2 - bounds.y1);
							cr->fill();
                        }
                        break;

						case ElementShapeType::Ellipse:
						{
							double cx = (bounds.x1 + bounds.x2) / 2, cy = (bounds.y1 + bounds.y2) / 2;
							cr->set_source(gGradient);
							cr->arc(cx, cy, bounds.Width()/2, 0, M_PI * 2);
							cr->fill();
						}
                        break;
					}
				}

				void GuiGradientBackgroundElementRenderer::OnElementStateChanged()
				{
					if (renderTarget)
					{
						collections::Pair<Color, Color> color = collections::Pair<Color, Color>(element->GetColor1(), element->GetColor2());
						if (color != oldColor)
						{
							CreateGGacGradient();
						}
					}
				}

				void GuiGradientBackgroundElementRenderer::CreateGGacGradient()
				{
					oldColor = collections::Pair<Color, Color>(element->GetColor1(), element->GetColor2());
				}

			}

		}

	}

}