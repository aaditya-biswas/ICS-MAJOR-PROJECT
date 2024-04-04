#include <stdio.h>
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
int Check_User(char * str1,char * str2);
int Check_User(char * str1,char * str2)
{

}
int main()
{
    int new_user = 0; //Checking if a new user is present or not
    char c,str1[100],str2[100]; // String constant
    FILE * user_ptr, * records_ptr; // File pointers to each database. Check Users.txt for more details
    printf("------------------------------------------------------LIBRARY MANAGEMENT SYSTEM--------------------------------------------------------------------");
    printf("1.New User\n2.Old User\n");
    switch (getchar()) // Choice by numbering.
    {
        case '1':
        {
            printf("Enter Username:\n");
            fgets(str1,100,stdin);
            while (valid_str(str1) == 0) // Checks for a valid string . We have used '/' as delimeter .
            {
                fgets(str1,100,stdin);
            }
            printf("Enter Password:\n");
            fgets(str2,100,stdin);
            while (valid_str(str2) == 0) // Checks for a valid string . We have used '/' as delimeter .
            {
                fgets(str2,100,stdin);
            }
            Add_User(str1,str2); // Function for adding a new user in User.txt
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
            fgets(str1,100,stdin); // Taking input str1 which will take user id
            printf("Enter Password:\n");
            fgets(str2,100,stdin); // Taking input str2 which is password to check
            if (valid_str(str1) && valid_str(str2)) // Validating the string by checking for / character (/ - separator)
            {
                rem_newline(str1); // removing newline from fgets
                rem_newline(str2);
                if (Check_User(str1,str2) != 0) //  Function Check_User will return non - zero value if User _id & Password match else it will return 0
                {
                    printf("\n WELCOME %s!\n",str1);
                    fseek(user_ptr,Book_User_pos(str1),SEEK_SET); // Book_User_pos to set the  file pointer to the Books locaation
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
                Read_User_Books(str1);
            }
        }
        case '2':
        {
            printf("1.Search for a particular book\n2.Show all available books");
            switch (getchar())
            {
            case '1':
            {
                
                break;
            }
            case '2':
            
            default:
            {
                printf("\nInvalid choice");
                
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