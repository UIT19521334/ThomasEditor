#include <iostream>
#include <conio.h>
#include "snake.h"
#include <time.h>
// Hàm thay đổi kích cỡ của khung cmd.
void resizeConsole(int width, int height)
{
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

// Hàm tô màu.
void textcolor(int x)
{
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau, x);
}

// Hàm dịch chuyển con trỏ đến tọa độ x, y.
void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x - 1, y - 1 };
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

// Hàm xóa màn hình.
void XoaManHinh()
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}


snake::snake()
{
    srand(time(NULL));
    head.x = X0 + WIDTH / 2;
    head.y = Y0 + HEIGHT / 2;

    tao.x = X0 + 1 + rand() % (WIDTH - 1);
    tao.y = Y0 + 1 + rand() % (HEIGHT - 1);

    prev = RIGHT;
    gameOver = false;
    score = 0;
    soDuoi = 1;

    tail.push_back(head);
}


snake::~snake()
{
}

void snake::veKhung() {
    resizeConsole(640, 480);
    veTao();
    veDiem();
    veRan();


    for (int i = X0; i <= X0 + WIDTH; i++) {
        textcolor(10);
        gotoxy(i, Y0);
        std::cout << char(CHAR);

        gotoxy(i, Y0 + HEIGHT);
        std::cout << char(CHAR);

    }

    for (int i = Y0; i <= Y0 + HEIGHT; i++) {
        gotoxy(X0, i);
        std::cout << char(CHAR);

        gotoxy(X0 + WIDTH, i);
        std::cout << char(CHAR);
    }
    _getch();
}

void snake::veRan() {

    textcolor(11);

    for (int i = 0; i < tail.size(); i++) {
        if (i == 0) {
            gotoxy(tail[0].x, tail[0].y);
            std::cout << "O";
            //gotoxy(1, 1 + i); std::cout << tail[i].x0 << ";" << tail[i].y0 << "|" << tail[i].x << ";" << tail[i].y;
        }
        else {
            initPrev(tail[i]);

            gotoxy(tail[i].x, tail[i].y); std::cout << " ";

            tail[i].x = tail[i - 1].x0;
            tail[i].y = tail[i - 1].y0;

            gotoxy(tail[i].x, tail[i].y); std::cout << "o";
            //gotoxy(1, 1 + i); std::cout << tail[i].x0 << ";" << tail[i].y0 << "|" << tail[i].x << ";" << tail[i].y;
        }
    }
    Sleep(60 + speed);
}

void snake::dieuKhien() {
    Sleep(15);
    initPrev(tail[0]);
    xoaDiem(head.x, head.y);
    if (GetAsyncKeyState(VK_LEFT) && prev != RIGHT) {
        head.x--;
        prev = LEFT;
    }
    else if (GetAsyncKeyState(VK_RIGHT) && prev != LEFT) {
        //xoaDiem(head.x, head.y);
        head.x++;
        prev = RIGHT;
    }
    else if (GetAsyncKeyState(VK_UP) && prev != DOWN) {
        //xoaDiem(head.x, head.y);
        head.y--;
        prev = UP;
    }
    else if (GetAsyncKeyState(VK_DOWN) && prev != UP) {
        //xoaDiem(head.x, head.y);
        head.y++;
        prev = DOWN;
    }
    else if (GetAsyncKeyState(32)) {
        gotoxy(2, 2);
        system("pause");
        gotoxy(2, 2);
        std::cout << "                                                                      ";
    }
    else {
        switch (prev) {
        case LEFT:
            head.x--;
            break;
        case RIGHT:
            head.x++;
            break;
        case UP:
            head.y--;
            break;
        case DOWN:
            head.y++;
            break;
        }
    }

    tail[0].x = head.x;
    tail[0].y = head.y;

}

void snake::xoaDiem(int x, int y) {
    gotoxy(x, y);
    std::cout << " ";
}

void snake::kiemTraThua() {
    if (head.x <= X0 || head.x >= X0 + WIDTH) {
        gameOver = true;
    }
    if (head.y <= Y0 || head.y >= Y0 + HEIGHT) {
        gameOver = true;
    }

    if (gameOver) {
        gotoxy(X0 + WIDTH / 2 - 6, Y0 + HEIGHT / 2);
        textcolor(10);
        std::cout << "GAME OVER !";

        std::cin.ignore(1);
        //_getch();
        exit(1);
    }
    for (int i = 1; i < soDuoi; i++) {
        if (tail[0].x == tail[i].x && tail[0].y == tail[i].y) {
            gameOver = true;
        }
    }
}

void snake::veTao() {
    textcolor(12);
    gotoxy(tao.x, tao.y);
    std::cout << "*";
}
void snake::veToHon() {
    textcolor(7);
    gotoxy(tao.x, tao.y);
    std::cout << "@";
}
void snake::veDiem() {
    textcolor(7);
    gotoxy(4 + WIDTH / 2, Y0 - 4);
    std::cout << "SCORE : " << score;
}

void snake::kiemTraAn() {
    if (head.x == tao.x && head.y == tao.y) {
        score += 10;
        soDuoi++;

        if (score > 300) {
            speed /= 2;
        }

        ToaDo t;
        tail.push_back(t);

        veDiem();
        gotoxy(tao.x, tao.y);
        std::cout << " ";
        srand(time(NULL));
        tao.x = X0 + 1 + rand() % (WIDTH - 1);
        tao.y = Y0 + 1 + rand() % (HEIGHT - 1);
        if (score % 50 == 0) 
            veToHon();
        else veTao();
        
    }
}

void snake::initPrev(ToaDo& td) {
    td.x0 = td.x;
    td.y0 = td.y;
}

void snake::changeSpeed()
{
    int k;
    std::cout << "\n Nhap cap do: \n\t1.De \t 2.TrungBinh \t 3.Kho\n\t\t----->Your choice : ";
    std::cin >> k;
    this->speed = 200 / k;
}

unsigned int snake::getScore()
{
    return this->score;
}
