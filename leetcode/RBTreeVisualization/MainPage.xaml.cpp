//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "RBTree.h"
#include <queue>
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

int GetHeight(RBTree::Node* node)
{
	if (!node) return 0;
	int lHeight = GetHeight(node->left);
	int rHeight = GetHeight(node->right);
	return lHeight > rHeight ? lHeight + 1 : rHeight + 1;
}

void RBTreeVisualization::MainPage::DrawRBTree(RBTree::Node * root)
{
	std::queue<RBTree::Node*> qu;
	qu.push(root);

	int level = GetHeight(root);

	root->y = 0;
	root->x = 0;

	cv->Children->Clear();
	double width = gd->ActualWidth;
	double height = gd->ActualHeight;

	while (!qu.empty())
	{
		auto top = qu.front();
		qu.pop();
		if (top->left)
		{
			top->left->y = top->y + 1;
			top->left->x = top->x * 2;
			qu.push(top->left);
		}
		if (top->right)
		{
			top->right->y = top->y + 1;
			top->right->x = top->x * 2 + 1;
			qu.push(top->right);
		}

		top->offsetY = (top->y) * height / level + 20;
		top->offsetX = (top->x + 1) * width / ((1 << top->y) + 1);

		// draw circle 
		Windows::UI::Xaml::Shapes::Ellipse^ circle = ref new Windows::UI::Xaml::Shapes::Ellipse();
		circle->Width = 20;
		circle->Height = 20;
		circle->Stroke = ref new SolidColorBrush(top->color == RBTree::Color::Red ? Windows::UI::Colors::Red : Windows::UI::Colors::Black);
		circle->Fill = ref new SolidColorBrush(Windows::UI::Colors::White);
		Canvas::SetLeft(circle, top->offsetX);
		Canvas::SetTop(circle, top->offsetY);
		Canvas::SetZIndex(circle, 500);
		cv->Children->Append(circle);

		// draw number
		TextBlock^ tb = ref new TextBlock();
		tb->Text = top->val.ToString();
		Canvas::SetLeft(tb, top->offsetX);
		Canvas::SetTop(tb, top->offsetY);
		Canvas::SetZIndex(tb, 1000);
		cv->Children->Append(tb);

		// draw line, if parent exist
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
	}
}

void RBTreeVisualization::MainPage::OnLoaded(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e)
{
	array<int, 80> input;
	int k = 0;
	for (auto& i : input)
	{
		i = input.size() - (k++);
	}
	// comment both line if you want to insert decreasingly
	// comment random_shuffle if you want to insert increasingly 
	// comment short if you want insert randomly.

	//sort(input.begin(), input.end());
	//random_shuffle(input.begin(), input.end());
	RBTree rbtree;
	rbtree.DumpFn = [&](RBTree::Node* root)
	{
		snapshots.push_back(root->Clone());
	};
	for (auto& i : input)
	{
		auto result = rbtree.Insert(i);
	}

	DrawRBTree();
}
void RBTreeVisualization::MainPage::DrawRBTree()
{
	if (snapshotIndex >= 0 && snapshotIndex < snapshots.size())
	{
		DrawRBTree(snapshots[snapshotIndex]);
	}
}

void RBTreeVisualization::MainPage::prev_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	snapshotIndex--;
	if (snapshotIndex < 0) snapshotIndex = 0;

	DrawRBTree();
}


void RBTreeVisualization::MainPage::next_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	snapshotIndex++;
	if (snapshotIndex >= snapshots.size()) snapshotIndex = snapshots.size() - 1;

	DrawRBTree();
}
