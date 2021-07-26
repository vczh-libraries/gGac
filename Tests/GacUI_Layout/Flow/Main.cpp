#define GAC_HEADER_USE_NAMESPACE
#include "UI/Source/Demo.h"

using namespace vl::collections;
using namespace vl::stream;

void GuiMain()
{
	{
		FileStream fileStream(L"/tmp/Flow.bin", FileStream::ReadOnly);
		GetResourceManager()->LoadResourceOrPending(fileStream);
	}
	demo::MainWindow window;
	window.MoveToScreenCenter();
	GetApplication()->Run(&window);
}