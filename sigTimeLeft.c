#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int timeLeft(int month, int day){
	time_t t;
	struct tm *tmp;
	char buf1[16];
	char buf2[64];
  
	time(&t);
	tmp = localtime(&t);
  
	if (strftime(buf1, 16, "Current Date and Time: %r, %a %b %d, %Y", tmp) == 0)
		printf("");
	else
		printf("%s\n", buf1);
	if (strftime(buf2, 64, "Current Date and Time: %r, %a %b %d, %Y", tmp) == 0)
		printf("");
	else
		printf("%s\n", buf2);

	/* getting values of current month, day, year, hour, minute, and second for calculations */
	int c_mon, c_day, c_year, c_hour, c_min, c_sec;
	c_mon = tmp->tm_mon;
	c_day = tmp->tm_mday + 1;
	c_year = tmp->tm_year + 1900;
	c_hour = tmp->tm_hour;
	c_min = tmp->tm_min;
	c_sec = tmp->tm_sec;

	/* calculating the time until user input date */
	int t_mon, t_day, t_hour, t_min, t_sec;
	t_mon = abs((month - c_mon) * 31);
	t_day = abs((day - c_day) + t_mon);
	t_hour = 24 - c_hour;
	t_min = 60 - c_min;
	t_sec = 60 - c_sec;

	printf("Until target date: %d days, %d hours, %d minutes, %d seconds\n", t_day, t_hour, t_min, t_sec);

	/* calculating time in seconds */
	int s_day, s_hour, s_min, s_sec;
	s_day = t_day * 86400;
	s_hour = t_hour * 3600;
	s_min = t_min * 60;
	s_sec = s_day + s_hour + s_min + t_sec;

	printf("Total number of seconds of the target date: %d\n\n", s_sec);

	return 0;
}

void catch_alarm(int signum){
	static int count = 0;
	count++;
  
	if(count%3==0){
		alarm(5);
		return;
	}
  
	printf("%d By SIGALARM: \n", count-1);
	timeLeft(12, 25);

	alarm(3);
}

void catch_int(int signum){
	static int count = 0;
	char answer;

	do{
		count++;
    
		if(count < 3){
			printf("%d By SIGINT: \n", count);
			timeLeft(7, 4);
      }
  
		if(count == 3){
			signal(SIGINT, SIG_DFL);
      }
    
		printf("Quit? (y/n): ");
		scanf("%s", &answer);

		if(answer == 'y' || answer == 'Y'){
			signal(SIGINT, SIG_DFL);
   	 }
	}while(answer == 'n' || answer == 'N');
  
	return;
}

int main(){
	signal(SIGALRM, catch_alarm);
	signal(SIGINT, catch_int);

	alarm(3);
  
	for(;;){
		pause();
	}
}

