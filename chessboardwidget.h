#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QObject>
#include <QWidget>
#include <QColor>
#include <QVector>
#include <QSize>
#include <QRect>
#include <QMouseEvent>
#include <QPaintEvent>

#include "playercontroller.h"
#include "board.h"
#include "position.h"
#include "enums.h"

class ChessBoardWidget: public QWidget
{
    Q_OBJECT

public:    
    ChessBoardWidget(QWidget *parent = 0, QSize size = QSize(800, 800));
    ~ChessBoardWidget();

    QSize sizeHint() const;
    void reset(PlayerType white, PlayerType black);

protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);

private:
    QRect getSquareRect(Position position);
    QImage getPieceImage(Piece* piece);
    QColor *getSquareColour(Position position);
    void setSquareColour(Position position, QColor * colour);

    void makeAutomaticMove();

    int squareWidth;
    int squareHeight;
    QColor lightSquareColour;
    QColor darkSquareColour;
    QColor selectedSquareColour;
    QColor errorSquareColour;
    QColor lightTargetSquareColour;
    QColor darkTargetSquareColour;
    QVector< QVector<QColor *> > squareColours;

    Position *selectedSquare;
    QVector<Position> targetSquares;

    PlayerController playerController;
    Board board;

signals:
    void squareClicked(int file, int rank);
    void stateChanged(GameState state);
    void activePlayerChanged(Player player);

};

#endif // CHESSBOARDWIDGET_H
