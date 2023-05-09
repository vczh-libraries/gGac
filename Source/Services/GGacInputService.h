//
// Created by roodkcab on 6/27/21.
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
				int 									usedHotKeys;

				collections::Dictionary<WString, VKEY>  keys;
				collections::Array<WString>             keyNames;

				void onAccelGroupActivate(vint id);

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
				vint RegisterGlobalShortcutKey(bool ctrl, bool shift, bool alt, VKEY code) override;
				bool UnregisterGlobalShortcutKey(vint id) override;

				void InitKeyMapping();
				WString GetKeyNameInternal(VKEY code);
			};

		}

	}

}


#endif //GGAC_GGACINPUTSERVICE_H
