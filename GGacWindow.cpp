//
// Created by css on 6/27/21.
//

#include "GGacWindow.h"


namespace vl {

	namespace presentation {

		namespace gtk {
			Point GGacWindow::Convert(NativePoint value) {
				return vl::presentation::Point();
			}

			NativePoint GGacWindow::Convert(Point value) {
				return vl::presentation::NativePoint();
			}

			Size GGacWindow::Convert(NativeSize value) {
				return vl::presentation::Size();
			}

			NativeSize GGacWindow::Convert(Size value) {
				return vl::presentation::NativeSize();
			}

			Margin GGacWindow::Convert(NativeMargin value) {
				return vl::presentation::Margin();
			}

			NativeMargin GGacWindow::Convert(Margin value) {
				return vl::presentation::NativeMargin();
			}

			NativeRect GGacWindow::GetBounds() {
				return vl::presentation::NativeRect();
			}

			void GGacWindow::SetBounds(const NativeRect &bounds) {

			}

			NativeSize GGacWindow::GetClientSize() {
				return vl::presentation::NativeSize();
			}

			void GGacWindow::SetClientSize(NativeSize size) {

			}

			NativeRect GGacWindow::GetClientBoundsInScreen() {
				return vl::presentation::NativeRect();
			}

			WString GGacWindow::GetTitle() {
				return vl::WString();
			}

			void GGacWindow::SetTitle(WString title) {

			}

			INativeCursor *GGacWindow::GetWindowCursor() {
				return nullptr;
			}

			void GGacWindow::SetWindowCursor(INativeCursor *cursor) {

			}

			NativePoint GGacWindow::GetCaretPoint() {
				return vl::presentation::NativePoint();
			}

			void GGacWindow::SetCaretPoint(NativePoint point) {

			}

			INativeWindow *GGacWindow::GetParent() {
				return nullptr;
			}

			void GGacWindow::SetParent(INativeWindow *parent) {

			}

			INativeWindow::WindowMode GGacWindow::GetWindowMode() {
				return Tooltip;
			}

			void GGacWindow::SetWindowMode(INativeWindow::WindowMode mode) {

			}

			void GGacWindow::EnableCustomFrameMode() {

			}

			void GGacWindow::DisableCustomFrameMode() {

			}

			bool GGacWindow::IsCustomFrameModeEnabled() {
				return false;
			}

			NativeMargin GGacWindow::GetCustomFramePadding() {
				return vl::presentation::NativeMargin();
			}

			Ptr<GuiImageData> GGacWindow::GetIcon() {
				return Ptr<GuiImageData>();
			}

			void GGacWindow::SetIcon(Ptr<GuiImageData> icon) {

			}

			INativeWindow::WindowSizeState GGacWindow::GetSizeState() {
				return Restored;
			}

			void GGacWindow::Show() {

			}

			void GGacWindow::ShowDeactivated() {

			}

			void GGacWindow::ShowRestored() {

			}

			void GGacWindow::ShowMaximized() {

			}

			void GGacWindow::ShowMinimized() {

			}

			void GGacWindow::Hide(bool closeWindow) {

			}

			bool GGacWindow::IsVisible() {
				return false;
			}

			void GGacWindow::Enable() {

			}

			void GGacWindow::Disable() {

			}

			bool GGacWindow::IsEnabled() {
				return false;
			}

			void GGacWindow::SetFocus() {

			}

			bool GGacWindow::IsFocused() {
				return false;
			}

			void GGacWindow::SetActivate() {

			}

			bool GGacWindow::IsActivated() {
				return false;
			}

			void GGacWindow::ShowInTaskBar() {

			}

			void GGacWindow::HideInTaskBar() {

			}

			bool GGacWindow::IsAppearedInTaskBar() {
				return false;
			}

			void GGacWindow::EnableActivate() {

			}

			void GGacWindow::DisableActivate() {

			}

			bool GGacWindow::IsEnabledActivate() {
				return false;
			}

			bool GGacWindow::RequireCapture() {
				return false;
			}

			bool GGacWindow::ReleaseCapture() {
				return false;
			}

			bool GGacWindow::IsCapturing() {
				return false;
			}

			bool GGacWindow::GetMaximizedBox() {
				return false;
			}

			void GGacWindow::SetMaximizedBox(bool visible) {

			}

			bool GGacWindow::GetMinimizedBox() {
				return false;
			}

			void GGacWindow::SetMinimizedBox(bool visible) {

			}

			bool GGacWindow::GetBorder() {
				return false;
			}

			void GGacWindow::SetBorder(bool visible) {

			}

			bool GGacWindow::GetSizeBox() {
				return false;
			}

			void GGacWindow::SetSizeBox(bool visible) {

			}

			bool GGacWindow::GetIconVisible() {
				return false;
			}

			void GGacWindow::SetIconVisible(bool visible) {

			}

			bool GGacWindow::GetTitleBar() {
				return false;
			}

			void GGacWindow::SetTitleBar(bool visible) {

			}

			bool GGacWindow::GetTopMost() {
				return false;
			}

			void GGacWindow::SetTopMost(bool topmost) {

			}

			void GGacWindow::SupressAlt() {

			}

			bool GGacWindow::InstallListener(INativeWindowListener *listener) {
				return false;
			}

			bool GGacWindow::UninstallListener(INativeWindowListener *listener) {
				return false;
			}

			void GGacWindow::RedrawContent() {

			}
		}

	}

}