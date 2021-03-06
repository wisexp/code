﻿//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include "RBTree.h"
#include <vector>
namespace RBTreeVisualization
{

	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		void DrawRBTree(RBTree::Node* root);
		void DrawRBTree();

		void OnLoaded(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e);

		void prev_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void next_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		std::vector<RBTree::Node*> snapshots;
		int snapshotIndex = 0;
	};
}
