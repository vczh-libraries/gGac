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
				//signal_configure_event().connect(sigc::mem_fun(*this, &GGacView::onConfigure));
				//signal_draw().connect(sigc::mem_fun(*this, &GGacView::onDraw));
				//signal_event().connect(sigc::mem_fun(*this, &GGacView::onEvent));
				/*add_events( static_cast<Gdk::Event>(
						Gdk::Event::Type::ENTER_NOTIFY | Gdk::Event::Type::LEAVE_NOTIFY |
						Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::DOUBLE_BUTTON_PRESS
						));*/
				set_can_focus(true);
                set_draw_func(sigc::mem_fun(*this, &GGacView::onDraw));
                signal_resize().connect(sigc::mem_fun(*this, &GGacView::onResize));

                //auto controller = gtk_event_controller_key_new();
                /*GtkWidget *area = gtk_drawing_area_new();
                gtk_drawing_area_set_content_width(GTK_DRAWING_AREA (area), 100);
                gtk_drawing_area_set_content_height(GTK_DRAWING_AREA (area), 100);*/
			}

			GGacView::~GGacView()
			{
			}

			void GGacView::onResize(int width, int height)
			{
                auto window = static_cast<GGacWindow*>(this->window);
                surface = window->GetNativeWindow()->get_surface()->create_similar_surface(Cairo::Content::CONTENT_COLOR, width, height);
                context = Cairo::Context::create(surface);
                window->RedrawContent();
                needRepaint = true;
			}

			void GGacView::onDraw(const ::Cairo::RefPtr<::Cairo::Context> &cr, int width, int height)
			{
				if (needRepaint)
				{
					dynamic_cast<GGacCallbackService *>(GetCurrentController()->CallbackService())->InvokeGlobalTimer();
					needRepaint = false;
				}
				cr->set_source(surface, 0, 0);
				cr->paint();
			}

			bool GGacView::onEvent(Gdk::Event *gdk_event)
			{
                return true;
				//return dynamic_cast<GGacWindow *>(window)->HandleEventInternal(gdk_event);
			}

			void GGacView::resize(int width, int height)
			{
				this->set_size_request(width, height);
                needRepaint = true;
			}

			Cairo::RefPtr<::Cairo::Context> GGacView::GetGGacContext()
			{
				return context;
			}

		}

	}

}