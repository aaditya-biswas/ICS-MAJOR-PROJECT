#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    char Book_Id[10]; // Book Description
    char Title[75];
    char Author[75];
    int Quantity;
} Book;
typedef struct {
    char User_Name[75]; // User
    char Password[75];
    char DOB[15];
    char Issued_Books[1500];
} User;

int Borrow_Book();
void exit_func();
void Read_User_Books(int n);                               // Function to read Books of user
int Add_User();              // Function to Add New User to the database
void rem_newline( char * str);                                 // Function to remove newline 
int Check_User();                         
void Read_Users();
int valid_str(char str[100]);
void print_Book(char * Book_name);
int Book_Search();
Book get_book(int n);

int Borrow_Book()
{

}

void exit_func()
{
    printf("Thank you for using our Library Management System. Exiting");
    exit(0);
}

void Read_User_Books(int n)
{
    FILE * user_data;
    user_data = fopen("Users.txt","r");
    char c,str[1500];
    int count = 0;
    while (n)
    {
        fgets(str,1500,user_data);
        n--;
    }
    c = fgetc(user_data);
    while (c != EOF && c != '\n')
    {
        if (c == '/')
        {
            count++;
        }
        if (count > 2)
        {
            printf("%c",c);
        }
        c = fgetc(user_data);
    }
    fclose(user_data);

}
int Add_User() // Please follow this outline to design a function
{
    fflush(stdin);
    FILE * user_ptr = fopen("Users.txt","a");
    char c,user_name[100],pass_word[100],DOB[100];
    printf("Enter Username:\n");
    fgets(user_name,100,stdin);
    printf("Enter Password:\n");
    fgets(pass_word,100,stdin);
    printf("Enter Date Of Birth:\n");
    fgets(DOB,100,stdin);
    rem_newline(user_name);
    rem_newline(pass_word);
    rem_newline(DOB);
    if (valid_str(user_name) && valid_str(pass_word) && valid_str(DOB))
    {
        fprintf(user_ptr,"\n%s/%s/%s/",user_name,pass_word,DOB);
        printf("Added User Successfully!");
        fclose(user_ptr);
    }
    else
    {
        fclose(user_ptr);
        printf("Invalid details entered.Would you like to try again? Y or N");
        if (getchar() == 'Y')
        {
            Add_User();
        } 
        else
        {
           exit_func();
        }
    }
}

void rem_newline(char * str)
{
    char * ptr = str;
    while (*ptr != '\n')
    {
        ptr++;
    }
    *ptr = '\0';
}

Book get_book(int n)
{
    int i = 0,qty,count = 0;
    Book Req_Book;
    FILE * fptr;
    char c = fgetc(fptr),last[20],Book_id_req[120],Title_Req[120],Author_req[120];
    while (n - 1)
    {
        if (c == '\n')
        {
            n--;
        }
        c = fgetc(fptr);
    }
    while (c != '\n' && c != EOF)
    {
        if (c == '/')
        {
            count++;
            switch (count)
            {
                case 1:
                    Book_id_req[i] = '\0';
                case 2:
                    Title_Req[i] = '\0';
                case 3:
                    Author_req[i] = '\0';  
            }
            i = 0;
        }
        switch (count)
        {
            case 0:
            {
                Book_id_req[i] = c;
                c = fgetc(fptr);
                i++;
                break;
            }
            case 1:
            {
                c = fgetc(fptr);
                Title_Req[i] = c;
                i++;
                break;
            }
            case 2:
            {
                c = fgetc(fptr);
                Author_req[i] = c;
                i++;
                break;

            }
            case 3:
            {
                fgets(last,20,fptr);
                break;
            }
        }
    }  
}

int Check_User()
{
    fflush(stdin);
    int count = 0,i=0,num = 0,check = 0;
    char c,user_name[100],username[100],password[100],pass_word[100],str3[1500];
    printf("Enter Username\n");
    fgets(username,100,stdin);
    printf("Enter Password\n");
    fgets(password,100,stdin);
    rem_newline(username);
    rem_newline(password);
    FILE * fptr = fopen("Users.txt","r");
    c = fgetc(fptr);
    while (!feof(fptr))
    {
        if (c == '/')
        {
            count++;
        }
        switch (count )
        {
            case 0:
            {
                user_name[i] = c;
                i++;
                c = fgetc(fptr);
                break;
                
            }
            case 1:
            {
                if (c == '/')
                {
                    user_name[i] = '\0';
                    i = 0;
                    c = fgetc(fptr);
                }
                pass_word[i] = c;
                i++;
                c = fgetc(fptr);
                break;

            }
            case 2:
            {
                if (c == '/');
                {
                    pass_word[i] = '\0';
                    i = 0;
                    c = fgetc(fptr);
                }
                if (strcmp(username,user_name) == 0 && strcmp(pass_word,password) == 0)
                {
                    check = 1;
                    fclose(fptr);
                    return num;
                    break;

                }
                else
                {
                    num++;
                    count = 0;
                    fgets(str3,1500,fptr);
                    c = fgetc(fptr);
                    break;
                }
                break;   
            }
        }
    }
    fclose(fptr);
    if (check == 1)
    {
        return 1;
    }
    else
    {
        printf("Invalid Input !\n Do you want to retry? Y or N");
        if (getchar() == 'Y')
        {
            Check_User();
        }
        else
        {
            exit_func();
        }
    }
}

