//
// Created by roodkcab on 6/28/21.
//

#include "GuiInnerShadowElementRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				IMPLEMENT_ELEMENT_RENDERER(GuiInnerShadowElementRenderer)
				{
                    Cairo::RefPtr<Cairo::Context> cr = GetCurrentGGacContextFromRenderTarget();
                    vint width = bounds.Width();
                    vint height = bounds.Height();
                    vint radius = element->GetThickness();
                    vint bW = width - 2 * radius;
                    vint bH = height - 2 * radius;
                    if (bW > 0 && bH > 0)
                    {
                        auto corner_tl = collections::Pair<vint, vint>(bounds.x1 + radius, bounds.y1 + radius);
                        auto corner_tr = collections::Pair<vint, vint>(bounds.x2 - radius, bounds.y1 + radius);
                        auto corner_bl = collections::Pair<vint, vint>(bounds.x1 + radius, bounds.y2 - radius);
                        auto corner_br = collections::Pair<vint, vint>(bounds.x2 - radius, bounds.y2 - radius);
                        auto corner_points = collections::Array<collections::Pair<vint, vint>>(4);
                        corner_points[0] = corner_tl;
                        corner_points[1] = corner_tr;
                        corner_points[2] = corner_br;
                        corner_points[3] = corner_bl;

                        vint i = 0;
                        for (auto point : corner_points)
                        {
                            auto rg = Cairo::RadialGradient::create(point.key, point.value, 0, point.key, point.value, radius);
                            rg->add_color_stop_rgba(0.0, 0.1, 0.1, 0.1, 0.9);
                            rg->add_color_stop_rgba(1.0, 1.0, 1.0, 1.0, 0.9);
                            cr->move_to(point.key, point.value);
                            switch (i)
                            {
                                case 0:
                                    cr->rectangle(point.key - radius, point.value - radius, radius, radius);
                                    break;
                                case 1:
                                    cr->rectangle(point.key, point.value - radius, radius, radius);
                                    break;
                                case 2:
                                    cr->rectangle(point.key, point.value, radius, radius);
                                    break;
                                case 3:
                                    cr->rectangle(point.key - radius, point.value, radius, radius);
                                    break;
                            }
                            cr->set_source(rg);
                            cr->fill();
                            i++;
                        }

                        auto lg_left = Cairo::LinearGradient::create(bounds.x1 + radius, bounds.y1 + radius, bounds.x1, bounds.y1 + radius);
                        lg_left->add_color_stop_rgba(0.0, 0.1, 0.1, 0.1, 0.9);
                        lg_left->add_color_stop_rgba(1.0, 1.0, 1.0, 1.0, 0.9);
                        cr->rectangle(bounds.x1, bounds.y1 + radius, radius, height - 2 * radius);
                        cr->set_source(lg_left);
                        cr->fill();

                        auto lg_top = Cairo::LinearGradient::create(bounds.x1 + radius, bounds.y1 + radius, bounds.x1 + radius, bounds.y1);
                        lg_top->add_color_stop_rgba(0.0, 0.1, 0.1, 0.1, 0.9);
                        lg_top->add_color_stop_rgba(1.0, 1.0, 1.0, 1.0, 0.9);
                        cr->rectangle(bounds.x1 + radius, bounds.y1, width - 2 * radius, radius);
                        cr->set_source(lg_top);
                        cr->fill();

                        auto lg_right = Cairo::LinearGradient::create(bounds.x2 - radius, bounds.y1 + radius, bounds.x2, bounds.y1 + radius);
                        lg_right->add_color_stop_rgba(0.0, 0.1, 0.1, 0.1, 0.9);
                        lg_right->add_color_stop_rgba(1.0, 1.0, 1.0, 1.0, 0.9);
                        cr->rectangle(bounds.x2 - radius, bounds.y1 + radius, radius, height - 2 * radius);
                        cr->set_source(lg_right);
                        cr->fill();

                        auto lg_bottom = Cairo::LinearGradient::create(bounds.x1 + radius, bounds.y2 - radius, bounds.x1 + radius, bounds.y2);
                        lg_bottom->add_color_stop_rgba(0.0, 0.1, 0.1, 0.1, 0.9);
                        lg_bottom->add_color_stop_rgba(1.0, 1.0, 1.0, 1.0, 0.9);
                        cr->rectangle(bounds.x1 + radius, bounds.y2 - radius, width - 2 * radius, radius);
                        cr->set_source(lg_bottom);
                        cr->fill();

                    }
				}

			}

		}

	}

}