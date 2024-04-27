//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GUISOLIDBACKGROUNDELEMENTRENDERER_H
#define GGAC_GUISOLIDBACKGROUNDELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

 
				class GuiSolidBackgroundElementRenderer : public GuiElementRendererBase<GuiSolidBackgroundElement, GuiSolidBackgroundElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<GuiSolidBackgroundElement, GuiSolidBackgroundElementRenderer, IGGacRenderTarget>;

				protected:
					Color oldColor;

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

#endif //GGAC_GUISOLIDBACKGROUNDELEMENTRENDERER_H
