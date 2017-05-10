/* Copyrightⓒ 2014. 김희원 all rights reserved.
   해야할것 : 플레이어 이름 저장 , 랭킹*/

///////전처리구문///////
#include <stdio.h>										
#include <Windows.h>									
#include <conio.h>
#include <string.h>
#include <time.h>

/////////함수 선언///////// 
void gotoxy(int x, int y); //API
void gamecontrol(void);	//게임컨트롤
void Omok_Pan(void);	//오목판 그리기
void Push(int Board[][20], char key,int *x, int *y); //입력받았을때 처리하는 함수 
void Erase(int x, int y); //오목돌 지우기 
void Draw(void); //오목알 그리기
void GameRule(void); //도움말 
void Omok_Save(int Board[][20],int x, int y); //오목알 저장
void Omok_print(int Board[][20]); //오목알 출력 
int Win_Check(int Board[][20]); //승리 체크
void removeCursor(void); //커서 없애기
void GamePlayer(void); //플레이어 이름 저장 
void GameTitle(void); //게임 로고 
void Rank(void); //랭킹 
void Status1(void); //1p 차례일때 
void Status2(void); //2p 차례일때
int Game_Dol=2; //1은 흰돌 , 2는 흑돌
char player1[10];
char player2[10];

//////API//////
void gotoxy(int x, int y) 
{
	COORD Pos;									
	Pos.X = x;										
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}

void SetColor(int color) 
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void removeCursor(void)
{
	CONSOLE_CURSOR_INFO cur;
 	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cur);
 	cur.bVisible=0;
 	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cur);
}

//////게임 로고////// 
void GameTitle(void)
{
	srand((unsigned)time(NULL));
	int x = 12, y = 19;
	
	gotoxy(3,2);SetColor(11);printf("######## #### ##     ## ########");    
	gotoxy(3,3);SetColor(11);printf("##        ##  ##     ## ##      ");    
	gotoxy(3,4);SetColor(11);printf("##        ##  ##     ## ##      ");    
	gotoxy(3,5);SetColor(11);printf("######    ##  ##     ## ######  ");    
	gotoxy(3,6);SetColor(11);printf("##        ##   ##   ##  ##      ");    
	gotoxy(3,7);SetColor(11);printf("##        ##    ## ##   ##      ");    
	gotoxy(3,8);SetColor(11);printf("##       ####    ###    ########");    
	gotoxy(38,2);SetColor(10);printf("######## ########  ######## ########");
	gotoxy(38,3);SetColor(10);printf("   ##    ##     ## ##       ##      ");
	gotoxy(38,4);SetColor(10);printf("   ##    ##     ## ##       ##      ");
	gotoxy(38,5);SetColor(10);printf("   ##    ########  ######   ######  ");
	gotoxy(38,6);SetColor(10);printf("   ##    ##   ##   ##       ##      ");
	gotoxy(38,7);SetColor(10);printf("   ##    ##    ##  ##       ##      ");
	gotoxy(38,8);SetColor(10);printf("   ##    ##     ## ######## ########\n");
	gotoxy(30,12);SetColor(13);printf("Five Tree Ver 1.0");
	gotoxy(24,15);SetColor(14);printf("Made By 평촌경영고등학교 김희원");
	gotoxy(15,19);SetColor(11);printf("게임 시작");
	gotoxy(35,19);SetColor(10);printf("게임 방법");
	gotoxy(55,19);SetColor(13);printf("랭킹 확인");
	
	//////에이싱크로////// 
	while(1)
	{
		int col = rand() % ((15 - 1) + 1) - 1;
		
		gotoxy(x, y);
		printf("  ");
	
		if(GetAsyncKeyState(VK_RIGHT) & 0x8000 && x == 12)
			x = 32;
			
		else if(GetAsyncKeyState(VK_RIGHT) & 0x8000 && x == 32)
			x = 52;
		
		else if(GetAsyncKeyState(VK_LEFT) & 0x8000 && x == 52)
			x = 32;
			
		else if(GetAsyncKeyState(VK_LEFT) & 0x8000 && x == 32)
			x = 12;
		
		if(GetAsyncKeyState(VK_RETURN) & 0x8000 && x == 12)
		{
			fgetc(stdin);
			GamePlayer();
		}
			
			
		else if(GetAsyncKeyState(VK_RETURN) & 0x8000 && x == 32)
			GameRule();
			
		else if(GetAsyncKeyState(VK_RETURN) & 0x8000 && x == 52)
			Rank();
			
		gotoxy(x, y);
		SetColor(col);
		printf("▶");
		Sleep(100);
	}
}

