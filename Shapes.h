#pragma once
#include "Board.h"
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
class Board;

class Bullet {
public:
	int x, y;
	bool IsActive;
	int Type;
	Bullet();
	void Move(int NewX, int NewY);
};

class Shapes
{
private:
	
	
protected:

	int x;
	int y;
	int id;

public:
	std::vector<Bullet> Bullets;
	int PowerLevel;
	std::vector<std::vector<int>> Points;
	Shapes();
	void Move(int NewX, int NewY);
	int GetX();
	int GetY();
	void SetX(int NewX);
	void SetY(int NewY);
	void SetId(int NewId);
	int GetId();
	void RotateRight();
	void RotateLeft();
	void RandRotation();
	virtual void SuperPower(Board& Plansza);
	void ShowContest(Board& Plansza);
};


class Block : public Shapes 
{
public:
	Block();
	void SuperPower(Board& Plansza) override;
};

class TBlock : public Shapes
{

public:
	//std::vector<Bullet> Bullets;
	TBlock();
	void SuperPower(Board& Plansza) override;
};


class JBlock : public Shapes 
{
public:
	JBlock();
	void SuperPower(Board& Plansza) override;
};

class LBlock : public Shapes
{
public:
	LBlock();
	void SuperPower(Board& Plansza) override;
};


class SBlock : public Shapes
{
public:
	SBlock();
	void SuperPower(Board& Plansza) override;
};
class ZBlock : public Shapes
{
public:
	ZBlock();
	void SuperPower(Board& Plansza) override;
};

class Line : public Shapes
{
public:
	Line();
	void SuperPower(Board& Plansza) override;
};
