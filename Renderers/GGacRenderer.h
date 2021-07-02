//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACRENDERER_H
#define GGAC_GGACRENDERER_H

#include "GacUI.h"
#include <gtkmm.h>

#define DEFINE_ELEMENT_RENDERER(TELEMENT, TRENDERER, TBRUSHCOLOR)\
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

				class IGGacRenderTarget : public IGuiGraphicsRenderTarget
				{
				public:
					virtual Cairo::RefPtr<Cairo::Context> GetGGacContext() = 0;
				};

				extern int SetupGGacRenderer();
				extern void SetCurrentRenderTarget(IGGacRenderTarget* renderTarget);
				extern IGGacRenderTarget* GetCurrentRenderTarget();
				inline Cairo::RefPtr<Cairo::Context> GetCurrentGGacContextFromRenderTarget() {
					return (Cairo::RefPtr<Cairo::Context>)(GetCurrentRenderTarget()->GetGGacContext());
				}

			}

		}

	}

}

#endif //GGAC_GGACRENDERER_H
