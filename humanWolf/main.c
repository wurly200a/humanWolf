#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

enum
{
    PLAYER_JINRO  ,
    PLAYER_PROPHET,
    PLAYER_THIEF  ,
    MAX_PLAYER,
};
#define PLAYER_NONE 8//表示に限り+1する(1originの影響)

typedef struct playe
{
    char username[30];
    int position;
    int alive;
    int vote;
}player;

player user[MAX_PLAYER];
static void nightTurn(void);
static void dayTurn(void);

static void getPosition(void);
static void openPosition(void);
static void waitKey(char);
static char getKey(void);
static void clearScreen(void);
static int getTarget(void);
static void judgeVictory(void);

char positionName[MAX_PLAYER][50] =
{
    "人狼",
    "占い師",
    "怪盗"
};
int deathflag = NULL;
char target[350] = "";
char buff[150] = "";
int f = 0;
int e = 0;
int targetPlayer = 0;


int
humanWolfMain(int argc, char* argv[])
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
    while (1)
    {
        nightTurn();

        printf("おはようございます！");

        dayTurn();

        printf("夜に入ります。おやすみなさい...\n");
    }
        
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
        clearScreen();
        printf("%sさん、Spaceを押してください\n", user[i].username);
        waitKey(' ');
        printf("%sさんは%sです\n", user[i].username, positionName[user[i].position]);

        if (user[i].alive)
        {
            target[0] = '\0';
            switch (user[i].position)
            {
                case PLAYER_JINRO://人狼の場合
                    for (f = 0; f < MAX_PLAYER; f++)
                    {
                        if (user[f].alive && i != f)
                        {
                            sprintf_s(buff, 150, "%d:%s\n",f + 1,user[f].username);
                            strcat(target,buff);
                        }
                    }
                    sprintf(buff, "%d:襲撃しない\n", PLAYER_NONE + 1);
                    strcat(target, buff);
                    printf("襲撃する人を選んでください---\n%s",target);
                    targetPlayer = getTarget() - 1;
                    if (targetPlayer == PLAYER_NONE)
                    {
                        printf("この夜をスキップします...Spaceを押し、朝までお待ちください。\n");
                        deathflag = NULL;
                        waitKey(' ');
                        break;
                    }
                    
                    printf("%sを攻撃します...Spaceを押し、朝までお待ちください。\n",user[targetPlayer].username);
                    waitKey(' ');
                    if (targetPlayer != PLAYER_NONE)//人狼噛み処理
                    {
                        user[targetPlayer].alive = 0;
                        deathflag = targetPlayer;
                    }
                    break;

                case PLAYER_PROPHET://占い師の場合
                    /* 対象の人をリストアップ */
                    for (f = 0; f < MAX_PLAYER; f++)
                    {
                        if (user[f].alive && i != f)
                        { /* 生きてて、自分以外 */
                            sprintf_s(buff, 150, "%d:%s\n", f + 1, user[f].username);
                            strcat(target, buff);
                        }
                    }
                    sprintf(buff, "%d:占わない\n", PLAYER_NONE + 1);
                    strcat(target, buff);
                    printf("占う人を選んで下さい---\n%s",target);
                    targetPlayer = getTarget() - 1;
                    if (targetPlayer)
                    {
                        sprintf(buff,"人狼ではありません");
                    }
                    else
                    {
                        sprintf(buff, "人狼です");
                    }
                    if (targetPlayer == PLAYER_NONE)
                    {
                        printf("この夜をスキップします...Spaceを押し、朝までお待ちください。\n");
                        deathflag = NULL;
                        waitKey(' ');
                        break;
                    }
                    printf("%sは%s!\n",user[targetPlayer].username,buff);
                    printf("Spaceを押し、朝までお待ちください...\n");
                    waitKey(' ');
                    break;

                case PLAYER_THIEF://怪盗の場合
                    for (f = 0; f < MAX_PLAYER; f++)
                    {
                        if (user[f].alive && i != f)
                        {
                            sprintf_s(buff, 150, "%d:%s\n", f + 1, user[f].username);
                            strcat(target, buff);
                        }
                    }
                    sprintf(buff, "%d:交換しない\n", PLAYER_NONE + 1);
                    strcat(target, buff);
                    printf("交換する人を選んで下さい---\n%s", target);
                    targetPlayer = getTarget() - 1;
                    if (targetPlayer == PLAYER_NONE)
                    {
                        printf("この夜をスキップします...Spaceを押し、朝までお待ちください。\n");
                        waitKey(' ');
                        break;
                    }
                    e = user[i].position;
                    user[i].position = user[targetPlayer].position;
                    user[targetPlayer].position = e;
                    printf("%sと役職を交換します...Spaceを押して朝までお待ちください。\n",user[targetPlayer].username);
                    waitKey(' ');
                    

            }
        }
        else
        {

            printf("あなたは死にました。Spaceを押して朝までお待ちください。\n");
            waitKey(' ');
            
        }
    }
    int aliveCnt = 0;
    
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        if (user[i].alive && user[i].position != PLAYER_JINRO)
        {
            aliveCnt += 1;
        }
    }
    if (aliveCnt <= 1)
    {
        printf("\n人狼陣営の勝利です!!\nSpaceを押して終了します。\n");
        waitKey(' ');
        exit(0);
    }
}

