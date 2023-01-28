//
// Created by roodkcab on 6/27/21.
//

#include "GuiSolidLabelElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				GuiSolidLabelElementRenderer::GuiSolidLabelElementRenderer()
				:oldText(L""),
				oldMaxWidth(-1)
				{
				}

				GuiSolidLabelElementRenderer::~GuiSolidLabelElementRenderer()
				{
				}

				void GuiSolidLabelElementRenderer::UpdateMinSize()
				{
					if (renderTarget)
					{
						int text_width;
						int text_height;
						if (element->GetWrapLine())
						{
							if (element->GetWrapLineHeightCalculation())
							{
								if (oldMaxWidth == -1 || oldText.Length() == 0)
								{
									layout->set_text(Glib::ustring::format(L""));
								}
								else
								{
									layout->set_width(oldMaxWidth * PANGO_SCALE);
									layout->set_text(Glib::ustring::format(oldText.Buffer()));
								}
							}
						}
						else
						{
							layout->set_text(Glib::ustring::format(oldText.Length() == 0 ? L"" : oldText.Buffer()));
						}
						layout->get_pixel_size(text_width, text_height);
						minSize = Size((element->GetEllipse() ? 0 : text_width), text_height);
					}
					else
					{
						minSize = Size(0, 0);
					}
				}

				void GuiSolidLabelElementRenderer::OnElementStateChanged()
				{
					oldText = element->GetText();
					FontProperties font = element->GetFont();
					if (oldFont != font)
					{
						oldFont = font;
						auto gFont = GetGGacResourceManager()->CreateGGacFont(font);
						layout->set_font_description(*gFont.Obj());
					}
					UpdateMinSize();
				}

				void GuiSolidLabelElementRenderer::InitializeInternal()
				{
					auto surface = Cairo::ImageSurface::create(Cairo::FORMAT_ARGB32, 1, 1);
					auto cr = Cairo::Context::create(surface);
					layout = Pango::Layout::create(cr);
				}

				void GuiSolidLabelElementRenderer::FinalizeInternal()
				{

				}

				void GuiSolidLabelElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{
					UpdateMinSize();
				}

				void GuiSolidLabelElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();

					Color c = element->GetColor();
					cr->set_source_rgba(c.r / 255.f, c.g / 255.f, c.b / 255.f, c.a / 255.f);
					cr->fill();

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
					if (oldMaxWidth != bounds.Width())
					{
						oldMaxWidth = bounds.Width();
						UpdateMinSize();
					}

				}

			}

		}

	}

}