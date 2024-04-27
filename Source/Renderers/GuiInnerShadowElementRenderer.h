//
// Created by roodkcab on 6/28/21.
//

#ifndef GGAC_GUIINNERSHADOWELEMENTRENDERER_H
#define GGAC_GUIINNERSHADOWELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiInnerShadowElementRenderer : public GuiElementRendererBase<GuiInnerShadowElement, GuiInnerShadowElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<GuiInnerShadowElement, GuiInnerShadowElementRenderer, IGGacRenderTarget>;

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


#endif //GGAC_GUIINNERSHADOWELEMENTRENDERER_H
