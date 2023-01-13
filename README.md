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
![image](https://user-images.githubusercontent.com/1700820/212225931-8a03dc81-6829-4ea1-9fef-9c7a174e84ca.png)



