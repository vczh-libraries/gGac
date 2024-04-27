//
// Created by roodkcab on 6/28/21.
//

#ifndef GGAC_GUIIMAGEFRAMEELEMENTRENDERER_H
#define GGAC_GUIIMAGEFRAMEELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiImageFrameElementRenderer : public GuiElementRendererBase<GuiImageFrameElement, GuiImageFrameElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<GuiImageFrameElement, GuiImageFrameElementRenderer, IGGacRenderTarget>;
				public:
					GuiImageFrameElementRenderer();
					void Render(Rect bounds) override;
					void OnElementStateChanged() override;
					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget);
				};

			}

		}

	}

}

#endif //GGAC_GUIIMAGEFRAMEELEMENTRENDERER_H
