#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE sizeof(struct sockaddr_in) 

int play();
int menu(void);
void catcher(int sig);
void mapBoard(char playBoard[][3]);
void showLogo();
void help(void);
void playerWinhandler(int signum);
int te=0;

int main(void)
{
        while(1)
        {
        /*해당문 선택 및 실행*/
        switch(menu())
                {
                case 1:
                {
                printf("\nPlay를 선택하셨습니다.\n\n");
                play();
                break;
                }
                case 2:
                {
                printf("\nHelp를 선택하셨습니다.\n\n");
                help();
                break;
                }
                case 3:
                {
                printf("\nquit를 선택하셨습니다.\n\n");
                exit(0);
                break;
                }
                default:
                {
                printf("\n잘못된 메뉴를 선택하셨습니다.\n\n");
                break;
                }
                }
        }
}

int play(void)
{
        void result(char [],char []);
        static struct sigaction act;
        act.sa_handler = SIG_IGN;
        sigfillset(&(act.sa_mask));
        sigaction(SIGTSTP, &act, 0);

        signal(SIGUSR1,playerWinhandler);
        signal(SIGUSR2,playerWinhandler);

        struct sockaddr_in server = {AF_INET, 8001};
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        int sockfd,i;
        int row,column,choice;
        int iclientRead;
        char input;
        char a[2][40];
        char pid[4];
        char clientRead[3][3];
        char clientWrite[1];

        char numberBoard [3][3] = {                                                     /* 선택할 수 있는 위치 표시 */
                                                {'1','2','3'},
                                                {'4','5','6'},
                                                {'7','8','9'}
                                  };

        char playBoard [3][3] =   {                                                     /* 실제 게임 상태를 표시 */
                                                {' ',' ',' '},
                                                {' ',' ',' '},
                                                {' ',' ',' '}
                                  };

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                perror("Socket 실패");
                exit(1);
        }
		
		if ( connect (sockfd, (struct sockaddr *)&server, SIZE) == -1)
        {
                perror("Connect 실패");
                exit(1);
        }

        read(sockfd,a,sizeof(a));
        printf("%s\n",a[0]);

        if(strcmp(a[1],"0")==0)
        {
                int num1 = getpid();
                sprintf(pid,"%d",num1);
                write(sockfd, pid, sizeof(pid));
                read(sockfd,a,sizeof(a));
                printf("%s\n",a[0]);
                showLogo();
        }

        if(strcmp(a[1],"2")==0)
        {
        int num2 = getpid();
        sprintf(pid,"%d",num2);
        write(sockfd, pid, sizeof(pid));
        }

        if (strcmp(a[1],"1")!=0)
        {

                showLogo();
                mapBoard(numberBoard);
                printf("\n    번호판\n\n");
                for(;;)
                        {
                        printf("\n플레이어 %d, 당신의 '%c'를 놓을 사각형의 번호를 입력하세요. \n",(strcmp(a[1], "1")==0)?1:2,(strcmp(a[1], "1")==0)?'X':'O');
                        scanf("%s",clientWrite);

                        choice = atoi(clientWrite);
                        row = --choice/3;
                        column = choice%3;

                        if(choice<0 || choice>9 || playBoard [row][column]>'9'|| playBoard [row][column]=='X' || playBoard [row][column]=='O')
                                printf("잘못된 입력입니다. 다시 입력하세요.\n\n");
						else
                        {
                                playBoard[row][column] = (strcmp(a[1], "1")==0)?'X':'O';                              
                                break;
                        }
                        }

                write(sockfd, clientWrite, sizeof(clientWrite));
                system("clear");
                showLogo();
                mapBoard(playBoard);
                printf("\n현재 플레이 보드\n\n");
        }

        for(input = 'x';;)
        {
                if (input == '\n')
                {       if (te==0)
                        {
                                mapBoard(numberBoard);
                                printf("\n    번호판\n\n");
                        }
                        for(;;)
                        {
                                if (te==0)
                                {
                                        printf("\n플레이어 %d, 당신의 '%c'를 놓을 사각형의 번호를 입력하세요. \n",(strcmp(a[1], "1")==0)?1:2,(strcmp(a[1], "1")==0)?'X':'O');
                                        scanf("%s",clientWrite);

                                        choice = atoi(clientWrite);
                                        row = --choice/3;
                                        column = choice%3;

                                        if(choice<0 || choice>9 || playBoard [row][column]>'9'|| playBoard [row][column]=='X' || playBoard [row][column]=='O')
                                                printf("잘못된 입력입니다. 다시 입력하세요.\n\n");

                                        else
                                        {
                                                playBoard[row][column] = (strcmp(a[1], "1")==0)?'X':'O';
                                                break;
                                        }
                                }
                        }
						write(sockfd, clientWrite, sizeof(clientWrite));
                        system("clear");
                        showLogo();
                        mapBoard(playBoard);
                        printf("\n현재 플레이 보드\n\n");
                        if (te==1)
                                {
                                printf("플레이어 1이 이겼습니다!!\n");
                                exit(0);
                                }
                        if (te==2)
                                {
                                printf("플레이어 2가 이겼습니다!!\n");
                                exit(0);
                                }
                }

                if (read(sockfd, clientRead, sizeof(clientRead)) >0)
                {
                        system("clear");
                        showLogo();
                        memcpy(playBoard, clientRead, sizeof(playBoard));       // 서버 측에서 받은 배열의 내용을 playBoard 배열에 복사
                        mapBoard(playBoard);
                        printf("\n현재 플레이 보드\n\n");
                        input = '\n';
                        if (te==1)
                                {
                                printf("플레이어 1이 이겼습니다!!\n");
                                exit(0);
                                }
                        if (te==2)
                                {
                                printf("플레이어 2가 이겼습니다!!\n");
                                exit(0);
                                }
                }
                else
                {
                        printf("당신이 이겼습니다!! 감사합니다. 또 다시 플레이 해주세요 :D\n");
                        close(sockfd);
                        exit(1);
                }
}
}

