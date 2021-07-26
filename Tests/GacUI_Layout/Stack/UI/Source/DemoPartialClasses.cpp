﻿/***********************************************************************
!!!!!! DO NOT MODIFY !!!!!!

GacGen.exe Resource.xml

This file is generated by Workflow compiler
https://github.com/vczh-libraries
***********************************************************************/

#include "Demo.h"
/* CodePack:BeginIgnore() */
#ifndef VCZH_DEBUG_NO_REFLECTION
/* CodePack:ConditionOff(VCZH_DEBUG_NO_REFLECTION, DemoReflection.h) */
#include "DemoReflection.h"
#endif
/* CodePack:EndIgnore() */

#if defined( _MSC_VER)
#pragma warning(push)
#pragma warning(disable:4250)
#elif defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses-equality"
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wparentheses-equality"
#endif

#define GLOBAL_SYMBOL ::vl_workflow_global::Demo::
#define GLOBAL_NAME ::vl_workflow_global::Demo::Instance().
#define GLOBAL_OBJ &::vl_workflow_global::Demo::Instance()

/***********************************************************************
Global Variables
***********************************************************************/

BEGIN_GLOBAL_STORAGE_CLASS(vl_workflow_global_Demo)
	vl_workflow_global::Demo instance;
	INITIALIZE_GLOBAL_STORAGE_CLASS
	FINALIZE_GLOBAL_STORAGE_CLASS
END_GLOBAL_STORAGE_CLASS(vl_workflow_global_Demo)

namespace vl_workflow_global
{
/***********************************************************************
Global Functions
***********************************************************************/

	Demo& Demo::Instance()
	{
		return Getvl_workflow_global_Demo().instance;
	}

/***********************************************************************
Closures
***********************************************************************/

	//-------------------------------------------------------------------

