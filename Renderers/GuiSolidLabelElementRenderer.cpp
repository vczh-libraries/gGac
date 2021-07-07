//
// Created by css on 6/27/21.
//

#include "GuiSolidLabelElementRenderer.h"
#include <gtkmm.h>

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				GuiSolidLabelElementRenderer::GuiSolidLabelElementRenderer()
				{

				}

				void GuiSolidLabelElementRenderer::CreateFont()
				{
					FontProperties font = element->GetFont();
					Pango::FontDescription gFont;
					gFont.set_family("Monospace");
					gFont.set_size(font.size * PANGO_SCALE);
					//gFont.set_stretch(Pango::STRETCH_NORMAL);

					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					layout = Pango::Layout::create(cr);
					layout->set_font_description(gFont);
					layout->set_text(Glib::ustring::format(element->GetText().Buffer()));
				}

				void GuiSolidLabelElementRenderer::UpdateMinSize()
				{
					int text_width;
					int text_height;
					layout->get_pixel_size(text_width, text_height);
					minSize = Size(text_width, text_height);
				}

				void GuiSolidLabelElementRenderer::OnElementStateChanged()
				{

				}

				void GuiSolidLabelElementRenderer::InitializeInternal()
				{

				}

				void GuiSolidLabelElementRenderer::FinalizeInternal()
				{

				}

				void GuiSolidLabelElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{
				}

				void GuiSolidLabelElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					CreateFont();
					UpdateMinSize();
					//layout->set_width(static_cast<long>(bounds.Width() * Pango::SCALE));

					vint x = 0;
					vint y = 0;

					switch(element->GetVerticalAlignment())
					{
						case Alignment::Top:
							y = bounds.Top();
							break;

						case Alignment::Center:
							y = bounds.Top() + (bounds.Height() - minSize.y) / 2;
							break;

						case Alignment::Bottom:
							y = bounds.Bottom() - minSize.y;
							break;
					}

					switch(element->GetHorizontalAlignment())
					{
						case Alignment::Left:
							x = bounds.Left();
							break;

						case Alignment::Center:
							x = bounds.Left() + (bounds.Width() - minSize.x) / 2;
							break;

						case Alignment::Right:
							x = bounds.Right() - minSize.x;
							break;
					}

					cr->move_to(x, y);
					layout->show_in_cairo_context(cr);
				}

			}

		}

	}

}