//
// Created by css on 7/3/21.
//

#include "GGacView.h"
#include "GGacWindow.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacView::GGacView(INativeWindow* _window)
			:window(_window)
			{
				signal_draw().connect(sigc::mem_fun(*this, &GGacView::onDraw));
				signal_configure_event().connect(sigc::mem_fun(*this, &GGacView::onConfigure));
			}

			GGacView::~GGacView()
			{
			}

			bool GGacView::onConfigure(GdkEventConfigure* event)
			{
				surface = this->get_window()->create_similar_surface(static_cast<Cairo::Content>(CAIRO_CONTENT_COLOR), this->get_width(), this->get_height());
			}

			bool GGacView::onDraw(const ::Cairo::RefPtr<::Cairo::Context> &cr)
			{
				cr->set_source(surface, this->get_width(), this->get_height());
				cr->paint();
			}

			::Cairo::RefPtr<::Cairo::Context> GGacView::GetGGacContext()
			{
				return Cairo::Context::create(surface);
			}

		}

	}

}