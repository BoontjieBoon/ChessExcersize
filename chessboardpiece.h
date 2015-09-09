#ifndef CHESSBOARDPIECE_H
#define CHESSBOARDPIECE_H

#include <QImage>

namespace CBW
{
    enum WidgetType {KING, QUEEN, ROOK, KNIGHT, BISHOP, PAWN};
    enum WidgetColor {WHITE, BLACK};
}

struct ChessBoardPiece
{
public:
    ChessBoardPiece(CBW::WidgetType type, CBW::WidgetColor color, int file, int rank);
    ~ChessBoardPiece();
    void setType(CBW::WidgetType type);
    void setColor(CBW::WidgetColor color);
    void setPostition(int file, int rank);
    int getFile();
    int getRank();
    QImage getImage();

private:
    int _rank;
    int _file;
    CBW::WidgetType _type;
    CBW::WidgetColor _color;
    QImage _image;

    bool updatePicture();
};

#endif // CHESSPIECEWIDGET_H