//////랭킹////// 
void Rank(void)
{

}

//////오목판 그리기//////
void Omok_Pan(void)
{
	int i,j;											
	
	puts("┌┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┐");
	for(i=0; i<17 ; i++)
	puts("├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤");
	puts("└┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┘");
	SetColor(7);
}

//////메인함수////// 
int main(void)
{
	while(1)
	{
		removeCursor();
		GameTitle();
		GamePlayer();
	}
}

//////유저 정보 저장////// 
void GamePlayer(void)
{
	system("cls");
	SetColor(10);printf("\t\t\t\tF");
	SetColor(11);printf("I");
	SetColor(12);printf("V");
	SetColor(13);printf("E");
	SetColor(14);printf(" TREE");
	SetColor(10);gotoxy(25,4);printf("1p(●) 플레이어의 이름 : ");
	scanf("%s", player1);
	SetColor(11);gotoxy(25,8);printf("2p(○) 플레이어의 이름 : "); 
	scanf("%s", player2);
	SetColor(7);
	gamecontrol();
}

//////도움말////// 
void GameRule(void) 
{
    char enter='\n';
    system("cls");
    SetColor(14);
	printf("\t\t\t★★★ 오목게임의 룰!!! ★★★\n\n");
    printf("\t\t①흑색(●)의 돌과 백색(○)의 돌을 사용합니다.\n\n");
    printf("\t\t※이 게임의 경우 1p는 흑색(●), 2p는 백색(○)입니다.\n\n");
    printf("\t\t②흑-백 교대로 둡니다.\n\n");
    printf("\t\t③플레이어가 가로나 세로 또는 대각선으로\n\n");
	printf("\t\t자기 돌을 5개 연달아 놓으면 이기게 됩니다.\n\n\n");
	printf("\t\t이기는 사람이 100포인트를 얻게 됩니다.\n\n.");
    printf("\t\t\t이제 게임을 시작해 볼까요?\n\n\n");
    printf("\t\t\t   (Press Enter!)");
    scanf("%c",&enter);
    getch();
    GamePlayer();
}

//////게임컨트롤////// 
void gamecontrol(void)
{
	int Baduk_Board[20][20] = {0};						
	int x = 0;
	int y= 0;										
	char Key;						
	system("cls");
	Omok_Pan();
	SetColor(7);printf("\n    1p(●)    2p(○)\n\n");
	SetColor(10);printf("   ← ↑ → ↓ space \n\n");
	gotoxy(41,2);SetColor(14);printf("※만약 플레이어가 반칙을 썻다면\n");
	gotoxy(43,4);SetColor(14);printf("찰진 등짝 스파이크를 날려주세요.\n");		
	gotoxy(x,y);										
	Draw();										
	do //한번이라도 실행함. 
	{													
		Key = getch();									
		Erase(x, y);						
		Push(Baduk_Board,Key,&x,&y);
		Omok_print(Baduk_Board);						
		if(Win_Check(Baduk_Board))						
			return;										
		gotoxy(x,y);					
		Draw();
	}
	while(Key != 27); //ESC를 누르면 종료	
}

//////오목돌 지우기////// 
void Erase(int x ,int y)
{						
	gotoxy(x,y);									
	if(x==0 && y==0)
		printf("┌");
	
	else if(x==36 && y==0)
		printf("┐");

	else if(x==0 && y==18)
		printf("└");
	
	else if(x==36 && y==18)
		printf("┘");

	else if(x==0)
		printf("├");
	
	else if(y==0)
		printf("┬");

	else if(x==36)
		printf("┤");
			
	else if(y==18)
		printf("┴");

	else
		printf("┼");
}													

