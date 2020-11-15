#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define MAX_PLAYER 3
#define PLAYER_NONE 8//�\���Ɍ���+1����(1origin�̉e��)

typedef struct playe
{
    char username[30];
    int position;
    int alive;
}player;

player user[MAX_PLAYER];

static void getPosition(void);
static void openPosition(void);
static void nightTurn(void);
static void waitKey(char);
static char getKey(void);
static void clearScreen(void);
static int getTarget(void);

char positionName[MAX_PLAYER][50] =
{
    "�l�T",
    "�肢�t",
    "����"
};

int main()
{
    char buff[70];

    
    for (int e = 0; e < MAX_PLAYER; e++ )
    {
        sprintf_s(buff, 70, "%dP", e + 1);
        strcpy_s(user[e].username, 20, buff );
        user[e].alive = 1;
    }

    

    getPosition();

    for (int f = 0; f < MAX_PLAYER; f++)//debug
    {
        printf("debug:%d,%d\n", f, user[f].position);
    }

    openPosition();

    nightTurn();

        return 0;
}

static void
getPosition(void)
{
    srand(time(NULL));
    for (int i = 0; i < MAX_PLAYER; i++)
    {

        if (i)
        { /* i �� 1�ȏ� */
            int bSameExist = 0;

            do
            {
                user[i].position = rand() % MAX_PLAYER; /* �܂��̓|�W�V�������擾 */

                bSameExist = 0;
                /* 0�`(i-1)�܂ŃT�[�`���āA�������������t���OON */
                for (int g = 0; g <= i - 1; g++)
                {
                    if (user[i].position == user[g].position)
                    {
                        bSameExist = 1; /* ����������� */
                    }
                    else
                    {
                    }
                }
            } while (bSameExist); /* ��������������J��Ԃ� */
        }
        else
        { /* i��1�̎��͍ŏ��Ȃ̂Ŋm�� */
            user[i].position = rand() % MAX_PLAYER;
        }
    }
}

static void openPosition(void)
{
    char collect;
    char sp = '�@';


    for (int a = 0; a < MAX_PLAYER; a++)
    {
        printf("%s����ASpace�������Ă��������B\n", user[a].username);
        waitKey(' ');

        printf("���Ȃ��̖�E��%s�ł��B\n", positionName[user[a].position]);
        printf("Space�������Ă��������B\n\n");
        waitKey(' ');
        clearScreen();
    }
}

static void nightTurn(void)
{
    char target[350] = "";
    char buff[150] = "";
    int f = 0;
    int e = 0;
    int targetPlayer = 0;
    for (int i = 0; i < MAX_PLAYER;i++)
    {
        clearScreen();
        printf("%s����ASpace�������Ă�������\n", user[i].username);
        waitKey(' ');
        printf("%s�����%s�ł�\n", user[i].username, positionName[user[i].position]);

        if (user[i].alive)
        {
            target[0] = '\0';
            switch (user[i].position)
            {
                case 0://�l�T�̏ꍇ
                    for (f = 0; f < MAX_PLAYER; f++)
                    {
                        if (user[f].alive && i != f)
                        {
                            sprintf_s(buff, 150, "%d:%s\n",f + 1,user[f].username);
                            strcat(target,buff);
                        }
                    }
                    sprintf(buff, "%d:�P�����Ȃ�\n", PLAYER_NONE + 1);
                    strcat(target, buff);
                    printf("�P������l��I��ł�������---\n%s",target);
                    targetPlayer = getTarget() - 1;
                    if (targetPlayer == PLAYER_NONE)
                    {
                        printf("���̖���X�L�b�v���܂�...Space�������A���܂ł��҂����������B\n");
                        waitKey(' ');
                        break;
                    }
                    
                    printf("%s���U�����܂�...Space�������A���܂ł��҂����������B\n",user[targetPlayer].username);
                    waitKey(' ');
                    if (targetPlayer != PLAYER_NONE)//�l�T���ݏ���
                    {
                        user[targetPlayer].alive = 0;
                    }
                    break;

                case 1://�肢�t�̏ꍇ
                    /* �Ώۂ̐l�����X�g�A�b�v */
                    for (f = 0; f < MAX_PLAYER; f++)
                    {
                        if (user[f].alive && i != f)
                        { /* �����ĂāA�����ȊO */
                            sprintf_s(buff, 150, "%d:%s\n", f + 1, user[f].username);
                            strcat(target, buff);
                        }
                    }
                    sprintf(buff, "%d:���Ȃ�\n", PLAYER_NONE + 1);
                    strcat(target, buff);
                    printf("�肤�l��I��ŉ�����---\n%s",target);
                    targetPlayer = getTarget() - 1;
                    if (targetPlayer)
                    {
                        sprintf(buff,"�l�T�ł͂���܂���");
                    }
                    else
                    {
                        sprintf(buff, "�l�T�ł�");
                    }
                    if (targetPlayer == PLAYER_NONE)
                    {
                        printf("���̖���X�L�b�v���܂�...Space�������A���܂ł��҂����������B\n");
                        waitKey(' ');
                        break;
                    }
                    printf("%s��%s!\n",user[targetPlayer].username,buff);
                    printf("Space�������A���܂ł��҂���������...\n");
                    waitKey(' ');
                    break;

                case 2://�����̏ꍇ
                    for (f = 0; f < MAX_PLAYER; f++)
                    {
                        if (user[f].alive && i != f)
                        {
                            sprintf_s(buff, 150, "%d:%s\n", f + 1, user[f].username);
                            strcat(target, buff);
                        }
                    }
                    sprintf(buff, "%d:�������Ȃ�\n", PLAYER_NONE + 1);
                    strcat(target, buff);
                    printf("��������l��I��ŉ�����---\n%s", target);
                    targetPlayer = getTarget() - 1;
                    if (targetPlayer == PLAYER_NONE)
                    {
                        printf("���̖���X�L�b�v���܂�...Space�������A���܂ł��҂����������B\n");
                        waitKey(' ');
                        break;
                    }
                    e = user[i].position;
                    user[i].position = user[targetPlayer].position;
                    user[targetPlayer].position = e;
                    printf("%s�Ɩ�E���������܂�...Space�������Ē��܂ł��҂����������B\n",user[targetPlayer].username);
                    waitKey(' ');
                    

            }
        }
        else
        {

            printf("���Ȃ��͎��ɂ܂����BSpace�������Ē��܂ł��҂����������B\n");
            waitKey(' ');
            
        }
    }
   
}

static void waitKey(char key)
{
     while (1)
    {
        if (_kbhit())
        {
            if (_getch() == key)
            {
                break;
            }
        }
    }
}

static char getKey(void)
{
    char key;

    while (1)
    {
        if (_kbhit())
        {
            if ( (key = _getch()) )
            {
                break;
            }
        }
    }

    return key;
}

static void clearScreen(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

static int getTarget(void)
{
    int cNum,num;

    do
    {
        cNum = getKey();
        num = cNum - '0';
    } while ( (num != PLAYER_NONE + 1) && (num < 0 || MAX_PLAYER + 1 < num) );//getKey�œ��͂ł��镶���̐���

    return num;
}