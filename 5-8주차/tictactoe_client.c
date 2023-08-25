#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char* message);

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

int main(int argc, char* argv[])
{
	int clnt_sock;
	struct sockaddr_in serv_addr;
	char message[1024] = {0x00, };

	/* TCP연결지향형이고 ipv4 도메인을 위한 소켓을 생성 */
	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(clnt_sock == -1)
		error_handling("socket error");

	/* 인자로 받은 서버 주소 정보를 저장 */
	memset(&serv_addr, 0, sizeof(serv_addr));
	/* 서버주소체계는 IPv4이다 */
	serv_addr.sin_family = AF_INET;                  
	/* 서버주소 IP저장해주기(인자로 받은거 넘겨주기) */
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  
	/* 서버주소 포트번호 인자로 받은거 저장해주기 */
	serv_addr.sin_port = htons(atoi(argv[2]));

	/* 클라이언트 소켓부분에 서버를 연결! */
	if(connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect error");

	/* 연결이 성공적으로 되었으면 데이터 받기 */
	 while(1)
	 {
		if(read(clnt_sock, board, sizeof(board)-1) == -1)
			error_handling("read error");
	 
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
	write(clnt_sock, board, sizeof(board));
	
	/* 마무리 부분 */
	if(read(clnt_sock, board, sizeof(board)-1) == -1)
			error_handling("read error");
	PrintBoard(); 
    WhoWin(); 
	
	/* 통신 후 소켓 클로우즈 */
	close(clnt_sock);
	return 0;
}
void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}