#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdbool.h>
#define PASSWORD1 "040131"
#define PASSWORD2 "040306"
#define PASSWORD3 "040416"
# define MAX 50
# define max 20

typedef struct 
{
    double history; 
    const char *Ptype;
} Record;

typedef struct 
{
    int answer;
    char question[max];
} Verify;

typedef struct
{
    char account[max]; 
    char passwd[max]; 
    double balance; 
    Record record[max]; 
    int NUM; 
    bool Freeze; 
    bool Submit; 
    double limitCost;
    Verify verify;
} User;

User users[MAX]; 
User* pr=NULL; 
int count=0;

void Code(char* code) 
{
    srand(time(NULL));  
    for (int i = 0; i < 4; i++) 
    {
        int r = rand() % 36;  
        if (r < 10) 
        {
            code[i] = '0' + r;  
        } 
        else 
        {
            code[i] = 'A' + r - 10;  
        }
    }
    code[4] = '\0';  
}

void saveFile(User* pr, int count) 
{
    FILE* file = fopen("save.bat", "wb");
    if (file == NULL) 
    {
        printf("无法打开文件。\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(pr, sizeof(User), count, file);
    fclose(file); 
}

void secret(char* s)
{
    int i = 0;
    while (1)
    {
        char c = getch(); 
        if (c == '\r')
        {
            s[i] = '\0';
            break;
        }
        else if (c == '\b')
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");  
            }
        }
        else
        {
            s[i] = c;
            i++;
            printf("*");
        }
    }
    printf("\n");
}

int searchResult(char* s)
{
    for (int i = 0; i < count; i++)
    {
        if (strcmp(users[i].account,s)==0)
        {
            return i;
        }
    }
    return -1;
}

void changePassword2(int i)  
{
    char Old[max];
    char New[max];
    char Confirm[max];
    strcpy(Old,users[i].passwd);

    printf("\n请输入新密码: \n");
    secret(New);
    if (strcmp(Old, New) == 0) 
    {
        printf("新密码与旧密码相同，无效操作\n");
        return;
    }
    printf("\n请再次输入新密码: \n");
    secret(Confirm);
    if (strcmp(New, Confirm) != 0) 
    {
        printf("\n两次输入的密码不一致\n");
        return;
    }
    strcpy(users[i].passwd, New);
    saveFile(users, count);
    printf("\n密码修改成功！\n");
}

void forgotPassword() 
{
    printf("输入忘记的密码的账号:\n");
    char forgotAccount[20];
    scanf("%s",forgotAccount);
    int i=searchResult(forgotAccount);
    if(i==-1)
    {
        printf("没有找到此用户");
        return;
    }
    printf("问题:%s\n", users[i].verify.question);
    int answer;
    printf("请输入答案:\n");
    scanf("%d", &answer);
    if (answer == users[i].verify.answer) 
    {
        changePassword2(i);
        return;
    } 
    else 
    {
        printf("答案错误，密码修改失败。\n");
        return;
    }
}

void printReceipt(double amount, int judge) 
{
    time_t currentTime;
    time(&currentTime);
    struct tm* localTime = localtime(&currentTime);
    char timeString[50];
    strftime(timeString, sizeof(timeString), "%Y-%m-%d %H:%M:%S", localTime);
    const char *TransType=NULL;
    if(judge==1)
        TransType="存款";
    if(judge==2)
        TransType="取款";
    if(judge==3)
        TransType="转账";
    printf("-------------------------------\n");
    printf("        ATM 交易凭据        \n");
    printf("-------------------------------\n");
    printf("时间: %s\n", timeString);
    printf("交易类型: %s\n", TransType);
    printf("交易金额: %.2f\n", amount);
    printf("-------------------------------\n");
}

void lastRecord(User* user) 
{
    if (user->NUM == max) 
    {
        for (int i = 0; i < max-1; i++) 
        {
            user->record[i] = user->record[i + 1]; 
        }
        user->NUM--; 
    }
}


void AddSecret(char* s)
{
    int head=0; 
    int tail=strlen(s)+1; 
    while(head!=tail)
    {
        printf("%c",s[head]);
        head++;
        s[tail]=s[head];
        tail++;
        head++;
    }
    printf("\n");
}

