#include "Board.h"
#include "Shapes.h"

void sortMatrix(std::vector<std::vector<int>>& arr) {
	std::sort(arr.begin(), arr.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
		return a[0] > b[0];
		});
}
int FindMax(std::vector<std::vector<int>>& Points) {
	int max = 0;
	for (int i = 0; i < Points.size(); i++) 
		if (max < Points[i][0]) max = Points[i][0];
	return max;
}
int FindMin(std::vector<std::vector<int>>& Points) {
	int max = 0;
	for (int i = 0; i < Points.size(); i++)
		if (max > Points[i][0]) max = Points[i][0];
	return max;
}


Shapes::Shapes() {
	this->id = 0;
	this->x = 0;
	this->y = 6;
	this->PowerLevel = 1;
}

void Shapes::Move(int NewX, int NewY) {
	this->x += NewX;
	this->y += NewY;
}
int Shapes::GetX() {
	return this->x;
}
int Shapes::GetY() {
	return this->y;
}
void Shapes::SetX(int NewX){
	this->x = NewX;
}
void Shapes::SetY(int NewY) {
	this->y = NewY;
}
void Shapes::SetId(int NewId) {
	this->id = NewId;
}
int Shapes::GetId() {
	return this->id;
}

void Shapes::RotateRight() {
	for (int i = 0; i < Points.size(); i++) {
		int x = Points[i][0];
		int y = Points[i][1];
		if (x == 0 && y == 1) { Points[i][0] = 1; Points[i][1] = 0; }
		else if (x == 1 && y == 0) { Points[i][0] = 0; Points[i][1] = -1; }
		else if (x == 0 && y == -1) { Points[i][0] = -1; Points[i][1] = 0; }
		else if (x == -1 && y == 0) { Points[i][0] = 0; Points[i][1] = 1; }
		else if (x == 0 && y == 1) { Points[i][0] = 1; Points[i][1] = 0; }
		else if (x == -1 && y == -1) { Points[i][0] = -1; Points[i][1] = 1; }
		else if (x == -1 && y == 1) { Points[i][0] = 1; Points[i][1] = 1; }
		else if (x == 1 && y == 1) { Points[i][0] = 1; Points[i][1] = -1; }
		else if (x == 1 && y == -1) { Points[i][0] = -1; Points[i][1] = -1; }
		else if (x == 0 && y == 2) { Points[i][0] = 2; Points[i][1] = 0; }
		else if (x == 2 && y == 0) { Points[i][0] = 0; Points[i][1] = -2; }
		else if (x == 0 && y == -2) { Points[i][0] = -2; Points[i][1] = 0; }
		else if (x == -2 && y == 0) { Points[i][0] = 0; Points[i][1] = 2; }
	}

}

void Shapes::RotateLeft() {
	for (int i = 0; i < Points.size(); i++) {
		int x = Points[i][0];
		int y = Points[i][1];
		if (x == 0 && y == 1) { Points[i][0] = -1; Points[i][1] = 0; }
		else if (x == 1 && y == 0) { Points[i][0] = 0; Points[i][1] = 1; }
		else if (x == 0 && y == -1) { Points[i][0] = 1; Points[i][1] = 0; }
		else if (x == -1 && y == 0) { Points[i][0] = 0; Points[i][1] = -1; }
		else if (x == 0 && y == 1) { Points[i][0] = -1; Points[i][1] = 0; }
		else if (x == -1 && y == -1) { Points[i][0] = 1; Points[i][1] = -1; }
		else if (x == -1 && y == 1) { Points[i][0] = -1; Points[i][1] = -1; }
		else if (x == 1 && y == 1) { Points[i][0] = -1; Points[i][1] = 1; }
		else if (x == 1 && y == -1) { Points[i][0] = 1; Points[i][1] = 1; }
		else if (x == 0 && y == 2) { Points[i][0] = -2; Points[i][1] = 0; }
		else if (x == 2 && y == 0) { Points[i][0] = 0; Points[i][1] = 2; }
		else if (x == 0 && y == -2) { Points[i][0] = 2; Points[i][1] = 0; }
		else if (x == -2 && y == 0) { Points[i][0] = 0; Points[i][1] = -2; }
	}
}

