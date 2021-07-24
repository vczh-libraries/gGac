#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/HelloWorld.h"
#include <Skins/DarkSkin/DarkSkin.h>
#include "GGacRenderer.h"

using namespace vl::collections;
using namespace vl::stream;
using namespace vl::regex;

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



class ViewModel : public Object, public virtual vm::IViewModel
{
private:
	WString userName;
	WString password;
	Regex regexLcLetters;
	Regex regexUcLetters;
	Regex regexNumbers;

public:
	ViewModel()
		:regexLcLetters(L"[a-z]")
		, regexUcLetters(L"[A-Z]")
		, regexNumbers(L"[0-9]")
	{
	}

	WString GetUserName()override
	{
		return userName;
	}

	void SetUserName(const WString& value)override
	{
		userName = value;
		UserNameErrorChanged();
	}

	WString GetUserNameError()override
	{
		if (userName == L"")
		{
			return L"User name should not be empty.";
		}
		return L"";
	}

	WString GetPassword()override
	{
		return password;
	}

	void SetPassword(const WString& value)override
	{
		password = value;
		PasswordErrorChanged();
	}

	WString GetPasswordError()override
	{
		if (password == L"")
		{
			return L"Password should not be empty.";
		}
		bool containsLowerCases = regexLcLetters.Match(password);
		bool containsUpperCases = regexUcLetters.Match(password);
		bool containsNumbers = regexNumbers.Match(password);
		if (!containsLowerCases || !containsUpperCases || !containsNumbers)
		{
			return L"Password should contains at least one lower case letter, one upper case letter and one digit.";
		}
		return L"";
	}

	bool SignUp()override
	{
		return true;
	}
};

void GuiMain()
{
	{
		FileStream fileStream(L"/tmp/MVVM.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	auto viewModel = MakePtr<ViewModel>();
	auto window = new helloworld::MainWindow(viewModel);
	window->MoveToScreenCenter();
	GetApplication()->Run(window);
	delete window;
}

int main(int argc, char **argv)
{
    return vl::presentation::elements::gtk::SetupGGacRenderer();
}