bool StrongPasswd(char *s)
{
    int book[4]={0}; 
    for(int i=0;s[i]!=0;i++)
    {
        if(isdigit(s[i])) 
            book[1]=1;
        if(islower(s[i]))
            book[2]=1;
        if(isupper(s[i]))
            book[3]=1;
    }
    if( (book[1]==1) && (book[2]==1) && (book[3]==1) )
        return true; 
    else    return false; 
}
bool Fridge(bool x)
{
    if(x==false)
        return false;
    else
        return true;
}
void atm() 
{
    printf("\t\t\t          *         ***********      **           **\n");
    printf("\t\t\t         * *             *           * *         * *\n");
    printf("\t\t\t        *   *            *           *  *       *  *\n");
    printf("\t\t\t       *******           *           *   *     *   *\n");
    printf("\t\t\t      *       *          *           *    *   *    *\n");
    printf("\t\t\t     *         *         *           *     * *     *\n");
    printf("\t\t\t    *           *        *           *      *      *\n");
}

int loadFile(User* pr) 
{
    FILE* file = fopen("save.bat", "rb");
    if (file == NULL) 
    {
        printf("目前无用户加入\n");
        return 0;
    }
    int number; 
    fread(&number, sizeof(int), 1, file);
    fread(pr, sizeof(User), number, file);
    fclose(file);
    return number;
}
void printSlowly(const char* str) 
{
    for (int i = 0; str[i]!=0 ; i++)
    {
        printf("%c",str[i]);
        Sleep(100);
    }
}
void printSlowly2(const char* str) 
{
    for (int i = 0; str[i]!=0 ; i++)
    {
        printf("%c",str[i]);
        Sleep(300);
    }
}
void clearLine() 
{
    printf("\r\033[K");
    fflush(stdout);
}

void submit(int i)
{

    users[i].Submit=true;
}

void logup()
{
    char account[20];
    char code[5]; 
    if (count>MAX) 
    {
        printf("抱歉，目前系统无法注册新账号");
        return;
    }
    printf("请输入注册账号:\n");
    scanf("%s",account);
    if (strlen(account) < 6) 
	{
        printf("账户名不得少于6个字符。\n");
        return;
    } 
    strcpy(users[count].account,account);
    if(searchResult(users[count].account)!=-1)
    {
        printf("该账号已经注册\n");
        return;
    }
    while(1)
    {
    printf("请输入注册密码:\n");
    secret(users[count].passwd);
    if(StrongPasswd(users[count].passwd)==false)
    {
        printf("请输入含有数字，大写字母，小写字母的强密码\n");
        continue;
    }
    Code(code); 
    printf("请输入验证码验证【%s】:\n",code); 
    char ccode[5];
    scanf("%s",ccode);
    if(strcmp(code,ccode)!=0)
    {
        printf("验证码错误,请重试!\n");
        continue;
    }
    else
        printf("验证成功\n");
    printf("请输入一个问题(在密码忘记时使用):\n");
    scanf("%s",users[count].verify.question);
    printf("请输入这个问题的答案(只能是数值):\n");
    scanf("%d",&users[count].verify.answer);
    users[count].balance=0.0; 
    users[count].Freeze=false;
    users[count].NUM=0;
    users[count].Submit=false; 
    users[count].limitCost=20000; 
    (count)++; 
    saveFile(users, count);
    printf("注册成功\n");
    break;
    }
}

void login() 
{
    char account[MAX];
    char passwd[MAX];
    char a;
    printf("请输入账号: \n");
    scanf("%s", account);
    for (int i = 0; i < count; i++) 
    {
        if (strcmp(users[i].account, account) == 0)  
        {
            if (Fridge(users[i].Freeze) == true) 
            {
                printf("账号已冻结，请联系管理员!\n");
                printf("是否联系管理员(y/n):\n");
                scanf(" %c", &a);
                if ((a == 'y') || (a == 'Y'))
                {
                  printf("已成功联系管理员\n");
                  submit(i);  
                }
                else if ((a == 'n') || (a == 'N'))
                {
                  printf("请及时联系管理员!\n");
                }
                else
                {
                  printf("无效输入\n");
                }
                return;
            }
            printf("请输入密码: \n");
            secret(passwd);
            char code[5]; 
            for (int j = 0; j < 5; j++)
            {
                if (strcmp(users[i].passwd, passwd) == 0)
                {
                    while(1)
                    {
                    Code(code); 
                    printf("请输入验证码验证【%s】:\n",code); 
                    char ccode[5];
                    scanf("%s",ccode);
                    if(strcmp(code,ccode)!=0)
                    {
                        printf("验证码错误,请重试!\n");
                        continue;
                    }
                    else    break;
                    } 
                    printf("登陆成功\n");
                    pr = users + i;  
                    return;
                }
                else
                {
                    printf("密码错误，请重新输入(还可输入%d次): \n",5-j);
                    secret(passwd);
                }
            }
            printf("密码重试次数超过限制，账号已冻结，请联系管理员!\n");
            users[i].Freeze=true; 
            saveFile(users, count);
            printf("是否联系管理员(y/n):\n");
            scanf(" %c", &a);
            if ((a == 'y') || (a == 'Y'))
            {
              printf("已成功联系管理员\n");
              submit(i);  
            }
            else if ((a == 'n') || (a == 'N'))
            {
                printf("请及时联系管理员!\n");
            }
            else
            {
                printf("无效输入\n");
            }
            return;
        }
    }
    printf("账号不存在，请重试\n");
    return;
}

