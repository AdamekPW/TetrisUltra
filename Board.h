#pragma once
#include <vector>
#include <random>

#include "Shapes.h"

using namespace std;
class Board
{
private:
	int SquareSize;
	int Width;
	int Height;
public:
	vector<vector<int>> BoardInfo;
	vector<Bullet> Bullets;
	Board();
	void SetWidth(int NewW);
	void SetHeight(int NewH);
	int GetWidth();
	int GetHeight();
	int GetSqSize();
	
	void DrawShape(Shapes* Shape);
	void RemoveShape(Shapes* Shape);
	bool IsFit(Shapes* Shape, int NewX, int NewY);
	bool IsThatFit(Shapes* Shape);
	bool IsRightRotationFit(Shapes* Shape);
	bool IsLeftRotationFit(Shapes* Shape);

	Shapes* RandomShape();

	
	void MoveLevels(int h);
	void RemoveOldBullets();
	void UpdateBullets();
	
};

