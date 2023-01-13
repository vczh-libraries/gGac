#include "GGacRenderer.h"
#include "Skin/Theme.h"

using namespace vl;
using namespace vl::presentation::controls;

class DefaultSkinPlugin : public Object, public IGuiPlugin
{
public:

	GUI_PLUGIN_NAME(Custom_DefaultSkinPlugin)
	{
		GUI_PLUGIN_DEPEND(GacGen_DarkSkinResourceLoader);
	}

	void Load()override
	{
		RegisterTheme(Ptr(new gtkskin::Theme()));
	}

	void Unload()override
	{
	}
};
GUI_REGISTER_PLUGIN(DefaultSkinPlugin)

int main(int argc, char **argv)
{
    return vl::presentation::elements::gtk::SetupGGacRenderer();
}