void showBalance()  
{
    printf("您的账户余额为: %.2f\n", pr->balance);
}

void deposit()  
{
    double amount;
    printf("请输入存款金额: \n");
    scanf("%lf", &amount);
    if(amount >= pr->limitCost)
    {
    	printf("金额过大，无效存款\n");
    	return; 
	}
    if (amount <= 0) 
    {
        printf("请输入正确的存款金额\n");
        return;
    }
    pr->balance += amount; 
    pr->record[pr->NUM].history=amount;
    pr->record[pr->NUM].Ptype="Deposit";
    pr->NUM++;
    lastRecord(pr);
    saveFile(users, count); 
    printf("存款成功！\n");
    printf("是否需要打印凭据:(y/n):\n");
    char a;
    scanf(" %c",&a);
    if ((a == 'y') || (a == 'Y'))
    {
        printReceipt(amount,1);
    }
    else if ((a == 'n') || (a == 'N'))
    {
        return;
    }
    else
    {
        printf("无效输入\n");
    }
}

void withdraw()  
{
    double amount;
    printf("请输入取款金额: \n");
    scanf("%lf", &amount);
    if (amount <= 0)
    {
        printf("取款金额无效\n");
        return;
    }
    if(amount > pr->balance)
    {
        printf("取款金额无效或余额不足。\n");
        return;
    }
    pr->balance -= amount;
    pr->record[pr->NUM].history=-amount;
    pr->record[pr->NUM].Ptype="withDraw";
    pr->NUM++;
    lastRecord(pr);
    saveFile(users, count);
    printf("取款成功！\n");
    printf("是否需要打印凭据:(y/n):\n");
    char a;
    scanf(" %c",&a);
    if ((a == 'y') || (a == 'Y'))
    {
        printReceipt(amount,2);
    }
    else if ((a == 'n') || (a == 'N'))
    {
        return;
    }
    else
    {
        printf("无效输入\n");
    }
}

void transfer()  
{
    char s[MAX]; 
    printf("请输入目标账号: \n");
    scanf("%s", s);
    int i = searchResult(s);
    if (i == -1) 
    {
        printf("目标账号不存在\n");
        return;
    }
    if(strcmp(s,pr->account)==0)
    {
        printf("非法操作，无法转账给自己\n");
        return;
    }
    double amount;
    printf("请输入转账金额: \n");
    scanf("%lf", &amount);
    if(amount >= pr->limitCost)
        printf("金额过大，无效转账\n");
    if (amount <= 0) 
    {
        printf("请输入正确的转账金额\n");
        return;
    }
    if (amount > pr->balance) 
    {
        printf("转账金额超过账户余额\n");
        return;
    }
    pr->balance -= amount; 
    users[i].balance += amount; 
    users[i].record[users[i].NUM].history=amount;
    users[i].record[users[i].NUM].Ptype="To_transfer";
    users[i].NUM++;
    lastRecord(users+i);
    pr->record[pr->NUM].history=-amount;
    pr->record[pr->NUM].Ptype="From_transfer";
    pr->NUM++;
    lastRecord(pr);
    saveFile(users, count); 
    printf("转账成功！\n");
    printf("是否需要打印凭据:(y/n):\n");
    char a;
    scanf(" %c",&a);
    if ((a == 'y') || (a == 'Y'))
    {
        printReceipt(amount,3);
    }
    else if ((a == 'n') || (a == 'N'))
    {
        return;
    }
    else
    {
        printf("无效输入\n");
    }
}

