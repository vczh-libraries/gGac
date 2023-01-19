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

			sigc::signal<void()> signal_blur;

            static void gtk_im_commit_cb(GtkIMContext *context, const gchar *str, GGacWindow *window)
            {
                auto code = (wchar_t *) g_convert(str, -1, "wchar_t", "utf-8", NULL, NULL, NULL);
                vint i = 0;
                while (wchar_t c = code[i++])
                {
                    window->IMCommit(c);
                }
            }

            static void gtk_im_preedit_changed_cb(GtkIMContext *context)
            {
                gchar *str;
                PangoAttrList* list;
                int pos;
                gtk_im_context_get_preedit_string(context, &str, &list, &pos);
                auto text = (wchar_t *) g_convert(str, -1, "wchar_t", "utf-8", NULL, NULL, NULL);
                console::Console::WriteLine(text);
            }

			GGacWindow::GGacWindow(INativeWindow::WindowMode _mode)
			:nativeWindow(0),
			parentWindow(0),
			mouseLastX(0),
			mouseLastY(0),
			mouseDownX(0),
			mouseDownY(0),
            scrollDelta(0),
			supressingAlt(false),
			enabled(true),
			capturing(false),
			resizing(false),
			moving(false),
			opened(false),
			mouseHoving(false),
            customFrameMode(true),
            border(true),
            sizeBox(true),
            titleBar(true),
            iconVisible(true),
            minimizedBox(true),
            maximizedBox(true),
            topMost(false),
			title(L""),
            imContext(0),
			mode(_mode)
			{
				if (mode == INativeWindow::WindowMode::Normal || mode == INativeWindow::WindowMode::Popup)
				{
                    nativeWindow = new Gtk::Window();
                    nativeWindow->set_decorated(false);
				}
				else
				{
                    nativeWindow = new Gtk::Window(Gtk::WindowType::WINDOW_POPUP);
                    nativeWindow->set_default_size(0, 0);
					blurHandler = signal_blur.connect(sigc::mem_fun(*this, &GGacWindow::onBlur));
				}
				nativeWindow->signal_size_allocate().connect(sigc::mem_fun(*this, &GGacWindow::onSizeChanged));
                nativeWindow->signal_event().connect(sigc::mem_fun(*this, &GGacWindow::HandleEventInternal));
                nativeWindow->add_events(Gdk::EventMask::ALL_EVENTS_MASK);

                imContext = gtk_im_multicontext_new();
                if (imContext)
                {
                    GdkWindow *gdk_window = gtk_widget_get_window(GTK_WIDGET(nativeWindow->gobj()));
                    gtk_im_context_set_client_window(imContext, gdk_window);
                    gtk_im_context_set_use_preedit(imContext, false);
                    g_signal_connect(imContext, "commit", G_CALLBACK(gtk_im_commit_cb), this);
                    //g_signal_connect(imContext, "preedit-changed", G_CALLBACK(gtk_im_preedit_changed_cb), NULL);
                }
            }

			GGacWindow::~GGacWindow()
			{
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->Destroying();
				}
				nativeWindow->close();
				blurHandler.disconnect();
				for (vint i = 0; i < listeners.Count(); i++)
				{
					listeners[i]->Destroyed();
				}
				delete nativeWindow;
			}

			///

			void GGacWindow::onBlur()
			{
                Hide(false);
			}

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
                static bool left = false;
                static bool middle = false;
                static bool right = false;
				NativeWindowMouseInfo info{};
                info.x = event->motion.x;
                info.y = event->motion.y;

                info.ctrl = event->key.state & GDK_CONTROL_MASK;
                info.shift = event->key.state & GDK_SHIFT_MASK;

                switch (event->type)
                {
                    case GDK_BUTTON_PRESS:
                    case GDK_PAD_BUTTON_PRESS:
                        left = event->button.button == GDK_BUTTON_PRIMARY;
                        middle = event->button.button == GDK_BUTTON_MIDDLE;
                        right = event->button.button == GDK_BUTTON_SECONDARY;
                        break;
                    case GDK_BUTTON_RELEASE:
                    case GDK_PAD_BUTTON_RELEASE:
                    case GDK_FOCUS_CHANGE:
                        left = false;
                        middle = false;
                        right = false;
                        break;
                    case GDK_SCROLL:
                        double x, y;
                        if (!event->scroll.is_stop)
                        {
                            if (event->scroll.direction == GDK_SCROLL_SMOOTH)
                            {
                                gdk_event_get_scroll_deltas(event, &x, &y);
                                info.wheel = event->scroll.direction == GDK_SCROLL_DOWN || event->scroll.direction == GDK_SCROLL_UP ? y : x;
                            }
                            else
                            {
                                if (scrollDelta <= 1)
                                {
                                    scrollDelta = 1000.;
                                }
                                else
                                {
                                    scrollDelta = MAX(0, scrollDelta - 20);
                                }
                                vint scroll = MAX(20, pow(1.3, scrollDelta/49));
                                switch (event->scroll.direction)
                                {
                                    case GDK_SCROLL_UP:
                                        info.wheel = scroll;
                                        break;
                                    case GDK_SCROLL_DOWN:
                                        info.wheel = -scroll;
                                        break;
                                    case GDK_SCROLL_LEFT:
                                        info.wheel = scroll;
                                        break;
                                    case GDK_SCROLL_RIGHT:
                                        info.wheel = -scroll;
                                        break;
                                }
                            }
                        }
                        else
                        {
                            scrollDelta = 0;
                        }
                        break;
                }

                info.left = left;
                info.middle = middle;
                info.right = right;

				int width, height;
				nativeWindow->get_size(width, height);
				info.nonClient = (info.x < 0 || info.y < 0 || info.x > width || info.y > height);

				return info;
			}

			NativeWindowKeyInfo GGacWindow::createKeyInfo(GdkEvent* event)
			{
				NativeWindowKeyInfo info{};

				info.ctrl = event->key.state & GDK_CONTROL_MASK;
				info.shift = event->key.state & GDK_SHIFT_MASK;
				info.alt = event->key.state & GDK_MOD1_MASK;
				info.capslock = event->key.state & GDK_LOCK_MASK;
				info.code = GdkEventKeyCodeToGacKeyCode(event->key.keyval);

				return info;
			}

			bool GGacWindow::HandleEventInternal(GdkEvent* event)
			{
                NativeWindowMouseInfo info = createMouseInfo(event);
                switch (event->type)
                {
                    case GDK_BUTTON_PRESS: {
                        mouseDownX = info.x.value;
                        mouseDownY = info.y.value;
                        for (vint i = 0; i < listeners.Count(); i++)
                        {
                            switch (event->button.button) {
                                case GDK_BUTTON_PRIMARY:
                                    listeners[i]->LeftButtonDown(info);
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
                        switch (event->button.button) {
                            case GDK_BUTTON_PRIMARY:
                                signal_blur.emit();
                                for (vint i = 0; i < listeners.Count(); i++) {
                                    listeners[i]->LeftButtonUp(info);
                                }
                                for (vint i = 0; i < listeners.Count(); i++) {
                                    auto control = listeners[i]->HitTest(NativePoint(info.x, info.y));
                                    switch (control) {
                                        case INativeWindowListener::ButtonMinimum:
                                            ShowMinimized();
                                            return true;
                                        case INativeWindowListener::ButtonMaximum:
                                            if (GetSizeState() == INativeWindow::Maximized) {
                                                ShowRestored();
                                            } else {
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
                                for (vint i = 0; i < listeners.Count(); i++) {
                                    listeners[i]->RightButtonUp(info);
                                }
                                break;

                            case GDK_BUTTON_MIDDLE:
                                for (vint i = 0; i < listeners.Count(); i++) {
                                    listeners[i]->MiddleButtonUp(info);
                                }
                                break;
                        }
                        break;
                    }

                    case GDK_DOUBLE_BUTTON_PRESS:
                    {
                        for (vint i = 0; i < listeners.Count(); i++) {
                            switch (event->button.button) {
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

                    case GDK_SCROLL:
                    {
                        if (event->scroll.direction == GDK_SCROLL_UP || event->scroll.direction == GDK_SCROLL_DOWN)
                        {
                            for (vint i = 0; i < listeners.Count(); i++)
                            {
                                listeners[i]->VerticalWheel(info);
                            }
                        }
                        else
                        {
                            for (vint i = 0; i < listeners.Count(); i++)
                            {
                                listeners[i]->HorizontalWheel(info);
                            }
                        }
                        break;
                    }

                    case GDK_MOTION_NOTIFY:
                    {
                        info.nonClient = !mouseHoving;
                        mouseLastX = event->motion.x_root;
                        mouseLastY = event->motion.y_root;

                        for (vint i = 0; i < listeners.Count(); i++)
                        {
                            listeners[i]->MouseMoving(info);
                        }

                        if (customFrameMode)
                        {
                            if (event->type == GDK_MOTION_NOTIFY)
                            {
                                for (vint i = 0; i < listeners.Count(); i++) {
                                    INativeWindowListener::HitTestResult r = PerformHitTest(From(listeners), NativePoint(info.x, info.y));
                                    vint edge = -1;
                                    switch (r) {
                                        case vl::presentation::INativeWindowListener::BorderLeft:
                                            edge = Gdk::WindowEdge::WINDOW_EDGE_WEST;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::LEFT_SIDE));
                                            break;
                                        case vl::presentation::INativeWindowListener::BorderRight:
                                            edge = Gdk::WindowEdge::WINDOW_EDGE_EAST;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::RIGHT_SIDE));
                                            break;
                                        case vl::presentation::INativeWindowListener::BorderTop:
                                            edge = Gdk::WindowEdge::WINDOW_EDGE_NORTH;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::TOP_SIDE));
                                            break;
                                        case vl::presentation::INativeWindowListener::BorderBottom:
                                            edge = Gdk::WindowEdge::WINDOW_EDGE_SOUTH;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::BOTTOM_SIDE));
                                            break;
                                        case vl::presentation::INativeWindowListener::BorderLeftTop:
                                            edge = Gdk::WindowEdge::WINDOW_EDGE_NORTH_WEST;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::TOP_LEFT_CORNER));
                                            break;
                                        case vl::presentation::INativeWindowListener::BorderRightTop:
                                            edge = Gdk::WindowEdge::WINDOW_EDGE_NORTH_EAST;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::TOP_RIGHT_CORNER));
                                            break;
                                        case vl::presentation::INativeWindowListener::BorderLeftBottom:
                                            edge = Gdk::WindowEdge::WINDOW_EDGE_SOUTH_WEST;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::BOTTOM_LEFT_CORNER));
                                            break;
                                        case vl::presentation::INativeWindowListener::BorderRightBottom:
                                            edge = Gdk::WindowEdge::WINDOW_EDGE_SOUTH_EAST;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::BOTTOM_RIGHT_CORNER));
                                            break;
                                        case vl::presentation::INativeWindowListener::Icon:
                                        case vl::presentation::INativeWindowListener::Title:
                                            edge = -2;
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::ARROW));
                                            break;
                                        case vl::presentation::INativeWindowListener::BorderNoSizing:
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::ARROW));
                                            break;
                                        case vl::presentation::INativeWindowListener::Client:
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::ARROW));
                                            break;
                                        default:
                                            nativeWindow->get_window()->set_cursor(Gdk::Cursor::create(Gdk::CursorType::ARROW));
                                            break;
                                    }

                                    if (info.left)
                                    {
                                        if (edge > 0)
                                        {
                                            nativeWindow->begin_resize_drag((Gdk::WindowEdge)edge, 1, mouseLastX, mouseLastY, gtk_get_current_event_time());
                                        }
                                        else if (edge == -2)
                                        {
                                            nativeWindow->begin_move_drag(1, mouseLastX, mouseLastY, gtk_get_current_event_time());
                                        }
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

                    case GDK_FOCUS_CHANGE:
                    {
                        if (event->focus_change.in)
                        {
                            gtk_im_context_focus_in(imContext);
                        }
                        else
                        {
                            ReleaseCapture();
                            gtk_im_context_focus_out(imContext);
                        }
                        break;
                    }

                    case GDK_KEY_PRESS:
                    {
                        if (!gtk_im_context_filter_keypress(imContext, &event->key))
                        {
                            NativeWindowKeyInfo keyInfo = createKeyInfo(event);
                            for (vint i = 0; i < listeners.Count(); i++)
                            {
                                listeners[i]->KeyDown(keyInfo);
                            }
                        }
                        break;
                    }

                    case GDK_KEY_RELEASE:
                    {
                        NativeWindowKeyInfo keyInfo = createKeyInfo(event);
                        for (vint i = 0; i < listeners.Count(); i++)
                        {
                            listeners[i]->KeyUp(keyInfo);
                        }
                        break;
                    }

					default:
						return false;
				}
				return true;
			}

            void GGacWindow::IMCommit(wchar_t code)
            {
                NativeWindowCharInfo charInfo{};
                charInfo.code = code;
                for (vint i = 0; i < listeners.Count(); i++)
                {
                    listeners[i]->Char(charInfo);
                }
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
					listeners[i]->Moving(newBounds, true, false);
				}
				nativeWindow->move(newBounds.Left().value, newBounds.Top().value);
				nativeWindow->set_size_request(newBounds.Width().value, newBounds.Height().value);
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
                int x, y, width, height;
                nativeWindow->get_position(x, y);
                nativeWindow->get_size(width, height);
                return NativeRect(x, y, width, height);
			}

			WString GGacWindow::GetTitle()
			{
				return title;
			}

			void GGacWindow::SetTitle(const WString& _title)
			{
				title = _title;
			}

			INativeCursor *GGacWindow::GetWindowCursor()
			{
				return cursor;
			}

			void GGacWindow::SetWindowCursor(INativeCursor *_cursor)
			{
                GGacCursor* newCursor=dynamic_cast<GGacCursor*>(_cursor);
                if(newCursor && cursor!=newCursor)
                {
                    cursor=newCursor;
                    if(mouseHoving && IsVisible())
                    {
                        nativeWindow->get_window()->set_cursor(Glib::RefPtr(cursor->GetCursor()));
                    }
                }
			}

			NativePoint GGacWindow::GetCaretPoint()
			{
				return vl::presentation::NativePoint();
			}

			void GGacWindow::SetCaretPoint(NativePoint point)
			{
                GdkRectangle imRect = {(int)point.x.value, (int)point.y.value, 1, 1};
                gtk_im_context_set_cursor_location(imContext, &imRect);
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
						//parentWindow->GetNativeWindow()->unset_transient_for();
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
				return vl::presentation::NativeMargin(1, 1, 1, 1);
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
					nativeWindow->hide();
				}
                for (vint i = 0; i < listeners.Count(); i++)
                {
                    listeners[i]->Closed();
                }
                ReleaseCapture();
                gtk_im_context_focus_out(imContext);
                opened = false;
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

			void GGacWindow::SetActivate()
			{
				nativeWindow->show_all();
                nativeWindow->set_can_focus(true);
                nativeWindow->grab_focus();
			}

			bool GGacWindow::IsActivated()
			{
				return nativeWindow->is_active();
			}

			void GGacWindow::ShowInTaskBar()
            {
			}

			void GGacWindow::HideInTaskBar()
            {
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
                return maximizedBox;
			}

			void GGacWindow::SetMaximizedBox(bool visible)
            {
                maximizedBox = visible;
			}

			bool GGacWindow::GetMinimizedBox()
			{
				return minimizedBox;
			}

			void GGacWindow::SetMinimizedBox(bool visible)
			{
                minimizedBox = visible;
			}

			bool GGacWindow::GetBorder()
			{
				return border;
			}

			void GGacWindow::SetBorder(bool visible)
			{
                border = visible;
			}

			bool GGacWindow::GetSizeBox()
			{
                return sizeBox;
			}

			void GGacWindow::SetSizeBox(bool visible)
			{
                sizeBox = visible;
			}

			bool GGacWindow::GetIconVisible()
			{
                return iconVisible;
			}

			void GGacWindow::SetIconVisible(bool visible)
			{
                iconVisible = visible;
			}

			bool GGacWindow::GetTitleBar()
			{
				return titleBar;
			}

			void GGacWindow::SetTitleBar(bool visible)
			{
                titleBar = visible;
			}

			bool GGacWindow::GetTopMost()
			{
                return topMost;
			}

			void GGacWindow::SetTopMost(bool top)
			{
                topMost = top;
                nativeWindow->set_keep_above(topMost);
			}

			void GGacWindow::SupressAlt()
			{
			}

			bool GGacWindow::InstallListener(INativeWindowListener *listener)
			{
				if (listeners.Contains(listener)) return false;
				listeners.Add(listener);
				return true;
			}

			bool GGacWindow::UninstallListener(INativeWindowListener *listener)
			{
				if (listeners.Contains(listener))
				{
					return listeners.Remove(listener);
				}
                return false;
			}

			void GGacWindow::RedrawContent()
			{
			}

            bool GGacWindow::IsActivelyRefreshing()
            {
                return true;
            }

            NativeSize GGacWindow::GetRenderingOffset()
            {
                return vl::presentation::NativeSize(0, 0);
            }

            bool GGacWindow::IsRenderingAsActivated()
            {
                return true;
            }
        }

	}

}