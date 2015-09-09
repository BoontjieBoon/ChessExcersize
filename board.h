#ifndef BOARD_H
#define BOARD_H

#include <QVector>

#include "piece.h"
#include "position.h"
#include "move.h"
#include "enums.h"

#define NUM_RANKS 8
#define NUM_FILES 8

class Board
{
public:
    Board();
    ~Board();

    void resetBoard();
    void movePiece(Position from, Position to);
    Piece *getPiece(Position position);

    QVector<Move> getMovesForSide(Side side);
    QVector<Move> getMovesForPieceAt(Position position);
    GameState getGameState(Side activeSide);

    int getNumFiles() const;
    int getNumRanks() const;

private:
    QVector< QVector<Piece*> > pieces;
    Position whiteKing;
    Position blackKing;

    void placePiece(Piece* piece, Position position);
    void removePiece(Position position);

    bool isValidPosition(Position position);
    bool isStartingPosition(Position position);
    bool isPositionThreatened(Position position, Side friendlySide);
    bool isPositionThreatenedOnOrthogonal(Position position, Side friendlySide, int fileChange, int rankChange);
    bool isPositionThreatenedOnDiagonal(Position position, Side friendlySide, int fileChange, int rankChange);
    bool isPositionThreatenedByKnight(Position position, Side friendlySide);

    QVector<Move> getPossibleMovesForPieceAt(Position position);
    bool doesSideHaveValidMoves(Side side);
    Position getKingPosition(Side side);

    bool addMove(QVector<Move> &moves, Move move, SpaceStatus status = OCCUPIED_OR_EMPTY);
    void addCustomMoves(QVector<Move> &moves, Position start, QVector<Position> offsets);
    void addDiagonalMoves(QVector<Move> &moves, Position start);
    void addOrthogonalMoves(QVector<Move> &moves, Position start);
    void addDirectionalMoves(QVector<Move> &moves, Position start, int fileChange, int rankChange);

    Position getFirstOccupiedPositionInDirection(Position start, int fileChange, int rankChange);
};

#endif // BOARD_H