//////1p 차례일때////// 
void Status1(void)
{
	gotoxy(41,7);SetColor(10);printf("┏━━━━━━━━━━━━━━━┓");
	gotoxy(41,8);SetColor(10);printf("┃ 흑돌이 공격!!                ┃");
	gotoxy(41,9);SetColor(10);printf("┃                              ┃");
	gotoxy(41,10);SetColor(10);printf("┃ %s님이 놓을 차례입니다.  ┃",player1);
	gotoxy(41,11);SetColor(10);printf("┗━━━━━━━━━━━━━━━┛");
	SetColor(7);
}

//////2p 차례일때////// 
void Status2(void)
{
	gotoxy(41,7);SetColor(11);printf("┏━━━━━━━━━━━━━━━┓");
	gotoxy(41,8);SetColor(11);printf("┃ 흰돌이 공격!!                ┃");
	gotoxy(41,9);SetColor(11);printf("┃                              ┃");
	gotoxy(41,10);SetColor(11);printf("┃ %s님이 놓을 차례입니다.  ┃",player2);
	gotoxy(41,11);SetColor(11);printf("┗━━━━━━━━━━━━━━━┛");
	SetColor(7);
}

void Win_Status1(void)
{
	gotoxy(41,7);SetColor(10);printf("┏━━━━━━━━━━━━━━━┓");
	gotoxy(41,8);SetColor(10);printf("┃ 흑돌 승리!                   ┃");
	gotoxy(41,9);SetColor(10);printf("┃                              ┃");
	gotoxy(41,10);SetColor(10);printf("┃ %s님이 승리하셨습니다.   ┃ ",player1);
	gotoxy(41,11);SetColor(10);printf("┗━━━━━━━━━━━━━━━┛");
	SetColor(7);
}

void Win_Status2(void)
{
	gotoxy(41,7);SetColor(11);printf("┏━━━━━━━━━━━━━━━┓");
	gotoxy(41,8);SetColor(11);printf("┃ 흰돌 승리!                   ┃");
	gotoxy(41,9);SetColor(11);printf("┃                              ┃");
	gotoxy(41,10);SetColor(11);printf("┃ %s님이 승리하셨습니다.   ┃",player2);
	gotoxy(41,11);SetColor(11);printf("┗━━━━━━━━━━━━━━━┛");
	SetColor(7);
}

							
//////오목알 그리기////// 
void Draw(void)
{
	if(Game_Dol == 1)
	{
		SetColor(7);
		printf("●");
		Status2();
	}
	
	else
	{
		SetColor(7);
		printf("○");
		Status1();
	}								
}

//////입력받았을때 처리하는 함수//////
void Push(int Board[][20], char key, int *x , int *y)
{
	switch(key)
	{
		case 72:											
			if(*y-1<0)									
		break;
		
		else											
			*y-=1;
		break;
	
		case 80:						
			if(*y+1>18)						
		break;
		
		else									
			*y+=1;
		break;
		
		case 75:									
			if(*x-2<0)								
		break;
		
		else									
			*x-=2;
		break;
		
		case 77:								
			if(*x+2>36)									
		break;
		
		else											
			*x+=2;
		break;
		
		case 32:											
			Omok_Save(Board,*x,*y);						
		break;
	
		default:												
		break;
	}
}

//////오목알 저장////// 
void Omok_Save(int Board[][20],int x, int y)
{
	if(Board[y][x/2]==0)
	{							
		if(Game_Dol==1)
		{								
			Board[y][x/2]=1;							
			Game_Dol=2;
		}									

		else
		{										
			Board[y][x/2]=2;								
			Game_Dol=1;
		}
	}
}

//////오목알 출력////// 
void Omok_print(int Board[][20])
{
	int i,j;	
	for(i=0; i<20; i++)
	{							
		for(j=0; j<20; j++)
		{	
			if (Board[j][i] == 1)
			{						
				gotoxy(i*2,j);
				SetColor(7);							
				printf("●");
			}							

			else if(Board[j][i] == 2)
			{					
				gotoxy(i*2,j);
				SetColor(7);						
				printf("○");
			}							
		}
	}
}

