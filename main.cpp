#include "GGacController.h"
#include "GGacControllerListener.h"
#include "Renderers/GuiSolidBorderElementRenderer.h"

using namespace vl::presentation;
using namespace vl::presentation::gtk;
using namespace vl::presentation::elements::gtk;

void GGacMain()
{
	// actually this has to init before ResourceManager
	// as we need to create underlying views first
	GGacControllerListener *gListener = new GGacControllerListener();
	GetCurrentController()->CallbackService()->InstallListener(gListener);

	/*CoreGraphicsResourceManager resourceManager;
	SetGuiGraphicsResourceManager(&resourceManager);
	SetCoreGraphicsResourceManager(&resourceManager);
	GetCurrentController()->CallbackService()->InstallListener(&resourceManager);*/

	GuiSolidBorderElementRenderer::Register();
	Gui3DBorderElementRenderer::Register();
	Gui3DSplitterElementRenderer::Register();
	GuiSolidBackgroundElementRenderer::Register();
	GuiGradientBackgroundElementRenderer::Register();
	GuiSolidLabelElementRenderer::Register();
	GuiImageFrameElementRenderer::Register();
	GuiPolygonElementRenderer::Register();
	GuiColorizedTextElementRenderer::Register();
	GuiCoreGraphicsElementRenderer::Register();
	GuiInnerShadowElementRenderer::Register();
	GuiFocusRectangleElementRenderer::Register();

	elements::GuiDocumentElement::GuiDocumentElementRenderer::Register();

	{
		//call native controller run
		GuiApplicationMain();
	}

	GetCurrentController()->CallbackService()->UninstallListener(gListener);
	delete gListener;
}

int SetupGTKRenderer()
{
    INativeController* controller = ::gtk::CreateGGacController();
    SetCurrentController(controller);
    {
        GGacMain();
    }
    ::gtk::DestroyGGacController(controller);
    return 0;
}

int main(int argc, char **argv)
{
    return SetupGTKRenderer();
}