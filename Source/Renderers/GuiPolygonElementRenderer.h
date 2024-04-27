//
// Created by roodkcab on 6/28/21.
//

#ifndef GGAC_GUIPOLYGONELEMENTRENDERER_H
#define GGAC_GUIPOLYGONELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiPolygonElementRenderer : public GuiElementRendererBase<GuiPolygonElement, GuiPolygonElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<GuiPolygonElement, GuiPolygonElementRenderer, IGGacRenderTarget>;
				public:
					GuiPolygonElementRenderer();
					~GuiPolygonElementRenderer();

					void Render(Rect bounds) override;
					void OnElementStateChanged() override;

				protected:
					collections::Array<Point>   oldPoints;

					void CreateGeometry();
					void DestroyGeometry();

					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget);
				};

			}

		}

	}

}

#endif //GGAC_GUIPOLYGONELEMENTRENDERER_H