//////승리 체크 함수////// 
int Win_Check(int Board[][20])
{
	int i;													
	int j;	
	int a;
	
	for(i=2; i<18; i++)
	{							
		for(j=0; j<20; j++)
		{						
			if(Board[j][i-2]==1 && Board[j][i-1]==1 && Board[j][i]==1 && Board[j][i+1]==1 && Board[j][i+2]==1)
			{	
				Win_Status2();
				SetColor(6);
				gotoxy(43,14);printf("2p(%s)님이 승리했습니다!\n",&player2);
				gotoxy(43,16);printf("%s님 +100포인트 획득!",&player2);
				getch();
				exit(1);
			}
			
			else if(Board[j][i-2]==2 && Board[j][i-1]==2 && Board[j][i]==2 && Board[j][i+1]==2 && Board[j][i+2]==2)
			{
				Win_Status1();
				SetColor(6);
				gotoxy(43,14);printf("1p(%s)님이 승리했습니다!\n",&player1);
				gotoxy(43,16);printf("%s님 +100포인트 획득!",&player1);
				getch();
				exit(1);
			}

			else if(Board[i-2][j]==1 && Board[i-1][j]==1 && Board[i][j]==1 && Board[i+1][j]==1 && Board[i+2][j]==1)
			{	
				Win_Status2();
				SetColor(6);
				gotoxy(43,14);printf("2p(%s)님이 승리했습니다!\n",&player2);
				gotoxy(43,16);printf("%s님 +100포인트 획득!",&player2);
				getch();
				exit(1);
			}
			
			else if(Board[i-2][j]==2 && Board[i-1][j]==2 && Board[i][j]==2 && Board[i+1][j]==2 && Board[i+2][j]==2)
			{
				Win_Status1();
				SetColor(6);
				gotoxy(43,14);printf("1p(%s)님이 승리했습니다!\n",&player1);
				gotoxy(43,16);printf("%s님 +100포인트 획득!",&player1);
				getch();
				exit(1);
			}
		}
	}

	for(i=2; i<18; i++)
	{					
		for(j=2; j<18; j++)
		{					
			if(Board[j-2][i-2]==1 && Board[j-1][i-1]==1 && Board[j][i]==1 && Board[j+1][i+1]==1 && Board[j+2][i+2]==1)
			{ 
				Win_Status2();
				SetColor(6);
				gotoxy(43,14);printf("2p(%s)님이 승리했습니다!\n",&player2);
				gotoxy(43,16);printf("%s님 +100포인트 획득!",&player2);
				getch();
				exit(1);
			}
			
			else if(Board[j-2][i-2]==2 && Board[j-1][i-1]==2 && Board[j][i]==2 && Board[j+1][i+1]==2 && Board[j+2][i+2]==2)
			{
				Win_Status1();
				SetColor(6);
				gotoxy(43,14);printf("1p(%s)님이 승리했습니다!\n",&player1);
				gotoxy(43,16);printf("%s님 +100포인트 획득!",&player1);
				getch();
				exit(1);
			}

			else if(Board[j+2][i-2]==1 && Board[j+1][i-1]==1 && Board[j][i]==1 && Board[j-1][i+1]==1 && Board[j-2][i+2]==1)
			{
				Win_Status2();
				SetColor(6);
				gotoxy(43,14);printf("2p(%s)님이 승리했습니다!\n",&player2);
				gotoxy(43,16);printf("%s님 +100포인트 획득!",&player2);
				getch();
				exit(1);
			}
			
			else if(Board[j+2][i-2]==2 && Board[j+1][i-1]==2 && Board[j][i]==2 && Board[j-1][i+1]==2 && Board[j-2][i+2]==2)
			{
				Win_Status1();
				SetColor(6);
				gotoxy(43,14);printf("1p(%s)님이 승리했습니다!\n",&player1);
				gotoxy(43,16);printf("%s님 +100포인트 획득!",&player1);
				getch();
				exit(1);
			}
		}
	} 
}
