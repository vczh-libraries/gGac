//
// Created by roodkcab on 6/28/21.
//

#ifndef GGAC_GUI3DSPLITTERELEMENTRENDERER_H
#define GGAC_GUI3DSPLITTERELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class Gui3DSplitterElementRenderer : public GuiElementRendererBase<Gui3DSplitterElement, Gui3DSplitterElementRenderer, IGGacRenderTarget>
				{
					friend class GuiElementRendererBase<Gui3DSplitterElement, Gui3DSplitterElementRenderer, IGGacRenderTarget>;
                protected:
                    Color					oldColor1;
                    Color					oldColor2;

					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget *oldRenderTarget, IGGacRenderTarget *newRenderTarget);

				public:
					void Render(Rect bounds) override;
					void OnElementStateChanged() override;
                };

			}

		}

	}

};


#endif //GGAC_GUI3DSPLITTERELEMENTRENDERER_H