	__vwsnf1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::__vwsnf1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0)
		:__vwsnthis_0(::vl::__vwsn::This(__vwsnctorthis_0))
	{
	}

	void __vwsnf1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const
	{
		auto radioButton = ::vl::__vwsn::Ensure(::vl::__vwsn::RawPtrCast<::vl::presentation::controls::GuiSelectableButton>(::vl::__vwsn::This(sender)->GetRelatedControl()));
		if (::vl::__vwsn::This(radioButton)->GetSelected())
		{
			::vl::__vwsn::This(__vwsnthis_0->stackLayout)->SetDirection(((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"Horizontal", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::Horizontal : ((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"Vertical", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::Vertical : ((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"ReversedHorizontal", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::ReversedHorizontal : ::vl::presentation::compositions::GuiStackComposition::Direction::ReversedVertical))));
		}
	}

	//-------------------------------------------------------------------

	__vwsnf2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::__vwsnf2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0)
		:__vwsnthis_0(::vl::__vwsn::This(__vwsnctorthis_0))
	{
	}

	void __vwsnf2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const
	{
		auto radioButton = ::vl::__vwsn::Ensure(::vl::__vwsn::RawPtrCast<::vl::presentation::controls::GuiSelectableButton>(::vl::__vwsn::This(sender)->GetRelatedControl()));
		if (::vl::__vwsn::This(radioButton)->GetSelected())
		{
			::vl::__vwsn::This(__vwsnthis_0->stackLayout)->SetDirection(((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"Horizontal", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::Horizontal : ((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"Vertical", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::Vertical : ((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"ReversedHorizontal", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::ReversedHorizontal : ::vl::presentation::compositions::GuiStackComposition::Direction::ReversedVertical))));
		}
	}

	//-------------------------------------------------------------------

	__vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::__vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0)
		:__vwsnthis_0(::vl::__vwsn::This(__vwsnctorthis_0))
	{
	}

	void __vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const
	{
		auto radioButton = ::vl::__vwsn::Ensure(::vl::__vwsn::RawPtrCast<::vl::presentation::controls::GuiSelectableButton>(::vl::__vwsn::This(sender)->GetRelatedControl()));
		if (::vl::__vwsn::This(radioButton)->GetSelected())
		{
			::vl::__vwsn::This(__vwsnthis_0->stackLayout)->SetDirection(((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"Horizontal", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::Horizontal : ((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"Vertical", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::Vertical : ((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"ReversedHorizontal", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::ReversedHorizontal : ::vl::presentation::compositions::GuiStackComposition::Direction::ReversedVertical))));
		}
	}

	//-------------------------------------------------------------------

	__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0)
		:__vwsnthis_0(::vl::__vwsn::This(__vwsnctorthis_0))
	{
	}

	void __vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const
	{
		auto radioButton = ::vl::__vwsn::Ensure(::vl::__vwsn::RawPtrCast<::vl::presentation::controls::GuiSelectableButton>(::vl::__vwsn::This(sender)->GetRelatedControl()));
		if (::vl::__vwsn::This(radioButton)->GetSelected())
		{
			::vl::__vwsn::This(__vwsnthis_0->stackLayout)->SetDirection(((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"Horizontal", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::Horizontal : ((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"Vertical", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::Vertical : ((::vl::__vwsn::This(radioButton)->GetText() == ::vl::WString(L"ReversedHorizontal", false)) ? ::vl::presentation::compositions::GuiStackComposition::Direction::ReversedHorizontal : ::vl::presentation::compositions::GuiStackComposition::Direction::ReversedVertical))));
		}
	}

	//-------------------------------------------------------------------

	__vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::__vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0)
		:__vwsnthis_0(::vl::__vwsn::This(__vwsnctorthis_0))
	{
	}

	void __vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const
	{
		{
			auto __vwsn_for_enumerable_stackItem = ::vl::Ptr<::vl::reflection::description::IValueEnumerable>(::vl::__vwsn::UnboxCollection<::vl::reflection::description::IValueReadonlyList>(::vl::__vwsn::This(__vwsnthis_0->stackLayout)->GetStackItems()));
			auto __vwsn_for_enumerator_stackItem = ::vl::__vwsn::This(__vwsn_for_enumerable_stackItem.Obj())->CreateEnumerator();
			while (::vl::__vwsn::This(__vwsn_for_enumerator_stackItem.Obj())->Next())
			{
				auto stackItem = ::vl::__vwsn::Unbox<::vl::presentation::compositions::GuiStackItemComposition*>(::vl::__vwsn::This(__vwsn_for_enumerator_stackItem.Obj())->GetCurrent());
				{
					::vl::__vwsn::This(stackItem)->SetExtraMargin(::vl::presentation::Margin{});
				}
			}
		}
		auto selectedItem = ::vl::__vwsn::Ensure(::vl::__vwsn::RawPtrCast<::vl::presentation::compositions::GuiStackItemComposition>(::vl::__vwsn::This(sender)->GetParent()));
		::vl::__vwsn::This(selectedItem)->SetExtraMargin([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(10); __vwsn_temp__.top = static_cast<::vl::vint>(10); __vwsn_temp__.right = static_cast<::vl::vint>(10); __vwsn_temp__.bottom = static_cast<::vl::vint>(10); return __vwsn_temp__; }());
		::vl::__vwsn::This(__vwsnthis_0->stackLayout)->MoveChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(selectedItem), (::vl::__vwsn::This(::vl::__vwsn::UnboxCollection<::vl::reflection::description::IValueReadonlyList>(::vl::__vwsn::This(__vwsnthis_0->stackLayout)->GetStackItems()).Obj())->GetCount() - static_cast<::vl::vint>(1)));
	}

	//-------------------------------------------------------------------

	__vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::__vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0)
		:__vwsnthis_0(::vl::__vwsn::This(__vwsnctorthis_0))
	{
	}

	void __vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const
	{
		{
			auto __vwsn_for_enumerable_stackItem = ::vl::Ptr<::vl::reflection::description::IValueEnumerable>(::vl::__vwsn::UnboxCollection<::vl::reflection::description::IValueReadonlyList>(::vl::__vwsn::This(__vwsnthis_0->stackLayout)->GetStackItems()));
			auto __vwsn_for_enumerator_stackItem = ::vl::__vwsn::This(__vwsn_for_enumerable_stackItem.Obj())->CreateEnumerator();
			while (::vl::__vwsn::This(__vwsn_for_enumerator_stackItem.Obj())->Next())
			{
				auto stackItem = ::vl::__vwsn::Unbox<::vl::presentation::compositions::GuiStackItemComposition*>(::vl::__vwsn::This(__vwsn_for_enumerator_stackItem.Obj())->GetCurrent());
				{
					::vl::__vwsn::This(stackItem)->SetExtraMargin(::vl::presentation::Margin{});
				}
			}
		}
		auto selectedItem = ::vl::__vwsn::Ensure(::vl::__vwsn::RawPtrCast<::vl::presentation::compositions::GuiStackItemComposition>(::vl::__vwsn::This(sender)->GetParent()));
		::vl::__vwsn::This(selectedItem)->SetExtraMargin([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(10); __vwsn_temp__.top = static_cast<::vl::vint>(10); __vwsn_temp__.right = static_cast<::vl::vint>(10); __vwsn_temp__.bottom = static_cast<::vl::vint>(10); return __vwsn_temp__; }());
		::vl::__vwsn::This(__vwsnthis_0->stackLayout)->MoveChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(selectedItem), (::vl::__vwsn::This(::vl::__vwsn::UnboxCollection<::vl::reflection::description::IValueReadonlyList>(::vl::__vwsn::This(__vwsnthis_0->stackLayout)->GetStackItems()).Obj())->GetCount() - static_cast<::vl::vint>(1)));
	}

	//-------------------------------------------------------------------

	__vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::__vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(::demo::MainWindowConstructor* __vwsnctorthis_0)
		:__vwsnthis_0(::vl::__vwsn::This(__vwsnctorthis_0))
	{
	}

	void __vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_::operator()(::vl::presentation::compositions::GuiGraphicsComposition* sender, ::vl::presentation::compositions::GuiEventArgs* arguments) const
	{
		{
			auto __vwsn_for_enumerable_stackItem = ::vl::Ptr<::vl::reflection::description::IValueEnumerable>(::vl::__vwsn::UnboxCollection<::vl::reflection::description::IValueReadonlyList>(::vl::__vwsn::This(__vwsnthis_0->stackLayout)->GetStackItems()));
			auto __vwsn_for_enumerator_stackItem = ::vl::__vwsn::This(__vwsn_for_enumerable_stackItem.Obj())->CreateEnumerator();
			while (::vl::__vwsn::This(__vwsn_for_enumerator_stackItem.Obj())->Next())
			{
				auto stackItem = ::vl::__vwsn::Unbox<::vl::presentation::compositions::GuiStackItemComposition*>(::vl::__vwsn::This(__vwsn_for_enumerator_stackItem.Obj())->GetCurrent());
				{
					::vl::__vwsn::This(stackItem)->SetExtraMargin(::vl::presentation::Margin{});
				}
			}
		}
		auto selectedItem = ::vl::__vwsn::Ensure(::vl::__vwsn::RawPtrCast<::vl::presentation::compositions::GuiStackItemComposition>(::vl::__vwsn::This(sender)->GetParent()));
		::vl::__vwsn::This(selectedItem)->SetExtraMargin([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(10); __vwsn_temp__.top = static_cast<::vl::vint>(10); __vwsn_temp__.right = static_cast<::vl::vint>(10); __vwsn_temp__.bottom = static_cast<::vl::vint>(10); return __vwsn_temp__; }());
		::vl::__vwsn::This(__vwsnthis_0->stackLayout)->MoveChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(selectedItem), (::vl::__vwsn::This(::vl::__vwsn::UnboxCollection<::vl::reflection::description::IValueReadonlyList>(::vl::__vwsn::This(__vwsnthis_0->stackLayout)->GetStackItems()).Obj())->GetCount() - static_cast<::vl::vint>(1)));
	}
}

/***********************************************************************
Class (::demo::MainWindowConstructor)
***********************************************************************/

namespace demo
{
	void MainWindowConstructor::__vwsn_demo_MainWindow_Initialize(::demo::MainWindow* __vwsn_this_)
	{
		(this->__vwsn_precompile_0 = __vwsn_this_);
		(this->__vwsn_precompile_22 = ::vl::__vwsn::This(this->__vwsn_precompile_0)->GetBoundsComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_22)->SetPreferredMinSize([&](){ ::vl::presentation::Size __vwsn_temp__; __vwsn_temp__.x = static_cast<::vl::vint>(480); __vwsn_temp__.y = static_cast<::vl::vint>(320); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_0)->SetClientSize([&](){ ::vl::presentation::Size __vwsn_temp__; __vwsn_temp__.x = static_cast<::vl::vint>(480); __vwsn_temp__.y = static_cast<::vl::vint>(320); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_0)->SetText(::vl::WString(L"Stack", false));
		}
		(this->groupStackDirection = new ::vl::presentation::controls::GuiSelectableButton::MutexGroupController());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_0)->AddComponent(static_cast<::vl::presentation::controls::GuiComponent*>(this->groupStackDirection));
		}
		(this->__vwsn_precompile_1 = new ::vl::presentation::compositions::GuiTableComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetCellPadding(static_cast<::vl::vint>(5));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetAlignmentToParent([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(5); __vwsn_temp__.top = static_cast<::vl::vint>(5); __vwsn_temp__.right = static_cast<::vl::vint>(5); __vwsn_temp__.bottom = static_cast<::vl::vint>(5); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetRowsAndColumns(static_cast<::vl::vint>(6), static_cast<::vl::vint>(1));
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetRowOption(static_cast<::vl::vint>(0), [&](){ ::vl::presentation::compositions::GuiCellOption __vwsn_temp__; __vwsn_temp__.composeType = ::vl::presentation::compositions::GuiCellOption::ComposeType::MinSize; return __vwsn_temp__; }());
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetRowOption(static_cast<::vl::vint>(1), [&](){ ::vl::presentation::compositions::GuiCellOption __vwsn_temp__; __vwsn_temp__.composeType = ::vl::presentation::compositions::GuiCellOption::ComposeType::MinSize; return __vwsn_temp__; }());
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetRowOption(static_cast<::vl::vint>(2), [&](){ ::vl::presentation::compositions::GuiCellOption __vwsn_temp__; __vwsn_temp__.composeType = ::vl::presentation::compositions::GuiCellOption::ComposeType::MinSize; return __vwsn_temp__; }());
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetRowOption(static_cast<::vl::vint>(3), [&](){ ::vl::presentation::compositions::GuiCellOption __vwsn_temp__; __vwsn_temp__.composeType = ::vl::presentation::compositions::GuiCellOption::ComposeType::MinSize; return __vwsn_temp__; }());
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetRowOption(static_cast<::vl::vint>(4), [&](){ ::vl::presentation::compositions::GuiCellOption __vwsn_temp__; __vwsn_temp__.composeType = ::vl::presentation::compositions::GuiCellOption::ComposeType::MinSize; return __vwsn_temp__; }());
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetRowOption(static_cast<::vl::vint>(5), [&](){ ::vl::presentation::compositions::GuiCellOption __vwsn_temp__; __vwsn_temp__.composeType = ::vl::presentation::compositions::GuiCellOption::ComposeType::Percentage; __vwsn_temp__.percentage = static_cast<double>(1.0); return __vwsn_temp__; }());
			::vl::__vwsn::This(this->__vwsn_precompile_1)->SetColumnOption(static_cast<::vl::vint>(0), [&](){ ::vl::presentation::compositions::GuiCellOption __vwsn_temp__; __vwsn_temp__.composeType = ::vl::presentation::compositions::GuiCellOption::ComposeType::Percentage; __vwsn_temp__.percentage = static_cast<double>(1.0); return __vwsn_temp__; }());
		}
		(this->__vwsn_precompile_2 = new ::vl::presentation::compositions::GuiCellComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_2)->SetSite(static_cast<::vl::vint>(0), static_cast<::vl::vint>(0), static_cast<::vl::vint>(1), static_cast<::vl::vint>(1));
		}
		{
			(this->__vwsn_precompile_3 = new ::vl::presentation::controls::GuiSelectableButton(::vl::presentation::theme::ThemeName::RadioButton));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_3)->SetSelected(true);
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_3)->SetText(::vl::WString(L"Horizontal", false));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_2)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(::vl::__vwsn::This(this->__vwsn_precompile_3)->GetBoundsComposition()));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_2));
		}
		(this->__vwsn_precompile_4 = new ::vl::presentation::compositions::GuiCellComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_4)->SetSite(static_cast<::vl::vint>(1), static_cast<::vl::vint>(0), static_cast<::vl::vint>(1), static_cast<::vl::vint>(1));
		}
		{
			(this->__vwsn_precompile_5 = new ::vl::presentation::controls::GuiSelectableButton(::vl::presentation::theme::ThemeName::RadioButton));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_5)->SetText(::vl::WString(L"Vertical", false));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_4)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(::vl::__vwsn::This(this->__vwsn_precompile_5)->GetBoundsComposition()));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_4));
		}
		(this->__vwsn_precompile_6 = new ::vl::presentation::compositions::GuiCellComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_6)->SetSite(static_cast<::vl::vint>(2), static_cast<::vl::vint>(0), static_cast<::vl::vint>(1), static_cast<::vl::vint>(1));
		}
		{
			(this->__vwsn_precompile_7 = new ::vl::presentation::controls::GuiSelectableButton(::vl::presentation::theme::ThemeName::RadioButton));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_7)->SetText(::vl::WString(L"ReversedHorizontal", false));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_6)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(::vl::__vwsn::This(this->__vwsn_precompile_7)->GetBoundsComposition()));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_6));
		}
		(this->__vwsn_precompile_8 = new ::vl::presentation::compositions::GuiCellComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_8)->SetSite(static_cast<::vl::vint>(3), static_cast<::vl::vint>(0), static_cast<::vl::vint>(1), static_cast<::vl::vint>(1));
		}
		{
			(this->__vwsn_precompile_9 = new ::vl::presentation::controls::GuiSelectableButton(::vl::presentation::theme::ThemeName::RadioButton));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_9)->SetText(::vl::WString(L"ReversedVertical", false));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_8)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(::vl::__vwsn::This(this->__vwsn_precompile_9)->GetBoundsComposition()));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_8));
		}
		(this->__vwsn_precompile_10 = new ::vl::presentation::compositions::GuiCellComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_10)->SetSite(static_cast<::vl::vint>(4), static_cast<::vl::vint>(0), static_cast<::vl::vint>(1), static_cast<::vl::vint>(1));
		}
		{
			(this->__vwsn_precompile_11 = new ::vl::presentation::controls::GuiLabel(::vl::presentation::theme::ThemeName::Label));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_11)->SetText(::vl::WString(L"Click any button in stack items to enlarge it.", false));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_10)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(::vl::__vwsn::This(this->__vwsn_precompile_11)->GetBoundsComposition()));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_10));
		}
		(this->__vwsn_precompile_12 = new ::vl::presentation::compositions::GuiCellComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_12)->SetSite(static_cast<::vl::vint>(5), static_cast<::vl::vint>(0), static_cast<::vl::vint>(1), static_cast<::vl::vint>(1));
		}
		(this->stackLayout = new ::vl::presentation::compositions::GuiStackComposition());
		{
			::vl::__vwsn::This(this->stackLayout)->SetExtraMargin([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(10); __vwsn_temp__.top = static_cast<::vl::vint>(10); __vwsn_temp__.right = static_cast<::vl::vint>(10); __vwsn_temp__.bottom = static_cast<::vl::vint>(10); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->stackLayout)->SetPadding(static_cast<::vl::vint>(5));
		}
		{
			::vl::__vwsn::This(this->stackLayout)->SetAlignmentToParent([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(0); __vwsn_temp__.top = static_cast<::vl::vint>(0); __vwsn_temp__.right = static_cast<::vl::vint>(0); __vwsn_temp__.bottom = static_cast<::vl::vint>(0); return __vwsn_temp__; }());
		}
		(this->__vwsn_precompile_13 = new ::vl::presentation::compositions::GuiStackItemComposition());
		{
			(this->__vwsn_precompile_14 = new ::vl::presentation::controls::GuiButton(::vl::presentation::theme::ThemeName::Button));
		}
		(this->__vwsn_precompile_15 = ::vl::__vwsn::This(this->__vwsn_precompile_14)->GetBoundsComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_15)->SetPreferredMinSize([&](){ ::vl::presentation::Size __vwsn_temp__; __vwsn_temp__.x = static_cast<::vl::vint>(100); __vwsn_temp__.y = static_cast<::vl::vint>(100); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_15)->SetAlignmentToParent([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(0); __vwsn_temp__.top = static_cast<::vl::vint>(0); __vwsn_temp__.right = static_cast<::vl::vint>(0); __vwsn_temp__.bottom = static_cast<::vl::vint>(0); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_14)->SetText(::vl::WString(L"Large", false));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_13)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(::vl::__vwsn::This(this->__vwsn_precompile_14)->GetBoundsComposition()));
		}
		{
			::vl::__vwsn::This(this->stackLayout)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_13));
		}
		(this->__vwsn_precompile_16 = new ::vl::presentation::compositions::GuiStackItemComposition());
		{
			(this->__vwsn_precompile_17 = new ::vl::presentation::controls::GuiButton(::vl::presentation::theme::ThemeName::Button));
		}
		(this->__vwsn_precompile_18 = ::vl::__vwsn::This(this->__vwsn_precompile_17)->GetBoundsComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_18)->SetPreferredMinSize([&](){ ::vl::presentation::Size __vwsn_temp__; __vwsn_temp__.x = static_cast<::vl::vint>(75); __vwsn_temp__.y = static_cast<::vl::vint>(75); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_18)->SetAlignmentToParent([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(0); __vwsn_temp__.top = static_cast<::vl::vint>(0); __vwsn_temp__.right = static_cast<::vl::vint>(0); __vwsn_temp__.bottom = static_cast<::vl::vint>(0); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_17)->SetText(::vl::WString(L"Medium", false));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_16)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(::vl::__vwsn::This(this->__vwsn_precompile_17)->GetBoundsComposition()));
		}
		{
			::vl::__vwsn::This(this->stackLayout)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_16));
		}
		(this->__vwsn_precompile_19 = new ::vl::presentation::compositions::GuiStackItemComposition());
		{
			(this->__vwsn_precompile_20 = new ::vl::presentation::controls::GuiButton(::vl::presentation::theme::ThemeName::Button));
		}
		(this->__vwsn_precompile_21 = ::vl::__vwsn::This(this->__vwsn_precompile_20)->GetBoundsComposition());
		{
			::vl::__vwsn::This(this->__vwsn_precompile_21)->SetPreferredMinSize([&](){ ::vl::presentation::Size __vwsn_temp__; __vwsn_temp__.x = static_cast<::vl::vint>(50); __vwsn_temp__.y = static_cast<::vl::vint>(50); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_21)->SetAlignmentToParent([&](){ ::vl::presentation::Margin __vwsn_temp__; __vwsn_temp__.left = static_cast<::vl::vint>(0); __vwsn_temp__.top = static_cast<::vl::vint>(0); __vwsn_temp__.right = static_cast<::vl::vint>(0); __vwsn_temp__.bottom = static_cast<::vl::vint>(0); return __vwsn_temp__; }());
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_20)->SetText(::vl::WString(L"Small", false));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_19)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(::vl::__vwsn::This(this->__vwsn_precompile_20)->GetBoundsComposition()));
		}
		{
			::vl::__vwsn::This(this->stackLayout)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_19));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_12)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->stackLayout));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_1)->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_12));
		}
		{
			::vl::__vwsn::This(::vl::__vwsn::This(this->__vwsn_precompile_0)->GetContainerComposition())->AddChild(static_cast<::vl::presentation::compositions::GuiGraphicsComposition*>(this->__vwsn_precompile_1));
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_3)->SetGroupController(static_cast<::vl::presentation::controls::GuiSelectableButton::GroupController*>(this->groupStackDirection));
		}
		{
			auto __vwsn_event_handler_ = LAMBDA(::vl_workflow_global::__vwsnf1_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(this));
			::vl::__vwsn::EventAttach(::vl::__vwsn::This(this->__vwsn_precompile_3)->SelectedChanged, __vwsn_event_handler_);
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_5)->SetGroupController(static_cast<::vl::presentation::controls::GuiSelectableButton::GroupController*>(this->groupStackDirection));
		}
		{
			auto __vwsn_event_handler_ = LAMBDA(::vl_workflow_global::__vwsnf2_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(this));
			::vl::__vwsn::EventAttach(::vl::__vwsn::This(this->__vwsn_precompile_5)->SelectedChanged, __vwsn_event_handler_);
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_7)->SetGroupController(static_cast<::vl::presentation::controls::GuiSelectableButton::GroupController*>(this->groupStackDirection));
		}
		{
			auto __vwsn_event_handler_ = LAMBDA(::vl_workflow_global::__vwsnf3_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(this));
			::vl::__vwsn::EventAttach(::vl::__vwsn::This(this->__vwsn_precompile_7)->SelectedChanged, __vwsn_event_handler_);
		}
		{
			::vl::__vwsn::This(this->__vwsn_precompile_9)->SetGroupController(static_cast<::vl::presentation::controls::GuiSelectableButton::GroupController*>(this->groupStackDirection));
		}
		{
			auto __vwsn_event_handler_ = LAMBDA(::vl_workflow_global::__vwsnf4_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(this));
			::vl::__vwsn::EventAttach(::vl::__vwsn::This(this->__vwsn_precompile_9)->SelectedChanged, __vwsn_event_handler_);
		}
		{
			auto __vwsn_event_handler_ = LAMBDA(::vl_workflow_global::__vwsnf5_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(this));
			::vl::__vwsn::EventAttach(::vl::__vwsn::This(this->__vwsn_precompile_14)->Clicked, __vwsn_event_handler_);
		}
		{
			auto __vwsn_event_handler_ = LAMBDA(::vl_workflow_global::__vwsnf6_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(this));
			::vl::__vwsn::EventAttach(::vl::__vwsn::This(this->__vwsn_precompile_17)->Clicked, __vwsn_event_handler_);
		}
		{
			auto __vwsn_event_handler_ = LAMBDA(::vl_workflow_global::__vwsnf7_Demo_demo_MainWindowConstructor___vwsn_demo_MainWindow_Initialize_(this));
			::vl::__vwsn::EventAttach(::vl::__vwsn::This(this->__vwsn_precompile_20)->Clicked, __vwsn_event_handler_);
		}
	}

	MainWindowConstructor::MainWindowConstructor()
		: groupStackDirection(static_cast<::vl::presentation::controls::GuiSelectableButton::MutexGroupController*>(nullptr))
		, stackLayout(static_cast<::vl::presentation::compositions::GuiStackComposition*>(nullptr))
		, __vwsn_precompile_0(static_cast<::demo::MainWindow*>(nullptr))
		, __vwsn_precompile_1(static_cast<::vl::presentation::compositions::GuiTableComposition*>(nullptr))
		, __vwsn_precompile_2(static_cast<::vl::presentation::compositions::GuiCellComposition*>(nullptr))
		, __vwsn_precompile_3(static_cast<::vl::presentation::controls::GuiSelectableButton*>(nullptr))
		, __vwsn_precompile_4(static_cast<::vl::presentation::compositions::GuiCellComposition*>(nullptr))
		, __vwsn_precompile_5(static_cast<::vl::presentation::controls::GuiSelectableButton*>(nullptr))
		, __vwsn_precompile_6(static_cast<::vl::presentation::compositions::GuiCellComposition*>(nullptr))
		, __vwsn_precompile_7(static_cast<::vl::presentation::controls::GuiSelectableButton*>(nullptr))
		, __vwsn_precompile_8(static_cast<::vl::presentation::compositions::GuiCellComposition*>(nullptr))
		, __vwsn_precompile_9(static_cast<::vl::presentation::controls::GuiSelectableButton*>(nullptr))
		, __vwsn_precompile_10(static_cast<::vl::presentation::compositions::GuiCellComposition*>(nullptr))
		, __vwsn_precompile_11(static_cast<::vl::presentation::controls::GuiLabel*>(nullptr))
		, __vwsn_precompile_12(static_cast<::vl::presentation::compositions::GuiCellComposition*>(nullptr))
		, __vwsn_precompile_13(static_cast<::vl::presentation::compositions::GuiStackItemComposition*>(nullptr))
		, __vwsn_precompile_14(static_cast<::vl::presentation::controls::GuiButton*>(nullptr))
		, __vwsn_precompile_15(static_cast<::vl::presentation::compositions::GuiBoundsComposition*>(nullptr))
		, __vwsn_precompile_16(static_cast<::vl::presentation::compositions::GuiStackItemComposition*>(nullptr))
		, __vwsn_precompile_17(static_cast<::vl::presentation::controls::GuiButton*>(nullptr))
		, __vwsn_precompile_18(static_cast<::vl::presentation::compositions::GuiBoundsComposition*>(nullptr))
		, __vwsn_precompile_19(static_cast<::vl::presentation::compositions::GuiStackItemComposition*>(nullptr))
		, __vwsn_precompile_20(static_cast<::vl::presentation::controls::GuiButton*>(nullptr))
		, __vwsn_precompile_21(static_cast<::vl::presentation::compositions::GuiBoundsComposition*>(nullptr))
		, __vwsn_precompile_22(static_cast<::vl::presentation::compositions::GuiBoundsComposition*>(nullptr))
	{
	}

