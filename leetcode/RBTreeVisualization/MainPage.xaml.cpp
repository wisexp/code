//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "RBTree.h"
using namespace concurrency;
using namespace RBTreeVisualization;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409




MainPage::MainPage()
{
	InitializeComponent();

	this->Loaded += ref new Windows::UI::Xaml::RoutedEventHandler(this, &RBTreeVisualization::MainPage::OnLoaded);
	
}


#include <queue>
void RBTreeVisualization::MainPage::DumpTree(RBTree::Node * root)
{
	std::queue<RBTree::Node*> qu;
	qu.push(root);
	
	int level = 0;
	int count = 0;
	int expectedCount = 1;
	bool hasMore = true;
	while (!qu.empty())
	{
		auto top = qu.front();
		qu.pop();
		if (top)
		{
			top->y = level;
			top->x = count;
			qu.push(top->left);
			qu.push(top->right);
			hasMore = true;
		}
		else
		{
			qu.push(nullptr);
			qu.push(nullptr);
		}
		count++;
		if (count == expectedCount)
		{
			if (!hasMore) break;
			level++;
			count = 0;
			expectedCount *= 2;
			hasMore = false;
		}
	}

	while (!qu.empty()) qu.pop();
	
	count /= 2;
	qu.push(root);

	
	auto result = this->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, ref new Windows::UI::Core::DispatchedHandler([&]()
	{
		cv->Children->Clear();
		double width = gd->ActualWidth;
		double height = gd->ActualHeight;
		while (!qu.empty())
		{
			auto top = qu.front();
			qu.pop();

			if (top->left) qu.push(top->left);
			if (top->right) qu.push(top->right);
			top->offsetY = (top->y ) * height / level + 20;
			top->offsetX = (top->x + 1) * width / ((1 << top->y) + 1);
			Windows::UI::Xaml::Shapes::Ellipse^ circle = ref new Windows::UI::Xaml::Shapes::Ellipse();
			circle->Width = 20;
			circle->Height = 20;
			circle->Stroke = ref new SolidColorBrush(top->color == RBTree::Color::Red ? Windows::UI::Colors::Red : Windows::UI::Colors::Black);
			circle->Fill = ref new SolidColorBrush(Windows::UI::Colors::White);
			Canvas::SetLeft(circle, top->offsetX);
			Canvas::SetTop(circle, top->offsetY);
			Canvas::SetZIndex(circle, 500);
			TextBlock^ tb = ref new TextBlock();
			tb->Text = top->val.ToString();
			
			Canvas::SetLeft(tb, top->offsetX);
			Canvas::SetTop(tb, top->offsetY);
			Canvas::SetZIndex(tb, 1000);

			if (top->parent)
			{
				Shapes::Line^ line = ref new Shapes::Line();
				line->Stroke = ref new SolidColorBrush(top->color == RBTree::Color::Red ? Windows::UI::Colors::Red : Windows::UI::Colors::Black);
				line->StrokeThickness = 3;
				line->X1 = top->offsetX;
				line->Y1 = top->offsetY;
				line->X2 = top->parent->offsetX;
				line->Y2 = top->parent->offsetY;
				cv->Children->Append(line);
			}
			cv->Children->Append(tb);
			cv->Children->Append(circle);
		}}
	));
	while (result->Status != Windows::Foundation::AsyncStatus::Completed)
		Sleep(10);
	Sleep(50);
	//task<int> t([]()
	//{
	//	Sleep(100);
	//	return 42;
	//});
	//t.wait();
	//Sleep(100);
}
#include <thread>

void RBTreeVisualization::MainPage::OnLoaded(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e)
{
	std::thread worker([&]()
	
	{
		array<int, 80> input;// = { 12,1,9,49,0,27,36,31,29,45,18,46,32 };
		int k = 0;
		for (auto& i : input)
		{
			i = input.size() - (k++);
		}
		//sort(input.begin(), input.end());
		//random_shuffle(input.begin(), input.end());
		RBTree rbtree;
		rbtree.DumpFn = [&](RBTree::Node* root)
		{
			DumpTree(root);
		};
		for (auto& i : input)
		{
			auto result = rbtree.Insert(i);
			//printf("insert %d, result %d\n", i, result);
		}
	});
	worker.detach();
}
