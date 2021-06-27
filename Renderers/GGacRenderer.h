//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACRENDERER_H
#define GGAC_GGACRENDERER_H

#include "GacUI.h"

#define DEFINE_ELEMENT_RENDERER(TELEMENT, TRENDERER, TBRUSHPROPERTY)\
				DEFINE_GUI_GRAPHICS_RENDERER(TELEMENT, TRENDERER, IGGacRenderTarget)\
				public:\
				TRENDERER();\
				void Render(Rect bounds) override;\
				void OnElementStateChanged() override;\
				void InitializeInternal();\
				void FinalizeInternal();\
				void RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget); \

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class IGGacRenderTarget : public Object, public IGuiGraphicsRenderTarget
				{

				};

			}

		}

	}

}

#endif //GGAC_GGACRENDERER_H
