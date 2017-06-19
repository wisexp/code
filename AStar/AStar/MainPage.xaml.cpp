//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

#include "AStar.h"
#include <vector>

using namespace std;

using namespace AStar;

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
Windows::UI::Color GetRanColor(int r, int c)
{
	Windows::UI::Color colors[] = { Windows::UI::Colors::Azure, Windows::UI::Colors::Black, Windows::UI::Colors::CadetBlue, Windows::UI::Colors::Beige, Windows::UI::Colors::Firebrick, Windows::UI::Colors::Khaki };
	int size = sizeof(colors) / sizeof(colors[0]);
	return colors[rand() % size];
}

Windows::UI::Color GetBKColor(CellInfo& cell)
{
	if (!cell.isAvailable)
		return Windows::UI::Colors::Black;
	if (cell.isOnCurrentPath)
		return Windows::UI::Colors::Yellow;
	else if (cell.kind == CellKind::Unknown)
		return Windows::UI::Colors::White;
	else if (cell.kind == CellKind::Open)
		return Windows::UI::Colors::Blue;
	else// if (kind == CellKind::Closed)
		return Windows::UI::Colors::Green;
}

int row = 40;
int col = 40;
double step = 1.0;
Position start = { 3,4 };
Position cellend = { 33,35 };
vector<vector<CellInfo>> cells(row, vector<CellInfo>(col));

vector<vector<vector<CellInfo>>> snapshots;

void InitializeMap()
{

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			cells[r][c].isAvailable = rand() % 4 != 0;
		}
	}
	for (int r = 4; r < row - 4; r++)
		cells[r][col / 2].isAvailable = false;
	cells[start.first][start.second].isAvailable = true;
	cells[cellend.first][cellend.second].isAvailable = true;
}
struct DataSource : IDataSource
{
	bool IsCellAvailable(Position pos) const override
	{
		if (pos.first < 0 || pos.first >= row) return false;
		if (pos.second < 0 || pos.second >= col) return false;
		return cells[pos.first][pos.second].isAvailable;
	}
};


MainPage::MainPage()
{
	srand(time(nullptr));
	AStarSearchTest test;
//	test.Run();
	InitializeComponent();
	InitializeMap();


}

int index = 0;

void AStar::MainPage::grid_KeyDown(Platform::Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e)
{
	if (e->Key == Windows::System::VirtualKey::Right)
	{
		index++;
	}
	else if (e->Key == Windows::System::VirtualKey::Left)
	{
		index--;
	}
	else
		return;

	index = (index + snapshots.size()) % snapshots.size();

	auto& snapshot = snapshots[index];

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			auto cell = safe_cast<CustomControl^>(grid->Children->GetAt(r * col + c));
			
			cell->Background = ref new SolidColorBrush(GetBKColor(snapshot[r][c]));

			SolidColorBrush^ bk = nullptr;
			if (start == Position(r, c))
			{
				bk = ref new SolidColorBrush(Windows::UI::Colors::Green);
			}
			else if (cellend == Position(r, c))
			{
				bk = ref new SolidColorBrush(Windows::UI::Colors::Red);
			}
			else
			{
				bk = ref new SolidColorBrush(Windows::UI::Colors::Gray);
			}
			cell->BorderBrush = bk;
		}
	}
}


void AStar::MainPage::xInitialize_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	swscanf_s(xRow->Text->Data(), L"%d", &row);
	swscanf_s(xCol->Text->Data(), L"%d", &col);
	swscanf_s(xStart->Text->Data(), L"%d,%d", &start.first, &start.second);
	swscanf_s(xEnd->Text->Data(), L"%d,%d", &cellend.first, &cellend.second);
	swscanf_s(xStep->Text->Data(), L"%lf", &step);
	cells.clear();
	cells.resize(row);
	for (int r = 0; r < row; r++)
	{
		cells[r].resize(col);
	}
	InitializeMap();

	grid->Children->Clear();
	grid->RowDefinitions->Clear();
	grid->ColumnDefinitions->Clear();

	for (int r = 0; r < row; r++)
	{
		RowDefinition^ rd = ref new RowDefinition();
		rd->Height = GridLength(1, Windows::UI::Xaml::GridUnitType::Star);
		grid->RowDefinitions->Append(rd);
	}

	for (int c = 0; c < col; c++)
	{
		ColumnDefinition^ cd = ref new ColumnDefinition();
		cd->Width = GridLength(1, Windows::UI::Xaml::GridUnitType::Star);
		grid->ColumnDefinitions->Append(cd);
	}

	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			CustomControl^ cc = ref new CustomControl();
			//cc->Background = ref new SolidColorBrush(GetRanColor(r, c));
			cc->Tag = r * col + c;
			
			cc->Tapped += ref new Windows::UI::Xaml::Input::TappedEventHandler(this, &AStar::MainPage::OnTapped);
			grid->Children->Append(cc);
			Grid::SetRow(cc, r);
			Grid::SetColumn(cc, c);
		}
	}
}


void AStar::MainPage::xCompute_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

	snapshots.clear();
	snapshots.push_back(cells);
	AStarSearch search;
	DataSource source;
	search.FindPath(&source, start, cellend, step,
		[&](unordered_set<Position, PositionHash>& closedCells, multiset<Node*, NodeCompare>& openCells, Node* current)
	{
		auto copy = cells;
		//copy[current->pos.second][current->pos.first].isOnCurrentPath = true;

		for (auto& pos : closedCells)
		{
			copy[pos.first][pos.second].kind = CellKind::Closed;
		}

		for (auto& node : openCells)
		{
			auto& cell = copy[node->pos.first][node->pos.second];
			cell.kind = CellKind::Open;
			cell.parent = node->parent ? node->parent->pos : Position(-1, -1);
			cell.moveCost = node->moveCost;
			cell.heuristicCost = node->heuristicCost;			
		}

		while (current)
		{
			auto& cell = copy[current->pos.first][current->pos.second];
			cell.isOnCurrentPath = true;
			cell.parent = current->parent ? current->parent->pos : Position(-1, -1);
			cell.moveCost = current->moveCost;
			cell.heuristicCost = current->heuristicCost;
			current = current->parent;
		}

		snapshots.emplace_back(std::move(copy));
	});

	index = 0;
}


void AStar::MainPage::xReset_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
	
}


void AStar::MainPage::OnTapped(Platform::Object ^sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs ^e)
{
	auto cc = safe_cast<CustomControl^>(sender);
	int tag = safe_cast<int>(cc->Tag);
	int r = tag / col;
	int c = tag % col;
	wchar_t buffer[1024];
	auto& cell = snapshots[index][r][c];
	swprintf_s(buffer, L"(%d,%d), parent (%d,%d)\r\n moveCost %4.1lf\r\n heuristicCost %4.1lf", r, c, cell.parent.first, cell.parent.second, cell.moveCost, cell.heuristicCost);
	xLog->Text = ref new Platform::String(buffer);
}
