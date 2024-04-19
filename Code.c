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

int Change_Qty(char  str[],int num);
int last_user_Line();
void Delete_User(int user_pos);                              // Function to delete User
int Issued_Book(int user_pos);        
void Menu(int new_user,int user_pos);                        
int Options(int new_user,int user_pos); 
int Borrow_Book();
void exit_func();
void Read_User_Books(int n);                                // Function to read Books of user
int Add_User();                                             // Function to Add New User to the database
void rem_newline( char * str);                              // Function to remove newline 
int Check_User();                         
void Read_Users();
int valid_str(char str[100]);
void print_Book(char * Book_name);
Book Book_Search();
Book get_book(int n);

int Change_Qty(char str[],int num)
{
    FILE * book_ptr = fopen("Books.txt","r"), * temp_ptr = fopen("Temp.txt","w");
    char c,b_name[200],* str_ptr =str;
    int i,n = 0,count = 0,flag = 0;
    c = fgetc(book_ptr);
    while (c != EOF)
    {

        if (c == '\n')
        {
            fputc(c,temp_ptr);
            flag = 0;
            i =0;
            count = 0;
            c = fgetc(book_ptr);
            continue;
        }
        if (c == '/')
        {
            count++;
            fputc(c,temp_ptr);
            c = fgetc(book_ptr);
            continue;
        }
        if (count == 1)
        {
            while (c != '/')
            {
                fputc(c,temp_ptr);
                b_name[i] = c;
                i++;
                c = fgetc(book_ptr); 
            }
            b_name[i] = '\0';
            if (strcmp(str,b_name) == 0)
                flag = 1;
            continue;
        }

        if (flag == 1 && count == 3)
        {
            while (c != EOF && c != '\n')
            {
                n = n * 10 + ((int) c - 48);
                c = fgetc(book_ptr);
            }
            fprintf(temp_ptr,"%d",n+num);
            continue;
        }
        fputc(c,temp_ptr);
        c = fgetc(book_ptr);
    }
    fclose(book_ptr);
    fclose(temp_ptr);
    remove("Books.txt");
    rename("Temp.txt","Books.txt");
}

int Return_Book(int user_pos)
{
    fflush(stdin);
    FILE * user_ptr = fopen("Users.txt","r");
    char c,usr_inp[200],book_name[200],residual[2000];
    int f_pos= 0,count = 0,i = 0,flag = 0,gh = 0;
    while (user_pos)
    {
        fgets(residual,2000,user_ptr);
        user_pos--;
    }
    printf("Enter the book name you want to return\n");
    fgets(usr_inp,200,stdin);
    rem_newline(usr_inp);
    while (feof(user_ptr) == 0)
    {
        c = fgetc(user_ptr);
        if (c == '\n')
        {
            break;
        }
        if (c == '/')
        {
            count++;
        }
        if (count == 3)
        {
            if (c == '/')
            {
                c = fgetc(user_ptr);
            }
            i = 0;
            while (c != ',' && c!='\n' && c != EOF)
            {
                book_name[i] = c;
                c = fgetc(user_ptr);
                i++;
            }
            book_name[i] = '\0';
            if (strcmp(book_name,usr_inp) == 0)
            {
                f_pos = ftell(user_ptr) - i;
                if (c == '\n')
                {
                    f_pos-=2;
                }
                flag = 1;
                break;
            }
            
        }
    }
    if (flag == 0)
    {
        printf("You don't have such a book!");
        fclose(user_ptr);
    }
    else
    {
        printf("Book found Successfully");
        fseek(user_ptr,0,SEEK_SET);
        FILE * temp_file = fopen("Temp.txt","w");
        while (feof(user_ptr) == 0)
        {
            c = fgetc(user_ptr);
            if (f_pos == ftell(user_ptr))
            {
                c = fgetc(user_ptr);
                while (c != ',' && c != '\n' && c != EOF)
                {
                    c = fgetc(user_ptr);
                }
                if (c != ',' && c !=EOF)
                {    
                    fputc(c,temp_file);
                    continue;
                }
                else
                {
                    continue;
                }

                
            }
            if (c != EOF)
                fputc(c,temp_file);
        }
        fclose(user_ptr);
        fclose(temp_file);
        remove("Users.txt");
        rename("Temp.txt","Users.txt");
        //Change_qty(book_name,1);
    }
}

int last_user_Line()
{
    char str[2000];
    int user_pos = 0;
    FILE * fptr = fopen("Users.txt","r");
    fgets(str,2000,fptr);
    while(feof(fptr) == 0)
    {
        fgets(str,2000,fptr);
        user_pos++;
    } 
    fclose(fptr);
    return user_pos;
}

