#include "Map.h"

Map::Map()
        : layout(
        "########"
        "#......#"
        "#......#"
        "#......#"
        "#......#"
        "#......#"
        "#......#"
        "########"
) {}

bool Map::isWall(int x, int y) const {
    return layout[y * width + x] == '#';
}
