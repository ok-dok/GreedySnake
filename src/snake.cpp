//
// Created by shawn on 2024/1/12 0012.
//

#include "snake.h"

Snake::Snake(int h, int t, int l, Direction d) {
    head = h;
    tail = t;
    length = l;
    direct = d;
    *body = new Position[N];
    switch (d) {
        case RIGHT:
            for (int j = 0; j < length; ++j) {
                body[j] = new Position(1, 1 + j);
            }
            break;
        case DOWN:
            for (int i = 0; i < length; ++i) {
                body[i] = new Position(1 + i, 1);
            }
            break;
    }
}

Position **Snake::getBody() {
    return body;
}


bool Snake::eat(Position *food) {
    if (length + 1 == maxSize) {
        return false;
    }
    head = (head + 1) % maxSize;
    body[head] = food;
    length++; //长度+1
    return true;
}

void Snake::move(Position *nextPos) {
    head = (head + 1) % maxSize;
    body[head] = nextPos;
    delete body[tail];
    tail = (tail + 1) % maxSize;
}

Position *Snake::getHeadPos() const {
    return body[head];
}

Position *Snake::getTailPos() const {
    return body[tail];
}

int Snake::getLength() const {
    return length;
}

Direction Snake::getDirection() const {
    return direct;
}

void Snake::setDirection(const Direction d) {
    direct = d;
}
