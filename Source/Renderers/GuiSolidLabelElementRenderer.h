//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GUISOLIDLABELELEMENTRENDERER_H
#define GGAC_GUISOLIDLABELELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiSolidLabelElementRenderer : public GuiElementRendererBase<GuiSolidLabelElement, GuiSolidLabelElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<GuiSolidLabelElement, GuiSolidLabelElementRenderer, IGGacRenderTarget>;
				protected:
					Glib::RefPtr<Pango::Layout> layout;
					Color 						oldColor;
					FontProperties				oldFont;
					WString						oldText;
					vint						oldMaxWidth;

					void CreateFont();
					void UpdateMinSize();
					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget);

				public:
					GuiSolidLabelElementRenderer();
					~GuiSolidLabelElementRenderer();

					void Render(Rect bounds) override;
					void OnElementStateChanged() override;
				};

			}

		}

	}

}

#endif //GGAC_GUISOLIDLABELELEMENTRENDERER_H
