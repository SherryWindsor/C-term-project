#ifndef SHARED_H
#define SHARED_H
//枚举
enum Role
{
    //没有人下
    EMPTY,
    //玩家下
    PLAYER,
    //人机下
    COMPUTER

};
enum Gamemode //枚举游戏模式
{
    PVP,
    PVE
};

enum Score //设计评分规则 便于人机根据算法决定落子的优先级
{
    //赢
    WIN=1000000000,
    //活四
    LIVE_FOUR=1000000,
    //冲四
    RUSH_FOUR=50000,
    //活三
    LIVE_THREE=10000,
    //眠三
    SLEEP_THREE=5000,
    //活二
    LIVE_TWO=1000,
    //眠二
    SLEEP_TWO=100
};

#endif // SHARED_H