void changePassword()  
{
    char Old[MAX];
    char New[MAX];
    char Confirm[MAX];
    printf("请输入旧密码: \n");
    secret(Old);
    if (strcmp(Old, pr->passwd) != 0) 
    {
        printf("旧密码不正确,请重新输入\n");
        return;
    }
    printf("\n请输入新密码: \n");
    secret(New);
    if (strcmp(Old, New) == 0) 
    {
        printf("新密码与旧密码相同，无效操作\n");
        return;
    }
    printf("\n请再次输入新密码: \n");
    secret(Confirm);
    if (strcmp(New, Confirm) != 0) 
    {
        printf("\n两次输入的密码不一致\n");
        return;
    }
    strcpy(pr->passwd, New);
    saveFile(users, count);
    printf("\n密码修改成功！\n");
}

void printAllUsers()  
{
    printf("所有用户信息：\n");
    for (int i = 0; i < count; i++) 
    {
        printf("账号：%s\t\t\t余额：%.2f\t\t\t", users[i].account,users[i].balance);
        printf("密码(已加密):");
        AddSecret(users[i].passwd);
    }
}

void timetable(int a)  
{
	while(a>=0)
	{
		system("cls"); 
		printf("账号已锁定, 还剩%d秒",a);
		Sleep(1000);
		a=a-1;
	}    
}

void Delete(char* s1)
{
    int result=searchResult(s1);
    if (result==-1)
        {
            printf("未找到相关信息!无法删除!\n");
            return;
        }
    else
    {
        for (int i = result; i < count; i++)
        {
            users[i]=users[i+1];
        }
        count--;
        printf("删除成功!\n");
    }
    saveFile(users,count);
}
/*
void writeFriNum()
{    
    FILE* file = fopen("save.bat", "wb");
    if (file != NULL) 
    {
        fwrite(&FriNum, sizeof(FriNum), 1, file);
        fclose(file);
    } 
    else 
    {
        printf("无法打开文件\n");
    }
}
void DeleteFridge(int i,int j)
{
    users[i].Freeze=false; 
    saveFile(users,count);   
    for (; j < FriNum; j++)
    {
        visit[j+1]=visit[j];
    }
    FriNum--; 
    writeFriNum();
}
void readFriNum()
{
    FILE* file = fopen("save.bat", "rb");
    if (file != NULL) 
    {
        fread(&FriNum, sizeof(FriNum), 1, file);
        fclose(file);
    } 
    else 
    {
        printf("无法打开文件\n");
    }
}
*/
void printRecord(User* ss)
{
    for (int i = 0; i < ss->NUM; i++)
    {
        printf("%.2lf\t",ss->record[i].history);
        printf("%s\t\n",ss->record[i].Ptype);        
        printf("_____________");
        putchar('\n');  
    }
    printf("目前余额:%.2lf",ss->balance);
    putchar('\n');
}

void printAll()
{
    double all=0.0;
    for(int i=0;i<count;i++)
    {
        all+=users[i].balance;
    }
    printf("银行的总存款为%lf\n",all);
}

void logout()
{
    printf("注销无法撤回，请慎重考虑!!!\n");
    printf("是否注销?(Y/N):\n");
    char a;
    scanf(" %c", &a);
    if ((a == 'y') || (a == 'Y'))
    {
        printf("请输入密码:");
        char Old[MAX];
        secret(Old);
        if (strcmp(Old, pr->passwd) != 0) 
        {
        printf("密码不正确\n");
        return;
        }
        Delete(pr->account);
    }
    else if ((a == 'n') || (a == 'N'))
    {
        ;
    }
    else
    {
        printf("无效输入");
    }
    return;
}

void DeleteFridge(int i)
{
    users[i].Freeze=false; 
    saveFile(users,count);
}
int issubmit(int i)
{
    if (users[i].Submit==true)
    {
        return 1;
    }
    else
        return 0;
}

void limit()
{
    char s1[20];
    printf("请输入需要限额的账号:\n");
    scanf("%s",s1);
    if (searchResult(s1)==-1)
    {
        printf("未找到相关信息!\n");
        getchar();
    }
    else 
    {
        int i=searchResult(s1);
        double limitCost2;
        printf("请输入额度:\n");
        scanf("%lf",&limitCost2);
        users[i].limitCost=limitCost2;
        saveFile(users,count);
    }
}

