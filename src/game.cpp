//
// Created by shawn on 2024/1/13 0013.
//

#include "game.h"

/**
 * \brief 设置光标定位到棋盘坐标
 * \param x 棋盘的行坐标
 * \param y 棋盘的列坐标
 */
void setCursorToPosition(Position pos) {
    int top = pos.x;
    int left = pos.y;
    // 如果定义了棋盘偏移，则对left、top定位进行偏移
#ifdef TOP_OFFSET
    top += TOP_OFFSET;
#endif
#ifdef LEFT_OFFSET
    left += LEFT_OFFSET;
#endif
    setCursorPos(left, top);
}

void putCharToPosition(char ch, Position pos) {
    int top = pos.x;
    int left = pos.y;
    // 如果定义了棋盘偏移，则对left、top定位进行偏移
#ifdef TOP_OFFSET
    top += TOP_OFFSET;
#endif
#ifdef LEFT_OFFSET
    left += LEFT_OFFSET;
#endif
    printChar(ch, left, top);
}

Game::Game() {
    food = new Position();
    snake = new Snake();
    score = 0;
    gameOver = false;
    int i, j;

    for (i = 0; i < HEIGHT; i++)
        for (j = 0; j < WIDTH; j++)
            map[i][j] = ' '; // 初始化贪吃蛇棋盘全部为空白

    // 初始化第0行和第HEIGHT-1行 为贪吃蛇棋盘上墙壁
    for (j = 0; j <= WIDTH - 1; j++)
        map[0][j] = '_';

    // 初始化第HEIGHT-1行 为贪吃蛇棋盘下墙壁
    for (j = 0; j <= WIDTH - 1; j++)
        map[HEIGHT - 1][j] = '-';
    //初始化第0列和第WIDTH-1列 为贪吃蛇棋盘左右墙壁
    for (i = 1; i <= HEIGHT - 2; i++)
        map[i][0] = map[i][WIDTH - 1] = '|';

    //初始化蛇身
    Position **body = snake->getBody();
    for (int i = 0; i < snake->getLength() - 1; ++i) {
        map[body[i]->x][body[i]->y] = SNAKE_BODY_SIGN;
    }
    // 设置蛇头
    map[snake->getHeadPos()->x][snake->getHeadPos()->y] = SNAKE_HEAD_SIGN;
}

void Game::chooseGrade() {
    char *menus[] = {
        "请选择游戏等级：\n",
        "1.等级一：移动耗时 1000ms/步（绿皮火车）\n",
        "2.等级二：移动耗时 800ms/步（普通快车）\n",
        "3.等级三：移动耗时 600ms/步（动车）\n",
        "4.等级四：移动耗时 400ms/步（高铁）\n",
        "5.等级五：移动耗时 200ms/步（磁悬浮）\n",
        "6.等级六：移动耗时 100ms/步（航天飞机）\n",
        "7.自动升级模式：自动加速（逐渐变快）\n"
    };
    int baseLeft = 0;
    int baseTop = 0;
#ifdef LEFT_OFFSET
    baseLeft += LEFT_OFFSET;
#endif
#ifdef TOP_OFFSET
    baseTop += TOP_OFFSET;
#endif
    // 打印标题
    printChars(menus[0], baseLeft, baseTop + 1);
    // 打印等级选择菜单
    for (int i = 1; i <= 7; ++i) {
        printChars(menus[i], baseLeft + 4, baseTop + 1 + 2 * i);
    }
    printChars("→", baseLeft + 3, baseTop + 1 + 2);
    int cursor = 1; // 默认指向等级1，cursor在等级1-7之间轮换
    Direction direction = NONE;
    int pressedKey = 0;
    while ((pressedKey = getPressedKey()) > 0) {
        //按下回车键后进入游戏
        if (isKeyEnter(pressedKey)) {
            grade = cursor;
            return;
        }
        Direction direction = getKeyDirection(pressedKey);
        switch (direction) {
            case Direction::UP:
                cursor--;
                break;
            case Direction::DOWN:
                cursor++;
                break;
            default:
                break;
        }
        if (cursor < 1) {
            cursor += 7;
        } else if (cursor > 7) {
            cursor -= 7;
        }
        for (int i = 1; i <= 7; ++i) {
            if (cursor == i) {
                printChars("→", baseLeft + 3, baseTop + 1 + 2 * i);
            } else {
                printChars(" ", baseLeft + 3, baseTop + 1 + 2 * i);
            }
        }
    }
}

int Game::getSpeed() {
    if (grade < 5)
        return 1000 - (grade - 1) * 200;
    else {
        return 100;
    }
}

void Game::produceFood() {
    // c++11生成随机数的方式
    std::default_random_engine e;
    std::uniform_int_distribution<int> xrand(1, HEIGHT - 3); // 随机数分布类，可以确定随机数范围 [1,HEIGHT - 2]
    std::uniform_int_distribution<int> yrand(1, WIDTH - 3); // 随机数分布类，可以确定随机数范围 [1, WIDTH - 2]
    // 利用当前时间来生成随机种子
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    e.seed(seed);
    int x, y;
    do {
        x = xrand(e);
        y = yrand(e);
    } while (map[x][y] != ' ');
    // 新建食物坐标
    food = new Position(x, y);
    //食物填充地图
    updateMap(food, FOOD_SIGN);
}

