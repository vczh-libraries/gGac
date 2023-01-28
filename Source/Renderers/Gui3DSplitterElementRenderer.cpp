//
// Created by roodkcab on 6/28/21.
//

#include "Gui3DSplitterElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(Gui3DSplitterElementRenderer)
				{
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
                    Point p11, p12, p21, p22;
                    switch(element->GetDirection())
                    {
                        case Gui3DSplitterElement::Horizontal:
                        {
                            vint y=bounds.y1+bounds.Height()/2-1;
                            p11=Point(bounds.x1, y);
                            p12=Point(bounds.x2, y);
                            p21=Point(bounds.x1, y+1);
                            p22=Point(bounds.x2, y+1);
                            break;
                        }
                        case Gui3DSplitterElement::Vertical:
                        {
                            vint x=bounds.x1+bounds.Width()/2-1;
                            p11=Point(x, bounds.y1);
                            p12=Point(x, bounds.y2);
                            p21=Point(x+1, bounds.y1);
                            p22=Point(x+1, bounds.y2);
                            break;
                        }
                    }
					Color c1 = element->GetColor1();
                    if (c1.a > 0)
                    {
                        cr->set_source_rgba(c1.r/255.0, c1.g/255.0, c1.b/255.0, c1.a/255.0);
                        cr->move_to(p11.x, p11.y);
                        cr->line_to(p12.x, p12.y);
                        cr->stroke();
                    }
					Color c2 = element->GetColor2();
                    if (c2.a > 0)
                    {
                        cr->set_source_rgba(c2.r/255.0, c2.g/255.0, c2.b/255.0, c2.a/255.0);
                        cr->move_to(p21.x, p21.y);
                        cr->line_to(p22.x, p22.y);
                        cr->stroke();
                    }
				}

			}

		}

	}

}