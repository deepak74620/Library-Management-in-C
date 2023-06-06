// C program to implement
// the above approach
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define BUFFER_SIZE 1000

void status()
{
    FILE *fPtr;
    FILE *fTemp;
    char path[100]="booklist.txt";

    char buffer[BUFFER_SIZE];
    char newline[BUFFER_SIZE];
    int line, count;


    printf("Enter line number to replace: ");
    scanf("%d", &line);

    /* Remove extra new line character from stdin */
    fflush(stdin);

    printf("Replace '%d' line with: ", line);
    fgets(newline, BUFFER_SIZE, stdin);

    /*  Open all required files */
    fPtr = fopen(path, "r");
    fTemp = fopen("replace.tmp", "w");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }

    /*
     * Read line from source file and write to destination
     * file after replacing given line.
     */
    count = 0;
    while ((fgets(buffer, BUFFER_SIZE, fPtr)) != NULL)
    {
        count++;

        /* If current line is line to replace */
        if (count == line)
            fputs(newline, fTemp);
        else
            fputs(buffer, fTemp);
    }

    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove(path);

    /* Rename temporary file as original file */
    rename("replace.tmp", path);

    printf("\nSuccessfully replaced '%d' line with '%s'.", line, newline);
}

void Teacher()
{
tch_pass:
    printf("\nPlease enter the password to access as teacher: ");
    int pass;
    scanf("%d", &pass);

    if (pass == 1)
    {
    tch:
        printf("\n\n1. To open Book list \n2. To open a student file\n3. To go home\n");
        printf("\nEnter your choice: ");
        int tch_choice;
        scanf("%d", &tch_choice);
        if (tch_choice == 1)
        {
            char data[100];
            FILE *fp;
            printf("\nList of books in the Libray \n");
            fp = fopen("booklist.txt", "a+");
            while (fgets(data, 100, fp) != NULL)
            {
                printf("%s", data);
            }
            fclose(fp);

            printf("\n\n1. To add books\n2. To edit book record\n");
            printf("3. To return to home\n\n");
            printf("Enter your choice: ");
            int add;
            scanf("%d", &add);

            if (add == 1)
            {

                char data[100];
                char new_book[100];
                FILE *fp;

                fp = fopen("booklist.txt", "a+");
                printf("\nAdd new book: ");
                // Reason unknown for two input
                gets(new_book);
                fgets(new_book, 100, stdin);
                // fgets(new_book,100,stdin);

                fputs(new_book, fp);
                fclose(fp);

                fp = fopen("booklist.txt", "a+");
                printf("\n\nThe updated booklist is:\n");
                while (fgets(data, 100, fp) != NULL)
                {
                    printf("%s", data);
                }
                fclose(fp);
                goto tch;
            }
            else if (add == 2)
            {
                status();
                goto tch;
            }
            else if (add == 3)
            {
                return;
            }
            else
            {
                printf("\nPlease select the correct option");
                printf("\nTo exit press any key: ");
                getch();
                goto tch;
            }
        }
        else if (tch_choice == 2)
        {
            int roll;
            FILE *fp;
            char id[50];
            char data[1000];
            printf("Enter the student roll no: ");
            scanf("%d", &roll);
            sprintf(id, "%d", roll);
            char txt[5] = ".txt";
            strcat(id, txt);
            if (roll <= 1800000 || roll >= 2200000)
            {
                printf("\nInvalid roll ");
                printf("\nTo exit press any key");
                getch();
                goto tch;
            }
            else
            {
                fp = fopen(id, "a+");
                printf("\n\nRecord of the student:\n");
                while (fgets(data, 1000, fp) != NULL)
                {
                    printf("%s", data);
                }
                fseek(fp, 0, SEEK_END);
                int size = ftell(fp);
                fclose(fp);

                if (size == 0)
                {
                    printf("\nThe student has no previous records:\n");
                    char name[50];
                    char roll[50];
                    char branch[50];
                    char batch[50];
                    char book_name[50];
                    char date[50];
                    char replace_book[50];
                    fp = fopen(id, "a+");
                    printf("Add details: \n");
                    fputs("Personal details:\n",fp);
                    printf("Name: ");
                    gets(name);
                    gets(name);

                    fputs(name, fp);
                    fputs("\n", fp);
                    printf("\nRoll no: ");
                    scanf("%s", roll);
                    fputs(roll, fp);
                    fputs("\n", fp);
                    printf("\nBranch: ");
                    scanf("%s", branch);
                    fputs(branch, fp);
                    fputs("\n", fp);
                    printf("\nBatch: ");
                    scanf("%s", batch);
                    fputs(batch, fp);
                    fputs("\n\n", fp);
                    fputs("Student Record :", fp);
                tch_std:
                    printf("\n\n1. To issue a book: ");
                    printf("\n2. To exit:");
                    printf("\nEnter your choice: ");
                    int issue_book;
                    scanf("%d", &issue_book);

                    if (issue_book == 1)
                    {
                        printf("\n\nBook name: ");
                        gets(book_name);
                        gets(book_name);

                        printf("\nDate: ");
                        gets(date);
                        char issued_book[50];
                        strcpy(issued_book, book_name);
                        strcat(issued_book, " issued on ");
                        strcat(issued_book, date);
                        fputs("\n",fp);
                        fputs(issued_book, fp);
                        printf("\n\nBook issued succesfully");
                        fclose(fp);
                        goto tch;
                        
                    }
                    else if (issue_book == 2)
                    {
                        fclose(fp);
                        goto tch;
                    }
                    else
                    {
                        printf("\n\nYou entered an invalid option\n");
                        printf("\nPress any key to continue:");
                        getch();
                        goto tch_std;
                    }
                }
                else
                {
                    is_or:
                    printf("\n\n    1. To issue a book \n");
                    printf("    2. To return a book: \n");
                    printf("    Enter your choice: ");
                    int iss_ret;
                    scanf("%d", &iss_ret);
                    if (iss_ret == 1)
                    {
                        char book_name[50];
                        char date[50];
                        fp = fopen(id, "a+");

                        printf("\n\nBook name: ");
                        gets(book_name);
                        gets(book_name);

                        printf("\nDate: ");
                        gets(date);
                        char issued_book[50];
                        strcpy(issued_book, book_name);
                        strcat(issued_book, " issued on ");
                        strcat(issued_book, date);
                        fputs("\n",fp);
                        fputs(issued_book, fp);
                        printf("\n\nBook issued succesfully");

                        fclose(fp);
                        goto tch;
                    }
                    else if (iss_ret == 2)
                    {

                        char book_name[50];
                        char date[50];
                        fp = fopen(id, "a+");

                        printf("\n\nBook name: ");
                        gets(book_name);
                        gets(book_name);

                        printf("\nDate: ");
                        gets(date);
                        char returned_book[50];
                        strcpy(returned_book, book_name);
                        strcat(returned_book, " returned on ");
                        strcat(returned_book, date);
                        fputs("\n",fp);
                        fputs(returned_book, fp);
                        printf("\n\nBook returned succesfully");
                        fclose(fp);
                        goto tch;
                    }
                    else{
                        printf("\n\nYou entered an incorrect number");
                        printf("\n\nPress any key to continue: ");
                        getch();
                        goto is_or;

                    }
                }
            }
        }
        else if (tch_choice == 3)
        {
            return;
        }
        else
        {
            printf("Please enter a valid number\n");
            printf("\nPress any key to continue\n");
            getch();
            goto tch;
        }
    }
    else
    {
        printf("\n\nIncorrect password\n");
        printf("\nPress any key to try again: \n");
        getch();
        goto tch_pass;
    }
}

