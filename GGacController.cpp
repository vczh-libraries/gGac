//
// Created by css on 6/27/21.
//

#include "GGacController.h"
#include "GGacWindow.h"
#include "Services/GGacAsyncService.h"
#include "Services/GGacCallbackService.h"
#include "Services/GGacClipboardService.h"
#include "Services/GGacDialogService.h"
#include "Services/GGacImageService.h"
#include "Services/GGacInputService.h"
#include "Services/GGacResourceService.h"
#include "Services/GGacScreenService.h"

#include "Renderers/GuiSolidBorderElementRenderer.h"
#include "Renderers/Gui3DBorderElementRenderer.h"
#include "Renderers/Gui3DSplitterElementRenderer.h"
#include "Renderers/GuiSoldBackgroundElementRenderer.h"
#include "Renderers/GuiSolidLabelElementRenderer.h"
#include "Renderers/GuiGradientBackgroundElementRenderer.h"
#include "Renderers/GuiImageFrameElementRenderer.h"
#include "Renderers/GuiPolygonElementRenderer.h"
#include "Renderers/GuiColorizedTextElementRenderer.h"
#include "Renderers/GuiInnerShadowElementRenderer.h"
#include "Renderers/GuiFocusRectangleElementRenderer.h"
#include "Renderers/GGacResourceManager.h"

#include "GGacControllerListener.h"

#include <gtkmm.h>
#include <GacUI.h>

using namespace vl::presentation;
using namespace vl::presentation::gtk;
using namespace vl::presentation::elements;
using namespace vl::presentation::elements::gtk;

namespace vl {

	namespace presentation {

		namespace gtk {

			using namespace collections;
			void GlobalTimerFunc();

			class GGacController : public Object, public virtual INativeController, public virtual INativeWindowService
			{
			protected:
				List<GGacWindow*>                      windows;
				INativeWindow*                         mainWindow;

				GGacCallbackService                    callbackService;
				GGacInputService                       inputService;
				GGacResourceService                    resourceService;
				GGacScreenService                      screenService;
				GGacAsyncService                       asyncService;
				GGacClipboardService                   clipboardService;
				GGacImageService                       imageService;
				GGacDialogService                      dialogService;

			private:
				Glib::RefPtr<Gtk::Application> app;
				void onActive() {
				}

			public:
				GGacController():
						mainWindow(0),
						inputService(&GlobalTimerFunc)
				{
					app = Gtk::Application::create("org.gtkmm.examples.base");
					app->signal_activate().connect(sigc::mem_fun(*this, &GGacController::onActive));
				}

				~GGacController()
				{
					inputService.StopTimer();
				}

				void InvokeGlobalTimer()
				{
					//asyncService.ExecuteAsyncTasks();
					callbackService.InvokeGlobalTimer();
				}

				//========================================[INativeWindowService]========================================

				INativeWindow* CreateNativeWindow()
				{
					GGacWindow* window = new GGacWindow();
					callbackService.InvokeNativeWindowCreated(window);
					windows.Add(window);
					return window;
				}

				void DestroyNativeWindow(INativeWindow* window)
				{
					GGacWindow* gWin = dynamic_cast<GGacWindow*>(window);
					if (gWin != 0 && windows.Contains(gWin))
					{
						callbackService.InvokeNativeWindowDestroyed(window);
						windows.Remove(gWin);

						if (gWin == mainWindow)
							app->quit();
						delete gWin;
					}
				}

				INativeWindow* GetMainWindow()
				{
					return mainWindow;
				}

				void Run(INativeWindow* window)
				{
					mainWindow = window;
					mainWindow->Show();
					app->run(*dynamic_cast<GGacWindow*>(window)->GetNativeWindow());
				}

				INativeWindow* GetWindow(NativePoint location)
				{
					GGacWindow* result = 0;
					return result;
				}

				//========================================[INativeController]========================================

				INativeCallbackService* CallbackService()
				{
					return &callbackService;
				}

				INativeResourceService* ResourceService()
				{
					return &resourceService;
				}

				INativeAsyncService* AsyncService()
				{
					return &asyncService;
				}

				INativeClipboardService* ClipboardService()
				{
					return &clipboardService;
				}

				INativeImageService* ImageService()
				{
					return &imageService;
				}

				INativeScreenService* ScreenService()
				{
					return &screenService;
				}

				INativeInputService* InputService()
				{
					return &inputService;
				}

				INativeDialogService* DialogService()
				{
					return &dialogService;
				}

				INativeWindowService* WindowService()
				{
					return this;
				}

				WString GetOSVersion()
				{
					return L"";
					//return NSStringToWString(vl::presentation::gtk::GetOSVersion());
				}

				WString GetExecutablePath()
				{
					return L"";
					//return GetApplicationPath();
				}
			};

			//========================================[Global Functions]========================================

			INativeController* CreateGGacController()
			{
				return new GGacController();
			}

			void DestroyGGacController(INativeController* controller)
			{
				delete controller;
			}

			void GlobalTimerFunc()
			{
				dynamic_cast<GGacController*>(GetCurrentController())->InvokeGlobalTimer();
			}

			void SetupRenderer()
			{
				elements::gtk::GuiSolidBorderElementRenderer::Register();
				elements::gtk::Gui3DBorderElementRenderer::Register();
				elements::gtk::GuiSolidBackgroundElementRenderer::Register();
				elements::gtk::GuiSolidLabelElementRenderer::Register();
				elements::gtk::Gui3DSplitterElementRenderer::Register();
				elements::gtk::GuiGradientBackgroundElementRenderer::Register();
				elements::gtk::GuiImageFrameElementRenderer::Register();
				elements::gtk::GuiPolygonElementRenderer::Register();
				elements::gtk::GuiColorizedTextElementRenderer::Register();
				//elements::gtk::GuiGGacElementRenderer::Register();
				elements::gtk::GuiInnerShadowElementRenderer::Register();
				elements::gtk::GuiFocusRectangleElementRenderer::Register();
				elements::GuiDocumentElement::GuiDocumentElementRenderer::Register();
			}

			int GGacMain()
			{
				INativeController* controller = CreateGGacController();
				SetCurrentController(controller);
				{
					auto gListener = new GGacControllerListener();
					GetCurrentController()->CallbackService()->InstallListener(gListener);
					GGacResourceManager resourceManager;
					SetGuiGraphicsResourceManager(&resourceManager);
					//SetGGacResourceManager(&resourceManager);
					GetCurrentController()->CallbackService()->InstallListener(&resourceManager);
					SetupRenderer();
					{
						GuiApplicationMain();
					}
					GetCurrentController()->CallbackService()->UninstallListener(gListener);
				}
				DestroyGGacController(controller);
				return 0;
			}

		}

	}

}