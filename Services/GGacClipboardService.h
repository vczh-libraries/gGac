//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACCLIPBOARDSERVICE_H
#define GGAC_GGACCLIPBOARDSERVICE_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacClipboardService : public Object, public INativeClipboardService {
			public:
				Ptr<INativeClipboardReader> ReadClipboard() override;
				Ptr<INativeClipboardWriter> WriteClipboard() override;
			};

		}

	}

}


#endif //GGAC_GGACCLIPBOARDSERVICE_H
