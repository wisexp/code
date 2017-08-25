//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace AStar
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void grid_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
		void xInitialize_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void xCompute_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void xReset_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnTapped(Platform::Object ^sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs ^e);
	};
}
