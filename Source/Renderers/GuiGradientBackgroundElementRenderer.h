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

				class GuiGradientBackgroundElementRenderer : public GuiElementRendererBase<GuiGradientBackgroundElement, GuiGradientBackgroundElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<GuiGradientBackgroundElement, GuiGradientBackgroundElementRenderer, IGGacRenderTarget>;
				public:
					GuiGradientBackgroundElementRenderer();
					void Render(Rect bounds) override;
					void OnElementStateChanged() override;
					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget);
					typedef collections::Pair<Color, Color> ColorPair;
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
