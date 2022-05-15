#include "chessboard.h"

ChessBoard::ChessBoard() {
	using cf = ChessFigure;
	_data = {
		{cf(cf::Side::BLACK, cf::Type::ROOK), cf(cf::Side::BLACK, cf::Type::KNIGHT),
		cf(cf::Side::BLACK, cf::Type::BISHOP), cf(cf::Side::BLACK, cf::Type::QUEEN),
		cf(cf::Side::BLACK, cf::Type::KING), cf(cf::Side::BLACK, cf::Type::BISHOP),
		cf(cf::Side::BLACK, cf::Type::KNIGHT), cf(cf::Side::BLACK, cf::Type::ROOK)},

		{cf(cf::Side::BLACK, cf::Type::PAWN), cf(cf::Side::BLACK, cf::Type::PAWN),
		cf(cf::Side::BLACK, cf::Type::PAWN), cf(cf::Side::BLACK, cf::Type::PAWN),
		cf(cf::Side::BLACK, cf::Type::PAWN), cf(cf::Side::BLACK, cf::Type::PAWN),
		cf(cf::Side::BLACK, cf::Type::PAWN), cf(cf::Side::BLACK, cf::Type::PAWN)},

		{cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE)},

		{cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE)},

		{cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE)},

		{cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE),
		cf(cf::Side::NONE, cf::Type::NONE), cf(cf::Side::NONE, cf::Type::NONE)},

		{cf(cf::Side::WHITE, cf::Type::PAWN), cf(cf::Side::WHITE, cf::Type::PAWN),
		cf(cf::Side::WHITE, cf::Type::PAWN), cf(cf::Side::WHITE, cf::Type::PAWN),
		cf(cf::Side::WHITE, cf::Type::PAWN), cf(cf::Side::WHITE, cf::Type::PAWN),
		cf(cf::Side::WHITE, cf::Type::PAWN), cf(cf::Side::WHITE, cf::Type::PAWN)},

		{cf(cf::Side::WHITE, cf::Type::ROOK), cf(cf::Side::WHITE, cf::Type::KNIGHT),
		cf(cf::Side::WHITE, cf::Type::BISHOP), cf(cf::Side::WHITE, cf::Type::QUEEN),
		cf(cf::Side::WHITE, cf::Type::KING), cf(cf::Side::WHITE, cf::Type::BISHOP),
		cf(cf::Side::WHITE, cf::Type::KNIGHT), cf(cf::Side::WHITE, cf::Type::ROOK)},
	};
}

std::vector<ChessFigure> ChessBoard::operator[](int index) {
	if (index < 0 || index > 7) {
		std::cout << "out of range...";
		exit(1);
	}

	return _data[index];
}

bool ChessBoard::hasFigure(int i, int j) const {
	if (i < 0 || j < 0 || i > 7 || j > 7) {
		return false;
	}

	return (_data[i][j].side() != ChessFigure::Side::NONE);
}

void ChessBoard::move(int i_f, int j_f, int i_m, int j_m) {
	if (i_f < 0 || j_f < 0 || i_m < 0 || j_m < 0 ||
		i_f > 7 || j_f > 7 || i_m > 7 || j_m > 7) {
		std::cout << "out of range...";
		exit(1);
	}

	_data[i_m][j_m] = _data[i_f][j_f];
	_data[i_f][j_f] = ChessFigure(ChessFigure::Side::NONE, ChessFigure::Type::NONE);
}