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
#include "GuiGGacElementRenderer.h"

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
					IGGacResourceManager* g_gGacResourceManager;
					GGacControllerListener* g_gGacControllerListener;
				}

				///

				GuiGGacElement::GuiGGacElement()
				{
				}

				GuiGGacElement::~GuiGGacElement()
				{
				}

				///

				class GGacRenderTarget: public IGGacRenderTarget
				{
				protected:
					Ptr<GGacView>           view;
					List<Rect>              clippers;
					vint                    clipperCoverWholeTargetCounter;
					INativeWindow*          window;
				public:
					GGacRenderTarget(INativeWindow* _window)
					:window(_window),
					clipperCoverWholeTargetCounter(0)
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
						Gtk::Allocation allocation = view->get_allocation();
						cr->rectangle(allocation.get_x(), allocation.get_y(), allocation.get_width(), allocation.get_height());
						cr->fill();
						cr->save();
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
						if (clipperCoverWholeTargetCounter > 0)
						{
							clipperCoverWholeTargetCounter++;
						}
						else
						{
							Rect previousClipper = GetClipper();
							Rect currentClipper;
							currentClipper.x1 = MAX(previousClipper.x1, clipper.x1);
							currentClipper.y1 = MAX(previousClipper.y1, clipper.y1);
							currentClipper.x2 = MIN(previousClipper.x2, clipper.x2);
							currentClipper.y2 = MIN(previousClipper.y2, clipper.y2);

							if (currentClipper.x1 < currentClipper.x2 && currentClipper.y1 < currentClipper.y2)
							{
								clippers.Add(currentClipper);
								Cairo::RefPtr<Cairo::Context> cr = GetGGacContext();
								cr->save();
								cr->rectangle(currentClipper.Left(), currentClipper.Top(), currentClipper.Width(), currentClipper.Height());
								cr->clip();
							}
							else
							{
								clipperCoverWholeTargetCounter++;
							}
						}
					}

					void PopClipper() override
					{
						if (clippers.Count() > 0)
						{
							if (clipperCoverWholeTargetCounter > 0)
							{
								clipperCoverWholeTargetCounter--;
							}
							else
							{
								clippers.RemoveAt(clippers.Count() - 1);
								Cairo::RefPtr<Cairo::Context> cr = GetGGacContext();
								cr->restore();
							}
						}
					}

					Rect GetClipper() override
					{
						if (clippers.Count() == 0)
						{
							return Rect(Point(0, 0), window->Convert(window->GetClientSize()));
						}
						else
						{
							return clippers[clippers.Count() - 1];
						}
					}

					bool IsClipperCoverWholeTarget() override
					{
						return clipperCoverWholeTargetCounter > 0;
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

				class GGacResourceManager : public GuiGraphicsResourceManager, public INativeControllerListener, public IGGacResourceManager
				{
				protected:
					SortedList<Ptr<GGacRenderTarget>> renderTargets;
					Ptr<GGacLayoutProvider>           layoutProvider;
				public:

					GGacResourceManager()
					{
						g_gGacObjectProvider = new GGacObjectProvider;
						layoutProvider = new GGacLayoutProvider;
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

					Ptr <elements::text::CharMeasurer> CreateCharMeasurer(const FontProperties &fontProperties) override
					{
						//TODO: CharMeasurer
						return Ptr<elements::text::CharMeasurer>();
					}

					void DestroyCharMeasurer(const FontProperties &fontProperties) override
					{
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

				IGGacResourceManager* GetGGacResourceManager()
				{
					return g_gGacResourceManager;
				}

				void SetGGacResourceManager(IGGacResourceManager* manager)
				{
					g_gGacResourceManager = manager;
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
						SetGGacResourceManager(&resourceManager);
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
							GuiGGacElementRenderer::Register();
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
