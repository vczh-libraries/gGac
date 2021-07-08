//
// Created by css on 7/7/21.
//

#ifndef GGAC_GUIGGACELEMENTRENDERER_H
#define GGAC_GUIGGACELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiGGacElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(GuiGGacElement, GuiGGacElementRenderer, Color)
				};

			}

		}

	}

}

#endif //GGAC_GUIGGACELEMENTRENDERER_H
