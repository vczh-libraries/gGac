//
// Created by css on 6/28/21.
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
					switch(element->GetShape().shapeType)
					{
						case ElementShapeType::Rectangle:
							cr->save();
							cr->set_source(gGradient);
							cr->rectangle(bounds.x1, bounds.y1, bounds.x2 - bounds.x1, bounds.y2 - bounds.y1);
							cr->fill();
							cr->restore();
							break;

						case ElementShapeType::Ellipse:
						{
							cr->save();
							double cx = (bounds.x1 + bounds.x2) / 2, cy = (bounds.y1 + bounds.y2) / 2;
							cr->set_source(gGradient);
							cr->arc(0, 0, bounds.Width()/2, 0, M_PI * 2);
							cr->fill();
							cr->restore();
							break;
						}
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
					gGradient = Cairo::LinearGradient::create(0, 0, 400., 0);
					gGradient->add_color_stop_rgba(0.0, oldColor.key.r / 255.0, oldColor.key.g / 255.0, oldColor.key.b / 255.0, oldColor.key.a / 255.0);
					gGradient->add_color_stop_rgba(1.0, oldColor.value.r / 255.0, oldColor.value.g / 255.0, oldColor.value.b / 255.0, oldColor.value.a / 255.0);
				}

			}

		}

	}

}