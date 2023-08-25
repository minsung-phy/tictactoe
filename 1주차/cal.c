#include <stdio.h>
#include <math.h>
#include <stdlib.h> // exit
#include <unistd.h> // cls, sleep

int a;
char oper;
float num1;
float num2;
double n1;

int main(void)
{
	printf("1번: 일반계산기, 2번: 공학용 계산기 (한 자리 계산), 3번: 공학용 계산기 (두 자리 계산)\n");
	printf("1,2 or 3을 입력하세요. 선택에 따라 계산기가 설정됩니다. \n");
	printf("입력: \n");
	scanf("%d", &a);
	if(a==1){ // 일반 계산기
		printf("사칙연산만 가능한 일반계산기입니다. 입력하세요. \n");
		scanf("%f %c %f", &num1, &oper, &num2);
		
		switch(oper)
		{
			case '+':
				printf("%f %c %f = %f \n", num1, oper, num2, num1+num2);
				break;
			case '-':
				printf("%f %c %f = %f \n", num1, oper, num2, num1-num2);
				break;
			case '*':
				printf("%f %c %f = %f \n", num1, oper, num2, num1*num2);
				break;
			case '/':
				printf("%f %c %f = %f \n", num1, oper, num2, num1/num2);
				break;
			default:
				printf("Fail \n");
		}
	}
	else if(a==2){ // 공학용 계산기 (한 자리 계산)
		printf("한 자리 계산만 가능한 공학용 계산기입니다. \n");
		scanf("%c %f", &oper, &num1);
		
		switch(oper)
		{
			case 'sin': // 오류 발생
				printf("%c %lf = %lf \n", oper, n1, double sin(n1));
				break;
			case '-':
				printf("%f %c %f = %f \n", num1, oper, num2, num1-num2);
				break;
			case '*':
				printf("%f %c %f = %f \n", num1, oper, num2, num1*num2);
				break;
			case '/':
				printf("%f %c %f = %f \n", num1, oper, num2, num1/num2);
				break;
			default:
				printf("Fail \n");
		}
	}
	else if(a==3){ // 공학용 계산기 (두 자리 계산)
		
	}	
	else{
        printf("잘못입력하셨습니다. 프로그램이 5초후 종료됩니다.\n");
        sleep(1);
        system("clear"); //콘솔창 clear
        sleep(5);
        exit(0);
	}
	
}	

