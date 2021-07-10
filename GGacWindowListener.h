//
// Created by css on 7/2/21.
//

#ifndef GGAC_GGACWINDOWLISTENER_H
#define GGAC_GGACWINDOWLISTENER_H

#include <GacUI.h>
#include "GGacView.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacWindowListener : public Object, public INativeWindowListener
			{
			protected:
				INativeWindow* 	window;
				Ptr<GGacView> 	view;
				NativeSize    	previousSize;
				bool          	rendering = false;
				bool          	movedWhileRendering = false;

				void RebuildLayer(NativeSize size);

			public:
				GGacWindowListener(INativeWindow *window);
				virtual ~GGacWindowListener();
				Ptr<GGacView> GetGGacView() const;
				void StartRendering();
				void StopRendering();
				void ResizeRenderTarget();
				void RecreateRenderTarget();
				bool RetrieveAndResetMovedWhileRendering();

				///
				void Moved() override;
				void LeftButtonUp(const NativeWindowMouseInfo &info) override;

				/*HitTestResult HitTest(NativePoint location) override;

				void Moving(NativeRect &bounds, bool fixSizeOnly) override;


				void DpiChanged() override;

				void Enabled() override;

				void Disabled() override;

				void GotFocus() override;

				void LostFocus() override;

				void Activated() override;

				void Deactivated() override;

				void Opened() override;

				void Closing(bool &cancel) override;

				void Closed() override;

				void Paint() override;

				void Destroying() override;

				void Destroyed() override;

				void LeftButtonDown(const NativeWindowMouseInfo &info) override;

				void LeftButtonUp(const NativeWindowMouseInfo &info) override;

				void LeftButtonDoubleClick(const NativeWindowMouseInfo &info) override;

				void RightButtonDown(const NativeWindowMouseInfo &info) override;

				void RightButtonUp(const NativeWindowMouseInfo &info) override;

				void RightButtonDoubleClick(const NativeWindowMouseInfo &info) override;

				void MiddleButtonDown(const NativeWindowMouseInfo &info) override;

				void MiddleButtonUp(const NativeWindowMouseInfo &info) override;

				void MiddleButtonDoubleClick(const NativeWindowMouseInfo &info) override;

				void HorizontalWheel(const NativeWindowMouseInfo &info) override;

				void VerticalWheel(const NativeWindowMouseInfo &info) override;

				void MouseMoving(const NativeWindowMouseInfo &info) override;

				void MouseEntered() override;

				void MouseLeaved() override;

				void KeyDown(const NativeWindowKeyInfo &info) override;

				void KeyUp(const NativeWindowKeyInfo &info) override;

				void SysKeyDown(const NativeWindowKeyInfo &info) override;

				void SysKeyUp(const NativeWindowKeyInfo &info) override;

				void Char(const NativeWindowCharInfo &info) override;*/

			};

		}

	}

}


#endif //GGAC_GGACWINDOWLISTENER_H
