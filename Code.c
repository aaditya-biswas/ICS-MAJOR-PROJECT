#include <stdio.h>
void Read_Users();
void Read_Users()
{
    char c;
    FILE * read_records;
    read_records = fopen("Users.txt","r");
    c = fgetc(read_records);
    printf("\n");
    while (c != EOF);
    {
        if (c == '/')
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
    char str[100];
    FILE * user_ptr, * records_ptr;
    printf("------------------------------------------------------LIBRARY MANAGEMENT SYSTEM--------------------------------------------------------------------");
    printf("1.New User\n2.Old User");
    switch (getchar())
    {
        case '1':
        {
            fgets(str,100,stdin);
            if (valid_str(str))
            {
                Add_User(valid_str);
            }
        }
        case '2':
        {
            
        }
    }
}