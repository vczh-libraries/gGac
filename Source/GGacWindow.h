//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GGACWINDOW_H
#define GGAC_GGACWINDOW_H

#include "GacUI.h"
#include "GGacCursor.h"
#include <gtkmm.h>

namespace vl {

	namespace presentation {

		namespace gtk {

            class GGacWindow : public Object, public INativeWindow
			{
                using WindowListenerList = collections::List<INativeWindowListener*>;
            protected:
				Gtk::Window* 					nativeWindow;
                GtkIMContext*                   imContext;
				GGacWindow* 					parentWindow;
				GGacCursor* 					cursor;
				Interface* 						graphicsHandler;
				WindowListenerList				listeners;
				WString							title;
				WindowMode 						mode;
				sigc::connection				blurHandler;
                Size                            minSize;

				vint                            mouseLastX;
				vint                            mouseLastY;
				vint                            mouseDownX;
				vint                            mouseDownY;
                vint                            edge;
                double                          scrollDelta;
				bool 							mouseHoving;
				bool                            customFrameMode;
				bool                            supressingAlt;
				bool                            enabled;
				bool                            capturing;
				bool                            resizing;
				bool                            moving;
				bool                            opened;
				bool 							border;
				bool 							sizeBox;
				bool							topMost;
				bool							titleBar;
				bool							iconVisible;
				bool 							maximizedBox;
				bool 							minimizedBox;
                bool                            keepPopup;

				void onBlur();
				void onSizeChanged(const Gdk::Rectangle& rect);
				NativeWindowMouseInfo createMouseInfo(GdkEvent* event);
				NativeWindowKeyInfo createKeyInfo(GdkEvent* event);

			public:
				GGacWindow(INativeWindow::WindowMode _mode);
				virtual ~GGacWindow();
				Gtk::Window* GetNativeWindow() const;
				void SetGraphicsHandler(Interface* handelr);
				Interface* GetGraphicsHandler() const;
				bool HandleEventInternal(GdkEvent* event);
                void IMCommit(wchar_t str);

				///

				Point Convert(NativePoint value) override;

				NativePoint Convert(Point value) override;

				Size Convert(NativeSize value) override;

				NativeSize Convert(Size value) override;

				Margin Convert(NativeMargin value) override;

				NativeMargin Convert(Margin value) override;

				NativeRect GetBounds() override;

				void SetBounds(const NativeRect &bounds) override;

				NativeSize GetClientSize() override;

				void SetClientSize(NativeSize size) override;

				NativeRect GetClientBoundsInScreen() override;

				WString GetTitle() override;

                void SetTitle(const WString &title) override;

				INativeCursor *GetWindowCursor() override;

				void SetWindowCursor(INativeCursor *cursor) override;

				NativePoint GetCaretPoint() override;

				void SetCaretPoint(NativePoint point) override;

				INativeWindow *GetParent() override;

				void SetParent(INativeWindow *parent) override;

				WindowMode GetWindowMode() override;

				void EnableCustomFrameMode() override;

				void DisableCustomFrameMode() override;

				bool IsCustomFrameModeEnabled() override;

				NativeMargin GetCustomFramePadding() override;

				Ptr<GuiImageData> GetIcon() override;

				void SetIcon(Ptr<GuiImageData> icon) override;

				WindowSizeState GetSizeState() override;

				void Show() override;

				void ShowDeactivated() override;

				void ShowRestored() override;

				void ShowMaximized() override;

				void ShowMinimized() override;

				void Hide(bool closeWindow) override;

				bool IsVisible() override;

				void Enable() override;

				void Disable() override;

				bool IsEnabled() override;

				void SetActivate() override;

				bool IsActivated() override;

				void ShowInTaskBar() override;

				void HideInTaskBar() override;

				bool IsAppearedInTaskBar() override;

				void EnableActivate() override;

				void DisableActivate() override;

				bool IsEnabledActivate() override;

				bool RequireCapture() override;

				bool ReleaseCapture() override;

				bool IsCapturing() override;

				bool GetMaximizedBox() override;

				void SetMaximizedBox(bool visible) override;

				bool GetMinimizedBox() override;

				void SetMinimizedBox(bool visible) override;

				bool GetBorder() override;

				void SetBorder(bool visible) override;

				bool GetSizeBox() override;

				void SetSizeBox(bool visible) override;

				bool GetIconVisible() override;

				void SetIconVisible(bool visible) override;

				bool GetTitleBar() override;

				void SetTitleBar(bool visible) override;

				bool GetTopMost() override;

				void SetTopMost(bool topMost) override;

				void SupressAlt() override;

				bool InstallListener(INativeWindowListener *listener) override;

				bool UninstallListener(INativeWindowListener *listener) override;

				void RedrawContent() override;

                bool IsActivelyRefreshing() override;

                NativeSize GetRenderingOffset() override;

                bool IsRenderingAsActivated() override;

            public:

			};

		}
	}
}


#endif //GGAC_GGACWINDOW_H
