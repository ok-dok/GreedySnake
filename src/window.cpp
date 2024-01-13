//
// Created by shawn on 2024/1/13 0013.
//
#include "game.h"

void hideCursor(bool hide) {
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = !hide;
    cursor.dwSize = 1;
    HANDLE Hand = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(Hand, &cursor);
}

void hideCursor(HANDLE hConsole) {
    CONSOLE_CURSOR_INFO cursorInfo; // 定义光标信息结构体变量
    GetConsoleCursorInfo(hConsole, &cursorInfo); // 获取当前光标信息
    cursorInfo.bVisible = FALSE; // 将光标可见性设为FALSE（不可见）
    SetConsoleCursorInfo(hConsole, &cursorInfo); // 应用新的光标信息到控制台
}

//windows句柄设置控制台光标位置
void setCursorPos(SHORT left, SHORT top) {
    HANDLE winHandle; //句柄

    COORD pos = {left, top};
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置光标位置
    SetConsoleCursorPosition(winHandle, pos);
    hideCursor(winHandle);
}
// 在指定位置打印字符
void printChar(char ch, SHORT left, SHORT top) {
    HANDLE winHandle; //句柄
    COORD pos = {left, top};
    winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置光标位置
    SetConsoleCursorPosition(winHandle, pos);
    hideCursor(winHandle);
    printf("%c", ch, pos);
}

void printChars(char *pchar, SHORT left, SHORT top)
{
    HANDLE winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD loc = { left,top };
    SetConsoleCursorPosition(winHandle, loc);
    hideCursor(winHandle);
    cout << pchar;
}