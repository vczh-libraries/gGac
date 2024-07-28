#include "GGacRenderer.h"
#include "Skins/DarkSkin/DarkSkin.h"

using namespace vl;
using namespace vl::presentation;

class DefaultSkinPlugin : public Object, public IGuiPlugin
{
public:

	GUI_PLUGIN_NAME(Custom_DefaultSkinPlugin)
	{
		GUI_PLUGIN_DEPEND(GacGen_DarkSkinResourceLoader);
	}

	void Load(bool controllerUnrelatedPlugins, bool controllerRelatedPlugins)override
	{
		RegisterTheme(Ptr(new darkskin::Theme()));
	}

	void Unload(bool controllerUnrelatedPlugins, bool controllerRelatedPlugins)override
	{
	}
};
GUI_REGISTER_PLUGIN(DefaultSkinPlugin)

int main(int argc, char **argv)
{
    std::locale::global(std::locale(""));
    return vl::presentation::elements::gtk::SetupGtkRenderer();
}