/***********************************************************************
Class (::demo::MainWindow)
***********************************************************************/

	MainWindow::MainWindow()
		: ::vl::presentation::controls::GuiWindow(::vl::presentation::theme::ThemeName::Window)
	{
		auto __vwsn_resource_ = ::vl::__vwsn::This(::vl::presentation::GetResourceManager())->GetResourceFromClassName(::vl::WString(L"demo::MainWindow", false));
		auto __vwsn_resolver_ = ::vl::Ptr<::vl::presentation::GuiResourcePathResolver>(new ::vl::presentation::GuiResourcePathResolver(__vwsn_resource_, ::vl::__vwsn::This(__vwsn_resource_.Obj())->GetWorkingDirectory()));
		::vl::__vwsn::This(this)->SetResourceResolver(__vwsn_resolver_);
		::vl::__vwsn::This(this)->__vwsn_demo_MainWindow_Initialize(this);
	}

	MainWindow::~MainWindow()
	{
		this->FinalizeInstanceRecursively(static_cast<::vl::presentation::controls::GuiControlHost*>(this));
	}

}
#undef GLOBAL_SYMBOL
#undef GLOBAL_NAME
#undef GLOBAL_OBJ

#if defined( _MSC_VER)
#pragma warning(pop)
#elif defined(__GNUC__)
#pragma GCC diagnostic pop
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
