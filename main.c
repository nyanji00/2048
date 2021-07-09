#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

int score = 0;

void print(int (*a)[4]) {
	printf("-------------------------\n");
	for(int i=0; i<4; i++) {
		printf("|     |     |     |     |\n");
		for(int j=0; j<4; j++) {
			if(a[i][j] == 0) {
				printf("|     ");
			}
			else {
				printf("|    ");
				printf("%d", a[i][j]);
			}
		}
		printf("|\n");
		printf("|     |     |     |     |\n");
		printf("-------------------------\n");
	}
	printf("Score: %d\n", score);

	return;
}

void rotate(int (*a)[4]) {
	int b[4][4];

	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			b[i][j]=a[j][i];
		}
	}

	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			a[i][j]=b[3-i][j];
		}
	}

	return;
}

void move_left_without_merge(int (*a)[4]) {
	for(int i=0; i<4; i++) {
		for(int k=0; k<3; k++) {
			for(int j=1; j<4; j++) {
				if(a[i][j-1] == 0) {
					a[i][j-1] = a[i][j];
					a[i][j] = 0;
				}
			}
		}
	}

	return;
}

void merge(int (*a)[4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<3; j++) {
			if(a[i][j] == a[i][j+1]) {
				a[i][j] += a[i][j+1];
				a[i][j+1] = 0;
				score += a[i][j];
			}
		}
	}
	move_left_without_merge(a);

	return;
}

void merge2(int (*a)[4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<3; j++) {
			if(a[i][j] == a[i][j+1]) {
				a[i][j] += a[i][j+1];
				a[i][j+1] = 0;
			}
		}
	}
	move_left_without_merge(a);

	return;
}

void create_num(int (*a)[4]) {
	srand(time(NULL));
	int n = rand() % 16;
	int m = -1;

	int i, j;
	for(int k=0; k<16; k++) {
		for(i=0; i<4; i++) {
			for(j=0; j<4; j++) {
				if(a[i][j]==0) {
					m++;
					if(n==m) break;
				}
			}
			if(n==m) break;
		}
		if(n==m) break;
	}
	a[i][j] = 2;

	return;
}

void copy(int (*a)[4], int (*b)[4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			b[i][j] = a[i][j];
		}
	}

	return;
}

int check(int (*a)[4], int (*b)[4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(a[i][j] != b[i][j]) {
				return 1;
			}
		}
	}

	return 0;
}

int win_check(int (*a)[4]) {
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(a[i][j] == 2048) {
				return 1;
			}
		}
	}

	return 0;
}

int lose_check(int (*a)[4]) {
	int b[4][4];

	copy(a, b);
	move_left_without_merge(b);
    merge2(b);
	if(check(a,b))
		return 0;

	copy(a, b);
	rotate(b);
	move_left_without_merge(b);
    merge2(b);
	rotate(b);
	rotate(b);
	rotate(b);
	if(check(a,b))
		return 0;

	copy(a, b);
	rotate(b);
	rotate(b);
	rotate(b);
	move_left_without_merge(b);
    merge2(b);
	rotate(b);
	if(check(a,b))
		return 0;

	copy(a, b);
	rotate(b);
	rotate(b);
	move_left_without_merge(b);
    merge2(b);
	rotate(b);
	rotate(b);
	if(check(a,b))
		return 0;

	return 1;
}

void move(int (*a)[4], char c) {
	int b[4][4];

	if(c=='a') {
		copy(a, b);
		move_left_without_merge(a);
        merge(a);
	}
	else if(c=='w') {
		copy(a, b);
		rotate(a);
		move_left_without_merge(a);
        merge(a);
		rotate(a);
		rotate(a);
		rotate(a);
	}
	else if(c=='s') {
		copy(a, b);
		rotate(a);
		rotate(a);
		rotate(a);
		move_left_without_merge(a);
        merge(a);
		rotate(a);
	}
	else if(c=='d') {
		copy(a, b);
		rotate(a);
		rotate(a);
		move_left_without_merge(a);
        merge(a);
		rotate(a);
		rotate(a);
	}

	if(check(a, b))
		create_num(a);

	system("cls");
	print(a);

	return;
}

int main() {

	int a[4][4]={0};
	a[0][0] = 2;

    char c;

    system("cls");
    print(a);

    while(1) {
        c=getch();
        move(a, c);

        if(wincheck(a)) {
            printf("Win\n");
            break;
        }
        else if(losecheck(a)) {
            printf("Lose\n");
            break;
        }
    }

	return 0;
}