void Shapes::RandRotation() {
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(1, 3);
	int Number = distribution(generator);
	for (int i = 0; i < Number; i++) {
		RotateRight();
	}

}
void Shapes::SuperPower(Board& Plansza) {}
void Shapes::ShowContest(Board& Plansza){
	int MaxValue = FindMax(this->Points);
	int MinValue = FindMin(this->Points);
	int max = Plansza.GetHeight() - MaxValue - 1;

	Shapes* Shape = new Shapes;
	*Shape = *this;
	Shape->id *= -1;
	
	
	Plansza.RemoveShape(this);
	
	for (int i = 0; i < Plansza.Bullets.size(); i++) {
		if (Plansza.Bullets[i].IsActive && Plansza.Bullets[i].Type != 5) {
			int x = Plansza.Bullets[i].x;
			int y = Plansza.Bullets[i].y;
			Plansza.BoardInfo[x][y] = 0;
		}
		
	}
	while (Plansza.IsFit(Shape, 1, 0));
	Plansza.DrawShape(this);
	for (int i = 0; i < Plansza.Bullets.size(); i++) {
		if (Plansza.Bullets[i].IsActive && Plansza.Bullets[i].Type != 5) {
			int x = Plansza.Bullets[i].x;
			int y = Plansza.Bullets[i].y;
			Plansza.BoardInfo[x][y] = Plansza.Bullets[i].Type;
		}
	}
	delete Shape;

	
}

Block::Block() {
	id = 2;
	PowerLevel = 1;
	std::vector<std::vector<int>> Wspolrzedne =
	{
		{0, 0},
		{0, 1},
		{1, 0},
		{1, 1},
	};
	for (int i = 0; i < Wspolrzedne.size(); i++) {
		Points.push_back(Wspolrzedne[i]);
	}

}
void Block::SuperPower(Board& Plansza) {
	
	if (PowerLevel < 0) PowerLevel = 0;
	if (PowerLevel > 2) PowerLevel = 2;
	if (PowerLevel == 0) {
		Points.resize(1);
	}
	if (PowerLevel == 1) {
		Points.resize(0);
		std::vector<std::vector<int>> Wspolrzedne =
		{
			{0, 0},
			{0, 1},
			{1, 0},
			{1, 1},
		};
		for (int i = 0; i < Wspolrzedne.size(); i++) {
			Points.push_back(Wspolrzedne[i]);
		}
	}
	if (PowerLevel == 2) {
		Points.resize(0);
		std::vector<std::vector<int>> Wspolrzedne =
		{
			{0, 0},
			{0, 1},
			{1, 0},
			{-1, 0},
			{0, -1},
			{1, 1},
			{1, -1},
			{-1, 1},
			{-1, -1},
		};
		for (int i = 0; i < Wspolrzedne.size(); i++) {
			Points.push_back(Wspolrzedne[i]);
		}
	}
}


TBlock::TBlock() {
	id = 3;
	Move(0, 1);
	std::vector<std::vector<int>> Wspolrzedne =
	{
		{0, 0},
		{0, -1},
		{0, 1},
		{1, 0},
	};
	for (int i = 0; i < Wspolrzedne.size(); i++) {
		Points.push_back(Wspolrzedne[i]);
	}
}
void TBlock::SuperPower(Board& Plansza) {
	Bullet B;
	B.x = this->GetX()+2;
	B.y = this->GetY();
	B.IsActive = true;
	B.Type = 3;
	Plansza.Bullets.push_back(B);
}

Bullet::Bullet() {
	this->x = 0;
	this->y = 0;
	this->IsActive = false;
	this->Type = 0;
	//type 0 to standardowy blok
	//type 1 to blok niszcz¹cy

}
void Bullet::Move(int NewX, int NewY) {
	this->x += NewX;
	this->y += NewY;
}

JBlock::JBlock() {
	id = 4;
	Move(0, 1);
	std::vector<std::vector<int>> Wspolrzedne =
	{
		{0, 0},
		{0, -1},
		{0, 1},
		{1, 1},
	};
	for (int i = 0; i < Wspolrzedne.size(); i++) {
		Points.push_back(Wspolrzedne[i]);

	}
}
void JBlock::SuperPower(Board& Plansza) {
	if (this->PowerLevel < 0) this->PowerLevel = 0;
	else if (this->PowerLevel > 4) this->PowerLevel = 4;
	
	Plansza.RemoveShape(this);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> Dis1(-1, 1);
	int Px = Dis1(gen);
	int Py = Dis1(gen);
	std::uniform_int_distribution<int> Dis2(0, 3);
	int indeks = Dis2(gen);
	if (0 <= this->x + Px && this->x + Px < Plansza.GetHeight() &&
		0 <= this->y + Py && this->y + Py < Plansza.GetWidth() &&
		Plansza.BoardInfo[this->x + Px][this->y + Py] == 0) 
	{
		Points[indeks][0] = Px;
		Points[indeks][1] = Py;
	}
	
	
	
	
	Plansza.DrawShape(this);
}

