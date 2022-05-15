#include "chess.h"

void Chess::_printLine(int iLine, int iColor1, int iColor2) {
	// Example (for CELL = 6):

	//  [6-char]
	//  |______| subline 1
	//  |___Q__| subline 2
	//  |______| subline 3

	// Define the CELL variable here. 
	// It represents how many horizontal characters will form one square
	// The number of vertical characters will be CELL/2
	// You can change it to alter the size of the board (an odd number will make the squares look rectangular)
	int CELL = 6;

	// Since the width of the characters BLACK and WHITE is half of the height,
	// we need to use two characters in a row.
	// So if we have CELL characters, we must have CELL/2 sublines
	for (int subLine = 0; subLine < CELL / 2; subLine++)
	{
		// A sub-line is consisted of 8 cells, but we can group it
		// in 4 iPairs of black&white
		for (int iPair = 0; iPair < 4; iPair++)
		{
			// First cell of the pair
			for (int subColumn = 0; subColumn < CELL; subColumn++)
			{
				// The piece should be in the "middle" of the cell
				// For 3 sub-lines, in sub-line 1
				// For 6 sub-columns, sub-column 3
				if (subLine == 1 && subColumn == 3 && _board.hasFigure(iLine, iPair * 2)) {
					std::cout << ((_board[iLine][iPair * 2].side() == ChessFigure::Side::WHITE) ?
						TextAttr(WHITE_FIGURE) : TextAttr(BLACK_FIGURE)) << _board[iLine][iPair * 2].charType();
				}
				else {
					std::cout << TextAttr(iColor1) << ' ';
				}
				std::cout << TextAttr(REGULAR_CONSOLE_ATTRIBUTE);

			}

			// Second cell of the pair
			for (int subColumn = 0; subColumn < CELL; subColumn++)
			{
				// The piece should be in the "middle" of the cell
				// For 3 sub-lines, in sub-line 1
				// For 6 sub-columns, sub-column 3
				if (subLine == 1 && subColumn == 3 && _board.hasFigure(iLine, iPair * 2 + 1)) {
					std::cout << ((_board[iLine][iPair * 2 + 1].side() == ChessFigure::Side::WHITE) ?
						TextAttr(WHITE_FIGURE) : TextAttr(BLACK_FIGURE)) << _board[iLine][iPair * 2 + 1].charType();
				}
				else {
					std::cout << TextAttr(iColor2) << ' ';
				}
				std::cout << TextAttr(REGULAR_CONSOLE_ATTRIBUTE);
			}
		}

		// Write the number of the line on the right
		if (subLine == 1)
		{
			std::cout << "   " << 8 - iLine;
		}

		std::cout << "\n";

	}
}

void Chess::_print() {
	std::cout << "   " << LETTER_FIELD.at(0);
	for (int i = 1; i < LETTER_FIELD.size(); i++) {
		std::cout << "     " << LETTER_FIELD.at(i);
	}
	std::cout << "\n\n";
	//std::cout << "   A     B     C     D     E     F     G     H\n\n";
	for (int i = 0; i < 8;i++)
	{
		if (i % 2 == 0)
		{
			// Line starting with WHITE
			_printLine(i, WHITE_SQUARE, BLACK_SQUARE);
		}

		else
		{
			// Line starting with BLACK
			_printLine(i, BLACK_SQUARE, WHITE_SQUARE);
		}
	}
	//std::cout << "\n   A     B     C     D     E     F     G     H\n\n";
	std::cout << "\n   " << LETTER_FIELD.at(0);
	for (int i = 1; i < LETTER_FIELD.size(); i++) {
		std::cout << "     " << LETTER_FIELD.at(i);
	}
	std::cout << "\n\n";
}

bool Chess::_isTurningPawn(const std::string& figure) {
	if (_board[_i(figure)][_j(figure)].type() != ChessFigure::Type::PAWN) {
		return false;
	}

	if (_board[_i(figure)][_j(figure)].side() == ChessFigure::Side::WHITE) {
		if (_i(figure) == 0) return true;
		else return false;
	}
	else {
		if (_i(figure) == 7) return true;
		else return false;
	}
}


std::string Chess::_findKing(ChessFigure::Side kingside) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0;j < 8;j++) {
			if (_board[i][j].side() == kingside && _board[i][j].type() == ChessFigure::Type::KING) {
				return _field(i, j);
			}
		}
	}

	return std::string();
}

