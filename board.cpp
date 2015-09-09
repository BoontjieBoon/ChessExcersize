#include "board.h"

Board::Board()
{
    // initialise pieces 2D vector with NULL pointers
    for (int i = 0; i < NUM_RANKS; i++)
    {
        QVector<Piece*> newRank;
        for (int j = 0; j < NUM_FILES ; j++)
        {
            newRank.append(NULL);
        }
        pieces.append(newRank);
    }
}

Board::~Board()
{

}

void Board::resetBoard()
{
    // fill board with pieces according to chess setup rules
    for (int i = 0; i < NUM_RANKS; ++i)
    {
        switch (i)
        {
        case 0:
            placePiece(new Piece(WHITE, ROOK), Position(0,i));
            placePiece(new Piece(WHITE, KNIGHT), Position(1,i));
            placePiece(new Piece(WHITE, BISHOP), Position(2,i));
            placePiece(new Piece(WHITE, QUEEN), Position(3,i));
            placePiece(new Piece(WHITE, KING), Position(4,i));
            placePiece(new Piece(WHITE, BISHOP), Position(5,i));
            placePiece(new Piece(WHITE, KNIGHT), Position(6,i));
            placePiece(new Piece(WHITE, ROOK), Position(7,i));
            break;
        case 1:
            for (int j = 0; j < NUM_FILES; j++)
            {
                placePiece(new Piece(WHITE, PAWN), Position(j,i));
            }
            break;
        case 6:
            for (int j = 0; j < NUM_FILES; j++)
            {
                placePiece(new Piece(BLACK, PAWN), Position(j,i));
            }
            break;
        case 7:
            placePiece(new Piece(BLACK, ROOK), Position(0,i));
            placePiece(new Piece(BLACK, KNIGHT), Position(1,i));
            placePiece(new Piece(BLACK, BISHOP), Position(2,i));
            placePiece(new Piece(BLACK, QUEEN), Position(3,i));
            placePiece(new Piece(BLACK, KING), Position(4,i));
            placePiece(new Piece(BLACK, BISHOP), Position(5,i));
            placePiece(new Piece(BLACK, KNIGHT), Position(6,i));
            placePiece(new Piece(BLACK, ROOK), Position(7,i));
            break;
        default:
            for (int j = 0; j < NUM_FILES; j++)
            {
                removePiece(Position(j,i));
            }
            break;
        }
    }
    return;
}

void Board::placePiece(Piece *piece, Position position)
{
    if (isValidPosition(position))
    {
        this->pieces[position.getFile()][position.getRank()] = piece;
        if (piece)
        {
            if (piece->getType() == KING)
            {
                if (piece->getSide() == WHITE) { whiteKing = position; }
                else { blackKing = position; }
            }
        }
    }
}

void Board::removePiece(Position position)
{
    if (isValidPosition(position))
    {
        this->pieces[position.getFile()][position.getRank()] = NULL;
    }
}

void Board::movePiece(Position from, Position to)
{
    placePiece(getPiece(from), to);
    removePiece(from);
}

Piece* Board::getPiece(Position position)
{
    if (isValidPosition(position))
        return this->pieces[position.getFile()][position.getRank()];
    else
        return NULL;
}

QVector<Move> Board::getMovesForSide(Side side)
{
    QVector<Move> moves;
    // go through all the positions on the board and look for the active king
    for (int i = 0; i < NUM_FILES; i++)
    {
        for (int j = 0; j < NUM_RANKS; j++)
        {
            Position currentPosition = Position(i, j);
            Piece *piece = getPiece(currentPosition);
            if ((piece) && (piece->getSide() == side))
            {
                QVector<Move> pieceMoves = getMovesForPieceAt(currentPosition);
                for (int k = 0; k < pieceMoves.length(); k++)
                {
                    moves.append(pieceMoves[k]);
                }
            }
        }
    }

    return moves;
}

QVector<Move> Board::getMovesForPieceAt(Position position)
{
    QVector<Move> moves;
    QVector<Move> possibleMoves = getPossibleMovesForPieceAt(position);
    for (int k = 0; k < possibleMoves.length(); k++)
    {
        Position from = possibleMoves[k].getStart();
        Position to = possibleMoves[k].getStop();
        Position kingPosition;

        // keep current pieces temporarily
        Piece *fromPiece = getPiece(from);
        Piece *toPiece = getPiece(to);

        // moves temporarily to test check if king is in danger after move
        movePiece(from, to);

        if (fromPiece->getType() == KING) { kingPosition = to; }
        else { kingPosition = getKingPosition(fromPiece->getSide()); }
        bool kingThreatened = isPositionThreatened(kingPosition, fromPiece->getSide());

        // return pieces to their original positions
        placePiece(fromPiece, from);
        placePiece(toPiece, to);

        if (!kingThreatened)
        {
            moves.append(possibleMoves[k]);
        }
    }

    return moves;
}

