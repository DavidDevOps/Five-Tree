/* Copyright�� 2014. ����� all rights reserved.
   �ؾ��Ұ� : �÷��̾� �̸� ���� , ��ŷ*/

///////��ó������///////
#include <stdio.h>										
#include <Windows.h>									
#include <conio.h>
#include <string.h>
#include <time.h>

/////////�Լ� ����///////// 
void gotoxy(int x, int y); //API
void gamecontrol(void);	//������Ʈ��
void Omok_Pan(void);	//������ �׸���
void Push(int Board[][20], char key,int *x, int *y); //�Է¹޾����� ó���ϴ� �Լ� 
void Erase(int x, int y); //���� ����� 
void Draw(void); //����� �׸���
void GameRule(void); //���� 
void Omok_Save(int Board[][20],int x, int y); //����� ����
void Omok_print(int Board[][20]); //����� ��� 
int Win_Check(int Board[][20]); //�¸� üũ
void removeCursor(void); //Ŀ�� ���ֱ�
void GamePlayer(void); //�÷��̾� �̸� ���� 
void GameTitle(void); //���� �ΰ� 
void Rank(void); //��ŷ 
void Status1(void); //1p �����϶� 
void Status2(void); //2p �����϶�
int Game_Dol=2; //1�� �� , 2�� �浹
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

//////���� �ΰ�////// 
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
	gotoxy(24,15);SetColor(14);printf("Made By ���̰濵����б� �����");
	gotoxy(15,19);SetColor(11);printf("���� ����");
	gotoxy(35,19);SetColor(10);printf("���� ���");
	gotoxy(55,19);SetColor(13);printf("��ŷ Ȯ��");
	
	//////���̽�ũ��////// 
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
		printf("��");
		Sleep(100);
	}
}

//////��ŷ////// 
void Rank(void)
{

}

//////������ �׸���//////
void Omok_Pan(void)
{
	int i,j;											
	
	puts("��������������������������������������");
	for(i=0; i<17 ; i++)
	puts("��������������������������������������");
	puts("��������������������������������������");
	SetColor(7);
}

//////�����Լ�////// 
int main(void)
{
	while(1)
	{
		removeCursor();
		GameTitle();
		GamePlayer();
	}
}

//////���� ���� ����////// 
void GamePlayer(void)
{
	system("cls");
	SetColor(10);printf("\t\t\t\tF");
	SetColor(11);printf("I");
	SetColor(12);printf("V");
	SetColor(13);printf("E");
	SetColor(14);printf(" TREE");
	SetColor(10);gotoxy(25,4);printf("1p(��) �÷��̾��� �̸� : ");
	scanf("%s", player1);
	SetColor(11);gotoxy(25,8);printf("2p(��) �÷��̾��� �̸� : "); 
	scanf("%s", player2);
	SetColor(7);
	gamecontrol();
}

//////����////// 
void GameRule(void) 
{
    char enter='\n';
    system("cls");
    SetColor(14);
	printf("\t\t\t�ڡڡ� ��������� ��!!! �ڡڡ�\n\n");
    printf("\t\t�����(��)�� ���� ���(��)�� ���� ����մϴ�.\n\n");
    printf("\t\t���� ������ ��� 1p�� ���(��), 2p�� ���(��)�Դϴ�.\n\n");
    printf("\t\t����-�� ����� �Ӵϴ�.\n\n");
    printf("\t\t���÷��̾ ���γ� ���� �Ǵ� �밢������\n\n");
	printf("\t\t�ڱ� ���� 5�� ���޾� ������ �̱�� �˴ϴ�.\n\n\n");
	printf("\t\t�̱�� ����� 100����Ʈ�� ��� �˴ϴ�.\n\n.");
    printf("\t\t\t���� ������ ������ �����?\n\n\n");
    printf("\t\t\t   (Press Enter!)");
    scanf("%c",&enter);
    getch();
    GamePlayer();
}

//////������Ʈ��////// 
void gamecontrol(void)
{
	int Baduk_Board[20][20] = {0};						
	int x = 0;
	int y= 0;										
	char Key;						
	system("cls");
	Omok_Pan();
	SetColor(7);printf("\n    1p(��)    2p(��)\n\n");
	SetColor(10);printf("   �� �� �� �� space \n\n");
	gotoxy(41,2);SetColor(14);printf("�ظ��� �÷��̾ ��Ģ�� ���ٸ�\n");
	gotoxy(43,4);SetColor(14);printf("���� ��¦ ������ũ�� �����ּ���.\n");		
	gotoxy(x,y);										
	Draw();										
	do //�ѹ��̶� ������. 
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
	while(Key != 27); //ESC�� ������ ����	
}

//////���� �����////// 
void Erase(int x ,int y)
{						
	gotoxy(x,y);									
	if(x==0 && y==0)
		printf("��");
	
	else if(x==36 && y==0)
		printf("��");

	else if(x==0 && y==18)
		printf("��");
	
	else if(x==36 && y==18)
		printf("��");

	else if(x==0)
		printf("��");
	
	else if(y==0)
		printf("��");

	else if(x==36)
		printf("��");
			
	else if(y==18)
		printf("��");

	else
		printf("��");
}													

//////1p �����϶�////// 
void Status1(void)
{
	gotoxy(41,7);SetColor(10);printf("����������������������������������");
	gotoxy(41,8);SetColor(10);printf("�� �浹�� ����!!                ��");
	gotoxy(41,9);SetColor(10);printf("��                              ��");
	gotoxy(41,10);SetColor(10);printf("�� %s���� ���� �����Դϴ�.  ��",player1);
	gotoxy(41,11);SetColor(10);printf("����������������������������������");
	SetColor(7);
}