void Student_enq()
{
std:

    printf("\n\n    1. To open book list\n");
    printf("    2. To view your record\n");
    printf("    3. To go home\n");
    printf("    Enter your choice: ");

    int std_choice;
    scanf("%d", &std_choice);

    if (std_choice == 1)
    {
        char data[100];
        FILE *fp;
        printf("\n\nThe books available in library are:\n\n");
        fp = fopen("booklist.txt", "a+");
        while (fgets(data, 100, fp) != NULL)
        {
            printf("%s", data);
        }
        fclose(fp);
        printf("\n\nPress any key to exit: ");
        getch();
        return;
    }
    else if (std_choice == 2)
    {
        int roll;
        FILE *fp;
        char id[50];
        char data[1000];
        printf("\n\nEnter your roll no: ");
        scanf("%d", &roll);
        printf("\n\n");
        sprintf(id, "%d", roll);
        char txt[5] = ".txt";
        strcat(id, txt);
        if (roll <= 1800000 || roll >= 2200000)
        {
            printf("    Roll No not found\n");
            // printf("\n\nPress any key to exit: ");
            // getch();
            // return;
        }
        else
        {
            fp = fopen(id, "a+");
            while (fgets(data, 1000, fp) != NULL)
            {
                printf("%s", data);
            }
            fseek(fp, 0, SEEK_END);
            int size = ftell(fp);

            if (0 == size)
            {
                printf("           No record found\n");
                printf("Please make sure that you are registered.\n");
                printf("\n\nPress any key to exit: ");
                getch();
                fclose(fp);
                goto std;
            }
            else
            {
                printf("\n\nPress any key to start again:");
                getch();
                fclose(fp);
                goto std;
            }

        }
    }
    else if(std_choice==3){
        return;
    }
    else
    {
        printf("You entered an invalid number\n\n");
        printf("Press any key to continue\n");
        goto std;
    }
}

void Login()
{
home:
    printf("    1. Login as teacher\n");
    printf("    2. Login as student\n\n");
    printf("    Enter your choice: ");

    int login_as;
    scanf("%d", &login_as);
    if (login_as == 1)
    {
        Teacher();
        system("cls");
        goto home;
    }
    else if (login_as == 2)
    {
        Student_enq();
        system("cls");
        goto home;
    }
    else
    {
        printf("    Please enter a valid number\n");
        printf("    Press any key to start again: ");
        getch();
        system("cls");
        goto home;
    }
}
// Driver code
int main()
{
    Login();
    return 0;
}