void menu2()
{
    printf("\t\t\t\t\t");
    printSlowly("\033[31m欢迎进入管理员系统,请将窗口拉长\n");
    system("color f6");
    char Password1[]=PASSWORD1; 
    char Password2[]=PASSWORD2; 
    char Password3[]=PASSWORD3; 
    char s2[10];
    int num=3; 
    int increase=0; 
    int time=5; 
    while (1)
    {
        system("cls");
        printf("请输入密钥:");
        secret(s2);
        if(strcmp(Password1,s2)==0||strcmp(Password3,s2)==0)
        {
            printf("管理员登录成功!");
            break;
        }  
        else if(strcmp(Password2,s2)==0)
        {
            printf("超级管理员登录成功!");
            break;
        }
        else
        {
            num--;
            if(num)
            {
                printf("登陆失败!请重试,最多还可重试%d次(按回车键继续)\n",num);
                getchar();
            }
            else
            {
                printf("已超过最大限制,需要锁定%d秒\n",time);
                increase++;
                time=time*increase;
                timetable(time);
                num=3;   
            }
        } 
    }
    int FriNum=0;
    while (1)
    {
        printf("\t\t\t\t\t"); 
        printf("\033[1m按回车键可打开管理员菜单");
        getchar();
        system("cls");
        if(strcmp(Password1,s2)==0||strcmp(Password3,s2)==0)
            printf("\t\t\t\t\t管理员系统");
        if(strcmp(Password2,s2)==0)
            printf("\t\t\t\t\t超级管理员");
        printf("\n");
        printf("请使用 h(左),l(右),a(确认) 操作: \n");
        printf("|查总|\t"); 
        printf("|删户|\t");
        printf("|修户|\t");
        printf("|查户|\t");
        printf("|退出|\t"); 
        printf("|交易|\t");
        printf("|冻结|\t"); 
        printf("|总额|\t");
        printf("|限额|\n"); 
        char s[]="******";
        int num=0; 
        printf("%s",s);
        while(1)
        {
            char ch=getch();
            if(ch=='l'||ch=='L')
            {
                if(num>11)
                    ;
                else
                {
                num++;
                clearLine();
                for (int i = 0; i < num; i++)
                    printf("\t");
                printf("%s",s);  
                }
            }
            if(ch=='h'||ch=='H')
            {
                if(num==0)
                    ;
                else
                {
                num--;
                clearLine();
                for (int i = 0; i < num; i++)
                    printf("\t");
                printf("%s",s); 
                }
            }
            if(ch=='a'||ch=='A')
                break;
        }
        printf("\n");
        char s1[25]; 
        switch (num+1)
        {
            case 1: 
                printAllUsers();
                getchar();printf("按回车键继续");
                break;
            case 2: 
                printf("请输入要删除的账号:\n");
                scanf("%s",s1);
                Delete(s1);
                getchar();printf("按回车键继续");
                break;
            case 3: 
                printf("请输入想要修改的账号:\n");
                scanf("%s",s1);
                if (searchResult(s1)==-1)
                {
                    printf("未找到相关信息!无法修改\n");
                    getchar();printf("按回车键继续");
                }
                else
                {
                    printf("请输入新的信息(账号和密码):\n");
                    int i=searchResult(s1);
                    scanf("%s%s",users[i].account,users[i].passwd);
                    printf("修改成功!");
                    saveFile(users,count);
                    getchar();printf("按回车键继续");
                }
                break;
            case 4: 
                    printf("请输入查询的账户:\n");
                    scanf("%s",s1);
                    if (searchResult(s1)==-1)
                    {
                        printf("未找到相关信息!\n");
                        getchar();printf("按回车键继续");
                    }
                    else 
                    {
                        int i=searchResult(s1);
                        printf("账号:%s\n余额:%.2lf\n单次限额:%.2lf\n加密密码:",users[i].account,users[i].balance,users[i].limitCost);
                        AddSecret(users[i].passwd);
                        getchar();printf("按回车键继续");
                    }
                    break;
            case 5: 
                return;         
                break; 
            case 6: 
                printf("请输入查找的账号:\n");
                gets(s1);
                if (searchResult(s1)==-1)
                {
                    printf("未找到相关信息!\n");
                    getchar();printf("按回车键继续");
                }
                else 
                {
                    int i=searchResult(s1);
                    User* pp=users+i;
                    printRecord(pp);
                }
                break;
            case 7:
                if(strcmp(Password1,s2)==0||strcmp(Password3,s2)==0)
                {
                    printf("权限不足，需要超级管理员身份!\n");
                    break;
                }
                int i;
                for (i = 0; i < count; i++) 
                {
                if (users[i].Freeze) 
                {
                printf("编号为%d,账号为%s的用户冻结,是否希望解除冻结(是为1,否为0):%d\n", i, users[i].account,issubmit(i));
                FriNum++;
                }
                }

                printf("选择你所需要解封的账号编号（若没有，则输入-1）:");
                scanf("%d",&i);
                if(i==-1)
                	break;
                DeleteFridge(i);
                printf("若为正确编号，则解封成功!");
                getchar();
                break;
            
            case 8:
                printAll();
                break;
            case 9:
                limit();
                break;
            default:
                printf("请移动到正确位置");
                getchar();printf("按回车键继续");
                break;
        system("pause"); 
        }
    }
}

