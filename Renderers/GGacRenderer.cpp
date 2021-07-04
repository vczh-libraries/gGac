//
// Created by css on 6/27/21.
//

#include "GGacRenderer.h"
#include "GGacLayoutProvider.h"
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
#include "../GGacWindow.h"
#include "../GGacView.h"

using namespace vl::collections;
using namespace vl::presentation::gtk;

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				namespace
				{
					IGGacRenderTarget* g_currentRenderTarget;
					IGGacObjectProvider* g_gGacObjectProvider;
				}

				class GGacRenderTarget: public IGGacRenderTarget
				{
				protected:
					Ptr<GGacView>           view;
					//List<Rect>              clippers;
					//vint                    clipperCoverWholeTargetCounter;
					INativeWindow*          window;
				public:
					GGacRenderTarget(INativeWindow* _window)
					:window(_window)
					{
						view = MakePtr<GGacView>(_window);
						dynamic_cast<GGacWindow*>(window)->GetNativeWindow()->add(*view.Obj());
						view->show();
					}

					void StartRendering() override
					{
						SetCurrentRenderTarget(this);
					}

					RenderTargetFailure StopRendering() override
					{
						return None;
					}

					void PushClipper(Rect clipper) override
					{

					}

					void PopClipper() override
					{

					}

					Rect GetClipper() override
					{
						return vl::presentation::Rect();
					}

					bool IsClipperCoverWholeTarget() override
					{
						return false;
					}

					Cairo::RefPtr<Cairo::Context> GetGGacContext() override
					{
						return view->GetGGacContext();
					}
				};

				///

				class GGacObjectProvider: public IGGacObjectProvider
				{

					void RecreateRenderTarget(INativeWindow* window)
					{
						// todo
					}

					IGGacRenderTarget* GetGGacRenderTarget(INativeWindow* window)
					{
						GGacWindow* gWin = dynamic_cast<GGacWindow*>(window);
						if (gWin)
							return dynamic_cast<IGGacRenderTarget*>(gWin->GetGraphicsHandler());
						return 0;
					}

					IGGacRenderTarget* GetBindedRenderTarget(INativeWindow* window)
					{
						GGacWindow* gWin = dynamic_cast<GGacWindow*>(window);
						if (gWin)
							return dynamic_cast<IGGacRenderTarget*>(gWin->GetGraphicsHandler());
						return 0;
					}

					void SetBindedRenderTarget(INativeWindow* window, IGGacRenderTarget* renderTarget)
					{
						GGacWindow* gWin = dynamic_cast<GGacWindow*>(window);
						if (gWin)
							gWin->SetGraphicsHandler(renderTarget);
					}

				};

				///

				class GGacResourceManager : public GuiGraphicsResourceManager, public INativeControllerListener
				{
				protected:
					SortedList<Ptr<GGacRenderTarget>> renderTargets;
					Ptr<GGacLayoutProvider>           layoutProvider;
				public:

					GGacResourceManager()
					:layoutProvider(new GGacLayoutProvider())
					{
						g_gGacObjectProvider = new GGacObjectProvider;
					}

					IGuiGraphicsRenderTarget *GetRenderTarget(INativeWindow *window) override
					{
						return GetGGacObjectProvider()->GetBindedRenderTarget(window);
					}

					void RecreateRenderTarget(INativeWindow *window) override
					{

					}

					void ResizeRenderTarget(INativeWindow *window) override
					{

					}

					IGuiGraphicsLayoutProvider *GetLayoutProvider() override
					{
						return layoutProvider.Obj();
					}

					void NativeWindowCreated(INativeWindow *window) override
					{
						GGacRenderTarget* renderTarget = new GGacRenderTarget(window);
						renderTargets.Add(renderTarget);
						GetGGacObjectProvider()->SetBindedRenderTarget(window, renderTarget);
					}

					void NativeWindowDestroying(INativeWindow *window) override
					{
						GGacRenderTarget* renderTarget=dynamic_cast<GGacRenderTarget*>(GetGGacObjectProvider()->GetBindedRenderTarget(window));
						GetGGacObjectProvider()->SetBindedRenderTarget(window, 0);
						renderTargets.Remove(renderTarget);
					}
				};

				///

				void SetCurrentRenderTarget(IGGacRenderTarget* renderTarget)
				{
					g_currentRenderTarget = renderTarget;
				}

				IGGacRenderTarget* GetCurrentRenderTarget()
				{
					return g_currentRenderTarget;
				}

				IGGacObjectProvider* GetGGacObjectProvider()
				{
					return g_gGacObjectProvider;
				}

				void SetGGacObjectProvider(IGGacObjectProvider* provider)
				{
					g_gGacObjectProvider = provider;
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