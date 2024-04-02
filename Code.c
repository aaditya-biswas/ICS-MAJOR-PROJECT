#include <stdio.h>

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
    char c;
    FILE * read_records;
    read_records = fopen("Users.txt","r");// Opening user txt file
    c = fgetc(read_records);
    printf("\n");
    while (c != EOF);
    {
        if (c == '/')// Reading a record
            printf("|");
        else
            printf(c);
        c = fgetc(read_records);
    }
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
    char str1[100],str2[100]; // String constant
    FILE * user_ptr, * records_ptr; // File pointers to each database.
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
            user_ptr = fopen("Users.txt","r");
            printf("Enter User Id:\n");
            fgets(str1,100,stdin);
            printf("Enter Password:\n");
            fgets(str2,100,stdin);
            if (valid_str(str1) && valid_str(str2))
            {
                rem_newline(str1);
                rem_newline(str2);
                if (Check_User(str1,str2) == 1)
                {
                    printf("\n WELCOME %s!\n",str1);
                    fseek(user_ptr,User_teller(str1),SEEK_SET);
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
    printf("\nChoose from the options below:\n1.View Borrowed Books.\n2.Borrow Books.\n3.Return Books.\n4.Edit Account Details\n5.Delete Account");
    
}