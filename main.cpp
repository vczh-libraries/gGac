#include "Renderers/GGacRenderer.h"
#include <Skins/DarkSkin/DarkSkin.h>

using namespace vl;
using namespace vl::presentation;
using namespace vl::presentation::elements;
using namespace vl::presentation::compositions;
using namespace vl::presentation::controls;
using namespace vl::presentation::theme;
using namespace vl::presentation::templates;

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
	auto window = new GuiWindow(theme::ThemeName::Window);
	window->SetText(L"Hello, world!");
	//window->SetTitleBar(false);
	window->SetClientSize(Size(480, 320));
	window->GetBoundsComposition()->SetPreferredMinSize(Size(480, 320));
	window->MoveToScreenCenter();

	FontProperties font;
	font.fontFamily = L"Segoe UI";
	font.size = 32;
	font.antialias = true;

	auto button1 = new GuiButton(theme::ThemeName::Button);
	button1->SetFont(font);
	button1->SetText(L"test1");
	window->AddChild(button1);

	auto button2 = new GuiButton(theme::ThemeName::Button);
	button2->SetFont(font);
	button2->SetText(L"test2");
	window->AddChild(button2);

	auto label = new GuiLabel(theme::ThemeName::Label);
	label->SetText(L"Welcome to GacUI Library!");
	label->SetFont(font);
	window->AddChild(label);

	GetApplication()->Run(window);
}

int main(int argc, char **argv)
{
    return vl::presentation::elements::gtk::SetupGGacRenderer();
}