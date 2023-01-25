# Linux port for [GacLib](http://www.gaclib.net)

using gtkmm/cairomm/pangomm

## License

**Read the [LICENSE](https://github.com/vczh-libraries/gGac/blob/master/LICENSE.md) first.**

## Building & Debug this repo

* need to have `build-essential`, `cmake`, `gtkmm-3.0`, `sigc++-2.0`
* build gGac using `CMakeLists.txt` in root directory 
  * mkdir build
  * cd build
  * cmake ..
  * make -j16
  * sudo make install
* build Tests using `CMakeLists.txt` in Tests directory
  * mkdir -p Tests/build
  * cd Tests/build
  * export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
  * cmake ../ 
  * make -j16
* use ```console::Console::WriteLine(L"xxx")``` to log anything interesting to console output, remember to set LC_ALL to your native lanaguage.

## Current Progress:
* 1.2.0.0 prereleasing
* waiting for remove webdings in darkskin

## Known Issues/Limiations:
* AsyncService::Semaphore::WaitForTime
* Code is compiled under VCZH_DEBUG_NO_REFLECTION, if u need Reflection, remember to remove VCZH_DEBUG_NO_REFLECTION in CMakeLists.txt and add all of Reflection cpp files.

## Roadmap
- Replace gtk by wayland
  - replace all gtk control including all dialog/window/pixbuf etc. by GacUI native control and wayland surface
  - replace all screen relative things by wayland
  - replace all gdk event by wayland
  - gtk4 branch is abandoned, since it remove eventbox and drop a lot work to X/Wayland. i.e. gtk4 is something same as gGac
- Add vulkan renderer

## Examples
|        |       |
|  ----  | ----  |
| <img name="helloworld" src="https://user-images.githubusercontent.com/1700820/214537578-eeb5e893-ed58-4e8a-bd39-60266f56fd8b.png" width="300px">  | <img name="mvvm" src="https://user-images.githubusercontent.com/1700820/214543772-e98a9741-bec3-4e25-af37-c47d2c27eab5.gif" width="300px"> |
| <img name="stack" src="https://user-images.githubusercontent.com/1700820/212236435-5c47a633-e3ca-4a3c-8e54-2dd4d02d8825.gif" width="300px"> | <img name="table" src="https://user-images.githubusercontent.com/1700820/212236583-2d756491-fc7f-4466-817d-f26bf0b76b45.png" width="300px"> |
| <img name="animation1" src="https://user-images.githubusercontent.com/1700820/214572219-8cf24ddf-7da3-42b4-8fc7-21f048679f88.gif" width="300px"> | <img name="animation2" src="https://user-images.githubusercontent.com/1700820/212237823-75ba77e7-b3f1-4e6c-9c97-e49ec5c18531.gif" width="300px">  |
|  <img name="editor" src="https://user-images.githubusercontent.com/1700820/212239463-45d09368-188c-4eca-8a84-2188bb2eaf1f.gif" width="300px"> | <img name="addressbook" src="https://user-images.githubusercontent.com/1700820/212237492-a7daccdf-7f71-4bc7-b770-860c81642136.gif" width="300px">  |







