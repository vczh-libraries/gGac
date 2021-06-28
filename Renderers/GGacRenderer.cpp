//
// Created by css on 6/27/21.
//

#include "GGacRenderer.h"

namespace vl {

	namespace presentation {

		namespace elements {

			namespace gtk {

				inline cairo_t* GetCurrentGGacContextFromRenderTarget() {
					return (cairo_t*)(GetCurrentRenderTarget()->GetGGacContext());
				}

			}

		}

	}

}