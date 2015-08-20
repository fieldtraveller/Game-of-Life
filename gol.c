#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define row 56//max=57
#define column 80

#define Invalid {\
                   printf(" Invalid Input.");\
                   fflush(stdin);\
                   getch();\
}

unsigned char data_0[row][column];
unsigned char data_1[row][column];

void clean(void);
void display(void);
void copy(void);
void set(void);
void random(void);
void check(void);
void wait(int);
void save(void);
void load(void);
void gotoxy(int,int);
void info(void);

COORD coord={0,0};

int main(void)
{
    unsigned long a=0;
    char s=1;

    start:
    printf("\n\t\t\t Game of Life.\n\t\t\t\t    By Alex\n\n Press D to Draw Pattern\n Press L to Load Pattern\n Press R to Create Random Pattern");
    printf("\n Press I for Instructions");

    while(s!=0)
    {
        s=getch();

        switch(s)
    {
        case 'l':
        case 'L':
        load();
        s=0;
        break;

        case 'd':
        case 'D':
        set();
        s=0;
        break;

        case 'r':
        case 'R':
        random();
        s=0;
        break;

        case 'i':
        case 'I':
        info();
        goto start;
        break;
    }
    }

    while((s!='y')&&(s!='Y')&&(s!='n')&&(s!='N'))
    {
        printf("\r Do you want to simulate the pattern [Y\\N]?");
        s=getch();

        switch(s)
        {
            case 'y':
            case 'Y':
            system("cls");
            break;

            case 'n':
            case 'N':
            system("cls");
            goto start;
            break;
        }
    }

    while(1)
    {
        display();
        printf(" Generations:%lu",a++);
        //wait(2);
        check();
        gotoxy(0,0);
    }

    return 0;
}

void clean(void)
{
    unsigned char a,s;
    for(a=0;a<row;a++) //Rows
    {
        for(s=0;s<column;s++) //Columns
        {
            data_0[a][s]=32;
            data_1[a][s]=32;
        }
    }
}

void display(void)
{
    unsigned char a,s;
    for(a=0;a<row;a++) //Rows
    {
        for(s=0;s<column;s++) //Columns
        printf("%c",data_0[a][s]);
    }
}

void copy(void)
{
    unsigned char a,s;
    for(a=0;a<row;a++) //Rows
    {
        for(s=0;s<column;s++) //Columns
        data_0[a][s]=data_1[a][s];
    }
}

void set(void)
{
    char a=0;
    int s,d,f;

    clean();

    while((a!='e')&&(a!='E'))
    {
        system("cls");
        display();
        printf(" Enter Coordinate followed by Value:");
        scanf("%d %d %d",&s,&d,&f);

        if(!((s>row)||(d>column)))
        {
        if(f==0)
        data_0[s][d]=32;
        else if(f==1)
        data_0[s][d]=219;
        else
        Invalid;
        }
        else
        Invalid;

        system("cls");
        display();
        printf(" Press E to Exit");
        fflush(stdin);
        a=getch();
    }

    save();

   // system("cls");
}

void random(void)
{
    unsigned char a,s,d,f;

    printf("\n\n Enter any Number between 0 and 255:");
    scanf("%d",&f);

    for(a=0;a<f;a++)
    d=rand();

    printf(" Enter Compare Value between 0 and 255:");
    scanf("%d",&f);

    for(a=0;a<row;a++) //Rows
    {
        for(s=0;s<column;s++) //Columns
        {
            d=rand();
            if(d<f)
            data_0[a][s]=32;
            else
            data_0[a][s]=219;
        }
    }

    display();
}

void check(void)
{
   int a,s,d,f,count=0;

    for(a=01;a<row-1;a++) //rows_main
    {
        for(s=01;s<column-1;s++) //column_main
        {
            for(d=-1;d<2;d++) //rows
            {
               for(f=-1;f<2;f++) //column
                {
                    if(!((f==0)&&(d==0)))
                    {
                        if(data_0[a+d][s+f]==219)
                        {
                            count++;
                        }
                    }
                }
            }

            if(count<2)
            data_1[a][s]=32;
            else if((count==2)&&(data_0[a][s]==219))
            data_1[a][s]=219;
            else if(count==3)
            {
                data_1[a][s]=219;
            }
            else
            data_1[a][s]=32;

            count=0;
        }
    }
    copy();
}

void wait(int a)
{
    int s;
    unsigned long d;

    for(s=0;s<a;s++)
    {
        d=0;
        while(d<42949)//max=4294967295
        {
            d++;
        }
    }
}

void save(void)
{
    FILE *f;
    unsigned char a=0,s;
    char d[10];

    while((a!='y')&&(a!='Y')&&(a!='n')&&(a!='N'))
    {
        printf("\r Do you want to save the pattern [Y\\N]?");
        a=getch();

        switch(a)
        {
            case 'y':
            case 'Y':
            break;

            case 'n':
            case 'N':
            return;
            break;
        }
    }

    printf("\n Save Pattern as:");
    gets(d);
    strcat(d,".gol");
    f=fopen(d,"w+");

    for(a=0;a<row;a++) //Rows
    {
        for(s=0;s<column;s++) //Columns
        {
            fputc(data_0[a][s],f);
        }
    }

    fclose(f);
    printf(" %s Saved\n",d);
}

void load(void)
{
    FILE *f;
    unsigned char a,s;
    char d[10];

    load_start:
    printf("\n\n Enter File Name:");
    gets(d);
    strcat(d,".gol");
    f=fopen(d,"r");

    if(f==NULL)
    {
        printf(" File does not exist.");
        goto load_start;
    }

    for(a=0;a<row;a++) //Rows
    {
        for(s=0;s<column;s++) //Columns
        {
            data_0[a][s]=fgetc(f);
        }
    }

    fclose(f);

    //system("cls");
    display();
}

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void info(void)
{
    FILE *f;
    char a;

    f=fopen("info.txt","r");

    if(f==NULL)
    {
        printf(" File does not exist.");
        printf("\n Please copy \"info.txt\" to the directory containing the program and then run the program.");
    }
    else
    {
        while((a=fgetc(f))!=EOF)
        printf("%c",a);
    }

    getch();
    system("cls");

    fclose(f);
}
