#include <Skins/DarkSkin/DarkSkin.h>
#include "Renderers/GGacRenderer.h"
#include "UI/Source/Demo.h"
#include <iostream>

using namespace vl;
using namespace vl::presentation;
using namespace vl::presentation::elements;
using namespace vl::presentation::compositions;
using namespace vl::presentation::controls;
using namespace vl::presentation::theme;
using namespace vl::presentation::templates;
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


class ViewModel : public Object, public virtual demo::IViewModel
{
public:
	void OpenUrl(const WString& url)override
	{
		//ShellExecute(NULL, L"OPEN", url.Buffer(), NULL, NULL, SW_MAXIMIZE);
	}
};

void GuiMain()
{
	FileStream fileStream(L"/tmp/RichTextEmbedding.bin", FileStream::ReadOnly);
	GetResourceManager()->LoadResourceOrPending(fileStream);
	demo::MainWindow window(new ViewModel);
	//window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}

int main(int argc, char **argv)
{
    return vl::presentation::elements::gtk::SetupGGacRenderer();
}