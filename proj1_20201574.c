#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <termios.h>
#include <sys/time.h>
#include <unistd.h>

int b[25][40], time_out, game_over, n, m;
int q,score=0,count=0;
int i,j,q,k,c,d,l=0;
int a=0;
int z=39;
int temp_val = 0;

void init(){
	n = 25, m = 40;
	time_out = game_over = 0;
	q=n/2;
	b[q][9]='@';
	/* user code */
	/* init board */

}

void draw_board(){
	system("clear");
	/* user code */
	printf("\nScore: \033[31m%d\033[0m\n",score);

	for(i=0;i<n;i++)
	{
	printf("\r");
		for(j=0;j<m;j++)
		{
			if(b[i][j]=='+')
			{
			printf("\033[32m%c\033[0m",b[i][j]);
			}
			else
			{
			printf("%c",b[i][j]);
			}
		}
	printf("\n");
	}
	b[q][9]=' ';
}


void Do(int sig) {
	/* processor call this function for every 0.2 sec */

	/* temp code */
	system("clear");
	printf("%d. Call Do function!", ++temp_val);

	/* user code */
	/* update board b[25][40] */

	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			if(b[i][j]=='+')
			{
			b[i][j-1]=b[i][j];
			b[i][j]=' ';
			}
			else
			b[i][j]=' ';
		}
	}
	b[q][9]='@';
	

	for(i=0;i<n;i++)
	{
	b[i][39]='+';
	}
	for(i=k;i<k+10;i++)
	{
	b[i][39]=' ';
	}
	if(l==25*a+9)
	{
	k=rand()%(14+1-0)+0;
	a=a+1;
	}
	
	l=l+1;
	
	for(i=0;i<n;i=i+1)
	{
		if(b[i][29]=='+'||b[i][24]=='+')
		{
			for(j=0;j<n;j=j+1)
			{
			b[j][39]=' ';
			}
		}
	}
	
	
	
	for(d=0;d<n;d=d+1)
	{
		if(b[d][9]=='+')
		{
		count=count+1;
			if(count%150==0)
			{
			score=count/150;
			}
			else
			{
			score=(count/150)+1;
			}
		}
	}

	/* update bird position*/
	/* if game over */ 
	// game over = 1;
	if(b[0][9]=='@'||b[-1][9]=='@'||b[-2][9]=='@'||b[24][9]=='@'||b[25][9]=='@')
	{
	game_over=1;
	}
	if(b[q-1][9]=='+')
	{
	game_over=1;
	}
	draw_board();
	/* do not erase this code */
	time_out = 0;
}

int getch(void)
{
	char   ch;
	int   error;
	static struct termios Otty, Ntty;

	fflush(stdout);
	tcgetattr(0, &Otty);
	Ntty = Otty;
	Ntty.c_iflag = 0;
	Ntty.c_oflag = 0;
	Ntty.c_lflag &= ~ICANON;
#if 1
	Ntty.c_lflag &= ~ECHO;
#else
	Ntty.c_lflag |= ECHO;
#endif
	Ntty.c_cc[VMIN] = 0;
	Ntty.c_cc[VTIME] = 1;

#if 1
#define FLAG TCSAFLUSH
#else
#define FLAG TCSANOW
#endif

	if (0 == (error = tcsetattr(0, FLAG, &Ntty)))
	{
		error = read(0, &ch, 1);
		error += tcsetattr(0, FLAG, &Otty);
	}

	return (error == 1 ? (int)ch : -1);
}


int GetCommand() {
	int ch = getch();

	switch (ch)
	{
	case 'd':
	case 'D': return 0;
	case 'w':
	case 'W': return 1;
	case 'a':
	case 'A': return 2;
	case 's':
	case 'S': return 3;
	default: return -1;
	}

	return -1;
}


int main() {
	int command = -1;
	srand(time(NULL));
	static struct sigaction act, oact;
	act.sa_handler = Do;
	sigaction(SIGALRM, &act, NULL);

	init();
	draw_board();

	do {

		if (time_out == 0) {
			ualarm(200000, 0); /* 20,000 = 0.2 sec, call Do function */
			time_out = 1;
		}
		c = command;
		command = GetCommand();
		/* user code */
		if(command==0||command==1||command==2||command==3)
		{
		q=q-2;
		}
		else if(command==-1)
		{
			if(c==0||c==1||c==2||c==3)
			{
			q=q-1;
			}
			else
			{
			q=q+1;
			}
		}
	} while (!game_over);

	system("clear");
	printf("game over!\n");
}
