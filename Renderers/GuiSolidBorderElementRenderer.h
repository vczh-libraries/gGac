//
// Created by css on 6/27/21.
//

#ifndef GGAC_GUISOLIDBORDERELEMENTRENDERER_H
#define GGAC_GUISOLIDBORDERELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiSolidBorderElementRenderer : public Object, public IGuiGraphicsRenderer
				{
					DEFINE_ELEMENT_RENDERER(GuiSolidBorderElement, GuiSolidBorderElementRenderer, Color)
				};

			}

		}

	}

}

#endif //GGAC_GUISOLIDBORDERELEMENTRENDERER_H
