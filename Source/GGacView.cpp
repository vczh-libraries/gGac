//
// Created by css on 7/3/21.
//

#include "GGacView.h"
#include "GGacWindow.h"
#include "Services/GGacCallbackService.h"
#include <gtkmm/eventcontrollerlegacy.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacView::GGacView(INativeWindow* _window)
			:window(_window)
			{
				/*add_events( static_cast<Gdk::Event>(
						Gdk::Event::Type::ENTER_NOTIFY | Gdk::Event::Type::LEAVE_NOTIFY |
						Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::DOUBLE_BUTTON_PRESS
						));*/
				set_can_focus(true);
                set_draw_func(sigc::mem_fun(*this, &GGacView::onDraw));
                signal_resize().connect(sigc::mem_fun(*this, &GGacView::onResize));

                //gtk4 is boring... you have to keep an event controller then get current event from a queue, so disgusting
                auto click = Gtk::GestureClick::create();
                click->set_button(GDK_BUTTON_PRIMARY);
                auto gWindow = dynamic_cast<GGacWindow *>(window);
                click->signal_pressed().connect([=](int , double , double ){ gWindow->HandleEventInternal(click->get_current_event()); });
                click->signal_released().connect([=](int , double , double ){ gWindow->HandleEventInternal(click->get_current_event()); });
                add_controller(click);

                auto motion = Gtk::EventControllerMotion::create();
                motion->signal_enter().connect([=](int, int) { gWindow->HandleEventInternal(motion->get_current_event()); }, true);
                motion->signal_leave().connect([=]{ gWindow->HandleEventInternal(motion->get_current_event()); }, true);
                add_controller(motion);

                auto legacy = Gtk::EventControllerLegacy::create();
                legacy->signal_event().connect(sigc::mem_fun(*this, &GGacView::onEvent), true);
                add_controller(legacy);
			}

			GGacView::~GGacView()
			{
			}

            void GGacView::resize(int width, int height)
            {
                this->set_size_request(width, height);
            }

			void GGacView::onResize(int width, int height)
			{
                auto windowSurface = static_cast<GGacWindow*>(window)->GetNativeWindow()->get_surface();
                surface = windowSurface->create_similar_surface(Cairo::Content::CONTENT_COLOR, width, height);
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

			bool GGacView::onEvent(const Glib::RefPtr<const Gdk::Event>& gdk_event)
			{
				return dynamic_cast<GGacWindow *>(window)->HandleEventInternal(gdk_event);
			}

			Cairo::RefPtr<::Cairo::Context> GGacView::GetGGacContext()
			{
				return context;
			}

		}

	}

}