// kingside сделала такой ход, что их король открылся для врага
bool Chess::_isKingInMate(ChessFigure::Side kingside, const std::string& kingfield) {
	ChessFigure::Side attackside = (kingside == ChessFigure::Side::WHITE) ? ChessFigure::Side::BLACK : ChessFigure::Side::WHITE;

	for (int i = 0; i < 8; i++) {
		for (int j = 0;j < 8;j++) {
			if (_board[i][j].side() == attackside && _canMove(_field(i, j), kingfield)) {
				return true;
			}
		}
	}

	return false;
}

// lastside сделала такой ход, что любой противник не спасет своего короля от шаха любым ходом => конец игры
bool Chess::_isKingInCheckmate(ChessFigure::Side lastside) {
	ChessFigure::Side defside = (lastside == ChessFigure::Side::WHITE) ? ChessFigure::Side::BLACK : ChessFigure::Side::WHITE;
	std::string king_field = _findKing(defside);

	// проходимя по всем фигурам
	for (int i_f = 0; i_f < 8; i_f++) {
		for (int j_f = 0;j_f < 8;j_f++) {

			if (_board[i_f][j_f].side() == defside) {
				// для каждой фигуры смотрим все клетки, в которые она может пойти
				// идём в эту клетку и смотрим, спасет ли это короля
				for (int i_m = 0; i_m < 8; i_m++) {
					for (int j_m = 0;j_m < 8;j_m++) {
						
						if (_canMove(_field(i_f, j_f), _field(i_m, j_m))) {
							ChessFigure last_figure(_board[i_m][j_m]);
							// передвигаем фигуру
							_board.move(i_f, j_f, i_m, j_m);

							// проверяем, будет ли открыт король
							if (_isKingInMate(defside, king_field)) {
								_board.move(i_m, j_m, i_f, j_f);
								_board[i_m][j_m] = last_figure;
								return true;
							}

							_board.move(i_m, j_m, i_f, j_f);
							_board[i_m][j_m] = last_figure;
						}
					}
				}
			}

		}
	}

	return false;
}

