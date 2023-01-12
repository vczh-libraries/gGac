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
	static collections::Dictionary<vl::presentation::INativeDialogService::MessageBoxButtonsInput, Gtk::ButtonsType> types;
	if (types.Count() == 0)
	{
		types.Add(vl::presentation::INativeDialogService::DisplayOK, Gtk::BUTTONS_OK);
		types.Add(vl::presentation::INativeDialogService::DisplayOKCancel, Gtk::BUTTONS_OK_CANCEL);
		types.Add(vl::presentation::INativeDialogService::DisplayYesNo, Gtk::BUTTONS_YES_NO);
		types.Add(vl::presentation::INativeDialogService::DisplayYesNoCancel, Gtk::BUTTONS_YES_NO);
		types.Add(vl::presentation::INativeDialogService::DisplayRetryCancel, Gtk::BUTTONS_OK_CANCEL);
		types.Add(vl::presentation::INativeDialogService::DisplayAbortRetryIgnore, Gtk::BUTTONS_OK_CANCEL);
		types.Add(vl::presentation::INativeDialogService::DisplayCancelTryAgainContinue, Gtk::BUTTONS_OK_CANCEL);
	}
	Gtk::MessageDialog dialog(Glib::ustring::format(title.Buffer()), false, Gtk::MESSAGE_QUESTION, types.Get(buttons), true);
	dialog.set_secondary_text(Glib::ustring::format(text.Buffer()));
	dialog.set_default_response(Gtk::RESPONSE_YES);
	if (dialog.run() == Gtk::RESPONSE_YES) {
		return SelectYes;
	}
	return SelectNo;
}

bool vl::presentation::gtk::GGacDialogService::ShowColorDialog(vl::presentation::INativeWindow *window,
															   vl::presentation::Color &selection, bool selected,
															   vl::presentation::INativeDialogService::ColorDialogCustomColorOptions customColorOptions,
															   vl::presentation::Color *customColors) {
    Gtk::ColorChooserDialog dialog;
    dialog.set_modal(true);
    if (dialog.run() ==  Gtk::RESPONSE_OK)
    {
        Gdk::RGBA rgba = dialog.get_rgba();
        selection.r = rgba.get_red_u();
        selection.g = rgba.get_green_u();
        selection.b = rgba.get_blue_u();
        selection.a = rgba.get_alpha_u();
        return true;
    }
    return false;
}

bool vl::presentation::gtk::GGacDialogService::ShowFontDialog(vl::presentation::INativeWindow *window,
															  vl::presentation::FontProperties &selectionFont,
															  vl::presentation::Color &selectionColor, bool selected,
															  bool showEffect, bool forceFontExist) {
    Gtk::FontChooserDialog dialog;
    dialog.set_modal(true);
    if (dialog.run() == Gtk::RESPONSE_OK)
    {
        auto font = dialog.get_font_desc();
        selectionFont.fontFamily = (wchar_t *) g_convert(font.get_family().c_str(), -1, "wchar_t", "utf-8", NULL, NULL, NULL);
        selectionFont.size = font.get_size() / PANGO_SCALE;
        selectionFont.bold = (font.get_weight() == Pango::WEIGHT_BOLD);
        selectionFont.italic = (font.get_style() != Pango::STYLE_NORMAL);
        return true;
    }
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
	Gtk::FileChooserDialog dialog(Glib::ustring::format(title.Buffer()), Gtk::FileChooserAction::FILE_CHOOSER_ACTION_OPEN);
	//dialog->set_transient_for(dynamic_cast<Gtk::Window*>(window));
	dialog.set_modal(true);

	if (filter.Length() > 0)
	{
		auto filter_text = Gtk::FileFilter::create();
		filter_text->add_mime_type(Glib::ustring::format(filter.Buffer()));
		//dialog.add_filter(filter_text);
	}
	auto filter_any = Gtk::FileFilter::create();
	filter_any->set_name("Any files");
	filter_any->add_pattern("*");
	dialog.add_filter(filter_any);

	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);

	if (dialog.run() ==  Gtk::RESPONSE_OK)
	{
		return true;
	}
	return false;
}
