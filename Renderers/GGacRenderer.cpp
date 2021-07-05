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
					GGacControllerListener* g_gGacControllerListener;
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
						auto listener = g_gGacControllerListener->GetGGacWindowListener(window);
						view = listener->GetGGacView();
					}

					void StartRendering() override
					{
						auto listener = g_gGacControllerListener->GetGGacWindowListener(window);
						listener->StartRendering();
						Cairo::RefPtr<Cairo::Context> cr = GetGGacContext();
						if (!cr)
							return;

						SetCurrentRenderTarget(this);
						cr->set_source_rgba(0, 0, 0, 0);
						cr->fill();
						cr->save();
						view->queue_draw();
					}

					RenderTargetFailure StopRendering() override
					{
						auto listener = g_gGacControllerListener->GetGGacWindowListener(window);
						listener->StopRendering();
						bool moved = listener->RetrieveAndResetMovedWhileRendering();

						Cairo::RefPtr<Cairo::Context> cr = GetGGacContext();
						if (!cr) {
							return RenderTargetFailure::LostDevice;
						}

						cr->restore();
						SetCurrentRenderTarget(0);
						return !moved ? RenderTargetFailure::None : RenderTargetFailure::ResizeWhileRendering;
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
						NativeWindowDestroying(window);
						GetGGacObjectProvider()->RecreateRenderTarget(window);
						NativeWindowCreated(window);
					}

					void ResizeRenderTarget(INativeWindow *window) override
					{
						auto listener = g_gGacControllerListener->GetGGacWindowListener(window);
						if (listener)
						{
							return listener->ResizeRenderTarget();
						}
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

				///

				int SetupGGacRenderer()
				{
					INativeController *controller = CreateGGacController();
					SetCurrentController(controller);
					{
						g_gGacControllerListener = new GGacControllerListener();
						GetCurrentController()->CallbackService()->InstallListener(g_gGacControllerListener);
						GGacResourceManager resourceManager;
						SetGuiGraphicsResourceManager(&resourceManager);
						//SetGGacResourceManager(&resourceManager);
						GetCurrentController()->CallbackService()->InstallListener(&resourceManager);
						{
							GuiSolidLabelElementRenderer::Register();
							GuiSolidBorderElementRenderer::Register();
							GuiSolidBackgroundElementRenderer::Register();
							Gui3DBorderElementRenderer::Register();
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
						GetCurrentController()->CallbackService()->UninstallListener(g_gGacControllerListener);
					}
					DestroyGGacController(controller);
					return 0;
				}

			}

		}

	}

}