void Delete_User(int user_pos)
{
    FILE * fptr = fopen("Users.txt","r"),*fptr2 = fopen("Temp.txt","w");
    char str1[2000];
    int run = 0;
    while (feof(fptr) == 0)
    {
        fgets(str1,2000,fptr);
        rem_newline(str1);
        if (user_pos == 0)
        {
            user_pos--;
            continue;
        }
        if (run == 0)
            fprintf(fptr2,"%s",str1);
        else
            fprintf(fptr2,"\n%s",str1);
        user_pos--;
        run++;
    }
    fclose(fptr2);
    fclose(fptr);
    remove("Users.txt");
    rename("Temp.txt","Users.txt");
}

int Issued_Book(int user_pos)
{
    int count = 0,char_int;
    FILE * fptr2 = fopen("Users.txt","r");
    char str[1000],c;
    while (user_pos)
    {
        fgets(str,1000,fptr2);
        user_pos--;
    }
    c = fgetc(fptr2);
    while (count < 3 && c!= EOF)
    {
        if (c =='/')
            count++;
        c = fgetc(fptr2);
    }
    char_int = (int) c;
    fclose(fptr2);
    if ((char_int >= 65 && char_int <= 90) || (char_int >= 97 && char_int <= 122))
        return 1;
    else
        return 0;
}
void Menu(int new_user,int user_pos)
{
    fflush(stdin);
    printf("Do you want to go back to menu? 0 or 1\n");
    switch (getchar())
    {
        case '0':
        {
            exit_func();
            break;
        }
        case '1':
        {
            Options(new_user,user_pos);
            break;
        }
        default :
        {
            printf("Invalid Choice\n");
            exit_func();
        }
        fflush(stdin);
    }
}



int Options(int new_user,int user_pos)
{
    char c;
    if (new_user == 0)
    {    
        printf("\nChoose from the options below:\n1.View Borrowed Books.\n2.Borrow Books.\n3.Return Books.\n4.Edit Account Details\n5.Delete Account\n6.Exit\n");
        switch (getchar())
        {
            
            case '1':
            {
                Read_User_Books(user_pos);
                Menu(new_user,user_pos);
                break;
            }
            case '2':
            {
                printf("1.Search for a particular book\n2.Show all available books\n");
                fflush(stdin);
                switch (getchar())
                {
                    case '1':
                    {
                        Book Req_Book;
                        Req_Book = Book_Search();
                        if (Req_Book.Book_Id == "NULL")
                        {
                            printf("No such Book found!\n");
                            exit_func();
                            Menu(new_user,user_pos);
                        }
                        else if (Req_Book.Quantity > 0)
                        {
                            printf("Found Book Successfully\n");
                            Borrow_Book(Req_Book,user_pos);
                            Change_Qty(Req_Book.Title,-1);
                            Menu(new_user,user_pos);
                        }
                        else
                        {
                            printf("The book is not available in sufficient quantity\n");
                            Menu(new_user,user_pos);
                        }
                        break;
                    }
                    case '2':
                    {
                        printf("The list of books are:");
                        printf("Book_Id |  Title  | Author    | Quantity ");
                    
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
                        Menu(new_user,user_pos);
                        break;
                    }
                    default:
                    {
                        printf("Invalid choice\n");
                        Menu(new_user,user_pos);
                        break;
                    }
                }
                break;
            }
            case '3':
            {
                Return_Book(user_pos);
                Menu(new_user,user_pos);
                break;
            }
            case '4':
            {

                break;
            }
            case '5':
            {
                Delete_User(user_pos);
                Menu(new_user,user_pos);
                break;
            }
            case '6':
            {
                exit_func();
                break;
            }
            default:
            {
                printf("Invalid Choice\n");
                exit_func();
                break;
            }

        }
    }
    else
    {
        printf("Choose from the options below\n1.Borrow Books\n2.Edit Account Details\n3.Delete Account\n");
        switch(getchar())
        {
            case '1':
            {
                printf("1.Search for a particular book\n2.Show all available books\n");
                fflush(stdin);
                switch (getchar())
                {
                    case '1':
                    {
                        Book Req_Book;
                        Req_Book = Book_Search();
                        if (Req_Book.Book_Id == "NULL")
                        {
                            printf("No such Book found!\n");
                            exit_func();
                            Menu(new_user,user_pos);
                        }
                        else if (Req_Book.Quantity > 0)
                        {
                            printf("Found Book Successfully\n");
                            Borrow_Book(Req_Book,user_pos);
                            Change_Qty(Req_Book.Title,-1);
                            Menu(0,last_user_Line());
                        }
                        else
                        {
                            printf("The book is not available in sufficient quantity\n");
                            Menu(new_user,user_pos);
                        }
                        break;
                    }
                }
                break;
            }
            case '2':
            {
                Menu(new_user,user_pos);
                break;
            }
            case '3':
            {
                Delete_User(last_user_Line());
                exit_func();
                break;
            }
            default:
            {
                printf("Invalid Input\n");
                exit_func();
                break;
            }
        }
    }
}

