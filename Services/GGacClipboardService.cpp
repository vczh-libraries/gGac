//
// Created by css on 6/27/21.
//

#include "GGacClipboardService.h"

vl::Ptr<vl::presentation::INativeClipboardReader> vl::presentation::gtk::GGacClipboardService::ReadClipboard() {
	return Ptr<INativeClipboardReader>();
}

vl::Ptr<vl::presentation::INativeClipboardWriter> vl::presentation::gtk::GGacClipboardService::WriteClipboard() {
	return Ptr<INativeClipboardWriter>();
}
