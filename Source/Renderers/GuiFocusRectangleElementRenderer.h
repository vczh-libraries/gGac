//
// Created by roodkcab on 6/28/21.
//

#ifndef GGAC_GUIFOCUSRECTANGLEELEMENTRENDERER_H
#define GGAC_GUIFOCUSRECTANGLEELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiFocusRectangleElementRenderer : public GuiElementRendererBase<GuiFocusRectangleElement, GuiFocusRectangleElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<GuiFocusRectangleElement, GuiFocusRectangleElementRenderer, IGGacRenderTarget>;

					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget *oldRenderTarget, IGGacRenderTarget *newRenderTarget);

				public:
					void Render(Rect bounds) override;
					void OnElementStateChanged() override;
				};

			}

		}

	}

}


#endif //GGAC_GUIFOCUSRECTANGLEELEMENTRENDERER_H