void showLogo()
{
        printf("--------------------------------------------------------------------------\n");
        printf("| # # #   # # #    # # #   # # #    #      # # #  # # #   # # #   # # #  |\n");
        printf("|   #       #      #   #     #     #  #    #   #    #     #   #   #      |\n");
        printf("|   #       #      #         #    #    #   #        #     #   #   # # #  |\n");
        printf("|   #       #      #   #     #   # #  # #  #   #    #     #   #   #      |\n");
        printf("|   #     # # #    # # #     #  #        # # # #    #     # # #   # # #  |\n");
        printf("--------------------------------------------------------------------------\n");
}

void mapBoard(char playBoard[][3])
{
        printf(" _________________\n");
        printf("|     |     |     | \n");
        printf("|  %c  |  %c  |  %c  |\n",playBoard[0][0],playBoard[0][1],playBoard[0][2]);
        printf("|_____|_____|_____|\n");
        printf("|     |     |     |\n");
        printf("|  %c  |  %c  |  %c  |\n",playBoard[1][0],playBoard[1][1],playBoard[1][2]);
        printf("|_____|_____|_____|\n");
        printf("|     |     |     |\n");
        printf("|  %c  |  %c  |  %c  |\n",playBoard[2][0],playBoard[2][1],playBoard[2][2]);
        printf("|_____|_____|_____|\n");
}

void catcher(int sig)
{
        printf("죄송합니다. 당신의 차례가 끝난 후에 그만둘 수 있습니다. \n");
}

/*menu function*/
int menu(void)
{
        int reply;
        /*display menu options*/
        printf("--------------------------------------------------------------------------\n");
        printf("| # # #   # # #    # # #   # # #    #      # # #  # # #   # # #   # # #  |\n");
        printf("|   #       #      #   #     #     #  #    #   #    #     #   #   #      |\n");
        printf("|   #       #      #         #    #    #   #        #     #   #   # # #  |\n");
        printf("|   #       #      #   #     #   # #  # #  #   #    #     #   #   #      |\n");
        printf("|   #     # # #    # # #     #  #        # # # #    #     # # #   # # #  |\n");
        printf("--------------------------------------------------------------------------\n");


        printf("Play를 하려면 1을 입력하세요.\n\n");
        printf("Help를 요청하려면 2을 입력하세요.\n\n");
        printf("Quit를 하려면 3을 입력하세요.\n\n");

		/*scan for user entry*/
        scanf("%d", &reply);

        return reply;
}

void playerWinhandler(int signum)
{
    if (signum == SIGUSR1)
    {
        te=1;
    }

    if (signum == SIGUSR2)
    {
        te=2;
    }
}

void help(void)
{
printf("틱택토는 X와 O는 번갈아 가며 3×3 공간을 표시합니다. 가로, 세로 또는 대각선으로 세 개의 각각의 마크를 배치하는데 성공한 플레이어가 게임에서 승리합니다.\n\n");
}
