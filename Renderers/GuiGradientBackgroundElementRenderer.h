//
// Created by css on 6/28/21.
//

#ifndef GGAC_GUIGRADIENTBACKGROUNDELEMENTRENDERER_H
#define GGAC_GUIGRADIENTBACKGROUNDELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiGradientBackgroundElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(GuiGradientBackgroundElement, GuiGradientBackgroundElementRenderer)
				};

			}

		}

	}

}

#endif //GGAC_GUIGRADIENTBACKGROUNDELEMENTRENDERER_H
