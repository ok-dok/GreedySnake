//
// Created by shawn on 2024/1/13 0013.
//

#ifndef GAME_H
#define GAME_H
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <clocale> // for setlocale() function
#include <cstring>
#include <cstdio>
#include <iostream>
#include <chrono>
#include <random>
using namespace std;
#include "snake.h"

// 按键映射关系
#define KEY_UP  0x48
#define KEY_DOWN 0x50
#define KEY_LEFT 0x4b
#define KEY_RIGHT 0x4d
#define KEY_y 0x79
#define KEY_n 0x6e
#define KEY_Y 0x59
#define KEY_N 0x4e
#define KEY_w 0x77
#define KEY_W 0x57
#define KEY_s 0x73
#define KEY_S 0x53
#define KEY_a 0x61
#define KEY_A 0x41
#define KEY_d 0x64
#define KEY_D 0x44
#define KEY_ESC 0xa4
#define KEY_ENTER 0x0D
#define KEY_SPACE 0x20

//食物符号
#define FOOD_SIGN '*'
//蛇身符号
#define SNAKE_BODY_SIGN '*'
//蛇头符号
#define SNAKE_HEAD_SIGN '#'

//地图左侧偏移量字符（左侧空白填充）
#define LEFT_OFFSET 16
//地图顶部偏移量
#define TOP_OFFSET 4

int getPressedKey();

bool isKeyLeft(int key);

bool isKeyRight(int key);

bool isKeyUp(int key);

bool isKeyDown(int key);

Direction getKeyDirection(int key);

bool isKeyYes(int key);

bool isKeyNo(int key);

bool isKeyPause(int key);

bool isKeyEnter(int key);

bool isKeyExit(int key);

class Game {
private:
    char map[HEIGHT][WIDTH]; //地图
    Position *food; //食物
    Snake *snake;
    int grade; //等级
    int score; //得分
    bool autoUpgrade; //自动升级
    bool gameOver; //游戏结束标志
    int key; //按键
public:
    Game();

    /**
     * \brief 返回移动速度
     * \return 移动一步需要的毫秒数
     */
    int getSpeed();

    /**
     * \brief 选择游戏等级
     */
    void chooseGrade();

    /**
     * \brief 产生食物
     */
    void produceFood();

    /**
     * \brief 移动蛇身
     */
    void moveSnake();

    /**
     * \brief 更新游戏地图，使指定坐标位置显示指定字符
     * \param pos 坐标位置
     * \param ch 要显示的字符
     */
    void updateMap(Position *pos, char ch);

    /**
     * \brief 显示游戏地图
     */
    void displayMap();

    /**
     * \brief 输出成绩结果
     */
    void displayResult();

    /**
     * \brief 运行游戏
     */
    void run();
};

void hideCursor(bool hide);

void setCursorPos(SHORT left, SHORT top);

void printChar(char ch, SHORT left, SHORT top);

void printChars(char *pchar, SHORT left, SHORT top);

#endif //GAME_H
