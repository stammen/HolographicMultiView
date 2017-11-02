//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "NoHMDPage.xaml.h"
#include "AppView.h"
#include <string>
#include <sstream> 
#include <algorithm>
#include <ppltasks.h>
#include <robuffer.h> // IBufferByteAccess

using namespace HolographicXAMLView;

using namespace Platform;
using namespace Concurrency;
using namespace Microsoft::WRL;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Imaging;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::ApplicationModel::Preview::Holographic;
using namespace Windows::System;


// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

NoHMDPage::NoHMDPage()
{
	InitializeComponent();
}

void NoHMDPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (!Windows::Graphics::Holographic::HolographicSpace::IsSupported)
	{
		warningText->Text = "Windows Mixed Reality is not supported on your PC";
	}
	else
	{
		Windows::Graphics::Holographic::HolographicSpace::IsAvailableChanged += ref new Windows::Foundation::EventHandler<Platform::Object ^>(this, &HolographicXAMLView::NoHMDPage::OnIsAvailableChanged);
	}

    OnIsAvailableChanged(nullptr, nullptr);
}


void NoHMDPage::OnIsAvailableChanged(Platform::Object ^sender, Platform::Object ^args)
{
	Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([this]()
	{
        if (!HolographicApplicationPreview::IsCurrentViewPresentedOnHolographicDisplay())
        {
            m_xamlViewWindow = CoreWindow::GetForCurrentThread();
            m_xamlViewId = ApplicationView::GetApplicationViewIdForWindow(m_xamlViewWindow.Get());

            auto holographicViewSource = ref new HolographicMultiView::AppViewSource();

            Windows::ApplicationModel::Core::CoreApplicationView^ view = Windows::ApplicationModel::Core::CoreApplication::CreateNewView(holographicViewSource);

            ApplicationView^ newAppView = nullptr;

            concurrency::task<void> newViewTask(
                view->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([this]()
            {
                auto newAppView = ApplicationView::GetForCurrentView();
                CoreWindow::GetForCurrentThread()->Activate();
                m_holographicViewId = newAppView->Id;
            })));

            newViewTask.then([this]()
            {
                ApplicationViewSwitcher::TryShowAsStandaloneAsync(m_holographicViewId);
            });
        }
    }));
}
