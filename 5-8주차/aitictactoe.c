#include <stdio.h>

char gridChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

void draw(int b[9]) {
    printf(" %c | %c | %c\n",gridChar(b[0]),gridChar(b[1]),gridChar(b[2]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[3]),gridChar(b[4]),gridChar(b[5]));
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",gridChar(b[6]),gridChar(b[7]),gridChar(b[8]));
}

int win(const int board[9]) {
    /* 플레이어가 이겼다면 0을 반환하기를 결정한다. */
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    /* 보드에 있는 플레이어(자기 차례)의 위치는 어떻습니까? */
    int winner = win(board);
    if(winner != 0) return winner*player;

    move = -1;
    int score = -2; // 움직임을 잃는 것은 움직이지 않는 것을 선호한다.
    int i;
    for(i = 0; i < 9; ++i) { // 모든 움직임을 위해서
        if(board[i] == 0) { // 만약 아니라면
            board[i] = player; // 움직이도록 노력해라
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            } // 상대에게 가장 나쁜 것을 선택하십시오
            board[i] = 0; // 시도한 후 보드를 리셋해라
        }
    }
    if(move == -1) return 0;
    return score;	
}
/* 각각의 가능한 이동을 살펴보고 가능한 각 이동에 대해 보드를 뒤집고 다른 플레이어(그 부분 player*-1)인 척하고 가능한 각 이동을 시도합니다.
   thisScore에 대한 재귀 호출의 음수 반환 값으로 설정됩니다 minimax. 다른 플레이어에게 좋은 것은 우리 자신에게 나쁜 것과 같기 때문입니다.
   computerMove는 가능한 모든 이동을 살펴보고 minimax가능한 각 이동을 호출하고 최상의 결과를 가진 것을 사용합니다. */

void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    /* 주어진 노드에서 미니맥스 트리를 기반으로 점수를 반환합니다. */
    board[move] = 1;
}

void playerMove(int board[9]) {
    int move = 0;
    do {
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    } while (move >= 9 || move < 0 && board[move] == 0);
    board[move] = -1;
}

int main() {
    int board[9] = {0,0,0,0,0,0,0,0,0};
    /* 컴퓨터는 1, 플레이어는 -1 */
    printf("컴퓨터: O, 당신: X\nPlay (1)st or (2)nd? ");
    int player=0;
    scanf("%d",&player);
    printf("\n");
    unsigned turn;
    for(turn = 0; turn < 9 && win(board) == 0; ++turn) {
        if((turn+player) % 2 == 0)
            computerMove(board);
        else {
            draw(board);
            playerMove(board);
        }
    }
    switch(win(board)) {
        case 0:
            printf("비겼습니다.\n");
            break;
        case 1:
            draw(board);
            printf("당신이 졌습니다.\n");
            break;
        case -1:
            printf("당신이 이겼습니다!\n");
            break;
    }
}