//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "NoHMDPage.g.h"
#include "Common/StepTimer.h"
#include <vector>
#include <ppltasks.h>
#include <functional>
#include <collection.h>

namespace HolographicXAMLView
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class NoHMDPage sealed
	{
	public:
		NoHMDPage();

	private:
		void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void StartPage();

		Platform::Agile<Windows::UI::Core::CoreWindow> m_xamlViewWindow;
		int m_xamlViewId = -1;
		int m_holographicViewId = -1;
        void button3d_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
    };
}
