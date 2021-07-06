//
// Created by css on 6/27/21.
//

#include "GuiSolidLabelElementRenderer.h"
#include <gtkmm.h>

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				const Pango::FontDescription& GuiSolidLabelElementRenderer::createFont()
				{
					FontProperties font = element->GetFont();
					Pango::FontDescription* gFont = new Pango::FontDescription();
					gFont->set_family("Monospace");
					gFont->set_size(font.size * PANGO_SCALE);
					//font.set_stretch(Pango::STRETCH_NORMAL);
					return *gFont;
				}

				IMPLEMENT_ELEMENT_RENDERER(GuiSolidLabelElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();

					Pango::FontDescription font = createFont();
					auto layout = Pango::Layout::create(cr);
					layout->set_text(Glib::ustring::format(element->GetText().Buffer()));
					layout->set_font_description(font);
					layout->set_width(static_cast<long>(bounds.Width() * Pango::SCALE));
					layout->show_in_cairo_context(cr);
				}

			}

		}

	}

}