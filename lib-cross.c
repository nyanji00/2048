#ifdef _WIN32

#include <windows.h>
#include <conio.h>

void msleep(int);
void screen_clear();
void hide_cursor();
void show_cursor();
void change_text_color(int);
void gotoxy(int, int);

enum Code {
    BLACK         = 0,
    DARK_BLUE     = 1,
    DARK_GREEN    = 2,
    DARK_SKY_BLUE = 3,
    DARK_RED      = 4,
    DARK_VIOLET   = 5,
    DARK_YELLOW   = 6,
    GRAY          = 7,
    DARK_GRAY     = 8,
    BLUE          = 9,
    GREEN         = 10,
    SKY_BLUE      = 11,
    RED           = 12,
    VIOLET        = 13,
    YELLOW        = 14,
    WHITE         = 15,
};

void msleep(int t) {
    Sleep(t);
}

void CursorView(int show) {
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO ConsoleCursor;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ConsoleCursor.bVisible = show;
    ConsoleCursor.dwSize = 1;

    SetConsoleCursorInfo(hConsole , &ConsoleCursor);
}

void screen_clear() {
    system("cls");
}

void hide_cursor() {
    CursorView(0);
}

void show_cursor() {
    CursorView(1);
}

void change_text_color(int code) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), code);
}

void gotoxy(int x, int y) {
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

#else

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int kbhit();
int getch();
void msleep(int);
void screen_clear();
void hide_cursor();
void show_cursor();
void change_text_color(int);
void gotoxy(int, int);

enum {
		BLACK         = 30,
		DARK_BLUE     = 34,
		DARK_GREEN    = 32,
		DARK_SKY_BLUE = 36,
		DARK_RED      = 31,
		DARK_VIOLET   = 35,
		DARK_YELLOW   = 33,
		GRAY          = 37,
		DARK_GRAY     = 90,
		BLUE          = 94,
		GREEN         = 92,
		SKY_BLUE      = 96,
		RED           = 91,
		VIOLET        = 95,
		YELLOW        = 93,
		WHITE         = 97,
};

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    
    ch = getchar();
    
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}

int getch() {
    struct termios oldattr, newattr;
    int ch;

    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );

    ch = getchar();

    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );

    return ch;
}

void msleep(int t) {
		usleep(t * 1000);
}

void screen_clear() {
		printf("\e[2J\e[H");
}

void hide_cursor() {
		printf("\e[?25l");
}

void show_cursor() {
		printf("\e[?25h");
}

void change_text_color(int color_code) {
		printf("\e[%dm", color_code);
}

void gotoxy(int x, int y) {
    printf("\e[%d;%df", y + 1, x + 1);
}
#endif
