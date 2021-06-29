//
// Created by css on 6/28/21.
//

#include "GuiPolygonElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				GuiPolygonElementRenderer::GuiPolygonElementRenderer():
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
				}

				void GuiPolygonElementRenderer::DestroyGeometry()
				{
				}

				void GuiPolygonElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					cr->save();
					for (vint i=0; i < oldPoints.Count(); ++i)
					{
						Point p = oldPoints[i];
						if (i == 0)
							cr->move_to(p.x, p.y);
						else
							cr->line_to(p.x, p.y);
					}
					Color bgC = element->GetBackgroundColor();
					cr->set_source_rgba(bgC.r, bgC.g, bgC.g, bgC.a);
					cr->fill_preserve();
					Color bdC = element->GetBorderColor();
					cr->set_source_rgba(bdC.r, bdC.g, bdC.g, bdC.a);
					cr->stroke();
					cr->restore();
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