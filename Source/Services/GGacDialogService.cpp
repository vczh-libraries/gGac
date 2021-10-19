//
// Created by css on 6/27/21.
//

#include "GGacDialogService.h"

vl::presentation::INativeDialogService::MessageBoxButtonsOutput
vl::presentation::gtk::GGacDialogService::ShowMessageBox(vl::presentation::INativeWindow *window,
														 const vl::WString &text, const vl::WString &title,
														 vl::presentation::INativeDialogService::MessageBoxButtonsInput buttons,
														 vl::presentation::INativeDialogService::MessageBoxDefaultButton defaultButton,
														 vl::presentation::INativeDialogService::MessageBoxIcons icon,
														 vl::presentation::INativeDialogService::MessageBoxModalOptions modal) {
	return SelectNo;
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