GameState Board::getGameState(Side activeSide)
{
    // check if king is in danger
    bool inCheck = isPositionThreatened(getKingPosition(activeSide), activeSide);
    // check is any valid moves can be made by pieces
    bool hasValidMoves = doesSideHaveValidMoves(activeSide);

    if (inCheck)
    {
        // if side has valid moves in 'check', then 'check', if not 'checkmate'
        if (hasValidMoves)
        {
            return CHECK;
        }
        else
        {
            return CHECKMATE;
        }
    }
    else
    {
        // if side has valid moves and is not in 'check', then 'normal', if not 'stalemate'
        if (hasValidMoves)
        {
            return NORMAL;
        }
        else
        {
            return STALEMATE;
        }
    }
}

int Board::getNumFiles() const
{
    return NUM_FILES;
}

int Board::getNumRanks() const
{
    return NUM_RANKS;
}

bool Board::isValidPosition(Position position)
{
    if ((position.getFile() >= 0) && (position.getFile() <= NUM_FILES - 1)
            && (position.getRank() >= 0) && (position.getRank() <= NUM_RANKS - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::isStartingPosition(Position position)
{
    Piece *piece = getPiece(position);
    if ((piece->getSide() == WHITE) && (position.getRank() == 1))
    {
        return true;
    }
    if ((piece->getSide() == BLACK) && (position.getRank() == 6))
    {
        return true;
    }
    return false;
}

bool Board::isPositionThreatened(Position position, Side friendlySide)
{
    // up
    if (isPositionThreatenedOnOrthogonal(position, friendlySide, 0, 1)) { return true; }
    // right
    if (isPositionThreatenedOnOrthogonal(position, friendlySide, 1, 0)) { return true; }
    // down
    if (isPositionThreatenedOnOrthogonal(position, friendlySide, 0, -1)) { return true; }
    // left
    if (isPositionThreatenedOnOrthogonal(position, friendlySide, -1, 0)) { return true; }
    // up-right
    if (isPositionThreatenedOnDiagonal(position, friendlySide, 1, 1)) { return true; }
    // down-right
    if (isPositionThreatenedOnDiagonal(position, friendlySide, 1, -1)) { return true; }
    // down-left
    if (isPositionThreatenedOnDiagonal(position, friendlySide, -1, -1)) { return true; }
    // up-left
    if (isPositionThreatenedOnDiagonal(position, friendlySide, -1, 1)) { return true; }
    // L-shaped
    if (isPositionThreatenedByKnight(position, friendlySide)) { return true; }

    // if the position wasn't threathed from anywhere
    return false;
}

bool Board::isPositionThreatenedOnOrthogonal(Position position, Side friendlySide, int fileChange, int rankChange)
{
    Position piecePosition = getFirstOccupiedPositionInDirection(position, fileChange, rankChange);
    Piece *piece = getPiece(piecePosition);

    // if there's a piece of the opposite side
    if ((piece) && (piece->getSide() != friendlySide))
    {
        switch (piece->getType()) {
        case KING:
            return (position.getDistance(piecePosition) <= 1);
            break;
        case QUEEN:
        case ROOK:
            return true;
            break;
        default:
            return false;
            break;
        }
    }

    return false;
}

bool Board::isPositionThreatenedOnDiagonal(Position position, Side friendlySide, int fileChange, int rankChange)
{
    Position piecePosition = getFirstOccupiedPositionInDirection(position, fileChange, rankChange);
    Piece *piece = getPiece(piecePosition);

    // if there's a piece of the opposite side
    if ((piece) && (piece->getSide() != friendlySide))
    {
        switch (piece->getType()) {
        case PAWN:
            if (friendlySide == WHITE)
            {
                return (piecePosition.getRank() - position.getRank() == 1);
            }
            else
            {
                return (piecePosition.getRank() - position.getRank() == -1);
            }
            break;
        case KING:
            return (position.getDistance(piecePosition) <= 1);
            break;
        case QUEEN:
        case BISHOP:
            return true;
            break;
        default:
            return false;
            break;
        }
    }

    return false;
}

bool Board::isPositionThreatenedByKnight(Position position, Side friendlySide)
{
    QVector<Position> offsets;

    offsets.append(Position(-1,2));
    offsets.append(Position(1,2));
    offsets.append(Position(2,1));
    offsets.append(Position(2,-1));
    offsets.append(Position(1,-2));
    offsets.append(Position(-1,-2));
    offsets.append(Position(-2,-1));
    offsets.append(Position(-2,1));

    for (int i = 0; i < offsets.length(); i++)
    {
        Piece *piece = getPiece(position + offsets[i]);
        // if the piece in the position is the other players knight the position is threatened
        if ((piece)
                && (piece->getSide() != friendlySide)
                && (piece->getType() == KNIGHT))
        {
            return true;
        }
    }

    return false;
}

QVector<Move> Board::getPossibleMovesForPieceAt(Position position)
{
    QVector<Move> moves;
    Piece *piece = getPiece(position);
    QVector<Position> offsets;

    if (piece)
    {
        switch (piece->getType())
        {
        case PAWN:
            if (piece->getSide() == WHITE)
            {
                if ((addMove(moves, Move(position, Position(0, 1)), EMPTY)) && (isStartingPosition(position)))
                {
                    addMove(moves, Move(position, Position(0, 2)), EMPTY);
                }
                addMove(moves, Move(position, Position(1, 1)), OCCUPIED);
                addMove(moves, Move(position, Position(-1, 1)), OCCUPIED);
            }
            else
            {
                if ((addMove(moves, Move(position, Position(0, -1)), EMPTY)) && (isStartingPosition(position)))
                {
                    addMove(moves, Move(position, Position(0, -2)), EMPTY);
                }
                addMove(moves, Move(position, Position(1, -1)), OCCUPIED);
                addMove(moves, Move(position, Position(-1, -1)), OCCUPIED);
            }
            break;
        case KNIGHT:
            offsets.append(Position(-1,2));
            offsets.append(Position(1,2));
            offsets.append(Position(2,1));
            offsets.append(Position(2,-1));
            offsets.append(Position(1,-2));
            offsets.append(Position(-1,-2));
            offsets.append(Position(-2,-1));
            offsets.append(Position(-2,1));
            addCustomMoves(moves, position, offsets);
            break;
        case KING:
            offsets.append(Position(0,1));
            offsets.append(Position(1,1));
            offsets.append(Position(1,0));
            offsets.append(Position(1,-1));
            offsets.append(Position(0,-1));
            offsets.append(Position(-1,-1));
            offsets.append(Position(-1,0));
            offsets.append(Position(-1,1));
            addCustomMoves(moves, position, offsets);
            break;
        case QUEEN:
            addDiagonalMoves(moves, position);
            addOrthogonalMoves(moves, position);
            break;
        case BISHOP:
            addDiagonalMoves(moves, position);
            break;
        case ROOK:
            addOrthogonalMoves(moves, position);
            break;
        default:
            break;
        }
    }

    return moves;
}

bool Board::doesSideHaveValidMoves(Side side)
{
    // go through all the positions on the board and look for the active king
    for (int i = 0; i < NUM_FILES; i++)
    {
        for (int j = 0; j < NUM_RANKS; j++)
        {
            Position currentPosition = Position(i, j);
            Piece *piece = getPiece(currentPosition);
            if ((piece) && (piece->getSide() == side))
            {
                if (getMovesForPieceAt(currentPosition).length() > 0) { return true; }
            }
        }
    }

    // return false if all pieces were checked and no valid moves were found
    return false;
}

Position Board::getKingPosition(Side side)
{
    if (side == WHITE)
    {
        return whiteKing;
    }
    else
    {
        return blackKing;
    }
}

bool Board::addMove(QVector<Move> &moves, Move move, SpaceStatus status)
{
    if (isValidPosition(move.getStart()) && isValidPosition(move.getStop()))
    {
        Piece *movingPiece = getPiece(move.getStart());
        Piece *targetPiece = getPiece(move.getStop());
        // check if the end position contains a piece
        if (targetPiece)
        {
            // only return true if destination position should contain a piece
            // and the pieces are not on the same side
            if ((status != EMPTY) && (targetPiece->getSide() != movingPiece->getSide()))
            {
                moves.append(move);
                return true;
            }
        }
        else
        {
            // only return true if destination position should be empty
            if (status != OCCUPIED)
            {
                moves.append(move);
                return true;
            }
        }
    }
    return false;
}

void Board::addCustomMoves(QVector<Move> &moves, Position start, QVector<Position> offsets)
{
    for (int i = 0; i < offsets.length(); i++)
    {
        addMove(moves, Move(start, offsets[i]));
    }
}

void Board::addDiagonalMoves(QVector<Move> &moves, Position start)
{
    addDirectionalMoves(moves, start, 1, 1);
    addDirectionalMoves(moves, start, 1, -1);
    addDirectionalMoves(moves, start, -1, -1);
    addDirectionalMoves(moves, start, -1, 1);
}

void Board::addOrthogonalMoves(QVector<Move> &moves, Position start)
{
    addDirectionalMoves(moves, start, 1, 0);
    addDirectionalMoves(moves, start, 0, 1);
    addDirectionalMoves(moves, start, -1, 0);
    addDirectionalMoves(moves, start, 0, -1);
}

void Board::addDirectionalMoves(QVector<Move> &moves, Position start, int fileChange, int rankChange)
{
    Position offset = Position(fileChange, rankChange);

    Move move = Move(start, offset);
    // add move and continue if succeeded
    while (addMove(moves, move))
    {
        if (getPiece(move.getStop())) { break; }

        // add offset to get next position
        move += offset;
    }
}

Position Board::getFirstOccupiedPositionInDirection(Position start, int fileChange, int rankChange)
{
    Position offset = Position(fileChange, rankChange);
    do
    {
        // add offset to start value each iteration
        start += offset;
    } while (!getPiece(start) && isValidPosition(start));

    // return the position a piece was found
    return start;
}