void email(User* pr)
{
    for(int i=0;i<pr->NUM;i++)
    {
        printf("您近期的第%d笔此笔交易为:%.2lf\n",i+1,pr->record[i].history);
        printf("交易类型为:%s\n",pr->record[i].Ptype);
        printf("_______________________\n");
    }
    printf("您的账户还有%.2lf元\n",pr->balance);
}

void menu()
{
    printf("\t\t\t\t\t");
    printSlowly("\033[31m欢迎来到常工银行ATM系统");
    printSlowly2(".......\n");
    atm();
    printf("\t\t\t\t\t");
    printSlowly("\033[31m加载完成\n");
    system("color f6");
    while (1)
    {
        printf("\t\t\t\t\t"); 
        printf("\033[1m按回车键可打开菜单");
        getchar();
        putchar('\n');
        printf("\t\t\t\t\t用户界面");
        if(pr!=NULL)
        printf("\t\t%s",pr->account);
        printf("\n");
        printf("请使用 h(左),l(右),a(确认) 操作: \n");
        printf("|注册|\t"); 
        printf("|登录|\t");
        printf("|查余|\t");
        printf("|存款|\t");
        printf("|取款|\t");
        printf("|管理|\t");
        printf("|退出|\t"); 
        printf("|转账|\t");
        printf("|改密|\t");
        printf("|注销|\t");
        printf("|邮箱|\t");
        printf("|忘密|\t");
        printf("|退登|\t\n");
        char s[]="******";
        int num=0; 
        printf("%s",s);
        while(1)
        {
            char ch=getch();
            if(ch=='l'||ch=='L')
            {
                if(num>13)
                    ;
                else
                {
                num++;
                clearLine();
                for (int i = 0; i < num; i++)
                    printf("\t");
                printf("%s",s); 
                }
            }
            if(ch=='h'||ch=='H')
            {
                if(num==0)
                    ;
                else
                {
                num--;
                clearLine();
                for (int i = 0; i < num; i++)
                    printf("\t");
                printf("%s",s);
                }
            }
            if(ch=='a'||ch=='A')
                break;
        }
        printf("\n");
        switch (num+1)
        {
            case 1:
                logup();
                break;
            case 2:
                login();
                break;
            case 3:
                if(pr==NULL)
                    printf("请先登录");
                else
                    showBalance();
                break;
            case 4:
                if(pr==NULL)
                    printf("请先登录");
                else
                    deposit();
                break;
            case 5:
                if(pr==NULL)
                    printf("请先登录");
                else
                    withdraw();           
                break;
            case 6:
                system("cls");
                menu2(); 
                break;
            case 7:
                printf("谢谢使用！\n");
                exit(0);
                break;
            case 8:
                if(pr==NULL)
                    printf("请先登录");
                else
                    transfer();
                break;
            case 9:
                if(pr==NULL)
                    printf("请先登录");
                else changePassword();
                break;
            case 10:
                if(pr==NULL)
                    printf("请先登录");
                else logout();
                break;
            case 11:
                if(pr==NULL)
                    printf("请先登录");
                else email(pr);
                break;
            case 12:
                if(pr!=NULL)
                    printf("你已登录");
                else
                {
                    forgotPassword();
                }
                break;
            case 13:
                pr=NULL;
                printf("退出登录成功\n");
                break;
            default:
                printf("请移动到正确位置");
                break;
        }
        system("pause"); 
        system("cls"); 
    }
}

int main()
{
    for (int i = 0; i < MAX; i++)
    {
        users[i].record[i].Ptype = NULL;
    }

    count=loadFile(users);
    menu();
    system("pause"); 
    return 0;
}
