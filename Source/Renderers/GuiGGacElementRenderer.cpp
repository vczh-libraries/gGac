//
// Created by roodkcab on 7/7/21.
//

#include "GuiGGacElementRenderer.h"
namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				GuiGGacElementRenderer::GuiGGacElementRenderer()
				{
				}

				void GuiGGacElementRenderer::InitializeInternal()
				{

				}

				void GuiGGacElementRenderer::FinalizeInternal()
				{

				}

				void GuiGGacElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{
					IGGacRenderTarget* newTarget = (IGGacRenderTarget*)newRenderTarget;
					IGGacRenderTarget* oldTarget = (IGGacRenderTarget*)oldRenderTarget;

					if (oldRenderTarget)
					{
						GuiGGacElementEventArgs arguments(element, Rect(), oldTarget->GetGGacContext());
						element->BeforeRenderTargetChanged.Execute(arguments);
					}

					if (newRenderTarget)
					{
						GuiGGacElementEventArgs arguments(element, Rect(), newTarget->GetGGacContext());
						element->AfterRenderTargetChanged.Execute(arguments);
					}
				}

				void GuiGGacElementRenderer::Render(Rect bounds)
				{
					if (renderTarget)
					{
						renderTarget->PushClipper(bounds, element);
						if (!renderTarget->IsClipperCoverWholeTarget())
						{
							GuiGGacElementEventArgs arguments(element, bounds, GetCurrentGGacContextFromRenderTarget());
							element->Rendering.Execute(arguments);
						}
						renderTarget->PopClipper(element);
					}
				}

				void GuiGGacElementRenderer::OnElementStateChanged()
				{

				}

			}

		}

	}

}
