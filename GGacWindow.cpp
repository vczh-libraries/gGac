//
// Created by css on 6/27/21.
//

#include "GGacWindow.h"


namespace vl {

	namespace presentation {

		namespace gtk {

			GGacWindow::GGacWindow()
			:window(0),
			mouseLastX(0),
			mouseLastY(0),
			mouseDownX(0),
			mouseDownY(0),
			mouseHoving(false)
			{
				window = new Gtk::Window();
				window->signal_size_allocate().connect(sigc::mem_fun(*this, &GGacWindow::onSizeChanged));
			}

			GGacWindow::~GGacWindow()
			{
				window->close();
				delete window;
			}

			///

			void GGacWindow::onSizeChanged(const Gdk::Rectangle& rect)
			{
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->Moved();
				}
			}

			///

			Gtk::Window* GGacWindow::GetNativeWindow() const
			{
				return window;
			}

			void GGacWindow::SetGraphicsHandler(Interface* handler)
			{
				graphicsHandler = handler;
			}

			Interface* GGacWindow::GetGraphicsHandler() const
			{
				return graphicsHandler;
			}

			NativeWindowMouseInfo GGacWindow::createMouseInfo(GdkEvent* event)
			{
				NativeWindowMouseInfo info{};

				info.left = event->button.button == GDK_BUTTON_PRIMARY;
				info.right = event->button.button == GDK_BUTTON_SECONDARY;
				info.middle = event->button.button == GDK_BUTTON_MIDDLE;

				/*info.ctrl = event.modifierFlags & NSEventModifierFlagControl;
				info.shift = event.modifierFlags & NSEventModifierFlagShift;*/

				int width, height;
				window->get_size(width, height);
				info.x = event->motion.x;
				info.y = event->motion.y;
				info.nonClient = (info.x < 0 || info.y < 0 || info.x > width || info.y > height);
				return info;
			}

			bool GGacWindow::HandleEventInternal(GdkEvent* event)
			{
				switch (event->type)
				{
					case GDK_BUTTON_PRESS:
					{
						NativeWindowMouseInfo info = createMouseInfo(event);
						for (vint i = 0; i < listeners.Count(); i++)
						{
							if (info.left)
							{
								listeners[i]->LeftButtonDown(info);
								mouseDownX = info.x.value;
								mouseDownY = info.y.value;
								if (customFrameMode)
									listeners[i]->HitTest(NativePoint(mouseDownX, mouseDownY));
							}

							if (info.right)
								listeners[i]->RightButtonDown(info);

							if (info.middle)
								listeners[i]->MiddleButtonDown(info);
						}

						break;
					}

					case GDK_BUTTON_RELEASE:
					{
						NativeWindowMouseInfo info = createMouseInfo(event);
						for (vint i = 0; i < listeners.Count(); i++)
						{
							if (info.left)
								listeners[i]->LeftButtonUp(info);

							if (info.right)
								listeners[i]->RightButtonUp(info);

							if (info.middle)
								listeners[i]->MiddleButtonUp(info);
						}
						break;
					}

					case GDK_DOUBLE_BUTTON_PRESS:
					{
						NativeWindowMouseInfo info = createMouseInfo(event);
						for (vint i = 0; i < listeners.Count(); i++)
						{
							if (info.left)
								listeners[i]->LeftButtonDoubleClick(info);

							if (info.right)
								listeners[i]->RightButtonDoubleClick(info);

							if (info.middle)
								listeners[i]->MiddleButtonDoubleClick(info);
						}
						break;
					}

					case GDK_MOTION_NOTIFY:
					{
						break;
					}

					case GDK_ENTER_NOTIFY:
					{
						for (vint i = 0; i < listeners.Count(); i++)
						{
							listeners[i]->MouseEntered();
						}
						mouseHoving = true;
						break;
					}

					case GDK_LEAVE_NOTIFY:
					{
						for (vint i = 0; i < listeners.Count(); i++)
						{
							listeners[i]->MouseLeaved();
						}
						mouseHoving = false;
						break;
					}

					default:
						return false;
				}
				return true;
			}

