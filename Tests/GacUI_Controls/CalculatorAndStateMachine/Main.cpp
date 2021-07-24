#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"
#include <Skins/DarkSkin/DarkSkin.h>
#include "GGacRenderer.h"

using namespace vl::collections;
using namespace vl::stream;

class DefaultSkinPlugin : public Object, public IGuiPlugin
{
public:

	GUI_PLUGIN_NAME(Custom_DefaultSkinPlugin)
	{
		GUI_PLUGIN_DEPEND(GacGen_DarkSkinResourceLoader);
	}

	void Load()override
	{
		RegisterTheme(MakePtr<darkskin::Theme>());
	}

	void Unload()override
	{
	}
};
GUI_REGISTER_PLUGIN(DefaultSkinPlugin)

void GuiMain()
{
	{
		FileStream fileStream(L"/tmp/CalculatorAndStateMachine.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(new demo::Calculator);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}

int main(int argc, char **argv)
{
    return vl::presentation::elements::gtk::SetupGGacRenderer();
}