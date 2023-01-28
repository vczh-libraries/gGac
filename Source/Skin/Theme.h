//
// Created by roodkcab on 1/13/23.
//

#ifndef GGAC_THEME_H
#define GGAC_THEME_H

#include "Skins/DarkSkin/DarkSkin.h"

namespace gtkskin
{
    class WindowTemplateContructor;
    class WindowTemplate;
}

namespace gtkskin
{
    class WindowTemplateConstructor : public ::vl::Object, public ::vl::reflection::Description<WindowTemplateConstructor>
    {
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
        friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<WindowTemplateConstructor>;
#endif
    protected:
        WindowTemplate* self;
        ::vl::Ptr<::vl::presentation::elements::GuiSolidBackgroundElement> __vwsn_precompile_0;
        void __vwsn_gtkskin_WindowTemplate_Initialize(WindowTemplate* __vwsn_this_);
    public:
        WindowTemplateConstructor();
    };

    class WindowTemplate : public ::vl::presentation::templates::GuiWindowTemplate, public ::gtkskin::WindowTemplateConstructor, public ::vl::reflection::Description<WindowTemplate>
    {
        friend class ::gtkskin::WindowTemplateConstructor;
#ifdef VCZH_DESCRIPTABLEOBJECT_WITH_METADATA
        friend struct ::vl::reflection::description::CustomTypeDescriptorSelector<WindowTemplate>;
#endif
    public:
        WindowTemplate();
        ~WindowTemplate();
    };

    class Theme : public darkskin::Theme
    {
    public:
        Theme();
        ~Theme();
    };
}

#endif //GGAC_THEME_H
