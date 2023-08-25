#include <stdio.h>
#include <stdlib.h> //atoi를 사용하려면 있어야함
#include <string.h> // memset 등
#include <unistd.h> //sockaddr_in, read, write 등
#include <arpa/inet.h>  //htnol, htons, INADDR_ANY, sockaddr_in 등
#include <sys/socket.h> // socket 생성하려면 있어야함
void error_handling(char * message);

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
    int serv_sock;
    int clnt_sock;
   
    /* sockaddr_in은 소켓 주소의 틀을 형셩해주는 구조체로 AF_INET일 경우 사용 */
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr; //accept함수에서 사용됨.
    socklen_t clnt_addr_size;
   
    /* TCP연결지향형이고 ipv4 도메인을 위한 소켓을 생성 */
    serv_sock=socket(PF_INET, SOCK_STREAM, 0); 
    if(serv_sock == -1)
         error_handling("socket error");
    
    /* 주소를 초기화한 후 IP주소와 포트 지정 */
    memset(&serv_addr, 0, sizeof(serv_addr)); 
    serv_addr.sin_family=AF_INET;                //타입: ipv4
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //ip주소
    serv_addr.sin_port=htons(atoi(argv[1]));     //port
    
    /* 소켓과 서버 주소를 바인딩 */
    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
    	error_handling("bind error");
    
    /* 연결 대기열 5개 생성 */
    if(listen(serv_sock, 5)==-1)
    	error_handling("listen error");
    
    /* 클라이언트로부터 요청이 오면 연결 수락 */
    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1)
        error_handling("accept error");
        
    /*-----데이터 전송-----*/
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
		
		write(clnt_sock, board, sizeof(board));
		
		if(read(clnt_sock, board, sizeof(board)-1) == -1)
		error_handling("read error");
		PrintBoard();
	}	
	/* 마무리 부분 */
	PrintBoard(); 
    WhoWin(); 
    write(clnt_sock, board, sizeof(board));
	
    /* 소켓들 닫기 */
    close(clnt_sock);
    close(serv_sock);
    
    return 0;
	
}
void error_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n', stderr);
    exit(1);
}