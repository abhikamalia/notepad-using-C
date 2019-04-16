#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_HEADING 51
#define MAX_TEXT 100001
int i;
//#define MAX_DELETE 31
char heading_data[MAX_HEADING];
char text_data[MAX_TEXT];





struct node
{
    char heading[MAX_HEADING];
    char text[MAX_TEXT];
    struct node *next;
};struct node *head;

struct recycle_node
{
    struct node *location;
    struct recycle_node *next;
};struct recycle_node *head_delete;

void clrscr()
{
    system("@cls||clear");
}

void create_dir(char *dir_name)
{
    mkdir(dir_name);
}


void Empty_recycle_bin()
{
    int choose;

    if(head_delete != NULL)
    {
        printf("Empty recycle bin (0) , Home (1)\n");
        scanf("%d" , &choose);
        if(choose == 0)
        {

            while(head_delete != NULL)
            {
                struct recycle_node *temp_in = head_delete;
                head_delete = temp_in -> next;
                free(temp_in);
            }

            return;
        }return;

    }
    if(head_delete == NULL)
    {
        printf("\nRecycle bin empty ..\n\n\n");
        return;
    }

}


void Print_deleted()
{

    clrscr();
    printf("\n------------------------------ RECYCLE BIN ------------------------------\n\n\n");
    struct recycle_node *temp_del = head_delete ;
    struct node *temp = head;
    while(temp_del != NULL)
    {
        temp = temp_del -> location;
        printf("Heading : ");
        printf("%s" , temp -> heading);
        printf("Text : ");
        printf("%s\n\n\n" , temp -> text);
        temp_del = temp_del -> next;
    }printf("\n\n");


}


void Print()
{
    clrscr();
    printf("\n------------------------------  NOTES  ------------------------------\n\n\n");
    struct node *temp = head;
    while(temp != NULL)
    {
        printf("Heading : ");
        printf("%s " , temp -> heading);
        printf("Text : ");
        printf("%s\n\n\n" , temp -> text);
        temp = temp -> next;
    }printf("\n");
}

void Delete(int del_position)
{
    int i;
    struct recycle_node *temp_del = (struct recycle_node*)malloc(sizeof(struct recycle_node));
    struct node *temp1 = head;

    if(del_position == 1)
    {

        temp_del -> location = temp1;
        temp_del -> next = head_delete;
        head_delete = temp_del;

        head = temp1 -> next;
        temp1 -> next = NULL;
        printf("Deleted .\n\n");
        return;
    }
    for(i = 0 ; i < del_position - 2 ; i ++)
    {
        temp1 = temp1 -> next;
    }
    struct node *temp2 = temp1 -> next;
    temp1 -> next = temp2 -> next;

    temp_del -> location = temp2;
    temp_del -> next = head_delete;
    head_delete = temp_del;
    printf("Deleted .\n\n");
}

void file_retrive(char *file_name)
{
    FILE *fr;

    struct node *temp1 = (struct node*)malloc(sizeof(struct node));

    fr = fopen(file_name , "rt");

    /*while(temp2 -> next != NULL)
    {
        temp2 = temp2 -> next;
    }*/
    temp1 -> next = head;
    head = temp1;

    fgets(temp1 -> heading , 51 , fr);

    fgets(temp1 -> text , 100001 , fr);

    //temp1 -> next = temp2 -> next;
    //temp2 -> next = temp1;

    //fscanf(fr , "%[^\t\n]s" , buffer);
    //printf("%s\n" , buffer);
    fclose(fr);


}

void Insert()
{
    FILE *fp;
    char file_name[51] , ext[] = ".txt";
    //char str[3] ;
    char dirname[31];
    clrscr();
    struct node *temp1 = (struct node *)malloc(sizeof(struct node));
    if(head == NULL)
    {
        //i = 1;

        strcpy(temp1 -> heading , heading_data);
        strcpy(temp1 -> text , text_data);
        temp1 -> next = head;
        head = temp1;
        printf("Save as : ");
        gets(file_name);
        printf("Directory path : ");
        gets(dirname);
        //sprintf(str , "%d" , i);

        //fp = fopen(strcat(file_name , str), "w");
        fp = fopen(strcat(dirname , strcat(file_name , ext)), "w");
        fprintf(fp , strcat(temp1 -> heading , "\n"));
        fprintf(fp , temp1 -> text);
        fclose(fp);
        return;
    }
    struct node *temp2 = head;
    while(temp2 -> next != NULL)
    {
        temp2 = temp2 -> next;

    }

    temp1 -> next = temp2 -> next;
    temp2 -> next = temp1;
    strcpy(temp1 -> heading , heading_data);
    strcpy(temp1 -> text , text_data);

    //i = i + 1;
    //sprintf(str , "%d" , i);
    printf("Save as : ");
    gets(file_name);
    printf("Directory path : ");
    gets(dirname);
    //fp = fopen(strcat(file_name , str), "w");
    fp = fopen(strcat( dirname, strcat(file_name , ext)), "w");
    fprintf(fp , strcat( temp1 -> heading , "\n"));
    fprintf(fp , temp1 -> text);
    fclose(fp);
}

void surface_input()
{
    char file_name[30] , dir_name[31];
    char again , useless;
    int choose , del_position;
    printf("Write notes (0) , delete notes (1) , show all notes (2) , recycle bin (3)\n");
    printf("retrieve file (4) , Create directory(5)\n");
    scanf("%d" , &choose);
    scanf("%c" , &useless);
    if(choose == 0)
    {
        clrscr();
        while(again != 'n')
        {
            clrscr();
            printf("\n------------------------------  WRITE NOTE ------------------------------\n\n\n");
            printf("Heading : ");
            gets(heading_data);
            printf("Text : ");
            gets(text_data);
            Insert();

            printf("Write one more (y or n)?? : ");
            scanf("%c" , &again);
            scanf("%c" , &useless);
        }
        clrscr();
        surface_input();
    }
    if(choose == 1)
    {
        clrscr();
        printf("position to be deleted : ");
        scanf("%d" , &del_position);
        Delete(del_position);

        surface_input();
    }
    if(choose == 2)
    {
        clrscr();
        Print();
        surface_input();
    }
    if(choose == 3)
    {
        clrscr();
        Print_deleted();
        Empty_recycle_bin();

        surface_input();
    }
    if(choose == 4)
    {

        clrscr();
        printf("File name : ");
        gets(file_name);
        file_retrive(file_name);
        surface_input();
    }
    if(choose == 5)
    {
        clrscr();
        printf("Directory name : ");
        gets(dir_name);
        create_dir(dir_name);
        printf("\nDirectory created..\n\n");
        surface_input();
    }

}


int main()
{

    head = NULL;
    head_delete = NULL;
    printf("\n\n------------------------------  MINI NOTE OS  ------------------------------ \n\n\n");
    surface_input();
    return 0;
}

