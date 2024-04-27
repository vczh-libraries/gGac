//
// Created by roodkcab on 6/28/21.
//

#include "GuiFocusRectangleElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				void GuiFocusRectangleElementRenderer::InitializeInternal()
				{
				}

				void GuiFocusRectangleElementRenderer::FinalizeInternal()
				{
				}

				void GuiFocusRectangleElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{
				}

				void GuiFocusRectangleElementRenderer::OnElementStateChanged()
				{
				}

				void GuiFocusRectangleElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					cr->set_source_rgba(0.8, 0.8, 0.8, 1.0);
					auto dashes = std::valarray<double>({1.0, 1.0});
					cr->set_dash(dashes, 0.0);
					cr->rectangle(bounds.x1, bounds.y1, bounds.Width(), bounds.Height());
					cr->stroke();
				}

			}

		}

	}

}