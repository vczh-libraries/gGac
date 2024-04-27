//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GUISOLIDBORDERELEMENTRENDERER_H
#define GGAC_GUISOLIDBORDERELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiSolidBorderElementRenderer : public GuiElementRendererBase<GuiSolidBorderElement, GuiSolidBorderElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<GuiSolidBorderElement, GuiSolidBorderElementRenderer, IGGacRenderTarget>;

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

#endif //GGAC_GUISOLIDBORDERELEMENTRENDERER_H
