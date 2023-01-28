//
// Created by roodkcab on 6/28/21.
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
					typedef collections::Pair<Color, Color> ColorPair;
					DEFINE_ELEMENT_RENDERER(GuiGradientBackgroundElement, GuiGradientBackgroundElementRenderer, ColorPair)

					virtual ~GuiGradientBackgroundElementRenderer();

				protected:
					collections::Pair<Color, Color>     oldColor;
					Cairo::RefPtr<Cairo::LinearGradient> gGradient;

					void CreateGGacGradient();
				};

			}

		}

	}

}

#endif //GGAC_GUIGRADIENTBACKGROUNDELEMENTRENDERER_H
