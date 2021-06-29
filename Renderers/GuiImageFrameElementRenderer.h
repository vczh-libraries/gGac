//
// Created by css on 6/28/21.
//

#ifndef GGAC_GUIIMAGEFRAMEELEMENTRENDERER_H
#define GGAC_GUIIMAGEFRAMEELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiImageFrameElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(GuiImageFrameElement, GuiImageFrameElementRenderer, Color)
				};

			}

		}

	}

}

#endif //GGAC_GUIIMAGEFRAMEELEMENTRENDERER_H
