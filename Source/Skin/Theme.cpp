//
// Created by roodkcab on 1/13/23.
//

#include "Theme.h"

namespace gtkskin
{
    struct Theme_Initialize
    {
        ::darkskin::ThemeConstructor* __vwsnthis_0;

        Theme_Initialize(::darkskin::ThemeConstructor* __vwsnctorthis_0)
                :__vwsnthis_0(::vl::__vwsn::This(__vwsnctorthis_0))
        {
        }

        ::vl::presentation::templates::GuiWindowTemplate* operator()(const ::vl::reflection::description::Value& __vwsn_viewModel_) const
        {
            return static_cast<::vl::presentation::templates::GuiWindowTemplate*>(new WindowTemplate());
        }
    };

    WindowTemplateConstructor::WindowTemplateConstructor()
            : self(static_cast<WindowTemplate*>(nullptr))
            , __vwsn_precompile_0(::vl::Ptr<::vl::presentation::elements::GuiSolidBackgroundElement>())
    {
    }

    void WindowTemplateConstructor::__vwsn_gtkskin_WindowTemplate_Initialize(::gtkskin::WindowTemplate* __vwsn_this_)
    {
        (this->self = __vwsn_this_);
        {
            ::vl::__vwsn::This(this->self)->SetTitleBarOption(::vl::presentation::templates::BoolOption::AlwaysTrue);
        }
        {
            ::vl::__vwsn::This(this->self)->SetIconVisibleOption(::vl::presentation::templates::BoolOption::AlwaysTrue);
        }
        {
            ::vl::__vwsn::This(this->self)->SetSizeBoxOption(::vl::presentation::templates::BoolOption::AlwaysTrue);
        }
        {
            ::vl::__vwsn::This(this->self)->SetBorderOption(::vl::presentation::templates::BoolOption::AlwaysFalse);
        }
        {
            ::vl::__vwsn::This(this->self)->SetMinimizedBoxOption(::vl::presentation::templates::BoolOption::AlwaysTrue);
        }
        {
            ::vl::__vwsn::This(this->self)->SetMaximizedBoxOption(::vl::presentation::templates::BoolOption::AlwaysTrue);
        }
        {
            ::vl::__vwsn::This(this->self)->SetCustomFrameEnabled(true);
        }
        {
            ::vl::__vwsn::This(this->self)->SetMinSizeLimitation(::vl::presentation::compositions::GuiGraphicsComposition::MinSizeLimitation::LimitToElementAndChildren);
        }
        (this->__vwsn_precompile_0 = ::vl::Ptr<::vl::presentation::elements::GuiSolidBackgroundElement>(::vl::reflection::description::Element_Constructor<::vl::presentation::elements::GuiSolidBackgroundElement>()));
        {
            ::vl::__vwsn::This(this->__vwsn_precompile_0.Obj())->SetColor(::vl::__vwsn::Parse<::vl::presentation::Color>(::vl::WString::Unmanaged(L"#2D2D30")));
        }
        {
            ::vl::__vwsn::This(this->self)->SetOwnedElement(::vl::Ptr<::vl::presentation::elements::IGuiGraphicsElement>(this->__vwsn_precompile_0));
        }
    }

    WindowTemplate::WindowTemplate()
    {
        ::vl::__vwsn::This(this)->__vwsn_gtkskin_WindowTemplate_Initialize(this);
    }

    WindowTemplate::~WindowTemplate()
    {
        this->FinalizeInstanceRecursively(static_cast<::vl::presentation::templates::GuiTemplate*>(this));
    }

    Theme::Theme()
    {
        (::vl::__vwsn::This(this->__vwsn_precompile_0)->Window = vl::Func(Theme_Initialize(this)));
    }

    Theme::~Theme()
    {
    }
}