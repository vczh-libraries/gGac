//
// Created by css on 6/27/21.
//

#include "GGacDialogService.h"
#include <gtkmm.h>

vl::presentation::INativeDialogService::MessageBoxButtonsOutput
vl::presentation::gtk::GGacDialogService::ShowMessageBox(vl::presentation::INativeWindow *window,
														 const vl::WString &text, const vl::WString &title,
														 vl::presentation::INativeDialogService::MessageBoxButtonsInput buttons,
														 vl::presentation::INativeDialogService::MessageBoxDefaultButton defaultButton,
														 vl::presentation::INativeDialogService::MessageBoxIcons icon,
														 vl::presentation::INativeDialogService::MessageBoxModalOptions modal) {
	Gtk::MessageDialog dialog(Glib::ustring::format(title.Buffer()), false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO, true);
	dialog.set_secondary_text(Glib::ustring::format(text.Buffer()));
	dialog.set_default_response(Gtk::RESPONSE_YES);
	switch (dialog.run()) {
	case Gtk::RESPONSE_YES:
		return SelectYes;
	case Gtk::RESPONSE_NO:
	case Gtk::RESPONSE_NONE:
	case Gtk::RESPONSE_CLOSE:
		return SelectNo;
	}
}

bool vl::presentation::gtk::GGacDialogService::ShowColorDialog(vl::presentation::INativeWindow *window,
															   vl::presentation::Color &selection, bool selected,
															   vl::presentation::INativeDialogService::ColorDialogCustomColorOptions customColorOptions,
															   vl::presentation::Color *customColors) {
	return false;
}

bool vl::presentation::gtk::GGacDialogService::ShowFontDialog(vl::presentation::INativeWindow *window,
															  vl::presentation::FontProperties &selectionFont,
															  vl::presentation::Color &selectionColor, bool selected,
															  bool showEffect, bool forceFontExist) {
	return false;
}

bool vl::presentation::gtk::GGacDialogService::ShowFileDialog(vl::presentation::INativeWindow *window,
															  vl::collections::List<vl::WString> &selectionFileNames,
															  vl::vint &selectionFilterIndex,
															  vl::presentation::INativeDialogService::FileDialogTypes dialogType,
															  const vl::WString &title,
															  const vl::WString &initialFileName,
															  const vl::WString &initialDirectory,
															  const vl::WString &defaultExtension,
															  const vl::WString &filter,
															  vl::presentation::INativeDialogService::FileDialogOptions options) {
	return false;
}
