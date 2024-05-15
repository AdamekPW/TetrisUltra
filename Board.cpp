#include "Board.h"
#include "Shapes.h"
Board::Board() {
	
	this->SquareSize = 30;
	this->Width = 13;
	this->Height = 21;
	for (int i = 0; i < 21; i++) {
		vector<int> A;
		for (int j = 0; j < 13; j++) {
			A.push_back(0);
		}
		BoardInfo.push_back(A);
	}
	/*for (int i = 9; i < Height; i++) {
		BoardInfo[i][6] = 3;
	}*/
}


void Board::SetHeight(int NewH) {
	this->Height = NewH;
	BoardInfo.resize(NewH);
}
void Board::SetWidth(int NewW) {
	this->Width = NewW;
	for (int i = 0; i < BoardInfo.size(); i++)
		BoardInfo[i].resize(NewW);
}

int Board::GetHeight() {
	return this->Height;
}
int Board::GetWidth() {
	return this->Width;
}
int Board::GetSqSize() {
	return this->SquareSize;
}

void Board::DrawShape(Shapes* Shape){
	for (int i = 0; i < Shape->Points.size(); i++) {
		int Px = Shape->Points[i][0];
		int Py = Shape->Points[i][1];
		BoardInfo[Shape->GetX() + Px][Shape->GetY() + Py] = Shape->GetId();
	}

}
void Board::RemoveShape(Shapes* Shape) {
	for (int i = 0; i < Shape->Points.size(); i++) {
		int Px = Shape->Points[i][0];
		int Py = Shape->Points[i][1];
		BoardInfo[Shape->GetX() + Px][Shape->GetY() + Py] = 0;
	}

}

bool Board::IsFit(Shapes* Shape, int NewX, int NewY) {
	RemoveShape(Shape);
	for (int i = 0; i < Shape->Points.size(); i++) {
		int Px = Shape->Points[i][0];
		int Py = Shape->Points[i][1];
		if (Shape->GetX() + Px + NewX >= BoardInfo.size() || Shape->GetY() + Py + NewY >= BoardInfo[0].size()) {
			DrawShape(Shape);
			return false;
		}
		if (BoardInfo[Shape->GetX() + Px + NewX][Shape->GetY() + Py + NewY] > 0) {
			DrawShape(Shape);
			return false;
		}
	}
	Shape->Move(NewX, NewY);
	DrawShape(Shape);
	return true;

}
bool Board::IsThatFit(Shapes* Shape) {
	for (int i = 0; i < Shape->Points.size(); i++) {
		int Px = Shape->Points[i][0];
		int Py = Shape->Points[i][1];
		if (Shape->GetX() + Px < 0 || Shape->GetY() + Py < 0) {
			return false;
		}
		if (Shape->GetX() + Px >= BoardInfo.size() || Shape->GetY() + Py >= BoardInfo[0].size()) {
			return false;
		}
		if (BoardInfo[Shape->GetX() + Px][Shape->GetY() + Py] > 0) {
			return false;
		}
	}
	return true;

}
bool Board::IsRightRotationFit(Shapes *Shape) {
	RemoveShape(Shape);
	Shape->RotateRight();
	for (int i = 0; i < Shape->Points.size(); i++) {

		int NewX = Shape->GetX() + Shape->Points[i][0];
		int NewY = Shape->GetY() + Shape->Points[i][1];
		if (!(0 <= NewX && NewX < Height && 0 <= NewY && NewY < Width)) {
			Shape->RotateLeft();
			DrawShape(Shape);
			return false;
		}
		if (BoardInfo[NewX][NewY] > 0) {
			Shape->RotateLeft();
			DrawShape(Shape);
			return false;
		}
	}
	DrawShape(Shape);
	return true;
}

bool Board::IsLeftRotationFit(Shapes* Shape) {
	RemoveShape(Shape);
	Shape->RotateLeft();
	for (int i = 0; i < Shape->Points.size(); i++) {

		int NewX = Shape->GetX() + Shape->Points[i][0];
		int NewY = Shape->GetY() + Shape->Points[i][1];
		if (!(0 <= NewX && NewX < Height && 0 <= NewY && NewY < Width)) {
			Shape->RotateRight();
			DrawShape(Shape);
			return false;
		}
		if (BoardInfo[NewX][NewY] > 0) {
			Shape->RotateRight();
			DrawShape(Shape);
			return false;
		}
	}
	DrawShape(Shape);
	return true;
}

Shapes* Board::RandomShape() { 
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(2, 8);
	int Number = distribution(generator);
	if (Number == 2) return new Block;
	else if (Number == 3) return new TBlock;
	else if (Number == 4) return new JBlock;
	else if (Number == 5) return new LBlock;
	else if (Number == 6) return new SBlock;
	else if (Number == 7) return new ZBlock;
	else if (Number == 8) return new Line;
	return new Block;
	//return new Line;
}





void Board::MoveLevels(int h) {
	for (int i = h; i >= 1; i--) {
		for (int j = 0; j < Width; j++) {
			BoardInfo[i][j] = BoardInfo[i - 1][j];
		}
	}
}

void Board::RemoveOldBullets() {
	std::vector<Bullet> Bullets_Temp;
	for (int i = 0; i < this->Bullets.size(); i++) {
		if (this->Bullets[i].IsActive) {
			Bullets_Temp.push_back(this->Bullets[i]);
		}
	}
	this->Bullets.resize(0);
	for (int i = 0; i < Bullets_Temp.size(); i++) {
		this->Bullets.push_back(Bullets_Temp[i]);
	}
}

void Board::UpdateBullets() {
	for (int i = 0; i < Bullets.size(); i++) {
		if (Bullets[i].IsActive) {
			
			int Bx = Bullets[i].x;
			int By = Bullets[i].y;
			if (Bullets[i].Type == 3)
				if (Bx + 1 < Height && BoardInfo[Bx + 1][By] <= 0) {
					BoardInfo[Bx][By] = 0;
					BoardInfo[Bx + 1][By] = 3;
					Bullets[i].Move(1, 0);
				}
				else {
					Bullets[i].IsActive = false;
				}
			if (Bullets[i].Type == 8)
				if (Bx + 1 < Height && BoardInfo[Bx + 1][By] <= 0) {
					BoardInfo[Bx][By] = 0;
					BoardInfo[Bx + 1][By] = 8;
					Bullets[i].Move(1, 0);
				}
				else if (Bx + 1 < Height && BoardInfo[Bx + 1][By] > 0) {
					BoardInfo[Bx][By] = 0;
					BoardInfo[Bx + 1][By] = 0;
					Bullets[i].IsActive = false;
				}
				else {
					BoardInfo[Bx][By] = 0;
					Bullets[i].IsActive = false;
				}
			if (Bullets[i].Type == 5)
				if (Bx + 1 < Height && BoardInfo[Bx + 1][By] <= 0) {
					BoardInfo[Bx][By] = 0;
					BoardInfo[Bx + 1][By] = 5;
					Bullets[i].Move(1, 0);
				}
				else {
					Bullets[i].IsActive = false;
				}
			
		}
		
	}
	RemoveOldBullets();
}