void Game::moveSnake() {
    Position *next = new Position(); //记录移动的下一个坐标位置
    long start = clock(); //记录时间戳
    //没有按键的情况下，循环等待一个移动时间间隔，超过移动间隔或者有按键事件发生则终止等待
    while (!_kbhit() && (clock() - start) <= getSpeed());
    // 默认取蛇的移动方向（自动移动）
    Direction direction = snake->getDirection();
    if (_kbhit()) {
        // 有按键则取按键方向
        key = getPressedKey();
        direction = getKeyDirection(key);
    }
    if (direction != NONE) {
        //按下方向键（方向键是双值）
        snake->setDirection(direction);
    } else if (isKeyPause(key)) {
        setCursorToPosition(*new Position(18, WIDTH));
        cout << "\t\033[0;35m游戏已暂停";
        do {
            key = getPressedKey(); //获取按键
            // 按下ESC后结束游戏
            if (isKeyExit(key)) {
                break;
            }
        } while (!isKeyPause(key)); // 非空格键、非ESC退出键则继续等待
        setCursorToPosition(*new Position(18, WIDTH));
        cout << "\t\033[m游戏进行中";
    }
    if (isKeyExit(key)) {
        // 按下ESC后结束游戏
        gameOver = true;
        return;
    } else {
        // 按下非方向键、非暂停键、非ESC键则忽略，游戏继续
    }
    Position *headPos = snake->getHeadPos();
    // 根据方向判断下一个坐标位置
    switch (snake->getDirection()) {
        case UP:
            next->x = headPos->x - 1;
            next->y = headPos->y;
            break;
        case DOWN:
            next->x = headPos->x + 1;
            next->y = headPos->y;
            break;
        case LEFT:
            next->x = headPos->x;
            next->y = headPos->y - 1;
            break;
        case RIGHT:
            next->x = headPos->x;
            next->y = headPos->y + 1;
            break;
    }
    //检测下个位置是否符合条件
    if (next->x == 0 || next->x == HEIGHT - 1 || next->y == 0 || next->y == WIDTH - 1) {
        //当下一个坐标在地图上到达边界，说明碰到墙壁，死亡
        gameOver = true;
    } else if (map[next->x][next->y] != ' ' && !(food->x == next->x && food->y == next->y)) {
        // 当下一个坐标在地图上是非空白位置且不是食物时，说明撞到了自己，死亡
        gameOver = true;
    } else if (food->x == next->x && food->y == next->y) {
        //地图上旧的头部更新为身体
        updateMap(snake->getHeadPos(), SNAKE_BODY_SIGN);
        //地图上更新头部为食物
        updateMap(food, SNAKE_HEAD_SIGN);
        int oldLength = snake->getLength();
        // 吃食
        bool eat = snake->eat(food);
        if (eat) {
            //根据等级加分
            score += grade * 20;
            setCursorToPosition(*new Position(10, WIDTH));
            cout << "\t得分：" << score << "分";
            //随机产生食物
            produceFood();
            setCursorToPosition(*next);
            // 自动升级，并更新等级和移动速度
            if (autoUpgrade && oldLength / 8 < snake->getLength() / 8) {
                grade++; // 等级自动升级
                setCursorToPosition(*new Position(2, WIDTH));
                cout << "\t等级：" << grade;
                setCursorToPosition(*new Position(6, WIDTH));
                cout << "\t移动速度：" << getSpeed() << "ms/步";
            }
        } else {
            gameOver = true;
        }
    } else {
        //未碰到食物，按照方向前进
        //旧蛇尾置空
        updateMap(snake->getTailPos(), ' ');

        //蛇头变蛇身
        updateMap(snake->getHeadPos(), SNAKE_BODY_SIGN);

        //蛇移动
        snake->move(next);
        //更新地图上的蛇头
        updateMap(next, SNAKE_HEAD_SIGN);
    }
}

void Game::updateMap(Position *pos, char ch) {
    map[pos->x][pos->y] = ch;
    putCharToPosition(ch, *pos);
}

void Game::displayMap() {
    system("cls"); // 清屏
    int i, j;

    for (j = 0; j < TOP_OFFSET; ++j) {
        cout << endl;
    }
    for (i = 0; i < HEIGHT; i++) //行
    {
        for (j = 0; j < LEFT_OFFSET; ++j) {
            cout << ' ';
        }

        for (j = 0; j < WIDTH; j++) //列

            cout << map[i][j]; // 输出贪吃蛇棋盘

        if (i == 2) cout << "\t等级：" << grade;

        if (i == 6) cout << "\t移动速度：" << getSpeed() << "ms/步";

        if (i == 10) cout << "\t得分：" << score << "分";

        if (i == 14) cout << "\t暂停/继续：按下空格键";

        if (i == 18) cout << "\t";

        cout << endl;
    }
    printChars("帮助：可通过键盘方向键 ↑ ← ↓ →  或 W A S D 按键控制上下左右移动，按下空格键暂停/继续，按下ESC键退出", 0, TOP_OFFSET + HEIGHT + 2);
}

void Game::displayResult() {
    cout << "\n\t\t\t\t等级：" << grade;

    cout << "\n\n\t\t\t\t得分：" << score << "分" << endl;

    cout << endl << endl;
}


void Game::run() {
    chooseGrade(); //选择等级
    displayMap(); // 显示地图
    produceFood(); //产生第一个食物
    while (!gameOver) {
        moveSnake();
    }
    system("cls"); //清屏
    cout << "\n\n\n\t\t\t\tGameover！\n\n" << endl;
    displayResult();
}
