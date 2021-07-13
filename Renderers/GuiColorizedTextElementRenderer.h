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


				struct ColorItemResource
				{
					Color   text;
					Color   background;
				};

				struct ColorEntryResource
				{
					ColorItemResource			normal;
					ColorItemResource			selectedFocused;
					ColorItemResource			selectedUnfocused;
					//TODO: make this faster
					bool						operator==(const ColorEntryResource& value){return false;}
					bool						operator!=(const ColorEntryResource& value){return true;}
				};

				typedef collections::Array<ColorEntryResource> ColorArray;

				class GuiColorizedTextElementRenderer : public Object, public IGuiGraphicsRenderer, public GuiColorizedTextElement::ICallback
				{
				protected:
					Ptr<Pango::FontDescription> gFont;
					ColorArray colors;

				DEFINE_ELEMENT_RENDERER(GuiColorizedTextElement, GuiColorizedTextElementRenderer, Color)
				void ColorChanged() override;
				void FontChanged() override;
				};

			}

		}

	}

}

#endif //GGAC_GUICOLORIZEDTEXTELEMENTRENDERER_H
