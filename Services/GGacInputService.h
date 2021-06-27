//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACINPUTSERVICE_H
#define GGAC_GGACINPUTSERVICE_H

#include "GacUI.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacInputService : public Object, public INativeInputService
			{
			public:
				typedef void (*TimerFunc)();

				GGacInputService(TimerFunc timer);
				void StartTimer() override;
				void StopTimer() override;
				bool IsTimerEnabled() override;
				bool IsKeyPressing(VKEY code) override;
				bool IsKeyToggled(VKEY code) override;
				WString GetKeyName(VKEY code) override;
				VKEY GetKey(const WString &name) override;
			};

		}

	}

}


#endif //GGAC_GGACINPUTSERVICE_H
