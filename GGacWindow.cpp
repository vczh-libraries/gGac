//
// Created by css on 6/27/21.
//

#include "GGacWindow.h"
#include "GGacHelper.h"
#include "Services/GGacInputService.h"
#include <iostream>

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacWindow::GGacWindow(INativeWindow::WindowMode _mode)
			:nativeWindow(0),
			parentWindow(0),
			mouseLastX(0),
			mouseLastY(0),
			mouseDownX(0),
			mouseDownY(0),
			supressingAlt(false),
			enabled(false),
			capturing(false),
			resizing(false),
			moving(false),
			opened(false),
			mouseHoving(false),
			mode(_mode)
			{
				if (mode == INativeWindow::WindowMode::Normal || mode == INativeWindow::WindowMode::Popup)
				{
					nativeWindow = new Gtk::Window();
				}
				else
				{
					nativeWindow = new Gtk::Window(Gtk::WindowType::WINDOW_POPUP);
					nativeWindow->set_modal(true);
					nativeWindow->set_decorated(false);
				}
				nativeWindow->signal_size_allocate().connect(sigc::mem_fun(*this, &GGacWindow::onSizeChanged));
			}

			GGacWindow::~GGacWindow()
			{
				nativeWindow->close();
				delete nativeWindow;
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
				return nativeWindow;
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

				info.left = event->button.button == GDK_BUTTON_PRIMARY && event->type == GDK_BUTTON_PRESS;
				info.right = event->button.button == GDK_BUTTON_SECONDARY && event->type == GDK_BUTTON_PRESS;
				info.middle = event->button.button == GDK_BUTTON_MIDDLE && event->type == GDK_BUTTON_PRESS;

				info.ctrl = false;
				info.shift = false;
				/*info.ctrl = event.modifierFlags & NSEventModifierFlagControl;
				info.shift = event.modifierFlags & NSEventModifierFlagShift;*/

				int width, height;
				nativeWindow->get_size(width, height);
				info.x = event->motion.x;
				info.y = event->motion.y;
				info.nonClient = (info.x < 0 || info.y < 0 || info.x > width || info.y > height);

				return info;
			}

			NativeWindowKeyInfo GGacWindow::createKeyInfo(GdkEvent* event)
			{
				NativeWindowKeyInfo info{};

				info.ctrl = false;
				info.shift = false;
				info.alt = false;
				info.capslock = false;
				info.code = GdkEventKeyCodeToGacKeyCode(event->key.keyval);

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
							switch (event->button.button)
							{
								case GDK_BUTTON_PRIMARY:
									listeners[i]->LeftButtonDown(info);
									mouseDownX = info.x.value;
									mouseDownY = info.y.value;
									if (customFrameMode)
									{
										auto control = listeners[i]->HitTest(NativePoint(mouseDownX, mouseDownY));
										switch(control)
										{
											case INativeWindowListener::NoDecision:
												break;
											case INativeWindowListener::Client:
												return true;
											default:
												break;
										}
									}
									break;
								case GDK_BUTTON_SECONDARY:
									listeners[i]->RightButtonDown(info);
									break;
								case GDK_BUTTON_MIDDLE:
									listeners[i]->MiddleButtonDown(info);
									break;
							}
						}
						break;
					}

					case GDK_BUTTON_RELEASE:
					{
						NativeWindowMouseInfo info = createMouseInfo(event);
						for (vint i = 0; i < listeners.Count(); i++)
						{
							switch (event->button.button)
							{
								case GDK_BUTTON_PRIMARY:
									listeners[i]->LeftButtonUp(info);
									if (customFrameMode)
									{
										auto control = listeners[i]->HitTest(NativePoint(info.x, info.y));
										switch(control)
										{
											case INativeWindowListener::ButtonMinimum:
												ShowMinimized();
												return true;
											case INativeWindowListener::ButtonMaximum:
												if (GetSizeState() == INativeWindow::Maximized)
												{
													ShowRestored();
												}
												else
												{
													ShowMaximized();
												}
												return true;
											case INativeWindowListener::ButtonClose:
												Hide(true);
												return true;
											case INativeWindowListener::NoDecision:
												break;
											case INativeWindowListener::Client:
												return true;
											default:
												break;
										}
									}
									break;
								case GDK_BUTTON_SECONDARY:
									listeners[i]->RightButtonUp(info);
									break;

								case GDK_BUTTON_MIDDLE:
									listeners[i]->MiddleButtonUp(info);
									break;
							}
						}
						break;
					}

					case GDK_DOUBLE_BUTTON_PRESS:
					{
						NativeWindowMouseInfo info = createMouseInfo(event);
						for (vint i = 0; i < listeners.Count(); i++)
						{
							switch (event->button.button)
							{
								case GDK_BUTTON_PRIMARY:
									listeners[i]->LeftButtonDoubleClick(info);
									break;
								case GDK_BUTTON_SECONDARY:
									listeners[i]->RightButtonDoubleClick(info);
									break;
								case GDK_BUTTON_MIDDLE:
									listeners[i]->MiddleButtonDoubleClick(info);
									break;
							}
						}
						break;
					}

					case GDK_MOTION_NOTIFY:
					case GDK_DRAG_MOTION:
					{
						NativeWindowMouseInfo info = createMouseInfo(event);
						info.nonClient = !mouseHoving;

						for (vint i = 0; i < listeners.Count(); i++)
						{
							listeners[i]->MouseMoving(info);
						}
						mouseLastX = info.x.value;
						mouseLastY = info.y.value;

						if (customFrameMode)
						{
							if (event->type == GDK_MOTION_NOTIFY)
							{
								if (!resizing)
								{
									for (vint i = 0; i < listeners.Count(); i++)
									{
										INativeWindowListener::HitTestResult r = listeners[i]->HitTest(NativePoint(info.x, info.y));
									}
								}
							}

							/*if(event.type == NSEventTypeLeftMouseDragged ||
							   event.type == NSEventTypeMouseMoved)
							{
								if(resizing)
									ResizingDragged();

								if(moving)
									MovingDragged();
							}*/
						}

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

					case GDK_KEY_PRESS:
					{
						NativeWindowKeyInfo info = createKeyInfo(event);
						for (vint i = 0; i < listeners.Count(); i++)
						{
							listeners[i]->KeyDown(info);
						}
						NativeWindowCharInfo charInfo{};
						if (dynamic_cast<GGacInputService *>(GetCurrentController()->InputService())->ConvertToPrintable(charInfo, event))
						{
							for (vint i = 0; i < listeners.Count(); i++)
							{
								listeners[i]->Char(charInfo);
							}
						}
						break;
					}

					case GDK_KEY_RELEASE:
					{
						NativeWindowKeyInfo info = createKeyInfo(event);
						for(vint i=0; i<listeners.Count(); ++i)
						{
							listeners[i]->KeyUp(info);
						}
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
				nativeWindow->get_position(x, y);
				nativeWindow->get_size(width, height);
				return NativeRect(x, y, x + width, y + height);
			}

			void GGacWindow::SetBounds(const NativeRect &bounds)
			{
				NativeRect newBounds = bounds;
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->Moving(newBounds, true);
				}
				nativeWindow->move(newBounds.Left().value, newBounds.Top().value);
				nativeWindow->set_default_size(newBounds.Width().value, newBounds.Height().value);
			}

			NativeSize GGacWindow::GetClientSize()
			{
				int x, y;
				nativeWindow->get_size(x, y);
				return NativeSize(x, y);
			}

			void GGacWindow::SetClientSize(NativeSize size)
			{
				if (size.x.value > 0 && size.y.value > 0)
					nativeWindow->set_default_size(size.x.value, size.y.value);
			}

			NativeRect GGacWindow::GetClientBoundsInScreen()
			{
				auto loc = nativeWindow->get_allocation();
				if (!nativeWindow->get_screen())
					loc = nativeWindow->get_allocation();
				/*Gdk::Rectangle contentFrame = [nsWindow convertRectToScreen:[nsWindow.contentView frame]];
				if(!([nsWindow screen]))
					contentFrame = [nsWindow frame];*/
				return NativeRect(loc.get_x(), loc.get_y(), loc.get_x() + loc.get_width(), loc.get_y() + loc.get_height());
			}

			WString GGacWindow::GetTitle()
			{
				nativeWindow->get_title();
			}

			void GGacWindow::SetTitle(WString title)
			{
				nativeWindow->set_title(Glib::ustring::format(title.Buffer()));
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
				return parentWindow;
			}

			void GGacWindow::SetParent(INativeWindow *parent)
			{
				GGacWindow* gWin = dynamic_cast<GGacWindow*>(parent);
				if (!gWin)
				{
					if (parentWindow) {
						//gWin->GetNativeWindow()->set_parent_window()
						//[gWIn->GetNativeWindow() removeChildWindow:nativeWindow];
					}
				}
				else
				{
					if (!parentWindow)
					{
						nativeWindow->set_transient_for(*gWin->GetNativeWindow());
					}
				}
				parentWindow = gWin;
			}

			INativeWindow::WindowMode GGacWindow::GetWindowMode()
			{
				return mode;
			}

			void GGacWindow::SetWindowMode(INativeWindow::WindowMode _mode)
			{
				switch (_mode)
				{
					case INativeWindow::Menu:
						break;
				}
				mode = _mode;
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
				return customFrameMode;
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
				nativeWindow->set_visible(true);
				if (!opened)
				{
					for (vint i = 0; i < listeners.Count(); i++)
					{
						listeners[i]->Opened();
					}
					opened = true;
				}
			}

			void GGacWindow::ShowDeactivated()
			{
				nativeWindow->set_visible(true);
				if (!opened)
				{
					for (vint i = 0; i < listeners.Count(); i++)
					{
						listeners[i]->Opened();
					}
					opened = true;
				}
			}

			void GGacWindow::ShowRestored()
			{

			}

			void GGacWindow::ShowMaximized()
			{
				if (nativeWindow->is_maximized())
				{
					nativeWindow->unmaximize();
				}
				else
				{
					nativeWindow->maximize();
				}
			}

			void GGacWindow::ShowMinimized()
			{
				nativeWindow->iconify();
			}

			void GGacWindow::Hide(bool closeWindow)
			{
				if (closeWindow)
				{
					nativeWindow->close();
				}
				else
				{
					nativeWindow->set_visible(false);
				}
				opened = false;
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->Closed();
				}
				ReleaseCapture();
			}

			bool GGacWindow::IsVisible()
			{
				return nativeWindow->is_visible();
			}

			void GGacWindow::Enable()
			{
				nativeWindow->set_focus_visible(true);
				enabled = true;
			}

			void GGacWindow::Disable()
			{
				nativeWindow->set_focus_visible(false);
				enabled = false;
			}

			bool GGacWindow::IsEnabled()
			{
				return enabled;
			}

			void GGacWindow::SetFocus()
			{
				nativeWindow->set_can_focus(true);
				nativeWindow->grab_focus();
			}

			bool GGacWindow::IsFocused()
			{
				return nativeWindow->is_focus();
			}

			void GGacWindow::SetActivate()
			{
				nativeWindow->show_all();
			}

			bool GGacWindow::IsActivated()
			{
				return nativeWindow->is_active();
			}

			void GGacWindow::ShowInTaskBar() {

			}

			void GGacWindow::HideInTaskBar() {

			}

			bool GGacWindow::IsAppearedInTaskBar()
			{
				return true;
			}

			void GGacWindow::EnableActivate()
			{

			}

			void GGacWindow::DisableActivate()
			{

			}

			bool GGacWindow::IsEnabledActivate()
			{
				return true;
			}

			bool GGacWindow::RequireCapture()
			{
				capturing = true;
				return true;
			}

			bool GGacWindow::ReleaseCapture()
			{
				capturing = false;
				return true;
			}

			bool GGacWindow::IsCapturing()
			{
				return capturing;
			}

			bool GGacWindow::GetMaximizedBox()
			{
				return false;
			}

			void GGacWindow::SetMaximizedBox(bool visible) {

			}

			bool GGacWindow::GetMinimizedBox()
			{
				return false;
			}

			void GGacWindow::SetMinimizedBox(bool visible)
			{

			}

			bool GGacWindow::GetBorder()
			{
				return false;
			}

			void GGacWindow::SetBorder(bool visible)
			{

			}

			bool GGacWindow::GetSizeBox()
			{
				return false;
			}

			void GGacWindow::SetSizeBox(bool visible)
			{

			}

			bool GGacWindow::GetIconVisible()
			{
				return false;
			}

			void GGacWindow::SetIconVisible(bool visible)
			{
			}

			bool GGacWindow::GetTitleBar()
			{
				return false;
			}

			void GGacWindow::SetTitleBar(bool visible)
			{

			}

			bool GGacWindow::GetTopMost()
			{
				return true;
			}

			void GGacWindow::SetTopMost(bool topmost)
			{

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

			void GGacWindow::RedrawContent()
			{
			}
		}

	}

}