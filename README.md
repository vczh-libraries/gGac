#### Linux port for [GacLib](http://www.gaclib.net) using gtkmm/cairomm/pangomm

##### License

**Read the [LICENSE](https://github.com/vczh-libraries/iGac/blob/master/LICENSE.md) first.**

##### Current Progress:
* Finalizing

##### Known Issues/Limiations:
* AsyncService::Semaphore::WaitForTime
* Code is compiled under VCZH_DEBUG_NO_REFLECTION, if u need Reflection, remember to remove VCZH_DEBUG_NO_REFLECTION in CMakeLists.txt and add all of Reflection cpp files.

##### TODO
* GuiInnerShadowElementRenderer/Gui3DBorderElementRenderer/Gui3DSplitterElementRenderer is not implemented yet
* CocoaClipboardWriter and CocoaClipboardReader is not implemented yet
