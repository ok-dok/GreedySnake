//
// Created by shawn on 2024/1/12 0012.
//
#include "game.h"

int getPressedKey() {
    int key = 0;
    while (1) {
        if (_kbhit()) {
            //如果有按键按下，则_kbhit()函数返回真
            key = _getch(); //使用_getch()函数获取按下的键值
            if (key == 0xe0 || key == 0xa1) {
                // 读取功能键需要两次
                key = _getch();
            }
            // cout << hex << key << endl;
            return key;
        }
    }
}

bool isKeyLeft(int key) {
    return KEY_LEFT == key || KEY_A == key || KEY_a == key;
}

bool isKeyRight(int key) {
    return KEY_RIGHT == key || KEY_D == key || KEY_d == key;
}

bool isKeyUp(int key) {
    return KEY_UP == key || KEY_W == key || KEY_w == key;;
}

bool isKeyDown(int key) {
    return KEY_DOWN == key || KEY_S == key || KEY_s == key;;
}

Direction getKeyDirection(int key) {
    if (isKeyUp(key)) {
        return UP;
    } else if (isKeyDown(key)) {
        return DOWN;
    } else if (isKeyLeft(key)) {
        return LEFT;
    } else if (isKeyRight(key)) {
        return RIGHT;
    } else {
        return NONE;
    }
}

bool isKeyYes(int key) {
    return KEY_y == key || KEY_Y == key;
}

bool isKeyNo(int key) {
    return KEY_n == key || KEY_N == key;
}

bool isKeyPause(int key) {
    return KEY_SPACE == key;
}

bool isKeyEnter(int key) {
    return KEY_ENTER == key;
}

bool isKeyExit(int key) {
    return KEY_ESC == key;
}
