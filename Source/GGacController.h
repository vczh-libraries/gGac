//
// Created by roodkcab on 6/27/21.
//

#ifndef GGAC_GGACCONTROLLER_H
#define GGAC_GGACCONTROLLER_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			extern INativeController*   GetGGacController();
			extern void                 DestroyGGacController(INativeController* controller);

		}

	}

}

#endif //GGAC_GGACCONTROLLER_H