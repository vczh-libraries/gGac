//
// Created by roodkcab on 6/27/21.
//

#include "Gui3DBorderElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(Gui3DBorderElementRenderer)
				{
                    Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
                    Color c1 = element->GetColor1();
                    if(c1.a>0)
                    {
                        cr->set_source_rgba(c1.r, c1.g, c1.b, c1.a);
                        cr->move_to(bounds.x1, bounds.y1);
                        cr->line_to(bounds.x2, bounds.y1);
                        cr->move_to(bounds.x1, bounds.y1);
                        cr->line_to(bounds.x1, bounds.y2);
                        cr->stroke();
                    }
                    Color c2 = element->GetColor2();
                    if(c2.a>0)
                    {
                        cr->set_source_rgba(c2.r, c2.g, c2.b, c2.a);
                        cr->move_to(bounds.x2-1, bounds.y2-1);
                        cr->line_to(bounds.x1, bounds.y2-1);
                        cr->move_to(bounds.x2-1, bounds.y2-1);
                        cr->line_to(bounds.x2-1, bounds.y1);
                        cr->stroke();
                    }
				}

			}

		}

	}

}