# Linux port for [GacLib](http://www.gaclib.net)

using gtkmm/cairomm/pangomm

## License

**Read the [LICENSE](https://github.com/vczh-libraries/gGac/blob/master/LICENSE.md) first.**

## Building this repo

* need to have `build-essential`, `cmake`, `gtkmm-3.0`
* run `build.sh` from the root folder
* go to each test app folder and `make`

## Current Progress:
* Finalizing

## Known Issues/Limiations:
* AsyncService::Semaphore::WaitForTime
* Code is compiled under VCZH_DEBUG_NO_REFLECTION, if u need Reflection, remember to remove VCZH_DEBUG_NO_REFLECTION in CMakeLists.txt and add all of Reflection cpp files.

## Roadmap
- Replace gtk by wayland
  - replace all gtk control including all dialog/window/pixbuf etc. by GacUI native control
  - replace all screen relative things by wayland
  - replace all gdk event by wayland
- Add vulkan renderer

## Examples
<img name="helloworld" src="https://user-images.githubusercontent.com/1700820/212235190-5d6563cc-35d9-4a0a-8197-6c3cd3199e48.png" width="300px"><img name="mvvm" src="https://user-images.githubusercontent.com/1700820/212235939-ea6ebf0d-4b3a-4e89-832b-94f0414f8b99.gif" width="300px">
 <img name="stack" src="https://user-images.githubusercontent.com/1700820/212236435-5c47a633-e3ca-4a3c-8e54-2dd4d02d8825.gif" width="300px"><img name="table" src="https://user-images.githubusercontent.com/1700820/212236583-2d756491-fc7f-4466-817d-f26bf0b76b45.png" width="300px"> 
 <img name="addressbook" src="https://user-images.githubusercontent.com/1700820/212237492-a7daccdf-7f71-4bc7-b770-860c81642136.gif" width="300px"><img name="animation" src="https://user-images.githubusercontent.com/1700820/212237823-75ba77e7-b3f1-4e6c-9c97-e49ec5c18531.gif" width="300px"> 
 <img name="editor" src="https://user-images.githubusercontent.com/1700820/212239463-45d09368-188c-4eca-8a84-2188bb2eaf1f.gif" width="300px"> 