bool Chess::_canMove(const std::string& figure, const std::string& move) {
	int i_f = _i(figure), j_f = _j(figure);
	int i_m = _i(move), j_m = _j(move);

	// за карту нельзя
	if (i_m > 7 || j_m > 7) {
		return false;
	}

	ChessFigure::Side figure_side = _board[i_f][j_f].side();

	// на своих (на самого себя) и на короля нельзя
	if (_board[i_m][j_m].side() == figure_side ||
		_board[i_m][j_m].type() == ChessFigure::Type::KING) {
		return false;
	}

	// проверяем клетки по правилу ходов у каждой фигур (без проверки на наличие врага)
	switch (_board[i_f][j_f].type()) {
	case ChessFigure::Type::PAWN: {
		int d = (figure_side == ChessFigure::Side::WHITE) ? -1 : 1; // d - направление вверх или вниз
		// обычный ход прямо
		if (i_m == i_f + d && j_m == j_f) { 
			return true;
		}
		// ход по диагонали на врага
		else if (i_m == i_f + d && (j_m == j_f + 1 || j_m == j_f - 1) && 
			_board.hasFigure(i_m, j_m)) {
			return true;
		}
		// ход со старта на +2 клетки
		else if ((i_f == 6 && figure_side == ChessFigure::Side::WHITE || i_f == 1 && figure_side == ChessFigure::Side::BLACK) &&
			i_m == i_f + 2 * d) {
			return true;
		}

		return false;
	}
	case ChessFigure::Type::KNIGHT: {
		if (abs(i_m - i_f) == 2 && abs(j_m - j_f) == 1 ||
			abs(i_m - i_f) == 1 && abs(j_m - j_f) == 2) {
			return true;
		}

		return false;
	}
	case ChessFigure::Type::BISHOP: {
		if (abs(i_m - i_f) == abs(j_m - j_f)) {
			int d_i, d_j;
			(i_m < i_f&& j_m < j_f) ? d_i = -1, d_j = -1 :
				(i_m > i_f && j_m < j_f) ? d_i = 1, d_j = -1 :
				(i_m < i_f&& j_m > j_f) ? d_i = -1, d_j = 1 :
				d_i = 1, d_j = 1;

			int i = i_f + d_i, j = j_f + d_j;
			while (i != i_m && j != j_m) {
				if (_board.hasFigure(i, j)) {
					return false;
				}
				i += d_i;
				j += d_j;
			}

			return true;
		}

		return false;
	}
	case ChessFigure::Type::ROOK: {
		if (i_m != i_f && j_m == j_f) {
			int d = (i_m > i_f) ? 1 : -1;
			int i = i_f + d;
			while (i != i_m) {
				if (_board.hasFigure(i, j_m)) {
					return false;
				}
				i += d;
			}

			return true;
		}
		else if (j_m != j_f && i_m == i_f) {
			int d = (j_m > j_f) ? 1 : -1;
			int j = j_f + d;
			while (j != j_m) {
				if (_board.hasFigure(i_m, j)) {
					return false;
				}
				j += d;
			}

			return true;
		}

		return false;
	}
	case ChessFigure::Type::QUEEN: {
		// условие от слона
		if (abs(i_m - i_f) == abs(j_m - j_f)) { 
			int d_i, d_j;
			(i_m > i_f && j_m > j_f) ? d_i = 1, d_j = 1 :
				(i_m > i_f && j_m < j_f) ? d_i = 1, d_j = -1 :
				(i_m < i_f&& j_m > j_f) ? d_i = -1, d_j = 1 :
				d_i = -1, d_j = -1;

			int i = i_f + d_i, j = j_f + d_j;
			while (i != i_m && j != j_m) {
				if (_board.hasFigure(i, j)) {
					return false;
				}
				i += d_i;
				j += d_j;
			}

			return true;
		}
		// условие от ладьи
		else if (i_m != i_f && j_m == j_f) { 
			int d = (i_m > i_f) ? 1 : -1;
			int i = i_f + d;
			while (i != i_m) {
				if (_board.hasFigure(i, j_m)) {
					return false;
				}
				i += d;
			}

			return true;
		}
		else if (j_m != j_f && i_m == i_f) {
			int d = (j_m > j_f) ? 1 : -1;
			int j = j_f + d;
			while (j != j_m) {
				if (_board.hasFigure(i_m, j)) {
					return false;
				}
				j += d;
			}

			return true;
		}

		return false;
	}
	case ChessFigure::Type::KING: {
		if (abs(i_m - i_f) <= 1 && abs(j_m - j_f) <= 1) {
			return true;
		}

		return false;
	}
	default:
		return false;
	}
}

int Chess::exec() {
	_is_game = true;

	size_t count_turn = 0;
	ChessFigure::Side side;

	while (_is_game) {
		system("cls");
		_print();

		if (count_turn % 2 == 0) {
			std::cout << "Current turn: WHITE\n\n";
			side = ChessFigure::Side::WHITE;
		}
		else {
			std::cout << "Current turn: BLACK\n\n";
			side = ChessFigure::Side::BLACK;
		}

		std::string figure, move;
		std::cout << "Type here (figure and move):\n";
		std::cout << ">";
		std::cin >> figure;
		std::cout << ">";
		std::cin >> move;

		if (_board[_i(figure)][_j(figure)].side() == side &&
			_canMove(figure, move)) {
			_board.move(_i(figure), _j(figure), _i(move), _j(move));
			count_turn++;

			// перерождение пешки
			if (_isTurningPawn(figure)) {
				char turn_pawn;
				std::cout << "What kind of figure will the Pawn be:\n";
				std::cout << ">";
				std::cin >> turn_pawn;

				while (std::string("NBRQ").find(toupper(turn_pawn)) == std::string::npos) {
					std::cout << "try again...\n";
					std::cout << ">";
					std::cin >> turn_pawn;
				}

				_board[_i(figure)][_j(figure)] = 
					(turn_pawn == 'N') ? ChessFigure(side, ChessFigure::Type::KNIGHT) :
					(turn_pawn == 'B') ? ChessFigure(side, ChessFigure::Type::BISHOP) :
					(turn_pawn == 'R') ? ChessFigure(side, ChessFigure::Type::ROOK) :
					ChessFigure(side, ChessFigure::Type::QUEEN);
			}

		}

		_is_game = !_isKingInCheckmate(side);
	}
	_print();

	if (side == ChessFigure::Side::WHITE) {
		std::cout << "\nWhite is a winner!\n";
	}
	else {
		std::cout << "\nBlack is a winner!\n";
	}

	return 0;
}