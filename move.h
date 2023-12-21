#ifndef MOVE_H
#define MOVE_H
class Move {
    int toX;
    int toY;
    double value;
    bool capture;
    Move* next;
  public:
    Move(int toX, int toY, double value, bool capture, Move* next);
    ~Move();
    int getNewX();
    int getNewY();
    double getVal();
    bool isCapture();
    Move* getNext();
};
#endif
