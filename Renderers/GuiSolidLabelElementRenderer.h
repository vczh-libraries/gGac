//
// Created by css on 6/27/21.
//

#ifndef GGAC_GUISOLIDLABELELEMENTRENDERER_H
#define GGAC_GUISOLIDLABELELEMENTRENDERER_H

#include <gtkmm.h>
#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiSolidLabelElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				protected:
					Glib::RefPtr<Pango::Layout> layout;

					void CreateFont();
					void UpdateMinSize();

				public:
				DEFINE_ELEMENT_RENDERER(GuiSolidLabelElement, GuiSolidLabelElementRenderer, GGacRenderTarget)

				};

			}

		}

	}

}

#endif //GGAC_GUISOLIDLABELELEMENTRENDERER_H
