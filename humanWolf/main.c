#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define MAX_PLAYER 3

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

char positionName[3][50] =
{
    "人狼",
    "占い師",
    "怪盗"
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
        { /* i が 1以上 */
            int bSameExist = 0;

            do
            {
                user[i].position = rand() % MAX_PLAYER; /* まずはポジションを取得 */

                bSameExist = 0;
                /* 0～(i-1)までサーチして、同じやつがいたらフラグON */
                for (int g = 0; g <= i - 1; g++)
                {
                    if (user[i].position == user[g].position)
                    {
                        bSameExist = 1; /* 同じやつがいた */
                    }
                    else
                    {
                    }
                }
            } while (bSameExist); /* 同じやつがいる限り繰り返す */
        }
        else
        { /* iが1の時は最初なので確定 */
            user[i].position = rand() % MAX_PLAYER;
        }
    }
}

static void openPosition(void)
{
    char collect;
    char sp = '　';


    for (int a = 0; a < MAX_PLAYER; a++)
    {
        printf("%sさん、Spaceを押してください。\n", user[a].username);
        waitKey(' ');

        printf("あなたの役職は%sです。\n", positionName[user[a].position]);
        printf("Spaceを押してください。\n\n");
        waitKey(' ');
        clearScreen();
    }
}

static void nightTurn(void)
{
    for (int i = 0; i < MAX_PLAYER;i++)
    {
        char attack[350] = "";
        char buff[150];
        if (user[i].alive)
        {
            switch (user[i].position)
            {
                case 0://人狼の場合
                    
                    printf("%sさん、Spaceを押してください\n",user[i].username);
                    waitKey(' ');
                    for (int f = 0; f < MAX_PLAYER; f++)
                    {
                        if (user[f].alive && i != f)
                        {
                            sprintf_s(buff, 150, "%d:%s\n",f,user[f].username);
                            strcat(attack,buff);
                        }
                    }
                    printf("襲撃する人を選んでください---\n%s",attack);
                    user[getKey()].alive = 0;


                    break;
            }
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