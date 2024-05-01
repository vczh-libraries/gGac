//
// Created by roodkcab on 6/28/21.
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

				class GuiColorizedTextElementRenderer : public GuiElementRendererBase<GuiColorizedTextElement, GuiColorizedTextElementRenderer, IGGacRenderTarget>, protected GuiColorizedTextElement::ICallback
				{
					friend class GuiElementRendererBase<GuiColorizedTextElement, GuiColorizedTextElementRenderer, IGGacRenderTarget>;
				protected:
					Ptr<Pango::FontDescription> gFont;
					ColorArray colors;

					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget *oldRenderTarget, IGGacRenderTarget *newRenderTarget);

				public:
					void Render(Rect bounds) override;
					void OnElementStateChanged() override;
					void FontChanged() override; 
					void ColorChanged() override;
				};

			}

		}

	}

}

#endif //GGAC_GUICOLORIZEDTEXTELEMENTRENDERER_H
