//
// Created by css on 6/28/21.
//

#ifndef GGAC_GUI3DSPLITTERELEMENTRENDERER_H
#define GGAC_GUI3DSPLITTERELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class Gui3DSplitterElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				DEFINE_ELEMENT_RENDERER(Gui3DSplitterElement, Gui3DSplitterElementRenderer)
				};

			}

		}

	}

};


#endif //GGAC_GUI3DSPLITTERELEMENTRENDERER_H
