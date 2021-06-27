//
// Created by css on 6/27/21.
//

#include "GGacAsyncService.h"

bool vl::presentation::gtk::GGacAsyncService::IsInMainThread(vl::presentation::INativeWindow *window) {
	return false;
}

void vl::presentation::gtk::GGacAsyncService::InvokeAsync(const vl::Func<void()> &proc) {

}

void vl::presentation::gtk::GGacAsyncService::InvokeInMainThread(vl::presentation::INativeWindow *window,
																 const vl::Func<void()> &proc) {

}

bool vl::presentation::gtk::GGacAsyncService::InvokeInMainThreadAndWait(vl::presentation::INativeWindow *window,
																		const vl::Func<void()> &proc,
																		vl::vint milliseconds) {
	return false;
}

vl::Ptr<vl::presentation::INativeDelay>
vl::presentation::gtk::GGacAsyncService::DelayExecute(const vl::Func<void()> &proc, vl::vint milliseconds) {
	return Ptr<INativeDelay>();
}

vl::Ptr<vl::presentation::INativeDelay>
vl::presentation::gtk::GGacAsyncService::DelayExecuteInMainThread(const vl::Func<void()> &proc, vl::vint milliseconds) {
	return Ptr<INativeDelay>();
}
