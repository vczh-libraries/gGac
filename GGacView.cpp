//
// Created by css on 7/3/21.
//

#include "GGacView.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacView::GGacView(INativeWindow* _window)
			:window(_window)
			{
				signal_draw().connect(sigc::mem_fun(*this, &GGacView::onDraw));
			}

			GGacView::~GGacView()
			{

			}

			bool GGacView::onDraw(const ::Cairo::RefPtr<::Cairo::Context> &cr)
			{
			}

			::Cairo::RefPtr<::Cairo::Context> GGacView::GetContext()
			{
				//todo return drawing area cario context;
			}

		}

	}

}