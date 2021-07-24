#### Linux port for [GacLib](http://www.gaclib.net) using gtkmm/cairomm/pangomm

##### License

**Read the [LICENSE](https://github.com/vczh-libraries/iGac/blob/master/LICENSE.md) first.**

##### Current Progress:
* Finalizing

##### Known Issues/Limiations:
* AsyncService::Semaphore::WaitForTime
* Code is compiled under VCZH_DEBUG_NO_REFLECTION, if u need Reflection, remember to remove VCZH_DEBUG_NO_REFLECTION in CMakeLists.txt and add all of Reflection cpp files.

##### TODO
* Titlebar of darkskin should be removed
* GuiInnerShadowElementRenderer/Gui3DBorderElementRenderer/Gui3DSplitterElementRenderer is not implemented yet
* CocoaClipboardWriter and CocoaClipboardReader is not implemented yet

![image](https://user-images.githubusercontent.com/1700820/126869373-a7bdbd9b-23f0-4d16-a370-5677f44928a4.png)
![animation](https://user-images.githubusercontent.com/1700820/126869419-8c1d7cef-3157-4b0c-976d-5e42a2b16e92.gif)
![calculator](https://user-images.githubusercontent.com/1700820/126869461-7ef8140a-5f54-4a98-865e-9b56d2db3609.gif)
