//
// Created by css on 6/28/21.
//

#ifndef GGAC_GUIINNERSHADOWELEMENTRENDERER_H
#define GGAC_GUIINNERSHADOWELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiInnerShadowElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_GUI_GRAPHICS_RENDERER(GuiInnerShadowElement, GuiInnerShadowElementRenderer, GGacRenderTarget)

				protected:
					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(GGacRenderTarget* oldRenderTarget, GGacRenderTarget* newRenderTarget);
				public:
					GuiInnerShadowElementRenderer();
					~GuiInnerShadowElementRenderer();

					void Render(Rect bounds)override;
					void OnElementStateChanged()override;
				};

			}

		}

	}

}


#endif //GGAC_GUIINNERSHADOWELEMENTRENDERER_H