int Borrow_Book(Book Req_Book,int user_pos)
{
    FILE * fptr = fopen("Users.txt","r"),*fptr2 = fopen("Temp.txt","w");
    int i = 0,count = 0,flag = 0,f_pos,us_book = Issued_Book(user_pos);
    char c,d,book_name[100],line[1000];
    while (user_pos)
    {
        fgets(line,1000,fptr);
        user_pos--;
    }
    c = fgetc(fptr);
    while (c != '\n' && c != EOF)
    {
        if (c == '/')
        {
            count++;
        }

        c = fgetc(fptr);

        if (count == 3)
        {
            i = 0;
            while (c != '\n' && c != ',' && c != EOF)
            {
                book_name[i] = c;
                c = fgetc(fptr);
                i++;
            }
            book_name[i] = '\0';
            if (c == '\n' || c == EOF)
            {
                if (strcmp(book_name,Req_Book.Title) == 0)
                {
                    flag = 1;
                    break;
                }
            }
            else if (c == ',') 
            {
                if (strcmp(book_name,Req_Book.Title) == 0)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if (c == EOF)
            break;
    }
    f_pos = ftell(fptr);
    if (flag == 0)
    {
        fseek(fptr,0,SEEK_SET);
        c = fgetc(fptr);
        while (c != EOF)
        {
            if (ftell(fptr) == f_pos)
            {
                if (c == '\n' && us_book == 1)
                {
                    fprintf(fptr2,",%s\n",Req_Book.Title);

                }
                else if (c == '\n' && us_book == 0)
                {
                    fprintf(fptr2,"%s\n",Req_Book.Title);
                }
                c = fgetc(fptr);
                if (c == EOF)
                    break;
            }
            fputc(c,fptr2);
            c = fgetc(fptr);
        }
        if (ftell(fptr) == f_pos)
        {
            if (us_book == 0)
            {
                fprintf(fptr2,"/%s",Req_Book.Title);
            }
            else if (us_book == 1)
            {
                fprintf(fptr2,",%s",Req_Book.Title);
            }
        }
        printf("Book Issued Successfully!\n");
        fclose(fptr);
        fclose(fptr2);
        remove("Users.txt");
        rename("Temp.txt","Users.txt");
        Change_Qty(Req_Book.Title,-1);
    }
    else if (flag == 1)
    { 
        printf("You have already issued the same book\n");
    }
    fclose(fptr);
    return 0;
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
    int count = 0,null = 0;
    while (n)
    {
        fgets(str,1500,user_data);
        n--;
    }
    c = fgetc(user_data);
    while (c != EOF && c != '\n')
    {
        if (count > 2)
        {
            printf("%c",c);
        }
        if (c == '/')
        {
            count++;
        }
        if (c != '\n' && c != ' ')
        {
            null = 1;
        }
        c = fgetc(user_data);
    }
    if (null == 0)
    {
        printf("This user has issued no books.");
    }
    printf("\n");
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

Book Book_Search()
{
    fflush(stdin);
    Book Searched_Book;
    int i = 0,count = 0,Qty = 0,check = 0;
    FILE * book_ptr = fopen("Books.txt","r");
    char c,book_id[120],book_name[120],book_author[120],user_input[120],rest_str[1200];
    printf("Please enter either Book Id or Book Name");
    fgets(user_input,120,stdin);
    rem_newline(user_input);
    while (feof(book_ptr) == 0)
    {
        c = fgetc(book_ptr);
        if (c == '/')
        {
            count++;
        }
        if (count == 0)
        {
            book_id[i] = c;
            i++;
        }
        else if (count == 1)
        {
            if (c == '/')
            {
                book_id[i] = '\0';
                i = 0;
                c = fgetc(book_ptr);
            }
            book_name[i] = c;
            i++;
        }
        else
        {
            count = 0;
            book_name[i] = '\0';
            i = 0;
            fgets(rest_str,1200,book_ptr);
            if (strcmp(book_id,user_input) == 0 || strcmp(book_name,user_input) == 0)
            {
                check = 1;
                for (int j = 0;;j++)
                {
                    if (rest_str[j] == '/')
                    {
                        book_author[j] = '\0';
                        j++;
                        while ((int)(rest_str[j]) - 48 >= 0 && (int)(rest_str[j]) - 48 <= 9 && rest_str[j] != EOF && rest_str[j] != '\n' && rest_str[j] != '\0')
                        {
                            Qty = Qty * 10 + ((int)(rest_str[j]) - 48);
                            j++;
                        }
                        break; 
                    }
                    book_author[j] = rest_str[j];
                }
                break; 
            }
        }
    }
    if (check == 1)
    {
        strcpy(Searched_Book.Book_Id,book_id);
        strcpy(Searched_Book.Title,book_name);
        strcpy(Searched_Book.Author,book_author);
        Searched_Book.Quantity =Qty;
        return Searched_Book;
    }
    else
    {
        Searched_Book = (Book) {"NULL","NULL","NULL",0};
        return Searched_Book;
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

int main()
{
    int new_user = 0,user_pos = -1; //Checking if a new user is present or not
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
            printf("\nPlease enter 1 or 2\a\n");
            exit_func();
            break;
        }
    }
    Options(new_user,user_pos);
}
