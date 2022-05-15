#pragma once

#include "console_attributes.h"
#include "chessboard.h"

/*
* id:
* 0   - � �
* 15  - � �
* 240 - � �
* 102 - ��� ���
* 238 - ��� ���
* 255 - � �
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
	
	// ��������� �����
	void _printLine(int iLine, int iColor1, int iColor2);
	void _print();
	
	// �������������� ���������
	int _i(const std::string& field) const { return 8 - atoi(&field[1]); }
	int _j(const std::string& field) const { return LETTER_FIELD.find(toupper(field[0])); }
	std::string _field(int i, int j) const { return std::string(LETTER_FIELD[j] + std::to_string(8 - i)); }

	// ��������, ����� �� figure ������������� � move
	bool _canMove(const std::string& figure, const std::string& move);

	// ���������� field ������ ��������� �������
	std::string _findKing(ChessFigure::Side kingside);

	// kingside ������� ����� ���, ��� �� ������ �������� ��� �����
	bool _isKingInMate(ChessFigure::Side kingside, const std::string& kingfield);

	// lastside ������� ����� ���, ��� ����� ��������� �� ������ ������ ������ �� ���� ����� ����� => ����� ����
	bool _isKingInCheckmate(ChessFigure::Side lastside);

	// �������� �� ����� �����
	bool _isTurningPawn(const std::string& figure);

public:
	Chess() : _is_game(false)
	{
	}

	int exec();
};

