#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>


void actualsignup(char user[], char pass[], char ifsc[])
{
    uid_t uid = getuid();
	struct passwd *pw = getpwuid(uid);
    char *filepath = pw->pw_dir;
    char *bank = "Bank";
    chdir(filepath);
    mkdir("Bank", 0777);
    chdir(bank);
    FILE *udata;
    udata = fopen("userdata.txt", "a+");
    fprintf(udata, "%s %s %s \n", user, pass, ifsc);
    fclose(udata);
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
    signup();
    return 0;
}
