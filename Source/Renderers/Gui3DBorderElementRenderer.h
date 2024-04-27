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

				class Gui3DBorderElementRenderer : public GuiElementRendererBase<Gui3DBorderElement, Gui3DBorderElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<Gui3DBorderElement, Gui3DBorderElementRenderer, IGGacRenderTarget>;
				protected:
					Color color1;
					Color color2;

					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget);
				public:
					void Render(Rect bounds) override;
					void OnElementStateChanged() override;
				};

			}

		}

	}

}


#endif //GGAC_GUI3DBORDERELEMENTRENDERER_H
