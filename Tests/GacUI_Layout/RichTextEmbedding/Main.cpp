#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl;
using namespace vl::stream;
using namespace demo;

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
	{
		FileStream fileStream(L"../UIRes/RichTextEmbedding.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window(new ViewModel);
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}
