#include "app/enemy.h"
#include "common/defines.h"

struct enemy enemy_get(void)
{
    struct enemy enemy = { ENEMY_POS_NONE, ENEMY_RANGE_NONE };
    return enemy;
}

bool enemy_detected(const struct enemy *enemy)
{
    return enemy->position != ENEMY_POS_NONE && enemy->position != ENEMY_POS_IMPOSSIBLE;
}

bool enemy_at_left(const struct enemy *enemy)
{
    return enemy->position == ENEMY_POS_LEFT || enemy->position == ENEMY_POS_FRONT_LEFT
        || enemy->position == ENEMY_POS_FRONT_AND_FRONT_LEFT;
}

bool enemy_at_right(const struct enemy *enemy)
{
    return enemy->position == ENEMY_POS_RIGHT || enemy->position == ENEMY_POS_FRONT_RIGHT
        || enemy->position == ENEMY_POS_FRONT_AND_FRONT_RIGHT;
}

bool enemy_at_front(const struct enemy *enemy)
{
    return enemy->position == ENEMY_POS_FRONT || enemy->position == ENEMY_POS_FRONT_ALL;
}

void enemy_init(void)
{
    // Initialize enemy detection
}
