#ifndef ENUMS_H
#define ENUMS_H

enum GameState { NORMAL, CHECK, CHECKMATE, STALEMATE };

enum Side { WHITE, BLACK };

enum PlayerType { HUMAN, COMPUTER };

enum PieceType { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN };

enum SpaceStatus { OCCUPIED, EMPTY, OCCUPIED_OR_EMPTY };

#endif // ENUMS_H
