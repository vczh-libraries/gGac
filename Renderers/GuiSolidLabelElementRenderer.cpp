//
// Created by css on 6/27/21.
//

#include "GuiSolidLabelElementRenderer.h"
#include <gtkmm.h>

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiSolidLabelElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();

					/*Pango::FontDescription font;
					font.set_family("Monospace");
					//font.set_stretch(Pango::STRETCH_NORMAL);
					font.set_size(30 * PANGO_SCALE);
					auto layout = create_pango_layout(Glib::ustring::format(element->GetText().Buffer()));
					layout->set_font_description(font);
					layout->set_width(static_cast<int>(bounds.Width() * Pango::SCALE));

					int text_width;
					int text_height;
					layout->get_pixel_size(text_width, text_height);
					cr->move_to((bounds.Width()-text_width)/2, (bounds.Height()-text_height)/2);
					layout->show_in_cairo_context(cr);*/
				}

			}

		}

	}

}