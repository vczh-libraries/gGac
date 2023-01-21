//
// Created by css on 6/27/21.
//

#ifndef GGAC_GUISOLIDBACKGROUNDELEMENTRENDERER_H
#define GGAC_GUISOLIDBACKGROUNDELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiSolidBackgroundElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(GuiSolidBackgroundElement, GuiSolidBackgroundElementRenderer, Color)

				};

			}

		}

	}

}

#endif //GGAC_GUISOLIDBACKGROUNDELEMENTRENDERER_H
