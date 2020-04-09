#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>


void encrypt_(char user[],char pass[],char ifsc[])
{
	int a, b, c, i;
	for(a=0;user[a]!='\0';a++);

	b=(int)user[0]-(int)user[a];

	if(b > 0)
	{
		for(c=0;user[c]!='\0';c++)
		{
			user[i] = (int)user[i] + b;
		}
		for(c=0;pass[c]!='\0';c++)
		{
			pass[i] = (int)pass[i] + b;
		}
		for(c=0;ifsc[c]!='\0';c++)
		{
			ifsc[i] = (int)ifsc[i] + b;
		}
	}
	else
	{
		for(c=0;user[c]!='\0';c++)
		{
			user[i] = (int)user[i] + c +1;
		}
		for(c=0;pass[c]!='\0';c++)
		{
			pass[i] = (int)pass[i] + c +1;
		}
		for(c=0;ifsc[c]!='\0';c++)
		{
			ifsc[i] = (int)ifsc[i] + c +1;
		}	
	}		
}


void decrypt_(char user[],char something[])
{
	int a,b,c;
	for(a=0;user[a]!='\0';a++);
	b=(int)user[0]-(int)user[a];
	if(b > 0)
	{
		for(c=0;something[c]!='\0';c++)
		{
		something[c] = (int)something[c] - b;	
		}	
	}
	else
	{
		for(c=0;something[c]!='\0';c++)
		{
		something[c] = (int)something[c] - c -1;
		}	
	}
}


void decorate(char c, int space)
{
    int i;
    for(i=0; i<space; i++)
    {
        printf(" ");
    }
    for(i=0; i<67; i++)
    {
        printf("%c", c);
    }
    printf("\n");
}


void encrypt(char something[])
{
	int shift = 3;	
	int b;
	for(b=0;something[b]!='\0';b++)
	{
		something[b]=(int)something[b] + shift;
	}
}


void decrypt(char something[])
{
	int shift = 3;	
	int b;
	for(b=0;something[b]!='\0';b++)
	{
		something[b]=(int)something[b] - shift;
	}
}


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


void get_upi_pass(char user[])
{
    decorate('-', 0);
    static char getupi[15];
    char userfile[strlen(user) + 4], txt[] = ".txt";
    int i;
    for(i=0; i<strlen(user); i++)
    {
        userfile[i] = user[i];
    }
    int j = 0;
    for(i=strlen(user); i<(strlen(user) + 4); i++)
    {
        userfile[i] = txt[j];
        j++;
    }
    userfile[strlen(user) + 4] = '\0';
    FILE *fp;
    fp = fopen(userfile, "r");
    int bufferLength = 255;
    char buffer[bufferLength];
    i = 0;
    int k = 0;
    while(fgets(buffer, bufferLength, fp)) 
    {
        if (i == 4)
        {
            int j;
            for(j=14; j<strlen(buffer) - 1; j++)
            {
                getupi[k] = buffer[j];
                k++;
            }
        }
        i++;
    }
    printf("Current UPI Password: %s\n", getupi);
}


void change_upi_pass(char user[])
{
    printf("Enter new UPI Password: ");
    char newupipasswd[15];
    scanf("%s", newupipasswd);
    char userfile[strlen(user) + 4], txt[] = ".txt";
    int i;
    for(i=0; i<strlen(user); i++)
    {
        userfile[i] = user[i];
    }
    int j = 0;
    for(i=strlen(user); i<(strlen(user) + 4); i++)
    {
        userfile[i] = txt[j];
        j++;
    }
    userfile[strlen(user) + 4] = '\0';
    FILE *change;
    FILE *tempfile;
    change = fopen(userfile, "r");
    tempfile = fopen("replace.tmp", "w");
    int bufferLength = 255;
    char buffer[bufferLength];
    i = 0;
    while(fgets(buffer, bufferLength, change)) 
    {
        if (i == 4)
        {
            fprintf(tempfile, "UPI Password: %s\n", newupipasswd);
        }
        else
        {
            fputs(buffer, tempfile);
        }
        i++;
    }
    fclose(change);
    fclose(tempfile);
    remove(userfile);
    rename("replace.tmp", userfile);
}


