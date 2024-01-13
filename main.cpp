#include <game.h>

void moveWindowToCenter() {
    RECT rectClient, rectWindow;
    HWND hWnd = GetConsoleWindow();
    int screenX = GetSystemMetrics(SM_CXFULLSCREEN);
    int screenY = GetSystemMetrics(SM_CYFULLSCREEN);
    // cout << "屏幕大小：" << screenX << " x " << screenY << endl;
    int cx = screenY / 4;
    int cy = cx * 1.25;
    int left = (screenX - cx) / 2;
    int top = (screenY - cy) / 2;
    // cout << "窗口大小：" << cx << " x " << cy << endl;
    // cout << "窗口坐标：" << left << " , " << top << endl;
    // 调用SetWindowPos函数设置窗口大小
    SetWindowPos(hWnd, HWND_TOPMOST, left, top, cx, cy,
                 SWP_SHOWWINDOW);
    system("mode con cols=60 lines=30");
}


void initWindow() {
    // 设置控制台字符集utf-8
    setlocale(LC_ALL, "en_US.UTF-8");
    SetConsoleOutputCP(65001);
    // 设置窗口标题
    SetConsoleTitle("Greedy Snake");
    // 将窗口居中
    moveWindowToCenter();
    // 隐藏光标
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // 获取控制台输出句柄
    CONSOLE_CURSOR_INFO cursorInfo; // 定义光标信息结构体变量
    GetConsoleCursorInfo(hConsole, &cursorInfo); // 获取当前光标信息

    cursorInfo.bVisible = FALSE; // 将光标可见性设为FALSE（不可见）
    SetConsoleCursorInfo(hConsole, &cursorInfo); // 应用新的光标信息到控制台
}

void welcome() {
    cout << "\n\n\n\n\n\t\t\t 欢迎进入贪吃蛇游戏!" << endl; //欢迎界面;
    cout << "\n\n\n\t\t\t 按任意键马上开始。。。" << endl; //准备开始;
    hideCursor(true);
}

int main() {
    initWindow();
    welcome();
    int pressedKey = getPressedKey();
    bool yes = true;
    while (yes) {
        cout << "\033c"; // 清空屏幕
        Game *game = new Game();
        game->run();
        delete game;

        cout << "\n\n\t\t是否选择继续游戏？按 Y 键或 回车 键继续，按 ESC 键退出" << endl;
        while ((pressedKey = getPressedKey()) > 0) {
            yes = isKeyYes(pressedKey) || isKeyEnter(pressedKey);
            if (yes) {
                break;
            }
            if (isKeyExit(pressedKey)) {
                return 0;
            }
        }
    }
    return 0;
}
