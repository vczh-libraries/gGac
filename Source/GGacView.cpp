//
// Created by css on 7/3/21.
//

#include "GGacView.h"
#include "GGacWindow.h"
#include "Services/GGacCallbackService.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacView::GGacView(INativeWindow* _window)
			:window(_window)
			{
				signal_configure_event().connect(sigc::mem_fun(*this, &GGacView::onConfigure));
				signal_draw().connect(sigc::mem_fun(*this, &GGacView::onDraw));
				signal_event().connect(sigc::mem_fun(*this, &GGacView::onEvent));
				add_events( static_cast<Gdk::EventMask>(
						Gdk::ENTER_NOTIFY_MASK | Gdk::LEAVE_NOTIFY_MASK | Gdk::MOTION_NOTIFY | Gdk::DRAG_MOTION |
						Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::DOUBLE_BUTTON_PRESS |
						Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK
						));
				set_can_focus(true);
			}

			GGacView::~GGacView()
			{
			}

			bool GGacView::onConfigure(GdkEventConfigure* event)
			{
				int width = MAX(1, this->get_width());
				int height = MAX(1, this->get_height());
				surface = this->get_window()->create_similar_surface(static_cast<Cairo::Content>(CAIRO_CONTENT_COLOR), width, height);
				context = Cairo::Context::create(surface);
				needRepaint = true;
			}

			bool GGacView::onDraw(const ::Cairo::RefPtr<::Cairo::Context> &cr)
			{
				if (needRepaint)
				{
					dynamic_cast<GGacCallbackService *>(GetCurrentController()->CallbackService())->InvokeGlobalTimer();
					needRepaint = false;
				}
				cr->set_source(surface, 0, 0);
				cr->paint();
			}

			bool GGacView::onEvent(GdkEvent *gdk_event)
			{
				return dynamic_cast<GGacWindow *>(window)->HandleEventInternal(gdk_event);
			}

			void GGacView::resize(int width, int height)
			{
				//this->set_size_request(width, height);
				needRepaint = true;
			}

			Cairo::RefPtr<::Cairo::Context> GGacView::GetGGacContext()
			{
				return context;
			}

		}

	}

}