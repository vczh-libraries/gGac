//
// Created by css on 6/28/21.
//

#ifndef GGAC_GUICOLORIZEDTEXTELEMENTRENDERER_H
#define GGAC_GUICOLORIZEDTEXTELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiColorizedTextElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(GuiColorizedTextElement, GuiColorizedTextElementRenderer)
				};

			}

		}

	}

}

#endif //GGAC_GUICOLORIZEDTEXTELEMENTRENDERER_H
