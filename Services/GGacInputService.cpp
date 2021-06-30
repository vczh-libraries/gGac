//
// Created by css on 6/27/21.
//

#include "GGacInputService.h"

namespace vl {

	namespace presentation {

		namespace gtk {

			GGacInputService::GGacInputService(TimerFunc timer)
			{

			}

			void GGacInputService::StartTimer() {

			}

			void GGacInputService::StopTimer() {

			}

			bool GGacInputService::IsTimerEnabled() {
				return false;
			}

			bool GGacInputService::IsKeyPressing(vl::presentation::VKEY code) {
				return false;
			}

			bool GGacInputService::IsKeyToggled(vl::presentation::VKEY code) {
				return false;
			}

			vl::WString GGacInputService::GetKeyName(vl::presentation::VKEY code) {
				return vl::WString();
			}

			vl::presentation::VKEY GGacInputService::GetKey(const vl::WString &name) {
				return VKEY::_RCONTROL;
			}
		}

	}

}