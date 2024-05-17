#ifndef MAP_H
#define MAP_H

class Map {
public:
    static const int width = 8;
    static const int height = 8;
    const char* layout;

    Map();
    bool isWall(int x, int y) const;
};

#endif // MAP_H
