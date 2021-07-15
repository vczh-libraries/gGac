//
// Created by css on 6/28/21.
//

#include "GuiPolygonElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				GuiPolygonElementRenderer::GuiPolygonElementRenderer()
				{
				}

				GuiPolygonElementRenderer::~GuiPolygonElementRenderer()
				{
				}

				void GuiPolygonElementRenderer::InitializeInternal()
				{
					CreateGeometry();
				}

				void GuiPolygonElementRenderer::FinalizeInternal()
				{

				}

				void GuiPolygonElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{
					CreateGeometry();
				}

				void GuiPolygonElementRenderer::CreateGeometry()
				{
					oldPoints.Resize(element->GetPointCount());
					if (oldPoints.Count() > 0)
					{
						memcpy(&oldPoints[0], &element->GetPoint(0), sizeof(Point)*element->GetPointCount());
					}
				}

				void GuiPolygonElementRenderer::DestroyGeometry()
				{
				}

				void GuiPolygonElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					vint x = (bounds.Width() - minSize.x) / 2 + bounds.x1;
					vint y = (bounds.Height() - minSize.y) / 2 + bounds.y1;
					for (vint i = 0; i < oldPoints.Count(); i++)
					{
						Point p = oldPoints[i];
						if (i == 0)
							cr->move_to(x + p.x + 0.5, y + p.y + 0.5);
						else
						{
							cr->line_to(x + p.x + 0.5, y + p.y + 0.5);
						}
					}
					cr->close_path();
					Color bgC = element->GetBackgroundColor();
					cr->set_source_rgba(bgC.r / 255.f, bgC.g / 255.f, bgC.b / 255.f, bgC.a / 255.f);
					cr->fill_preserve();
					Color bdC = element->GetBorderColor();
					cr->set_source_rgba(bdC.r / 255.f, bdC.g / 255.f, bdC.b / 255.f, bdC.a / 255.f);
					cr->stroke();
				}

				void GuiPolygonElementRenderer::OnElementStateChanged()
				{
					minSize = element->GetSize();

					bool polygonModified = false;
					if (oldPoints.Count() != element->GetPointCount())
					{
						polygonModified = true;
					}
					else
					{
						for (vint i = 0; i < oldPoints.Count(); i++)
						{
							if (oldPoints[i] != element->GetPoint(i))
							{
								polygonModified = true;
								break;
							}
						}
					}

					if (polygonModified)
					{
						DestroyGeometry();
						CreateGeometry();
					}
				}

			}

		}

	}

}