static void dayTurn(void)
{
    buff[0] = NULL;
    target[0] = NULL;
    int maxVote = 0;
    int aliveCnt = 0;
    if (deathflag != NULL)
    {
        printf("夜に%sさんが襲撃されました...\n\n",user[deathflag].username);
    }
    else
    {
        printf("今日はだれも殺されませんでした。\n\n");
    }
    printf("それでは話し合いを始めます。投票を始めるには、Spaceを押して下さい。\n");
    waitKey(' ');

    printf("それでは投票に入ります。");
    for (int i = 0;i < MAX_PLAYER;i++)
    {
        clearScreen();
        printf("%sさん、Spaceを押してください\n", user[i].username);
        waitKey(' ');

        if (user[i].alive)
        {
            for (int f = 0; f < MAX_PLAYER; f++)
            {
                if (user[f].alive && i != f)
                {
                    sprintf_s(buff, 150, "%d:%s\n", f + 1, user[f].username);
                    strcat(target, buff);
                }
            }
            sprintf(buff, "%d:投票しない\n", PLAYER_NONE + 1);
            strcat(target, buff);
            printf("投票する人を選んでください---\n%s", target);
            targetPlayer = getTarget() - 1;
            if (targetPlayer == PLAYER_NONE)
            {
                printf("この投票をスキップします...Spaceを押し、お待ちください。\n");
                waitKey(' ');
                break;
            }

            printf("%sに投票します...Spaceを押し、お待ちください。\n", user[targetPlayer].username);
            user[targetPlayer].vote += 1;
            waitKey(' ');
            break;
        }else
        {

            printf("あなたは死にました。Spaceを押してお待ちください。\n");
            waitKey(' ');

        }
    }
    for (int i = 0; i < MAX_PLAYER; i++)
    {
        if (maxVote < user[i].vote && user[i].alive)
        {
            maxVote = i;
                  
        }
        if (user[i].alive && user[i].position != PLAYER_JINRO)
        {
            aliveCnt += 1;
        }
    }
    printf("今日は%sさんが追放されます...(%d票)\n",user[maxVote].username,user[maxVote].vote);
    user[maxVote].alive = 0;
    if (user[maxVote].position == PLAYER_JINRO)
    {
        printf("\n市民陣営の勝利です!!\nSpaceを押して終了します。\n");
        waitKey(' ');
        exit(0);
    }
    else if (aliveCnt <= 1)
    {
        printf("\n人狼陣営の勝利です!!Spaceを押して終了します。\n");
        waitKey(' ');
        exit(0);
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
    } while ( (num != PLAYER_NONE + 1) && (num < 0 || MAX_PLAYER + 1 < num) );//getKeyで入力できる文字の制限

    return num;
}

static void judgeVictory(void)
{}
