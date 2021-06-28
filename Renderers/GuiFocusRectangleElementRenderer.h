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
				DEFINE_ELEMENT_RENDERER(GuiFocusRectangleElement, GuiFocusRectangleElementRenderer)
				};

			}

		}

	}

}


#endif //GGAC_GUIFOCUSRECTANGLEELEMENTRENDERER_H
