//
// Created by css on 6/28/21.
//

#include "GuiImageFrameElementRenderer.h"
#include "../Services/GGacImageService.h"

namespace vl {

	namespace presentation {

		using namespace gtk;

		namespace elements {

			namespace gtk {

				GuiImageFrameElementRenderer::GuiImageFrameElementRenderer()
				{

				}

				void GuiImageFrameElementRenderer::InitializeInternal()
				{

				}

				void GuiImageFrameElementRenderer::FinalizeInternal()
				{

				}

				void GuiImageFrameElementRenderer::RenderTargetChangedInternal(IGGacRenderTarget* oldRenderTarget, IGGacRenderTarget* newRenderTarget)
				{

				}

				void GuiImageFrameElementRenderer::Render(Rect bounds)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();

					if (element->GetImage())
					{
						GGacImageFrame* frame = static_cast<GGacImageFrame*>(element->GetImage()->GetFrame(element->GetFrameIndex()));
						frame->SetSize(bounds.Width(), bounds.Height());
						Glib::RefPtr<Gdk::Pixbuf> pixbuf = frame->GetPixbuf();
						vint x = 0;
						vint y = 0;
						if (element->GetStretch())
						{
							x = bounds.x1;
							y = bounds.y1;
						}
						else
						{

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
						}

						Gdk::Cairo::set_source_pixbuf(cr, pixbuf, x, y);
						cr->paint();
					}

				}

				void GuiImageFrameElementRenderer::OnElementStateChanged()
				{
					if (element->GetImage())
					{
						INativeImageFrame* frame = element->GetImage()->GetFrame(element->GetFrameIndex());
						minSize = frame->GetSize();
					}
					else
						minSize = Size(0, 0);
				}

			}

		}

	}

}