//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GUI3DBORDERELEMENTRENDERER_H
#define GGAC_GUI3DBORDERELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class Gui3DBorderElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(Gui3DBorderElement, Gui3DBorderElementRenderer, Color)
				};

			}

		}

	}

}


#endif //GGAC_GUI3DBORDERELEMENTRENDERER_H