			///

			Point GGacWindow::Convert(NativePoint value)
			{
				return Point(value.x.value, value.y.value);
			}

			NativePoint GGacWindow::Convert(Point value)
			{
				return NativePoint(value.x, value.y);
			}

			Size GGacWindow::Convert(NativeSize value)
			{
				return Size(value.x.value, value.y.value);
			}

			NativeSize GGacWindow::Convert(Size value)
			{
				return NativeSize(value.x, value.y);
			}

			Margin GGacWindow::Convert(NativeMargin value)
			{
				return Margin(value.left.value, value.top.value, value.right.value, value.bottom.value);
			}

			NativeMargin GGacWindow::Convert(Margin value)
			{
				return NativeMargin(value.left, value.top, value.right, value.bottom);
			}

			NativeRect GGacWindow::GetBounds()
			{
				int x, y, width, height;
				window->get_position(x, y);
				window->get_size(width, height);
				return NativeRect(x, y, x + width, y + height);
			}

			void GGacWindow::SetBounds(const NativeRect &bounds)
			{
				NativeRect newBounds = bounds;
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->Moving(newBounds, true);
				}
				window->set_allocation(Gtk::Allocation(newBounds.Left().value, newBounds.Top().value, newBounds.Width().value, newBounds.Height().value));
				Show();
			}

			NativeSize GGacWindow::GetClientSize()
			{
				int x, y;
				window->get_size(x, y);
				return NativeSize(x, y);
			}

			void GGacWindow::SetClientSize(NativeSize size)
			{
				window->set_default_size(size.x.value, size.y.value);
			}

			NativeRect GGacWindow::GetClientBoundsInScreen()
			{
				return vl::presentation::NativeRect();
			}

			WString GGacWindow::GetTitle()
			{
				window->get_title();
			}

			void GGacWindow::SetTitle(WString title)
			{
				window->set_title(Glib::ustring::format(title.Buffer()));
			}

			INativeCursor *GGacWindow::GetWindowCursor()
			{
				return nullptr;
			}

			void GGacWindow::SetWindowCursor(INativeCursor *cursor)
			{

			}

			NativePoint GGacWindow::GetCaretPoint()
			{
				return vl::presentation::NativePoint();
			}

			void GGacWindow::SetCaretPoint(NativePoint point)
			{

			}

			INativeWindow *GGacWindow::GetParent()
			{
				return nullptr;
			}

			void GGacWindow::SetParent(INativeWindow *parent)
			{

			}

			INativeWindow::WindowMode GGacWindow::GetWindowMode()
			{
				return Normal;
			}

			void GGacWindow::SetWindowMode(INativeWindow::WindowMode mode)
			{

			}

			void GGacWindow::EnableCustomFrameMode()
			{
				customFrameMode = true;
			}

			void GGacWindow::DisableCustomFrameMode()
			{
				customFrameMode = false;
			}

			bool GGacWindow::IsCustomFrameModeEnabled()
			{
				return false;
			}

			NativeMargin GGacWindow::GetCustomFramePadding()
			{
				return vl::presentation::NativeMargin();
			}

			Ptr<GuiImageData> GGacWindow::GetIcon()
			{
				return Ptr<GuiImageData>();
			}

			void GGacWindow::SetIcon(Ptr<GuiImageData> icon)
			{

			}

			INativeWindow::WindowSizeState GGacWindow::GetSizeState()
			{
				return Restored;
			}

			void GGacWindow::Show()
			{
				window->show();
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
				return true;
			}

			void GGacWindow::Enable() {

			}

			void GGacWindow::Disable() {

			}

			bool GGacWindow::IsEnabled() {
				return true;
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

			void GGacWindow::SupressAlt()
			{

			}

			bool GGacWindow::InstallListener(INativeWindowListener *listener)
			{
				listeners.Add(listener);
			}

			bool GGacWindow::UninstallListener(INativeWindowListener *listener)
			{
				listeners.Remove(listener);
			}

			void GGacWindow::RedrawContent() {

			}
		}

	}

}