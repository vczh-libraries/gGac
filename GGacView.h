//
// Created by css on 7/3/21.
//

#ifndef GGAC_GGACVIEW_H
#define GGAC_GGACVIEW_H

#include <gtkmm.h>
#include <GacUI.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacView : public Gtk::DrawingArea
			{
			protected:
				INativeWindow *window;

				bool onDraw(const ::Cairo::RefPtr<::Cairo::Context> &cr);

			public:
				GGacView(INativeWindow *window);
				virtual ~GGacView();

				::Cairo::RefPtr<::Cairo::Context> GetContext();
			};

		}

	}

}

#endif //GGAC_GGACVIEW_H