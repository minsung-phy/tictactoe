#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
	int endTime = (unsigned)time(NULL); // 끝나는 시간
	endTime += 6; // 6초
	
	while(1)
	{
		int startTime = (unsigned)time(NULL); // 현재시간 (while)문을 통해 점점 늘어나는 시간
		printf("%d초 \n", endTime - startTime); // 6-0, 6-1, 6-2, 6-3, 6-4, 6-5, 6-6
		sleep(0.01); // 0.01초 지연
		system("clear"); // 화면을 지운다
		if(endTime - startTime == 0) // 만약 시간이 0초라면 종료
		{
			printf("종료되었습니다.");
			return 0;
		}
	}
}