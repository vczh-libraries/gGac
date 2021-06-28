//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACRENDERER_H
#define GGAC_GGACRENDERER_H

#include "GacUI.h"
#include <gtk/gtk.h>

#define DEFINE_ELEMENT_RENDERER(TELEMENT, TRENDERER)\
	    DEFINE_GUI_GRAPHICS_RENDERER(TELEMENT, TRENDERER, IGGacRenderTarget)\
				public:\
				TRENDERER();\
				void Render(Rect bounds) override;\
				void OnElementStateChanged() override;\
				void InitializeInternal();\
				void FinalizeInternal();\
				void RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget); \


#define IMPLEMENT_ELEMENT_RENDERER(TRENDERER)\
    TRENDERER::TRENDERER()\
    {\
    }\
    void TRENDERER::InitializeInternal()\
    {\
    }\
    void TRENDERER::FinalizeInternal()\
    {\
    }\
    void TRENDERER::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)\
    {\
    }\
    void TRENDERER::OnElementStateChanged()\
    {\
    }\
    void TRENDERER::Render(Rect bounds)\

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class IGGacRenderTarget : public Object, public IGuiGraphicsRenderTarget
				{
				public:
					virtual cairo_t* GetGGacContext() const = 0;
				};

				inline cairo_t* GetCurrentGGacContextFromRenderTarget();
				extern IGGacRenderTarget* GetCurrentRenderTarget();

			}

		}

	}

}

#endif //GGAC_GGACRENDERER_H
