#include "chessboardpiece.h"

ChessBoardPiece::ChessBoardPiece(CBW::WidgetType type, CBW::WidgetColor color, int file, int rank)
{
    setPostition(file, rank);
    setType(type);
    setColor(color);
}

ChessBoardPiece::~ChessBoardPiece()
{

}

void ChessBoardPiece::setType(CBW::WidgetType type)
{
    this->_type = type;
    updatePicture();
}

void ChessBoardPiece::setColor(CBW::WidgetColor color)
{
    this->_color = color;
    updatePicture();
}

void ChessBoardPiece::setPostition(int file, int rank)
{
    this->_file = file;
    this->_rank = rank;
}

int ChessBoardPiece::getFile()
{
    return this->_file;
}

int ChessBoardPiece::getRank()
{
    return this->_rank;
}

QImage ChessBoardPiece::getImage()
{
    return this->_image;
}

bool ChessBoardPiece::updatePicture()
{
    QString path = ":/images/";

    switch (this->_type)
    {
        case CBW::KING: path += "king"; break;
        case CBW::QUEEN: path += "queen"; break;
        case CBW::BISHOP: path += "bishop"; break;
        case CBW::KNIGHT: path += "knight"; break;
        case CBW::ROOK: path += "rook"; break;
        case CBW::PAWN: path += "pawn"; break;
    }

    switch (this->_color)
    {
        case CBW::WHITE: path += "_w.png"; break;
        case CBW::BLACK: path += "_b.png"; break;
    }

    if (_image.load(path))
    {
        return true;
    }
}
