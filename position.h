#ifndef POSITION_H
#define POSITION_H

struct Position
{
private:
    int _file;
    int _rank;
public:
    Position();
    Position(int file, int rank);
    ~Position();

    int getFile() const;
    void setFile(int file);
    int getRank() const;
    void setRank(int rank);

    int getDistance(const Position& p = Position(0,0));

    Position operator + (const Position& p);
    Position& operator += (const Position& p);
    bool operator == (const Position& p);
};

#endif // POSITION_H
