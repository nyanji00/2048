#ifdef _WIN32

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

#else

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

#endif
