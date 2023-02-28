#ifndef WRIST_H
#define WRIST_H

class Wrist {
public:
    Wrist(int step, int direction, int sleep);
    ~Wrist();

    void turn()
    void setDirection(int direction);


private:
    int m_step;
    int m_direction;
    int m_sleep;


}

#endif // WRIST_H