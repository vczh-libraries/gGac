//
// Created by roodkcab on 6/28/21.
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

						Rect destination;
						if (element->GetStretch())
						{
							destination = Rect(bounds.x1, bounds.y1, bounds.x2, bounds.y2);
						}
						else
						{
							vint x;
							vint y;
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
							destination = Rect(x, y, minSize.x + x, minSize.y + y);
						}

                        //TODO: gif
                        /*if (element->GetImage()->GetFormat()==INativeImage::Gif &&  element->GetFrameIndex()>0)
                        {
                            vint max=element->GetFrameIndex();
                            for(vint i=0;i<=max;i++)
                            {
                                GGacImageFrame* frame = static_cast<GGacImageFrame*>(element->GetImage()->GetFrame(i));
                                frame->SetSize(destination.Width(), destination.Height());
                                Glib::RefPtr<Gdk::Pixbuf> pixbuf = frame->GetPixbuf();
                                Gdk::Cairo::set_source_pixbuf(cr, pixbuf, destination.x1, destination.y1);
                                cr->paint();
                            }
                        }
                        else*/
                        {
                            GGacImageFrame* frame = static_cast<GGacImageFrame*>(element->GetImage()->GetFrame(element->GetFrameIndex()));
                            frame->SetEnabled(element->GetEnabled());
                            frame->SetSize(destination.Width(), destination.Height());
                            Glib::RefPtr<Gdk::Pixbuf> pixbuf = frame->GetPixbuf();
                            Gdk::Cairo::set_source_pixbuf(cr, pixbuf, destination.x1, destination.y1);
                            cr->paint();
                        }
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