//////2p �����϶�////// 
void Status2(void)
{
	gotoxy(41,7);SetColor(11);printf("����������������������������������");
	gotoxy(41,8);SetColor(11);printf("�� ���� ����!!                ��");
	gotoxy(41,9);SetColor(11);printf("��                              ��");
	gotoxy(41,10);SetColor(11);printf("�� %s���� ���� �����Դϴ�.  ��",player2);
	gotoxy(41,11);SetColor(11);printf("����������������������������������");
	SetColor(7);
}

void Win_Status1(void)
{
	gotoxy(41,7);SetColor(10);printf("����������������������������������");
	gotoxy(41,8);SetColor(10);printf("�� �浹 �¸�!                   ��");
	gotoxy(41,9);SetColor(10);printf("��                              ��");
	gotoxy(41,10);SetColor(10);printf("�� %s���� �¸��ϼ̽��ϴ�.   �� ",player1);
	gotoxy(41,11);SetColor(10);printf("����������������������������������");
	SetColor(7);
}

void Win_Status2(void)
{
	gotoxy(41,7);SetColor(11);printf("����������������������������������");
	gotoxy(41,8);SetColor(11);printf("�� �� �¸�!                   ��");
	gotoxy(41,9);SetColor(11);printf("��                              ��");
	gotoxy(41,10);SetColor(11);printf("�� %s���� �¸��ϼ̽��ϴ�.   ��",player2);
	gotoxy(41,11);SetColor(11);printf("����������������������������������");
	SetColor(7);
}

							
//////����� �׸���////// 
void Draw(void)
{
	if(Game_Dol == 1)
	{
		SetColor(7);
		printf("��");
		Status2();
	}
	
	else
	{
		SetColor(7);
		printf("��");
		Status1();
	}								
}

//////�Է¹޾����� ó���ϴ� �Լ�//////
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

//////����� ����////// 
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

//////����� ���////// 
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
				printf("��");
			}							

			else if(Board[j][i] == 2)
			{					
				gotoxy(i*2,j);
				SetColor(7);						
				printf("��");
			}							
		}
	}
}

//////�¸� üũ �Լ�////// 
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
				gotoxy(43,14);printf("2p(%s)���� �¸��߽��ϴ�!\n",&player2);
				gotoxy(43,16);printf("%s�� +100����Ʈ ȹ��!",&player2);
				getch();
				exit(1);
			}
			
			else if(Board[j][i-2]==2 && Board[j][i-1]==2 && Board[j][i]==2 && Board[j][i+1]==2 && Board[j][i+2]==2)
			{
				Win_Status1();
				SetColor(6);
				gotoxy(43,14);printf("1p(%s)���� �¸��߽��ϴ�!\n",&player1);
				gotoxy(43,16);printf("%s�� +100����Ʈ ȹ��!",&player1);
				getch();
				exit(1);
			}

			else if(Board[i-2][j]==1 && Board[i-1][j]==1 && Board[i][j]==1 && Board[i+1][j]==1 && Board[i+2][j]==1)
			{	
				Win_Status2();
				SetColor(6);
				gotoxy(43,14);printf("2p(%s)���� �¸��߽��ϴ�!\n",&player2);
				gotoxy(43,16);printf("%s�� +100����Ʈ ȹ��!",&player2);
				getch();
				exit(1);
			}
			
			else if(Board[i-2][j]==2 && Board[i-1][j]==2 && Board[i][j]==2 && Board[i+1][j]==2 && Board[i+2][j]==2)
			{
				Win_Status1();
				SetColor(6);
				gotoxy(43,14);printf("1p(%s)���� �¸��߽��ϴ�!\n",&player1);
				gotoxy(43,16);printf("%s�� +100����Ʈ ȹ��!",&player1);
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
				gotoxy(43,14);printf("2p(%s)���� �¸��߽��ϴ�!\n",&player2);
				gotoxy(43,16);printf("%s�� +100����Ʈ ȹ��!",&player2);
				getch();
				exit(1);
			}
			
			else if(Board[j-2][i-2]==2 && Board[j-1][i-1]==2 && Board[j][i]==2 && Board[j+1][i+1]==2 && Board[j+2][i+2]==2)
			{
				Win_Status1();
				SetColor(6);
				gotoxy(43,14);printf("1p(%s)���� �¸��߽��ϴ�!\n",&player1);
				gotoxy(43,16);printf("%s�� +100����Ʈ ȹ��!",&player1);
				getch();
				exit(1);
			}

			else if(Board[j+2][i-2]==1 && Board[j+1][i-1]==1 && Board[j][i]==1 && Board[j-1][i+1]==1 && Board[j-2][i+2]==1)
			{
				Win_Status2();
				SetColor(6);
				gotoxy(43,14);printf("2p(%s)���� �¸��߽��ϴ�!\n",&player2);
				gotoxy(43,16);printf("%s�� +100����Ʈ ȹ��!",&player2);
				getch();
				exit(1);
			}
			
			else if(Board[j+2][i-2]==2 && Board[j+1][i-1]==2 && Board[j][i]==2 && Board[j-1][i+1]==2 && Board[j-2][i+2]==2)
			{
				Win_Status1();
				SetColor(6);
				gotoxy(43,14);printf("1p(%s)���� �¸��߽��ϴ�!\n",&player1);
				gotoxy(43,16);printf("%s�� +100����Ʈ ȹ��!",&player1);
				getch();
				exit(1);
			}
		}
	} 
}
