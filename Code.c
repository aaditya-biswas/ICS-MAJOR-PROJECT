#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int Book_Id; // Book Description
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
void Read_User_Books(FILE * fptr);
void Read_User_Books(FILE * fptr)
{
    char c = fgetc(fptr);
    printf("\n");
    while (c!='\n' && c!=EOF)
    {
        printf("%c",c);
        c = fgetc(fptr);
    }

}
void rem_newline( char * str); // Function to remove newline 
void rem_newline(char * str)
{
    char * ptr = str;
    while (*ptr != '\n')
    {
        ptr++;
    }
    *ptr = '\0';
}
Book get_book(int n);
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
int Check_User(char * username,char * password);
int Check_User(char * username,char * password)
{
    int count = 0,i=0,num = 1,check = 0;
    char c,user_name[100],pass_word[100],str3[1500];
    FILE * fptr = fopen("Users.txt","r");
    c = fgetc(fptr);
    while (!feof(fptr))
    {
        if (c == '/')
        {
            count++;
        }
        switch (count)
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
        return 0;
    }
}
int Book_User_pos(int n,FILE * fptr);
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
void Read_Users();
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

int valid_str(char str[100]);
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
int main()
{
    int new_user = 0; //Checking if a new user is present or not
    char c,user_name[100],pass_word[100],str3[1500]; // String constant
    FILE * user_ptr, * records_ptr; // File pointers to each database. Check Users.txt for more details
    printf("------------------------------------------------------LIBRARY MANAGEMENT SYSTEM--------------------------------------------------------------------");
    printf("1.New User\n2.Old User\n");
    switch (getchar()) // Choice by numbering.
    {
        case '1':
        {
            printf("Enter Username:\n");
            fgets(user_name,100,stdin);
            while (valid_str(user_name) == 0) // Checks for a valid string . We have used '/' as delimeter .
            {
                fgets(user_name,100,stdin);
            }
            printf("Enter Password:\n");
            fgets(pass_word,100,stdin);
            while (valid_str(pass_word) == 0) // Checks for a valid string . We have used '/' as delimeter .
            {
                fgets(pass_word,100,stdin);
            }
            Add_User(user_name,pass_word); // Function for adding a new user in User.txt
            printf("Added User Successfully!");
            new_user = 1;
            break;
        }
        case '2':
        {
            printf("The existing users are:\n");
            Read_Users();
            user_ptr = fopen("Users.txt","r");
            printf("Enter User Id:\n"); 
            fgets(user_name,100,stdin); // Taking input user_name which will take user id
            printf("Enter Password:\n");
            fgets(pass_word,100,stdin); // Taking input pass_word which is password to check
            if (valid_str(user_name) && valid_str(pass_word)) // Validating the string by checking for / character (/ - separator)
            {
                rem_newline(user_name); // removing newline from fgets
                rem_newline(pass_word);
                if (Check_User(user_name,pass_word) != 0) //  Function Check_User will return non - zero value if User _id & Password match else it will return 0
                {
                    printf("\n WELCOME %s!\n",user_name);
                    fseek(user_ptr,Book_User_pos(Check_User(user_name,pass_word),user_ptr),SEEK_SET); // Book_User_pos to set the  file pointer to the Books locaation
                }
                else 
                {
                    printf("Invalid Username or Password");
                    exit(0);
                }
            }
            break;
        }
        default:
        {
            printf("\nPlease enter 1 or 2\n");
            main();
            break;
        }
    }
    printf("\nChoose from the options below:\n1.View Borrowed Books.\n2.Borrow Books.\n3.Return Books.\n4.Edit Account Details\n5.Delete Account\n");
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
                Read_User_Books(user_ptr);
            }
        }
        case '2':
        {
            printf("1.Search for a particular book\n2.Show all available books\n");
            switch (getchar())
            {
            case '1':
            {
                printf("Enter the book name.\n");
                fgets(str3,1500,stdin);
                rem_newline(str3);
                if (Book_Search()) //Book_Search returns the line number of the book
                {
                    printf("Yes the book exists and the book details are:\n");
                    print_book(Book_Search);
                }
                break;
            }
            case '2':
            
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
    }
}