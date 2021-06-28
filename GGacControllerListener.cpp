//
// Created by css on 6/27/21.
//

#include "GGacControllerListener.h"

void vl::presentation::gtk::GGacControllerListener::GlobalTimer() {
	INativeControllerListener::GlobalTimer();
}

void vl::presentation::gtk::GGacControllerListener::ClipboardUpdated() {
	INativeControllerListener::ClipboardUpdated();
}

void vl::presentation::gtk::GGacControllerListener::NativeWindowCreated(vl::presentation::INativeWindow *window) {
	INativeControllerListener::NativeWindowCreated(window);
}

void vl::presentation::gtk::GGacControllerListener::NativeWindowDestroying(vl::presentation::INativeWindow *window) {
	INativeControllerListener::NativeWindowDestroying(window);
}
