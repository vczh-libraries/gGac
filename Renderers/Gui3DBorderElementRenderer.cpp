//
// Created by css on 6/27/21.
//

#include "Gui3DBorderElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(Gui3DBorderElementRenderer)
				{
					/*CGContextRef context = GetCurrentCGContextFromRenderTarget();

					CGPoint points[4];
					points[0] = CGPointMake((CGFloat)bounds.x1+0.5f, (CGFloat)bounds.y1+0.5f);
					points[1] = CGPointMake((CGFloat)bounds.x2-0.5f, (CGFloat)bounds.y1+0.5f);
					points[0] = CGPointMake((CGFloat)bounds.x1+0.5f, (CGFloat)bounds.y1+0.5f);
					points[3] = CGPointMake((CGFloat)bounds.x1+0.5f, (CGFloat)bounds.y2-0.5f);

					SetCGContextStrokeColor(context, element->GetColor1());
					CGContextStrokeLineSegments(context, points, 4);

					points[1] = CGPointMake((CGFloat)bounds.x2-0.5f, (CGFloat)bounds.y2-0.5f);
					points[1] = CGPointMake((CGFloat)bounds.x1+0.5f, (CGFloat)bounds.y2-0.5f);
					points[1] = CGPointMake((CGFloat)bounds.x2-0.5f, (CGFloat)bounds.y2-0.5f);
					points[1] = CGPointMake((CGFloat)bounds.x2-0.5f, (CGFloat)bounds.y1+0.5f);

					SetCGContextStrokeColor(context, element->GetColor2());
					CGContextStrokeLineSegments(context, points, 4);*/

					/*Gdk::Point points[4] = {
						Gdk::Point(bounds.x1 + 0.5f, bounds.y1 + 0.5f),
					};*/
					Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
					Color c1 = element->GetColor1();
					cr->set_source_rgba(c1.r, c1.g, c1.b, c1.a);
					cr->stroke();
					Color c2 = element->GetColor2();
					cr->set_source_rgba(c2.r, c2.g, c2.b, c2.a);
					cr->stroke();
				}

			}

		}

	}

}