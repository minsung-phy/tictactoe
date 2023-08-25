#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{ 
    int board[3][3]={0,};
    int i, j, flag, win, xin,yin;
    int x, y;
    /* 플레이어가 O이다. */
    srand((unsigned int )time(NULL));
   
    while(1)
    {
        system("clear");
        for(i=0 ; i<3 ; i++)
        {
                for(j=0 ; j<3 ; j++)
                {
                        if(board[i][j] == 1)
                             printf("O |");
                        else if(board[i][j] == 2)
                             printf("X |");
                        else if(board[i][j] ==0)
                             printf("  |");
                }
                printf("\n");
        } // 출력부분
       
        printf("O 차례 - y x 입력 : ");
        scanf("%d %d", &x,&y);
        if(board[x][y] == 0) // 놓이지 않았으면
                board[x][y] =1; // o를 놓는다.
        
        /* --------------검사부분----------------- */
        flag =0;
        for(i=0 ; i<3; i++) // 가로
        {
                if((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
                {
                        if(board[i][0] == 1) // o이 이겼을 경우에
                                   win =1,flag =1;
                        if(board[i][0] == 2) // x이 이겼을 경우에
                                   win =2, flag =1;
                }
        }
        for(i=0 ; i<3; i++) // 세로
        {
                if((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
                {
                        if(board[0][i] == 1) // o이 이겼을 경우에
                                   win =1,flag =1;
                        if(board[0][i] == 2) // x이 이겼을 경우에
                                   win =2, flag =1;
                }
        }
        if((board[0][0] == board[1][1]) &&(board[2][2] == board[1][1])) // 대각선
        {
                     if(board[0][0] == 1) // o이 이겼을 경우에
                                   win =1,flag =1;
                     if(board[0][0] == 2) // x이 이겼을 경우에
                                   win =2, flag =1;
        }
        if((board[0][2] == board[1][1]) &&(board[2][0] == board[1][1])) // 대각선
        {
                     if(board[0][2] == 1) // o이 이겼을 경우에
                                   win =1,flag =1;
                     if(board[0][2] == 2) // x이 이겼을 경우에
                                   win =2, flag =1;
        }  
        if(flag ==1)
              break; // 나간다  
                   
        flag =1;
        for(i=0 ; i<3; i++)
        {
                for(j=0 ; j<3 ; j++)
                {     
                       if(board[i][j] == 0)
                              flag = 0; // flag =1 이면 빠져나온다.
                }
        }
        if(flag ==1)
              break; // 나간다 
             
/*-------여기부터 X의 차례이며 인공지능을 넣어야할 부분입니다-------*/                    
        system("clear");             
        for(i=0 ; i<3 ; i++)
        {
                for(j=0 ; j<3 ; j++)
                {
                        if(board[i][j] == 1)
                             printf("O |");
                        else if(board[i][j] == 2)
                             printf("X |");
                        else if(board[i][j] ==0)
                             printf("  |");
                }
                printf("\n");
        } // 출력부분
        /* 여기서 자동입력! 인공지능으로 */
        /* 두개이상 이어진걸 찾아서 검사해서 한쪽에 놓는다. */
       
        /* =================================================================================================================================== */
        for(i=0 ; i<3; i++) // 반복하기
        {
            if((board[0][0] == board[1][1]) && (board[1][1]==1) && (board[2][2] == 0)) // 대각선
                    {board[2][2] = 2; break;}
            else if((board[2][2] == board[1][1]) && (board[1][1]==1)&& (board[0][0] == 0))
                          {board[0][0] = 2; break;}
            else if((board[2][2] == board[0][0]) && (board[0][0]==1)&& (board[1][1] == 0)) // 대각선 가운데 막기
                          {board[1][1] = 2; break;}             
            else if((board[0][2] == board[1][1]) && (board[1][1]==1) && (board[2][0] == 0)) // 대각선
                          {board[2][0] = 2; break;}
            else if((board[2][0] == board[1][1]) && (board[1][1]==1) &&(board[0][2] == 0))
                          {board[0][2] = 2; break;}
            else if((board[2][0] == board[0][2]) && (board[0][2]==1) &&(board[1][1] == 0)) // 대각선 가운데 막기
                          {board[1][1] = 2; break;}
                   
            else
            {
                    if((board[i][0] == board[i][1]) &&(board[i][1]== 1) && (board[i][2] == 0)) // 가로 왼쪽
                                 {board[i][2] = 2; break;}
                   
                    else if((board[i][1] == board[i][2]) &&(board[i][1]== 1) &&(board[i][0] == 0)) // 가로 오른쪽
                                 {board[i][0] = 2;break;}
                                
                    else if((board[i][0] == board[i][2]) &&(board[i][0]== 1) &&(board[i][1] == 0)) // 가로 양옆
                                 {board[i][1] = 2;break;}
                   
                    else if((board[0][i] == board[1][i]) &&(board[1][i]== 1) &&(board[2][i] == 0)) // 세로
                                 {board[2][i] = 2; break;}
                  
                    else if((board[1][i] == board[2][i]) &&(board[1][i]== 1) &&(board[0][i] == 0))
                                 {board[0][i] = 2;break;}
                    else if((board[0][i] == board[2][i]) &&(board[0][i]== 1) &&(board[1][i] == 0))
                                 {board[1][i] = 2;break;}
                   
                    else if(i>=2) // 이제 위에거 다 해당안되면서.... i가 2 즉 끝에 도달했을때 랜덤으로 아무데에나 둔다.
                    {         while(1)
                            {
                                    xin= rand()%3;
                                    yin= rand()%3;
                                    if(board[yin][xin] == 0) // yx임을 주의해야한다.
                                        {board[yin][xin] =2; break;}
                            }
                    }          
            }
        }
        /* --------------------------------------- 인공지능부분 끝남 ------------------------------------------- */
        /* ---------------검사부분---------------- */
        flag =0;
        for(i=0 ; i<3; i++) // 가로
        {
                if((board[i][0] == board[i][1]) && (board[i][1] == board[i][2]))
                {
                        if(board[i][0] == 1) // o이 이겼을 경우에
                                   win =1,flag =1;
                        if(board[i][0] == 2) // x이 이겼을 경우에
                                   win =2, flag =1;
                }
        }
        for(i=0 ; i<3; i++) // 세로
        {
                if((board[0][i] == board[1][i]) && (board[1][i] == board[2][i]))
                {
                        if(board[0][i] == 1) // o이 이겼을 경우에
                                   win =1,flag =1;
                        if(board[0][i] == 2) // x이 이겼을 경우에
                                   win =2, flag =1;
                }
        }
        if((board[0][0] == board[1][1]) &&(board[2][2] == board[1][1])) // 대각선
        {
                     if(board[0][0] == 1) // o이 이겼을 경우에
                                   win =1,flag =1;
                     if(board[0][0] == 2) // x이 이겼을 경우에
                                   win =2, flag =1;
        }
        if((board[0][2] == board[1][1]) &&(board[2][0] == board[1][1])) // 대각선
        {
                     if(board[0][2] == 1) // o이 이겼을 경우에
                                   win =1,flag =1;
                     if(board[0][2] == 2) // x이 이겼을 경우에
                                   win =2, flag =1;
        }  
        if(flag ==1)
              break; // 나간다  
                   
        flag =1;
        for(i=0 ; i<3; i++)
        {
                for(j=0 ; j<3 ; j++)
                {     
                       if(board[i][j] == 0)
                              flag = 0; // flag =1 이면 빠져나온다.
                }
        }
        if(flag ==1)
              break; // 나간다
        /*---------------------------------------*/              
    }
   
    /*-------------------------------------------------끝난것 -------------------------------------------------------------*/
    system("clear");
        for(i=0 ; i<3 ; i++)
        {
                for(j=0 ; j<3 ; j++)
                {
                        if(board[i][j] == 1)
                             printf("O |");
                        else if(board[i][j] == 2)
                             printf("X |");
                        else if(board[i][j] ==0)
                             printf("  |");
                }
                printf("\n");
        } // 출력부분
       
    if(win ==1)
        printf("\n\nO이 이겼습니다.\n"); 
    else if(win ==2)
        printf("\n\nX이 이겼습니다.\n");
    else
        printf("\n\n비겼습니다.\n");     
    return 0;

}  