//
// Created by css on 6/27/21.
//

#include "GGacRenderer.h"

#include "GuiSolidBorderElementRenderer.h"
#include "Gui3DBorderElementRenderer.h"
#include "Gui3DSplitterElementRenderer.h"
#include "GuiSoldBackgroundElementRenderer.h"
#include "GuiSolidLabelElementRenderer.h"
#include "GuiGradientBackgroundElementRenderer.h"
#include "GuiImageFrameElementRenderer.h"
#include "GuiPolygonElementRenderer.h"
#include "GuiColorizedTextElementRenderer.h"
#include "GuiInnerShadowElementRenderer.h"
#include "GuiFocusRectangleElementRenderer.h"

#include "../GGacController.h"
#include "../GGacControllerListener.h"

using namespace vl::collections;
using namespace vl::presentation::gtk;

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				class GGacRenderTarget: public IGGacRenderTarget
				{
				protected:
					//CoreGraphicsView*       nativeView;
					//List<Rect>              clippers;
					vint                    clipperCoverWholeTargetCounter;
					INativeWindow*          window;
				public:
					void StartRendering() override {

					}

					RenderTargetFailure StopRendering() override {
						return None;
					}

					void PushClipper(Rect clipper) override {

					}

					void PopClipper() override {

					}

					Rect GetClipper() override {
						return vl::presentation::Rect();
					}

					bool IsClipperCoverWholeTarget() override {
						return false;
					}

					Cairo::RefPtr<Cairo::Context> GetGGacContext() override {
						return Cairo::RefPtr<Cairo::Context>();
					}
				};

				///

				class GGacResourceManager : public GuiGraphicsResourceManager, public INativeControllerListener {
				protected:
					SortedList<Ptr<GGacRenderTarget>> renderTargets;
				public:
					IGuiGraphicsRenderTarget *GetRenderTarget(INativeWindow *window) override
					{
						return nullptr;
					}

					void RecreateRenderTarget(INativeWindow *window) override
					{

					}

					void ResizeRenderTarget(INativeWindow *window) override
					{

					}

					IGuiGraphicsLayoutProvider *GetLayoutProvider() override
					{
						return nullptr;
					}
				};

				///

				namespace {
					IGGacRenderTarget*      g_currentRenderTarget;
				}

				void SetCurrentRenderTarget(IGGacRenderTarget* renderTarget)
				{
					g_currentRenderTarget = renderTarget;
				}

				IGGacRenderTarget* GetCurrentRenderTarget()
				{
					return g_currentRenderTarget;
				}

				int SetupGGacRenderer()
				{

					INativeController *controller = CreateGGacController();
					SetCurrentController(controller);
					{
						auto controllerListener = new GGacControllerListener();
						GetCurrentController()->CallbackService()->InstallListener(controllerListener);
						GGacResourceManager resourceManager;
						SetGuiGraphicsResourceManager(&resourceManager);
						//SetGGacResourceManager(&resourceManager);
						GetCurrentController()->CallbackService()->InstallListener(&resourceManager);
						{
							GuiSolidBorderElementRenderer::Register();
							Gui3DBorderElementRenderer::Register();
							GuiSolidBackgroundElementRenderer::Register();
							GuiSolidLabelElementRenderer::Register();
							Gui3DSplitterElementRenderer::Register();
							GuiGradientBackgroundElementRenderer::Register();
							GuiImageFrameElementRenderer::Register();
							GuiPolygonElementRenderer::Register();
							GuiColorizedTextElementRenderer::Register();
							//GuiGGacElementRenderer::Register();
							GuiInnerShadowElementRenderer::Register();
							GuiFocusRectangleElementRenderer::Register();
							GuiDocumentElement::GuiDocumentElementRenderer::Register();
						}
						{
							GuiApplicationMain();
						}
						GetCurrentController()->CallbackService()->UninstallListener(&resourceManager);
						GetCurrentController()->CallbackService()->UninstallListener(controllerListener);
					}
					DestroyGGacController(controller);
					return 0;
				}

			}

		}

	}

}