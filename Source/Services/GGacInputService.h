//
// Created by css on 6/27/21.
//

#ifndef GGAC_GGACINPUTSERVICE_H
#define GGAC_GGACINPUTSERVICE_H

#include "GacUI.h"
#include <gtkmm.h>

namespace vl {

	namespace presentation {

		namespace gtk {

			class GGacInputService : public Object, public INativeInputService
			{
			typedef void (*TimerFunc)();

			protected:
				TimerFunc 								timer;
				bool      								isTimerEnabled;

				collections::Dictionary<WString, VKEY>  keys;
				collections::Array<WString>             keyNames;
				wchar_t                                 asciiLowerMap[256];
				wchar_t                                 asciiUpperMap[256];

			public:
				GGacInputService(TimerFunc timer);
				bool StartGDKTimer();

				void StartTimer() override;
				void StopTimer() override;
				bool IsTimerEnabled() override;
				bool IsKeyPressing(VKEY code) override;
				bool IsKeyToggled(VKEY code) override;
				WString GetKeyName(VKEY code) override;
				VKEY GetKey(const WString &name) override;

				void InitKeyMapping();
				bool ConvertToPrintable(NativeWindowCharInfo& info, Gdk::Event* event);

			};

		}

	}

}


#endif //GGAC_GGACINPUTSERVICE_H