int Book_User_pos(int n,FILE * fptr)
{
    int count = 0;
    char c;
    while (n-1)
    {
        c = fgetc(fptr);
        if (c == '\n')
        {
            n--;
        }
    }
    while (count < 2)
    {
        c = fgetc(fptr);
        if (c == '/')
        {
            return ftell(fptr);
            break;
            count++;
        }

    }
}

void Read_Users()
{
    int count = 1,i=0;
    char c,str[1500];
    FILE * read_users;
    read_users = fopen("Users.txt","r");// Opening user txt file
    printf("1.");
    c = fgetc(read_users);
    while (c != EOF)
    {
        if (c == '/')
        {
            while (c != '\n' && c != EOF)
            {
                c = fgetc(read_users);
            }
            c = fgetc(read_users);
            if (c != ' ' && c !=  EOF)
            {
                count++;
                printf("\n%d.%c",count,c);
                i++;
            }
            c = fgetc(read_users);
        }
        else
        {
            printf("%c",c);
            c = fgetc(read_users);
        }
    }
    printf("\n");
}


int valid_str(char str[100])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '/')
        {
            printf("Invalid character /");
            return 0;
            break;
        }
        i++;
    }
    return 1;

}

int Book_Search()
{
    ;
}

int main()
{
    int new_user = 0,user_pos; //Checking if a new user is present or not
    char c,user_name[100],pass_word[100],str3[1500]; // String constant
    printf("------------------------------------------------------LIBRARY MANAGEMENT SYSTEM--------------------------------------------------------------------\n");
    printf("1.New User\n2.Old User\n");
    switch (getchar()) // Choice by numbering.
    {
        case '1':
        {
            Add_User();
            new_user = 1;
            break;
        }
        case '2':
        {
            Read_Users();
            user_pos = Check_User();
            break;
        }
        default:
        {
            printf("\nPlease enter 1 or 2\n");
            exit_func();
            break;
        }
    }
    printf("\nChoose from the options below:\n1.View Borrowed Books.\n2.Borrow Books.\n3.Return Books.\n4.Edit Account Details\n5.Delete Account\n6.Exit\n");
    switch (getchar())
    {
        case '1':
        {
            if (new_user)
            {
                printf("You are a new user. You have issued no books till yet.");
            }
            else 
            {
                Read_User_Books(user_pos);
            }
        }
        case '2':
        {
            printf("1.Search for a particular book\n2.Show all available books\n");
            switch (getchar())
            {
            case '1':
            {
                int x = Book_Search();
                if (x && get_book(x).Quantity > 0)  //Book_Search returns the structure of the book
                {
                    printf("Yes the book exists and the book details are:\n");
                    printf("Book_Id |   Title   |   Author  |   Quantity\n%s    %s  %s  %d",get_book(x).Book_Id,get_book(x).Title,get_book(x).Author,get_book(x).Quantity);
                    printf("Would you like to borrow? Y or N");
                    if (getchar() == 'Y')
                    {
                        Borrow_Book();
                    }
                    
                }
                else
                {
                    printf("The book doesn't exist or is out of stock. Sorry for the inconvenience caused.");

                }
                break;
            }
            case '2':
            {
                printf("The list of books are:");
                printf("Book_Id |  Title     | Author    | Quantity ");
                {
                    FILE * Book_list = fopen("Books.txt","r");
                    c = fgetc(Book_list);
                    while (c != EOF)
                    {
                        if (c == '/')
                        {
                            printf("\t");
                        }
                        else
                        {
                            printf("%c",c);
                        }
                        c = fgetc(Book_list);
                    }
                    fclose(Book_list);
                }
            }
            
            default:
            {
                printf("Invalid choice\n");
                exit(0);
            }
                break;
            }

        }
        case '3':
        {

        }
        case '4':
        {

        }
        case '5':
        {

        }
        case '6':
        {
            exit_func();
        }
    }
}