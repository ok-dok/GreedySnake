//
// Created by shawn on 2024/1/12 0012.
//

#ifndef SNAKE_H
#define SNAKE_H
#define WIDTH 42
#define HEIGHT 22
#define N (HEIGHT - 2) * (WIDTH - 2)

enum Direction {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

//坐标类
class Position {
public:
    int x, y; //x表示行，y表示列
    Position() {
    }

    Position(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

//贪吃蛇类
class Snake {
private:
    Position *body[N]; //蛇的身体（包括头）坐标数组
    int head, tail; //蛇头、蛇尾在body数组中的下标
    int length; //蛇长度
    int maxSize = N; //最大数组长度
    Direction direct; //方向
public:
    //初始化构造函数，默认头下标3，尾下标0，蛇长4，移动方向向右
    Snake(int h = 3, int t = 0, int l = 4, Direction d = RIGHT);

    /**
     * \brief 尝试吃掉坐标上的食物，如果吃得下返回true，吃不下返回false
     * \param food 食物的坐标
     * \return false表示吃饱了，true表示还可以继续吃
     */
    bool eat(Position *food);

    /**
     * \brief 控制蛇头移动到下一个坐标位置
     * \param nextPos 下一个坐标位置
     */
    void move(Position *nextPos);

    /**
     * \brief 获取蛇头坐标
     * \return 蛇头坐标
     */
    Position *getHeadPos() const;

    /**
     * \brief 获取蛇尾坐标
     * \return 蛇尾坐标
     */
    Position *getTailPos() const;

    /**
     * \brief 获取蛇的长度
     * \return 蛇的长度
     */
    int getLength() const;


    Position** getBody();

    /**
     * \brief 获取蛇的移动方向
     * \return 蛇的移动方向
     */
    Direction getDirection() const;

    /**
     * \brief 设置蛇的下一步移动方向
     * \param d 移动方向
     */
    void setDirection(Direction d);
};


#endif //SNAKE_H
