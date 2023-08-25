#include <stdio.h>
#include <stdlib.h>

int board[3][3] = {0,};
int i, j, flag, win, xin, yin, x, y;

int PrintBoard(void) // 보드판 출력 함수
{
	system("clear");
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if(board[i][j] == 1)
					printf("O |");
				else if(board[i][j] == 2)
					printf("X |");
				else if(board[i][j] == 0)
					printf("  |");
			}
			printf("\n");
		} // 출력 부분
	return 0;
}

int Check(void) // 검사 함수
{
	flag = 0;
		for(i = 0; i < 3; i++) // 가로
		{
			if((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
			{
				if(board[i][1] == 1) // O가 이겼을 경우에
					win = 1, flag = 1;
				if(board[i][1] == 2) // X가 이겼을 경우에
					win = 2, flag = 1;
			}
		}
		for(i = 0; i < 3; i++) // 세로
		{
			if((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
			{
				if(board[1][i] == 1) // O가 이겼을 경우에
					win = 1, flag = 1;
				if(board[1][i] == 2) // X가 이겼을 경우에
					win = 2, flag = 1;
			}
		}
		for(i = 0; i < 3; i++) // 대각선
		{
			if((board[0][0] == board[1][1]) && (board[1][1] == board[2][2]))
			{
				if(board[1][1] == 1) // O가 이겼을 경우에
					win = 1, flag = 1;
				if(board[1][1] == 2) // X가 이겼을 경우에
					win = 2, flag = 1;
			}
		}
		for(i = 0; i < 3; i++) // 대각선
		{
			if((board[0][2] == board[1][1]) && (board[1][1] == board[2][0]))
			{
				if(board[1][1] == 1) // O가 이겼을 경우에
					win = 1, flag = 1;
				if(board[1][1] == 2) // X가 이겼을 경우에
					win = 2, flag = 1;
			}
		}
	return 0;
}

int WhoWin(void) // 마무리 출력 함수
{
	if(win == 1)
        printf("\n\nO이 이겼습니다.\n"); 
    else if(win == 2)
        printf("\n\nX이 이겼습니다.\n");
    else
        printf("\n\n비겼습니다.\n");     
    return 0;
}
	

int main()
{
	/* 플레이어가 O이다. */
	srand((unsigned int) time(NULL));
	
	while(1)
	{
		PrintBoard(); // 보드판 출력 함수
       
        printf("O 차례 - y x 입력 : ");
		scanf("%d %d", &y,&x);
		if(board[y][x] == 0) // 보드가 비어있다면
			board[y][x] = 1; // o를 놓는다.
		
		/* 검사부분 */
		Check();
		
		if(flag == 1)
			break; // 나간다
		
		flag = 1; // 승패가 아닌 비기는 경우를 위한 코드 (없으면 비길때 break가 안먹음 -> 승 패는 위의 코드에서 갈릴 것이고, 코드가 비어있다면 밑에 if문 때문에 flag가 0이 되서 계속 진행될 것이고, 코드가 다 찼지만 비긴다면 flag=1이니깐 break된다.) 
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if(board[i][j] == 0)
					flag = 0; // flag = 1이면 빠져나온다
			}
		}
		if(flag == 1)
			break; // 나간다
		
		/* X차례 */
		PrintBoard();
		
		printf("X 차례 - y x 입력 : ");
		scanf("%d %d", &y,&x);
		if(board[y][x] == 0) // 보드가 비어있다면
			board[y][x] = 2; // o를 놓는다.
		
		/* 검사부분 */
		Check();
		
		if(flag == 1)
			break; // 나간다
		
		flag = 1; 
		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if(board[i][j] == 0)
					flag = 0; // flag = 1이면 빠져나온다
			}
		}
		if(flag == 1)
			break; // 나간다
	} 
	
	/* 마무리 부분 */
	PrintBoard(); 
    WhoWin();    
	
    return 0;
}