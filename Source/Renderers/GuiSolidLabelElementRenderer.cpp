//
// Created by css on 6/27/21.
//

#include "GuiSolidLabelElementRenderer.h"
#include <gtkmm.h>
#include <iostream>

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

				void GuiSolidLabelElementRenderer::CreateFont()
				{
					oldFont = element->GetFont();
					IGGacResourceManager* rm = GetGGacResourceManager();
					auto gFont = rm->CreateGGacFont(oldFont);
					layout->set_font_description(*gFont.Obj());
				}

				void GuiSolidLabelElementRenderer::UpdateMinSize()
				{
					if (oldFont.fontFamily == L"Webdings" && oldText.Length() > 0)
					{
						// map webdings to unicode
						wchar_t* wsStr = new wchar_t[oldText.Length()];
						for (vint i = 0; i < oldText.Length(); ++i)
						{
							switch (oldText[i])
							{
							case L'a': wsStr[i] = 0x00002713; break;
							case L'r': wsStr[i] = 0x00002715; break;
							case L'0': wsStr[i] = 0x0000035F; break;
							case L'1': wsStr[i] = 0x0000002B; break;
							case L'2': wsStr[i] = 0x0000002B; break;
								// more todo
							default: wsStr[i] = oldText[i];
							}
						}

						layout->set_text(Glib::ustring::format(wsStr));
						delete[] wsStr;
					} 
					else
					{
						layout->set_text(Glib::ustring::format(oldText.Buffer()));
					}
					int text_width;
					int text_height;
					layout->get_pixel_size(text_width, text_height);
					minSize = Size(text_width, text_height);
				}

				void GuiSolidLabelElementRenderer::OnElementStateChanged()
				{
					oldText = element->GetText();
					FontProperties font = element->GetFont();
					if (oldFont != font)
					{
						CreateFont();
						UpdateMinSize();
					}
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
					CreateFont();
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
				}

			}

		}

	}

}