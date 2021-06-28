//
// Created by css on 6/28/21.
//

#ifndef GGAC_GUIPOLYGONELEMENTRENDERER_H
#define GGAC_GUIPOLYGONELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiPolygonElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(GuiPolygonElement, GuiPolygonElementRenderer)
				};

			}

		}

	}

}

#endif //GGAC_GUIPOLYGONELEMENTRENDERER_H
