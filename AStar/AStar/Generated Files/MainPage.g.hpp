﻿//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BINDING_DEBUG_OUTPUT
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent();
#endif

#include "MainPage.xaml.h"

void ::AStar::MainPage::InitializeComponent()
{
    if (_contentLoaded)
    {
        return;
    }
    _contentLoaded = true;
    ::Windows::Foundation::Uri^ resourceLocator = ref new ::Windows::Foundation::Uri(L"ms-appx:///MainPage.xaml");
    ::Windows::UI::Xaml::Application::LoadComponent(this, resourceLocator, ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);
}

void ::AStar::MainPage::Connect(int __connectionId, ::Platform::Object^ __target)
{
    switch (__connectionId)
    {
        case 1:
            {
                this->grid = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Grid^>(this->grid))->KeyDown += ref new ::Windows::UI::Xaml::Input::KeyEventHandler(this, (void (::AStar::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::Input::KeyRoutedEventArgs^))&MainPage::grid_KeyDown);
            }
            break;
        case 2:
            {
                this->xRow = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
            }
            break;
        case 3:
            {
                this->xCol = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
            }
            break;
        case 4:
            {
                this->xStart = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
            }
            break;
        case 5:
            {
                this->xEnd = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
            }
            break;
        case 6:
            {
                this->xStep = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(__target);
            }
            break;
        case 7:
            {
                this->xInitialize = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->xInitialize))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::AStar::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::xInitialize_Click);
            }
            break;
        case 8:
            {
                this->xCompute = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->xCompute))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::AStar::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::xCompute_Click);
            }
            break;
        case 9:
            {
                this->xReset = safe_cast<::Windows::UI::Xaml::Controls::Button^>(__target);
                (safe_cast<::Windows::UI::Xaml::Controls::Button^>(this->xReset))->Click += ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::AStar::MainPage::*)
                    (::Platform::Object^, ::Windows::UI::Xaml::RoutedEventArgs^))&MainPage::xReset_Click);
            }
            break;
        case 10:
            {
                this->xLog = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(__target);
            }
            break;
    }
    _contentLoaded = true;
}

::Windows::UI::Xaml::Markup::IComponentConnector^ ::AStar::MainPage::GetBindingConnector(int __connectionId, ::Platform::Object^ __target)
{
    __connectionId;         // unreferenced
    __target;               // unreferenced
    return nullptr;
}


