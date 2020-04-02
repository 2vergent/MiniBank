#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>


void changedir(void)
{
    uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
    char *filepath = pw->pw_dir;
    char *bank = "Bank";
    chdir(filepath);
    mkdir("Bank", 0777);
    chdir(bank);
}


int arrcompare(char arr1[], char arr2[])
{
    if(strlen(arr1) != strlen(arr2))
    {
        return 0;
    }
    int i;
    for(i=0; i<strlen(arr2); i++)
    {
        if(arr1[i] != arr2[i])
        {
            return 0;
        }
    }
    return 1;
}


void loggedin(char user[], char pass[], char ifsc[])
{
    printf("Finally, you're logged in.\n");
    printf("Username: %s\n", user);
    printf("Password: %s\n", pass);
    printf("ifsc: %s\n", ifsc);

}


void actuallogin(char user[], char pass[], char ifsc[])
{
    int checklog = 0;;
    char c;
    int count;
    changedir();
    FILE* reading;
    reading = fopen("userdata.txt", "r");
    for (c = getc(reading); c != EOF; c = getc(reading))
    {
        if (c == '\n')
        {
            count = count + 1;
        }
    }
    char userin[16], passin[16], ifscin[12];
    fclose(reading);
    int bufferLength = 255;
    char buffer[bufferLength];
    reading = fopen("userdata.txt", "r");
    while(fgets(buffer, bufferLength, reading)) 
    {
        int count;
        int i;
        for(i=0; i<strlen(buffer); i++)
        {
            if(buffer[i] != '|')
            {
                userin[i] = buffer[i];
                count = i;
            }
            else
            {
                break;
            }
        }
        if(arrcompare(userin, user))
        {
            int j, k = 0;
            for(j=count + 2; j<strlen(buffer); j++)
            {
                if(buffer[j] != '|')
                {
                    passin[k] = buffer[j];
                    count = j;
                    k++;
                }
                else
                {
                    break;
                }
            }
            if(arrcompare(pass, passin))
            {
                int i; int j = 0;
                for(i=count + 2; i<strlen(buffer); i++)
                {
                    if(buffer[i] != '|')
                    {
                        ifscin[j] = buffer[i];
                        j++;
                    }
                    else
                    {
                        break;
                    }
                }
                ifscin[12] = '\0';
                if(arrcompare(ifsc, ifscin))
                {
                    checklog = 1;
                }
                else
                {
                    printf("Invalid IFSC Code.\n");
                    return;
                }
            }
            else
            {
                printf("Invalid password.\n");
                return;
            }
        }
        else
        {
            memset(userin, 0, sizeof(userin));
            continue;
        }
    }
    if(checklog)
    {
        loggedin(user, pass, ifsc);
    }
    else
    {
        return;
    }
    fclose(reading);
}


void login(void)
{
    char username[16], password[16], ifsc[12];
    int check = 0;
    while(!check)
    {
        printf("Enter Username: ");
        scanf("%s[^\n]", username);
        int i;
        if(strlen(username) > 15)
        {
            printf("Username should not be more than 15 characters long.\n");
        }
        else
        {
            check = 1;
        }
    }
    char user[strlen(username)];
    int i;
    for(i=0; i<strlen(username); i++)
    {
        user[i] = username[i];
    }
    check = 0;
    while (!check)
    {
        printf("Enter Password: ");
        scanf("%s[^\n]", password);
        if(strlen(password) <= 15)
        {
            check = 1;
        }
        else
        {
            printf("Password should not be more than 15 characters long.\n");
        }
    }
    char pass[strlen(password)];
    for(i=0; i<strlen(password); i++)
    {
        pass[i] = password[i];
    }
    check = 0;
    while(!check)
    {
        printf("Enter IFSC Code: ");
        scanf("%s[^\n]", ifsc);
        int i;
        if(strlen(ifsc) != 11)
        {
            printf("IFSC Code is a 11 character long alpha-numeric code.\n");
            continue;
        }
        else
        {
            check = 1;
        }
    }
    char ifs[strlen(ifsc)];
    for(i=0; i<strlen(ifsc); i++)
    {
        ifs[i] = ifsc[i];
    }
    actuallogin(username, password, ifsc);
}


void actualsignup(char user[], char pass[], char ifsc[])
{
    changedir();
    FILE *udata;
    udata = fopen("userdata.txt", "a+");
    fprintf(udata, "%s|%s|%s|\n", user, pass, ifsc);
    fclose(udata);
    char details[10], txt[] = ".txt";
    int i, j = 10;
    for(i=0; i<6; i++)
    {
        details[i] = ifsc[j];
        j--;
    }
    j = 0;
    for(i=6; i<10; i++)
    {
        details[i] = txt[j];
        j++;
    }
    FILE *create;
    create = fopen(details, "w");
    fclose(create);
}


void signup(void)
{
    FILE *udata;
    char username[15], password[15], ifsc[11];
    int check = 0;
    while(!check)
    {
        printf("Enter Username: ");
        scanf("%s[^\n]", username);
        int i, usercheck = 0;
        for(i=0; i<strlen(username); i++)
        {
            if(username[i] == ' ')
            {
                usercheck = 1;
                break;
            }
        }
        if(usercheck || (strlen(username) > 15))
        {
            printf("Username should not contain spaces and should not be more than 15 characters long.\n");
        }
        else
        {
            check = 1;
        }
    }
    char user[strlen(username)];
    int i;
    for(i=0; i<strlen(username); i++)
    {
        user[i] = username[i];
    }
    user[strlen(username)] = '\0';
    check = 0;
    while (!check)
    {
        printf("Enter Password: ");
        scanf("%s[^\n]", password);
        if(strlen(password) <= 15)
        {
            check = 1;
        }
        else
        {
            printf("Password should not be more than 15 characters long.\n");
        }
    }
    check = 0;
    while(!check)
    {
        printf("Enter IFSC Code: ");
        scanf("%s[^\n]", ifsc);
        int i, passcheck = 0;
        if(strlen(ifsc) != 11)
        {
            printf("IFSC Code is a 11 character long alpha-numeric code.\n");
            continue;
        }
        for(i=0; i<11; i++)
        {
            if(isalnum(ifsc[i]) == 0)
            {
                passcheck = 1;
            }
        }
        if(passcheck || (strlen(ifsc) != 11))
        {
            printf("IFSC Code must not contain special characters.\n");
        }
        else
        {
            check = 1;
        }
    }
    actualsignup(user, password, ifsc);
}


int main(void)
{
    printf("WELCOME TO MINIBANK\n");
    printf("1- LOGIN OR 2 - SIGNUP : ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        login();
    }
    else if(choice == 2)
    {
        signup();
    }
    else
    {
        printf("Invalid choice\n");
    }
    return 0;
}
