//
// Created by css on 7/2/21.
//

#include "GGacWindowListener.h"

#include "GGacWindow.h"
#include "GGacView.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacWindowListener::GGacWindowListener(INativeWindow *_window)
					:window(_window)
			{
				view = MakePtr<GGacView>(_window);
				Gtk::Window *gWin = dynamic_cast<GGacWindow*>(window)->GetNativeWindow();
				gWin->add(*view.Obj());
				view->show_all();
			}

			GGacWindowListener::~GGacWindowListener()
			{

			}

			void GGacWindowListener::ResizeRenderTarget()
			{
				RebuildLayer(window->GetClientSize());
			}

			void GGacWindowListener::RebuildLayer(NativeSize size)
			{
				if (previousSize != size)
				{
					view->resize(size.x.value, size.y.value);
					previousSize = size;
				}
			}

			void GGacWindowListener::StartRendering()
			{
				rendering = true;
			}

			void GGacWindowListener::StopRendering()
			{
				rendering = false;
			}

			bool GGacWindowListener::RetrieveAndResetMovedWhileRendering()
			{
				bool result = movedWhileRendering;
				movedWhileRendering = false;
				return result;
			}

			Ptr<GGacView> GGacWindowListener::GetGGacView() const
			{
				return view;
			}

			void GGacWindowListener::RecreateRenderTarget()
			{
				RebuildLayer(window->GetClientSize());
			}

			void GGacWindowListener::Moved()
			{
				if (rendering)
				{
					movedWhileRendering = true;
				}
				else
				{
					RebuildLayer(window->GetClientSize());
				}
			}

			void GGacWindowListener::LeftButtonUp(const NativeWindowMouseInfo &info)
			{

			}

			/*INativeWindowListener::HitTestResult GGacWindowListener::HitTest(NativePoint location) {
				return INativeWindowListener::HitTest(location);
			}

			void GGacWindowListener::Moving(NativeRect &bounds, bool fixSizeOnly) {
				INativeWindowListener::Moving(bounds, fixSizeOnly);
			}

			void GGacWindowListener::DpiChanged() {
				INativeWindowListener::DpiChanged();
			}

			void GGacWindowListener::Enabled() {
				INativeWindowListener::Enabled();
			}

			void GGacWindowListener::Disabled() {
				INativeWindowListener::Disabled();
			}

			void GGacWindowListener::GotFocus() {
				INativeWindowListener::GotFocus();
			}

			void GGacWindowListener::LostFocus() {
				INativeWindowListener::LostFocus();
			}

			void GGacWindowListener::Activated() {
				INativeWindowListener::Activated();
			}

			void GGacWindowListener::Deactivated() {
				INativeWindowListener::Deactivated();
			}

			void GGacWindowListener::Opened() {
				INativeWindowListener::Opened();
			}

			void GGacWindowListener::Closing(bool &cancel) {
				INativeWindowListener::Closing(cancel);
			}

			void GGacWindowListener::Closed() {
				INativeWindowListener::Closed();
			}

			void GGacWindowListener::Paint() {
				INativeWindowListener::Paint();
			}

			void GGacWindowListener::Destroying() {
				INativeWindowListener::Destroying();
			}

			void GGacWindowListener::Destroyed() {
				INativeWindowListener::Destroyed();
			}

			void GGacWindowListener::LeftButtonDown(const NativeWindowMouseInfo &info) {
				INativeWindowListener::LeftButtonDown(info);
			}

			void GGacWindowListener::LeftButtonUp(const NativeWindowMouseInfo &info) {
				INativeWindowListener::LeftButtonUp(info);
			}

			void GGacWindowListener::LeftButtonDoubleClick(const NativeWindowMouseInfo &info) {
				INativeWindowListener::LeftButtonDoubleClick(info);
			}

			void GGacWindowListener::RightButtonDown(const NativeWindowMouseInfo &info) {
				INativeWindowListener::RightButtonDown(info);
			}

			void GGacWindowListener::RightButtonUp(const NativeWindowMouseInfo &info) {
				INativeWindowListener::RightButtonUp(info);
			}

			void GGacWindowListener::RightButtonDoubleClick(const NativeWindowMouseInfo &info) {
				INativeWindowListener::RightButtonDoubleClick(info);
			}

			void GGacWindowListener::MiddleButtonDown(const NativeWindowMouseInfo &info) {
				INativeWindowListener::MiddleButtonDown(info);
			}

			void GGacWindowListener::MiddleButtonUp(const NativeWindowMouseInfo &info) {
				INativeWindowListener::MiddleButtonUp(info);
			}

			void GGacWindowListener::MiddleButtonDoubleClick(const NativeWindowMouseInfo &info) {
				INativeWindowListener::MiddleButtonDoubleClick(info);
			}

			void GGacWindowListener::HorizontalWheel(const NativeWindowMouseInfo &info) {
				INativeWindowListener::HorizontalWheel(info);
			}

			void GGacWindowListener::VerticalWheel(const NativeWindowMouseInfo &info) {
				INativeWindowListener::VerticalWheel(info);
			}

			void GGacWindowListener::MouseMoving(const NativeWindowMouseInfo &info) {
				INativeWindowListener::MouseMoving(info);
			}

			void GGacWindowListener::MouseEntered() {
				INativeWindowListener::MouseEntered();
			}

			void GGacWindowListener::MouseLeaved() {
				INativeWindowListener::MouseLeaved();
			}

			void GGacWindowListener::KeyDown(const NativeWindowKeyInfo &info) {
				INativeWindowListener::KeyDown(info);
			}

			void GGacWindowListener::KeyUp(const NativeWindowKeyInfo &info) {
				INativeWindowListener::KeyUp(info);
			}

			void GGacWindowListener::SysKeyDown(const NativeWindowKeyInfo &info) {
				INativeWindowListener::SysKeyDown(info);
			}

			void GGacWindowListener::SysKeyUp(const NativeWindowKeyInfo &info) {
				INativeWindowListener::SysKeyUp(info);
			}

			void GGacWindowListener::Char(const NativeWindowCharInfo &info) {
				INativeWindowListener::Char(info);
			}*/

		}

	}

}