LBlock::LBlock() {
	id = 5;
	PowerLevel = 0;
	Move(0, 1);
	std::vector<std::vector<int>> Wspolrzedne =
	{
		{0, 0},
		{0, -1},
		{0, 1},
		{1, -1},
	};
	for (int i = 0; i < Wspolrzedne.size(); i++) {
		Points.push_back(Wspolrzedne[i]);

	}
}
void LBlock::SuperPower(Board& Plansza) {

	if (PowerLevel == 0) {
		Plansza.RemoveShape(this);
		this->id = 0;
		Plansza.Bullets.resize(0);
		sortMatrix(this->Points);
		for (int i = 0; i < Points.size(); i++) {
			Bullet B;
			B.x = this->x + Points[i][0];
			B.y = this->y + Points[i][1];
			B.IsActive = true;
			B.Type = 5;
			Plansza.Bullets.push_back(B);
		}
		PowerLevel = 1;
	}
	
}

SBlock::SBlock() {
	id = 6;
	Move(0, 1);
	std::vector<std::vector<int>> Wspolrzedne =
	{
		{0, 0},
		{1, -1},
		{1, 0},
		{0, 1},
	};
	for (int i = 0; i < Wspolrzedne.size(); i++) {
		Points.push_back(Wspolrzedne[i]);

	}
}
void SBlock::SuperPower(Board& Plansza) {
	std::vector<std::vector<int>> ObszarWybuchu = {
		{0, 0},
		{0, -2},
		{0, -1},
		{0, 1},
		{0, 2},
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{1, -1},
		{1, 0},
		{1, 1},
		{-2, 0},
		{2, 0},
		{-1, -2},
		{-2, -1},
		{-2, 1},
		{-1, 2},
		{1, -2},
		{2, -1},
		{2, 1},
		{1, 2},
	};
	for (int i = 0; i < ObszarWybuchu.size(); i++) {
		int Px = ObszarWybuchu[i][0];
		int Py = ObszarWybuchu[i][1];
		if (0 <= this->x + Px && this->x + Px < Plansza.GetHeight() && 0 <= this->y + Py && this->y + Py < Plansza.GetWidth()) {
			Plansza.BoardInfo[x + Px][y + Py] = 0;
		}
	}
}

ZBlock::ZBlock() {
	id = 7;
	Move(0, 1);
	std::vector<std::vector<int>> Wspolrzedne =
	{
		{0, 0},
		{0, -1},
		{1, 0},
		{1, 1},
	};
	for (int i = 0; i < Wspolrzedne.size(); i++) {
		Points.push_back(Wspolrzedne[i]);

	}
}
void ZBlock::SuperPower(Board& Plansza) {
	std::vector<std::vector<int>> ObszarWybuchu = {
		{0, 0},
		{0, -2},
		{0, -1},
		{0, 1},
		{0, 2},
		{-1, -1},
		{-1, 0},
		{-1, 1},
		{1, -1},
		{1, 0},
		{1, 1},
		{-2, 0},
		{2, 0},
	};
	for (int i = 0; i < ObszarWybuchu.size(); i++) {
		int Px = ObszarWybuchu[i][0];
		int Py = ObszarWybuchu[i][1];
		if (0 <= this->x + Px && this->x + Px < Plansza.GetHeight() && 0 <= this->y+Py &&this->y + Py < Plansza.GetWidth()) {
			Plansza.BoardInfo[x + Px][y + Py] = 0;
		}
	}
}

Line::Line() {
	id = 8;
	Move(0, 1);
	std::vector<std::vector<int>> Wspolrzedne =
	{
		{0, -1},
		{0, 0},
		{0, 1},
		{0, 2},
	};
	for (int i = 0; i < Wspolrzedne.size(); i++) {
		Points.push_back(Wspolrzedne[i]);

	}
}
void Line::SuperPower(Board& Plansza) {
	Bullet B;
	B.x = this->GetX() + 3;
	B.y = this->GetY();
	B.IsActive = true;
	B.Type = 8;
	Plansza.Bullets.push_back(B);
}

