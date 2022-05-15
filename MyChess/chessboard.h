#pragma once

#include <iostream>
#include <vector>
#include <string>


class ChessFigure {
public:
	enum class Side {
		NONE,
		WHITE,
		BLACK
	};

	enum class Type {
		NONE,
		KING,
		QUEEN,
		ROOK,
		BISHOP,
		KNIGHT,
		PAWN
	};

private:
	Side _side;
	Type _type;

public:
	ChessFigure(ChessFigure::Side side = Side::NONE, ChessFigure::Type type = Type::NONE)
		: _side(side), _type(type)
	{
	}

	ChessFigure::Side side() const { return _side; }
	ChessFigure::Type type() const { return _type; }

	char charSide() {
		switch (_side) {
		case ChessFigure::Side::NONE:  return ' ';
		case ChessFigure::Side::WHITE: return 'w';
		case ChessFigure::Side::BLACK: return 'b';
		default: return ' ';
		}
	}
	char charType() {
		switch (_type){
		case ChessFigure::Type::NONE:   return ' ';
		case ChessFigure::Type::KING:   return 'K';
		case ChessFigure::Type::QUEEN:  return 'Q';
		case ChessFigure::Type::ROOK:   return 'R';
		case ChessFigure::Type::BISHOP: return 'B';
		case ChessFigure::Type::KNIGHT: return 'N';
		case ChessFigure::Type::PAWN:   return 'P';
		default: return ' ';
		}
	}
};

class ChessBoard {
private:
	std::vector<std::vector<ChessFigure>> _data; // 8x8

public:
	ChessBoard();

	std::vector<ChessFigure> operator[](int index);

	bool hasFigure(int i, int j) const;
	void move(int i_f, int j_f, int i_m, int j_m);
};
