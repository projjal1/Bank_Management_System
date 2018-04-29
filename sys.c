#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<stdbool.h>
#include<time.h>

int point =0;
char a_pass[5]="12345";
struct user
{
    char name[20];
    int no;
    char pass[20];
}users[50];

struct account
{
    char message[50];
    int amount;
}us[50];

struct user new_us(struct user d);
int admin();
int reg_us(struct user d,int in);
int portal ();
int p_portal(char st[]);

int main(void)
{
    printf("\nWelcome to RCCIIT Banking Solutions.Inc");
    printf("\nThis sofware is  a emulator of banking softwares");
    printf("\nHappy to help and distribute\n-----------------------------------------------------------------");
    int f=1;
    while(f!=0)
    {
        printf("\n\nOptions:\n1.New User \n2.Registered User \n3.Admin \n4.Quit");
        int ch;
        int pt=0;
        printf("\nEnter option:");
        scanf("%i",&ch);
        switch(ch)
        {
            case 1:users[point]=new_us(users[point]);
                    ++point;
                    break;
            case 2:pt=portal();
                    if (pt==-1)
                    {
                        printf("No such name found, please register yourself");
                        break;
                    } 
                    reg_us(users[pt],pt);
                    break;
            case 3:admin(); 
                    break;
            case 4:exit(0);
            default:printf("\nSecurity Warning");
        }
    }
}
struct user new_us(struct user d)
{
    printf("\nEnter the id of user of your choice , Enter the password: ");
    scanf("%s",&(d.name));
    scanf("%s",&(d.pass));
    printf("\nNew user created succesfully");
    int n=1170*100+point+1;
    d.no=n;
    printf("\nAccount no. is : %i",d.no);
    return d;
}
int admin()
{   
    printf("\nEnter admin password:");
    if (p_portal(a_pass)==1)
        return 0;
    printf("\nWelcome to the admin panel");
    int f=0;
    while(f!=1)
    {
        printf("\n\nOptions:- \n1.Change Password \n2.View registered users \n3.Delete Users \n4.No of Users \n5.Message User \n6.Quit\n");
        int chr;
        printf("Enter option:");
        scanf("%i",&chr);
        int p=0;
        switch(chr)
        {
            case 1:printf("\nEnter new password:");
                    scanf("%s",a_pass);
                    printf("\nNew password is :%s",a_pass);
                    break;
            case 2:for (int k=0;k<point;k++)
                    {
                        printf("\nUser: %s  Password: %s  Account no:%i  ",users[k].name,users[k].pass,users[k].no);
                    }       
                    break;
            case 3:p=portal();
                    printf("Deleting user details");
                    for (int k=p;k<point-1;k++)
                    {
                        users[k]=users[k+1];
                        users[k]=users[k+1];
                        users[k]=users[k+1];
                        us[k]=us[k+1];
                    }
                    --point;
            case 4:printf("\nNo of users as of yet is :%i",point);
                    break;
            case 5:p=portal();
                    printf("\nEnter the message:");
                    scanf("%s",us[p].message);
                    break;
            case 6:return 0;
            default:printf("\nSecurity warning");
        }
    }
}

int portal()
{
    printf("\nWelcome to registered user portal");
    printf("\nEnter the name of registered user: ");
    char name[20];
    scanf("%s", name);
    for (int i=0;i<point;i++)
        if (strcmp(name,users[i].name)==0)
            return i;
    return -1;
}

int reg_us(struct user d,int in)
{
    printf("\nWelcome user %s to account portal",d.name);
    printf("\nEnter the password to verify identity");
    if (p_portal(d.pass)==1)
        return 0;
    int count =0;
    int f=0;
    FILE *op=fopen(d.name,"a+");
    FILE *op1=fopen(d.name,"r");
    while(f!=1)
    {
        printf("\n\nOptions:\n1.View amount in account \n2.Account credit \n3.Account debit \n4.View Message from admin \n5.Show log\n6.Quit");
        printf("\nEnter option:");
        int chr;
        
        time_t var;
        scanf("%i",&chr);
        switch(chr)
        {
            
            case 1:printf("\nAmount left in your account is :%i",us[in].amount);
                    break;
            case 2:printf("Enter the amount to credit :");
                    
                    int amt;
                    scanf("%i",&amt);
                    fputs("\n\n\n Time:-",op);
                    fprintf(op,"%s",ctime(&var));
                    fputs("\nAmount credited to account :- ",op);
                    fprintf(op,"%i",amt);
                    us[in].amount=us[in].amount+amt;
                    printf("\nAmount left in your account is :%i",us[in].amount);
                    break;
            case 3:printf("Enter the amount to debit :");
                    int amt1;
                    
                    scanf("%i",&amt1);
                    if (amt1>us[in].amount)
                    {
                        printf("\nInsufficient amount in balance");
                        break;
                    }
                    fputs("\n\n\n Time:-",op);
                    fprintf(op,"%s",ctime(&var));
                    fputs("\nAmount debited from account :- ",op);
                    fprintf(op,"%i",amt1);
                    us[in].amount=us[in].amount-amt1;
                    printf("\nAmount left in your account is :%i",us[in].amount);
                    break;
            case 4:printf("\nShowing message from admin\n");
                    printf("%s",us[in].message);
                    break;
            case 5:printf("\nShowing transaction log:-");
                    int c=0;
                    while((c=fgetc(op1))!=EOF)
                        putchar(c);
                    printf("\n\nSystem log finished\n");
                    break;
            case 6:return 0;
            default:printf("System Warning");
        }
        fflush(op1);
        fflush(op);
        
    }
    fclose(op1);
    fclose(op);
}

int p_portal(char st[])
{
    int count=0;
    int flag=1;
    char pas[5];
    do
    {
        printf("\n\nEnter the  password:");
        scanf("%s",&pas);
        if (strcmp(pas,st)==0)
        {   
            flag=0;
            break;
        }
        else
            printf("\nYou have %i chances left",(3-count));
        count++;
    }while(count!=3);
    return flag;
}