long int getbalance(char user[])
{
    char userfile[strlen(user) + 4], txt[] = ".txt";
    int i;
    for(i=0; i<strlen(user); i++)
    {
        userfile[i] = user[i];
    }
    int j = 0;
    for(i=strlen(user); i<(strlen(user) + 4); i++)
    {
        userfile[i] = txt[j];
        j++;
    }
    userfile[strlen(user) + 4] = '\0';
    FILE *fp;
    fp = fopen(userfile, "r");
    int bufferLength = 255;
    char gotbalance[255];
    char buffer[bufferLength];
    i = 0;
    int k = 0;
    while(fgets(buffer, bufferLength, fp)) 
    {
        if (i == 2)
        {
            int j;
            for(j=14; j<strlen(buffer) - 1; j++)
            {
                gotbalance[k] = buffer[j];
                k++;
            }
        }
        i++;
    }
    gotbalance[k+1] = '\0';
    long int balance = atoi(gotbalance);
    return balance;
}


void changebalance(char user[], char choice[])
{
    decorate('-', 0);
    long int current, amount, remaining;
    current = getbalance(user);
    char c1[] = "withdraw";
    char c2[] = "deposit";
    if(arrcompare(choice, c1))
    {
        printf("Enter Amount to be withdrawn (Balance: %ld): ", current);
        scanf("%ld", &amount);
        decorate('-', 0);
        if(amount > current)
        {
            printf("Cannot withdraw amount larger than current balance.");
            decorate('-', 0);
            return;
        }
        remaining = current - amount;
    }
    else
    {
        printf("Enter Ammount to be deposited (Balance: %ld): ", current);
        scanf("%ld", &amount);
        decorate('-', 0);
        remaining = current + amount;
    }
    
    char userfile[strlen(user) + 4], txt[] = ".txt";
    int i;
    for(i=0; i<strlen(user); i++)
    {
        userfile[i] = user[i];
    }
    int j = 0;
    for(i=strlen(user); i<(strlen(user) + 4); i++)
    {
        userfile[i] = txt[j];
        j++;
    }
    userfile[strlen(user) + 4] = '\0';
    FILE *change;
    FILE *tempfile;
    change = fopen(userfile, "r");
    tempfile = fopen("replace.tmp", "w");
    int bufferLength = 255;
    char buffer[bufferLength];
    i = 0;
    while(fgets(buffer, bufferLength, change)) 
    {
        if (i == 2)
        {
            fprintf(tempfile, "Bank Balance: %ld\n", remaining);
        }
        else
        {
            fputs(buffer, tempfile);
        }
        i++;
    }
    fclose(change);
    fclose(tempfile);
    remove(userfile);
    rename("replace.tmp", userfile);
}


void showbalance(char user[])
{
    decorate('-', 0);
    char userfile[strlen(user) + 4], txt[] = ".txt";
    int i;
    for(i=0; i<strlen(user); i++)
    {
        userfile[i] = user[i];
    }
    int j = 0;
    for(i=strlen(user); i<(strlen(user) + 4); i++)
    {
        userfile[i] = txt[j];
        j++;
    }
    userfile[strlen(user) + 4] = '\0';
    FILE *balancecheck;
    balancecheck = fopen(userfile, "r");
    int bufferLength = 255;
    char buffer[bufferLength];
    i = 0;
    while(fgets(buffer, bufferLength, balancecheck)) 
    {
        if(i == 2)
        {
            printf("%s", buffer);
        }
        i++;
    }
}


void details(char user[], char pass[], char ifsc[])
{
    decorate('-', 0);
    char fullname[15], upihandler[15], upipassword[5], accno[11];
    long int balance;
    int size;
    char userfile[strlen(user) + 4], txt[] = ".txt";
    int i;
    for(i=0; i<strlen(user); i++)
    {
        userfile[i] = user[i];
    }
    int j = 0;
    for(i=strlen(user); i<(strlen(user) + 4); i++)
    {
        userfile[i] = txt[j];
        j++;
    }
    userfile[strlen(user) + 4] = '\0';
    FILE *fp;
    fp = fopen(userfile, "r");
    if (NULL != fp)
    {
        fseek (fp, 0, SEEK_END);
        size = ftell(fp);
        if (size == 0) 
        {
            printf("> Proceed to enter your full details: \n");
            decorate('-', 0);
            printf("Enter Full Name: ");
            scanf("%s", fullname);
            printf("Enter Bank Account Number: ");
            scanf("%s", accno);
            printf("Enter Bank Balance: ");
            scanf("%ld", &balance);
            printf("Enter UPI Handler: ");
            scanf("%s", upihandler);
            printf("Enter UPI Password: ");
            scanf("%s", upipassword);
            FILE *writedetails;
            writedetails = fopen(userfile, "w");
            fprintf(writedetails, "Full Name: %s\n", fullname);
            fprintf(writedetails, "Bank Account Number: %s\n", accno);
            fprintf(writedetails, "Bank Balance: %ld\n", balance);
            fprintf(writedetails, "UPI Handler: %s\n", upihandler);
            fprintf(writedetails, "UPI Password: %s\n", upipassword);
            fclose(writedetails);
        }
        else
        {
            printf("> ACCOUNT DETAILS : \n");
            decorate('-', 0);
            FILE *printdetails;
            printdetails = fopen(userfile, "r");
            int bufferLength = 255;
            char buffer[bufferLength];
            while(fgets(buffer, bufferLength, printdetails)) 
            {
                printf("%s", buffer);
            }
        }
        
    }
}


