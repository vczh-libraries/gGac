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

				class GuiGGacElement;

				struct GuiGGacElementEventArgs : compositions::GuiEventArgs
				{
				public:
					GuiGGacElement*             	element;
					Rect                          	bounds;
					Cairo::RefPtr<Cairo::Context> 	context;

					GuiGGacElementEventArgs(GuiGGacElement* _element, Rect _bounds, Cairo::RefPtr<Cairo::Context> _context):
							element(_element),
							bounds(_bounds),
							context(_context)
					{
					}
				};

				class GuiGGacElement : public GuiElementBase<GuiGGacElement>
				{
					DEFINE_GUI_GRAPHICS_ELEMENT(GuiGGacElement, L"GGacElement")

				protected:
					GuiGGacElement();

				public:
					~GuiGGacElement();
					compositions::GuiGraphicsEvent<GuiGGacElementEventArgs>         BeforeRenderTargetChanged;
					compositions::GuiGraphicsEvent<GuiGGacElementEventArgs>         AfterRenderTargetChanged;
					compositions::GuiGraphicsEvent<GuiGGacElementEventArgs>         Rendering;
				};

				class IGGacRenderTarget : public Object, public IGuiGraphicsRenderTarget
				{
				public:
					virtual Cairo::RefPtr<Cairo::Context> GetGGacContext() = 0;
				};

				class IGGacObjectProvider : public Interface
				{
				public:
					virtual void						RecreateRenderTarget(INativeWindow* window) = 0;
					virtual IGGacRenderTarget*			GetGGacRenderTarget(INativeWindow* window) = 0;
					virtual IGGacRenderTarget*          GetBindedRenderTarget(INativeWindow* window) = 0;
					virtual void						SetBindedRenderTarget(INativeWindow* window, IGGacRenderTarget* renderTarget) = 0;
				};

				class IGGacResourceManager: public Interface
				{
				public:
					virtual Ptr<elements::text::CharMeasurer>   CreateCharMeasurer(const FontProperties& fontProperties) = 0;
					virtual Ptr<Pango::FontDescription>         CreateGGacFont(const FontProperties& fontProperties) = 0;
				};

				extern void								SetCurrentRenderTarget(IGGacRenderTarget* renderTarget);
				extern IGGacRenderTarget*				GetCurrentRenderTarget();
				extern IGGacObjectProvider*				GetGGacObjectProvider();
				extern void								SetGGacObjectProvider(IGGacObjectProvider* provider);
				extern IGGacResourceManager*			GetGGacResourceManager();
				extern void								SetGGacResourceManager(IGGacResourceManager* manager);

				inline Cairo::RefPtr<Cairo::Context>	GetCurrentGGacContextFromRenderTarget() {
					return (Cairo::RefPtr<Cairo::Context>)(GetCurrentRenderTarget()->GetGGacContext());
				}
				extern int								SetupGtkRenderer();

			}

		}

	}

}

#endif //GGAC_GGACRENDERER_H
