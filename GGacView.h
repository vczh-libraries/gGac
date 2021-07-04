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
			public:
				GGacView(INativeWindow *window);
				virtual ~GGacView();

				void resize(int width, int height);
				Cairo::RefPtr<::Cairo::Context> GetGGacContext();

			protected:
				INativeWindow *window;
				Cairo::RefPtr<Cairo::Surface> surface;
				Cairo::RefPtr<Cairo::Context> context;

				bool onDraw(const ::Cairo::RefPtr<::Cairo::Context> &cr);
				bool onConfigure(GdkEventConfigure* event);
			};

		}

	}

}

#endif //GGAC_GGACVIEW_H