#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    double x, y, angle;

    Player(double startX, double startY, double startAngle);

    void moveForward(double distance);
    void moveBackward(double distance);
    void turnLeft(double angleDelta);
    void turnRight(double angleDelta);
};

#endif // PLAYER_H
