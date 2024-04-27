//
// Created by roodkcab on 7/7/21.
//

#ifndef GGAC_GUIGGACELEMENTRENDERER_H
#define GGAC_GUIGGACELEMENTRENDERER_H

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GuiGGacElementRenderer : public Object, public IGuiGraphicsRenderer
				{
				public:
					class Factory : public Object, public IGuiGraphicsRendererFactory
					{
					public:
						IGuiGraphicsRenderer *Create()
						{
							GuiGGacElementRenderer *renderer = new GuiGGacElementRenderer;
							renderer->factory = this;
							renderer->element = nullptr;
							renderer->renderTarget = nullptr;
							return renderer;
						}
					};

				protected:
					IGuiGraphicsRendererFactory *factory;
					GuiGGacElement *element;
					IGGacRenderTarget *renderTarget;
					Size minSize;

				public:
					static void Register()
					{
						auto manager = GetGuiGraphicsResourceManager();
						CHECK_ERROR(manager != nullptr, L"SetGuiGraphicsResourceManager must be called before registering element renderers.");
						manager->RegisterRendererFactory(GuiGGacElement::GetElementType(), Ptr(new typename GuiGGacElementRenderer::Factory));
					}

					IGuiGraphicsRendererFactory *GetFactory() override
					{
						return factory;
					}

					void Initialize(IGuiGraphicsElement *_element) override
					{
						element = dynamic_cast<GuiGGacElement *>(_element);
						static_cast<GuiGGacElementRenderer *>(this)->InitializeInternal();
					}

					void Finalize() override
					{
						static_cast<GuiGGacElementRenderer *>(this)->FinalizeInternal();
					}

					void SetRenderTarget(IGuiGraphicsRenderTarget *_renderTarget) override
					{
						IGGacRenderTarget *oldRenderTarget = renderTarget;
						renderTarget = static_cast<IGGacRenderTarget *>(_renderTarget);
						static_cast<GuiGGacElementRenderer *>(this)->RenderTargetChangedInternal(oldRenderTarget, renderTarget);
					}

					Size GetMinSize() override
					{
						return minSize;
					}

					GuiGGacElementRenderer();
					void Render(Rect bounds) override;
					void OnElementStateChanged() override;
					void InitializeInternal();
					void FinalizeInternal();
					void RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget);
				};

			}

		}

	}

}

#endif //GGAC_GUIGGACELEMENTRENDERER_H
