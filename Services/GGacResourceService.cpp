//
// Created by css on 6/27/21.
//

#include "GGacResourceService.h"

vl::presentation::INativeCursor *
vl::presentation::gtk::GGacResourceService::GetSystemCursor(vl::presentation::INativeCursor::SystemCursorType type) {
	return nullptr;
}

vl::presentation::INativeCursor *vl::presentation::gtk::GGacResourceService::GetDefaultSystemCursor() {
	return nullptr;
}

vl::presentation::FontProperties vl::presentation::gtk::GGacResourceService::GetDefaultFont() {
	return FontProperties();
}

void vl::presentation::gtk::GGacResourceService::SetDefaultFont(const vl::presentation::FontProperties &value) {

}

bool vl::presentation::gtk::GGacCursor::IsSystemCursor() {
	return false;
}

vl::presentation::INativeCursor::SystemCursorType vl::presentation::gtk::GGacCursor::GetSystemCursorType() {
	return Hand;
}