void loggedin(char user[], char pass[], char ifsc[])
{
    decorate('-', 0);
    printf("LOG IN SUCCESSFUL\n");
    decorate('-', 0);
    char c0[] = "help";
    char c1[] = "details";
    char c2[] = "balance";
    char c3[] = "withdraw";
    char c4[] = "deposit";
    char c5[] = "upipasswd";
    char c6[] = "exit";
    char c7[] = "clear";
    char choice[10];
    int check = 1;
    while(check)
    {
        printf(" > ");
        scanf("%s", choice);
        if(arrcompare(choice, c0))
        {
            decorate('-', 0);
            printf("To get started, type any of these commands: \n");
            decorate('-', 0);
            printf("\t1. details: Display details about your account.\n\t2. balance: Check your current balance.\n\t3. withdraw: Withdraw cash from your account.\n\t4. deposit: Deposit cash to your account.\n\t5. upipasswd: Change UPI Password.\n\t6. clear: Clears the screen.\n\t7. exit: Exits MiniBank.\n");
            decorate('-', 0);
        }
        else if(arrcompare(choice, c1))
        {
            details(user, pass, ifsc);
            decorate('-', 0);
        }
        else if(arrcompare(choice, c2))
        {
            showbalance(user);
            decorate('-', 0);
        }
        else if(arrcompare(choice, c3) || arrcompare(choice, c4))
        {
            changebalance(user, choice);
        }
        else if(arrcompare(choice, c5))
        {
            get_upi_pass(user);
            change_upi_pass(user);
            decorate('-', 0);
        }
        else if(arrcompare(choice, c6))
        {
            decorate('-', 0);
            exit(0);
        }
        else if(arrcompare(choice, c7))
        {
            printf("\033[2J\033[1;1H");
        }
        else
        {
            decorate('-', 0);
            printf("Invalid command. Type \'help\' for more info\n");
            decorate('-', 0);
        }
        
    }

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
            if(buffer[i] != '.')
            {
                userin[i] = buffer[i];
                count = i;
            }
            else
            {
                break;
            }
        }
        decrypt(userin);
        if(arrcompare(userin, user))
        {
            int j, k = 0;
            for(j=count + 2; j<strlen(buffer); j++)
            {
                if(buffer[j] != '.')
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
            decrypt(passin);
            if(arrcompare(pass, passin))
            {
                int i; int j = 0;
                for(i=count + 2; i<strlen(buffer); i++)
                {
                    if(buffer[i] != '.')
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
                decrypt(ifscin);
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
    char euser[strlen(user)];
    strcpy(euser, user);
    char epass[strlen(pass)];
    strcpy(epass, pass);
    char eifsc[strlen(ifsc)];
    strcpy(eifsc, ifsc);
    encrypt(euser);
    encrypt(epass);
    encrypt(eifsc);
    FILE *udata;
    udata = fopen("userdata.txt", "a+");
    fprintf(udata, "%s.%s.%s.\n", euser, epass, eifsc);
    fclose(udata);
    char details[strlen(user) + 4], txt[] = ".txt";
    int i;
    for(i=0; i<strlen(user); i++)
    {
        details[i] = user[i];
    }
    int j = 0;
    for(i=strlen(user); i<(strlen(user) + 4); i++)
    {
        details[i] = txt[j];
        j++;
    }
    details[strlen(user) + 4] = '\0';
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
    decorate('-', 0);
    printf("                      WELCOME TO MINIBANK         \n");
    decorate('-', 0);
    printf("To continue into Minibank, press:\n\t1. Login\n\t2. Signup\n");
    decorate('-', 0);
    int choice;
    scanf("%d", &choice);
    decorate('-', 0);
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
