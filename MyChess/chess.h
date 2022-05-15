#pragma once

#include "console_attributes.h"
#include "chessboard.h"

/*
* id:
* 0   - ч ч
* 15  - б ч
* 240 - ч б
* 102 - кор кор
* 238 - беж беж
* 255 - б б
*/
#define REGULAR_CONSOLE_ATTRIBUTE static_cast<WORD>(15)
#define WHITE_FIGURE static_cast<WORD>(240)
#define BLACK_FIGURE REGULAR_CONSOLE_ATTRIBUTE
#define WHITE_SQUARE static_cast<WORD>(238)
#define BLACK_SQUARE static_cast<WORD>(102) 

const std::string LETTER_FIELD = "ABCDEFGH";

class Chess {
private:
	ChessBoard _board;
	bool _is_game;
	
	// рисование доски
	void _printLine(int iLine, int iColor1, int iColor2);
	void _print();
	
	// преобразование координат
	int _i(const std::string& field) const { return 8 - atoi(&field[1]); }
	int _j(const std::string& field) const { return LETTER_FIELD.find(toupper(field[0])); }
	std::string _field(int i, int j) const { return std::string(LETTER_FIELD[j] + std::to_string(8 - i)); }

	// проверка, может ли figure передвинуться в move
	bool _canMove(const std::string& figure, const std::string& move);

	// вовзращает field короля указанной стороны
	std::string _findKing(ChessFigure::Side kingside);

	// kingside сделала такой ход, что их король открылся для врага
	bool _isKingInMate(ChessFigure::Side kingside, const std::string& kingfield);

	// lastside сделала такой ход, что любой противник не спасет своего короля от шаха любым ходом => конец игры
	bool _isKingInCheckmate(ChessFigure::Side lastside);

	// достигла ли пешка конца
	bool _isTurningPawn(const std::string& figure);

public:
	Chess() : _is_game(false)
	{
	}

	int exec();
};

