//
// Created by css on 6/28/21.
//

#ifndef GGAC_GUIFOCUSRECTANGLEELEMENTRENDERER_H
#define GGAC_GUIFOCUSRECTANGLEELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiFocusRectangleElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_GUI_GRAPHICS_RENDERER(GuiFocusRectangleElement, GuiFocusRectangleElementRenderer, GGacRenderTarget)

				protected:
					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(GGacRenderTarget* oldRenderTarget, GGacRenderTarget* newRenderTarget);

				public:
					GuiFocusRectangleElementRenderer();
					~GuiFocusRectangleElementRenderer();

					void Render(Rect bounds)override;
					void OnElementStateChanged()override;
				};

			}

		}

	}

}


#endif //GGAC_GUIFOCUSRECTANGLEELEMENTRENDERER_H
