#include "chessboardwidget.h"

#include <cmath>

#include <QPainter>
#include <QBrush>
#include <QTime>

#include "piece.h"
#include "player.h"


ChessBoardWidget::ChessBoardWidget(QWidget *parent, QSize size)
    :QWidget(parent)
{
    squareWidth = size.width() / board.getNumFiles();
    squareHeight = size.height() / board.getNumRanks();

    lightSquareColour       = QColor(240, 235, 230);
    darkSquareColour        = QColor(160, 130, 100);
    selectedSquareColour    = QColor(204, 204, 255);
    errorSquareColour       = QColor(255, 204, 204);
    lightTargetSquareColour = QColor(153, 255, 153);
    darkTargetSquareColour  = QColor(  0, 153,   0);

    // initialise square colours
    for (int i = 0; i < board.getNumFiles(); i++)
    {
        QVector<QColor *> newFile;
        for (int j = 0 ; j < board.getNumRanks(); j++)
        {
            // select alternating dark and light colors for squares
            if ((i + j) % 2 == 0)
            { newFile.append(&darkSquareColour); }
            else
            { newFile.append(&lightSquareColour); }
        }
        squareColours.append(newFile);
    }

    selectedSquare = NULL;

    board.resetBoard();
}

ChessBoardWidget::~ChessBoardWidget()
{
}

QSize ChessBoardWidget::sizeHint() const
{
    return QSize(this->board.getNumFiles() * squareWidth, this->board.getNumRanks() * squareHeight);
}

void ChessBoardWidget::reset(PlayerType white, PlayerType black)
{
    board.resetBoard();
    game.reset(white, black);

    if (white == COMPUTER)
        makeAutomaticMove();

    // force redraw
    update();
}

QColor *ChessBoardWidget::getSquareColour(Position position)
{
    return this->squareColours[position.getFile()][position.getRank()];
}

void ChessBoardWidget::setSquareColour(Position position, QColor * colour)
{
    this->squareColours[position.getFile()][position.getRank()] = colour;
}

void ChessBoardWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();

    int file = floor(x / squareWidth);
    int rank = board.getNumRanks() - floor(y / squareHeight) - 1;

    Piece* piece = board.getPiece(Position(file,rank));
    Player *player = game.getActivePlayer();

    // boolean to check if new selections are allowed
    bool selectable = true;

    // if a piece is already selected, check if one of its targets got clicked
    if (selectedSquare)
    {
        for (int i = 0; i < targetSquares.length(); i++)
        {
            if (targetSquares[i] == Position(file, rank))
            {
                // if a target location was clicked
                // no new selections should be possible
                selectable = false;

                board.movePiece(*selectedSquare, targetSquares[i]);

                Player *newActivePlayer = game.changeActivePlayer();

                emit activePlayerChanged(*newActivePlayer);

                emit stateChanged(board.getGameState(newActivePlayer->getSide()));

                // automatically do computer move
                if (newActivePlayer->getType() == COMPUTER)
                {
                    makeAutomaticMove();
                }
            }
        }
    }

    //deselect currently selected square
    selectedSquare = NULL;

    // clear any target squres
    targetSquares.clear();

    // if new selection is allowed
    if (selectable)
    {
        // if clicked on a piece and there is an active player
        if (piece && player)
        {
            selectedSquare = new Position(file,rank);

            // only check valid moves if player clicked on his own piece
            if (piece->getSide() == player->getSide())
            {
                QVector<Move> validMoves = board.getMovesForPieceAt(Position(file,rank));

                if (selectedSquare)
                {
                    for (int i = 0; i < validMoves.length(); i++)
                    {
                        targetSquares.append(validMoves[i].getStop());
                    }
                }
            }
        }
    }

    // call update so widget gets repainted
    update();

    emit squareClicked(file, rank);

    return;
}

void ChessBoardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (int i = 0; i < board.getNumFiles(); ++i)
    {
        for (int j = 0; j < board.getNumRanks(); ++j)
        {
            QRect rect = getSquareRect(Position(i,j));

            painter.fillRect(rect, *getSquareColour(Position(i, j)));

            if ((selectedSquare) && (*selectedSquare == Position(i, j)))
            {
                Player *activePlayer = game.getActivePlayer();
                Piece *selectedPiece = board.getPiece(Position(i, j));
                if (activePlayer && selectedPiece)
                {
                    if (selectedPiece->getSide() == activePlayer->getSide())
                    {
                        painter.fillRect(rect, selectedSquareColour);
                    }
                    else
                    {
                        painter.fillRect(rect, errorSquareColour);
                    }
                }
            }

            for (int k = 0; k < targetSquares.length(); k++)
            {
                if (targetSquares[k] == Position(i, j))
                {
                    if (*getSquareColour(Position(i,j)) == darkSquareColour)
                    {
                        painter.fillRect(rect, darkTargetSquareColour);
                    }
                    else
                    {
                        painter.fillRect(rect, lightTargetSquareColour);
                    }
                }
            }

            Piece* piece = this->board.getPiece(Position(i,j));
            if (piece)
            {
                QImage image = getPieceImage(piece);
                double widthRatio = (double)squareWidth / (double)image.width();
                double heightRatio = (double)squareHeight / (double)image.height();
                //save current painter state
                painter.save();
                // change scale to draw image with correct size
                painter.scale(widthRatio , heightRatio);
                painter.drawImage(rect.x() / widthRatio, rect.y() / heightRatio, image);
                // restore the saved state to draw at noraml scale again
                painter.restore();
            }
        }
    }
}

QRect ChessBoardWidget::getSquareRect(Position position)
{
    QRect square((position.getFile())*squareWidth, (board.getNumRanks() - position.getRank() - 1) * squareHeight, squareWidth, squareHeight);
    return square;
}

QImage ChessBoardWidget::getPieceImage(Piece *piece)
{
    QImage image;
    if (piece)
    {
        QString path = ":/images/";

        switch (piece->getType())
        {
            case KING: path += "king"; break;
            case QUEEN: path += "queen"; break;
            case BISHOP: path += "bishop"; break;
            case KNIGHT: path += "knight"; break;
            case ROOK: path += "rook"; break;
            case PAWN: path += "pawn"; break;
        }

        switch (piece->getSide())
        {
            case WHITE: path += "_w.png"; break;
            case BLACK: path += "_b.png"; break;
        }
        if (image.load(path))
        {
            return image;
        }
    }
    return image;
}

void ChessBoardWidget::makeAutomaticMove()
{
    QVector<Move> allMoves = board.getMovesForSide(game.getActivePlayer()->getSide());
    qsrand(QTime::currentTime().msec());

    if (allMoves.length() > 0)
    {
        QVector<Move> takeMoves;
        for (int j = 0; j < allMoves.length(); j++)
        {
            Piece *piece = board.getPiece(allMoves[j].getStop());
            if ((piece) && (game.getActivePlayer()->getSide() != piece->getSide()))
            {
                takeMoves.append(allMoves[j]);
            }
        }

        Move aiMove;
        if (takeMoves.length() > 0)
        {
            aiMove = takeMoves[qrand() % takeMoves.length()];
        }
        else
        {
            aiMove = allMoves[qrand() % allMoves.length()];
        }

        board.movePiece(aiMove.getStart(), aiMove.getStop());

        emit activePlayerChanged(*game.changeActivePlayer());

        emit stateChanged(board.getGameState(game.getActivePlayer()->getSide()));
    }
}
