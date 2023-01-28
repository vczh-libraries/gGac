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

				class GuiInnerShadowElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(GuiInnerShadowElement, GuiInnerShadowElementRenderer, GGacRenderTarget)
				};

			}

		}

	}

}


#endif //GGAC_GUIINNERSHADOWELEMENTRENDERER_H
