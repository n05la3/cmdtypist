/* 
   cmd_typist: an extreme fast terminal typing tutor/meter designed to work 
   on terminals like gnome-terminal, xterm, uxterm and others
   <cmd_typist> Copyright (C) <*****>  by Prince Noslac

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include<math.h>
#include<stdio.h>	
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
char time_set=0;
int argc=1;
char file_to_read[19];//name of lesson file to read from
unsigned short int block_length;
//#include<math.h>
#define SIZE_NAME 81//variable to hold the name of the user.
void lesson_position(void);
void select_lesson(void);//selects lesson and passes to main_play() function.
void make_current(FILE *file_to_remove_from);
char mode=8;//mode of play, could be random or standard, setting it defined amount to prevent it from being initialised to 0
FILE *noslac_lessonp;
char ch;//used for character input and testing.
#define RED "\x1B[31m"//bash script for red color
#define GREEN "\x1B[32m"//bash script for Green color
#define SPEED_COLOR "\x1B[36m"//printing speed color
#define TIP_COLOR "\x1B[35m"//bash script for Green color
#define LAST_LINE "\x1B[34m"//bash script for Green color
#define RESET "\x1B[0m"//color reset to normal (black)
#include<termios.h>//a linux header file for echo
#if defined(_WIN32)//checking if the system on which the program is running is windows
#include<Windows.h>//and including the windows header file.
#elif defined(__linux__)//if machine is linux
#include<unistd.h>//include the linux header file
#endif
char firstarg[8];//global variable to hold the "select argument"
int lesson_choice=0;//global variable to hold the number corresponding to the chosen lesson.
unsigned short u=0;//global counter.
long length_to_read;//holds information on how long the text to be read is.

/*implementing a function to display the 
name of the program.*/
char new_name[81];
extern void name_display(void)
{
	printf("\t\t%s  %s  %s   %s","+*******", "+**********+", "+****",       "\t+**********+\n");
    printf("\t\t%s  %s  %s %s","|*******", "|**********|", "|***+*",        " \t|**********|\n");
    printf("\t\t%s  %s  %s %s","**", "      **   **   **",  "**   **",      "\t     **\n");
    printf("\t\t%s  %s  %s %s","**", "      **   **   **",  "**    **",     "\t     **\n");
    printf("\t\t%s  %s  %s %s","**", "      **   **   **",  "**    **",     "\t     **\n");
    printf("\t\t%s  %s  %s %s","**", "      **   **   **",  "**    **",     "\t     **\n");
    printf("\t\t%s  %s  %s%s","|*******", "|*   **   *|", "|*******",       "\t     **\n");
    printf("\t\t%s  %s  %s%s","+*******", "+*        *+", "+******",        "\t             ++\n");
    printf("%s\n", "                    CMD_TYPIST: enjoy the speed!!!");
}

/*This function opens a binary file on which zero was initally written, it then checks if the zero is still there, 
if yes then it is the first time the program is being opened  and then replaces the zero with 1*/
extern void message_conf(void)//Function for first time message display
{
    FILE *fconf;
    char num_test=8;//value different from 0 or 1
    if((fconf=fopen("firsttimemessage.dat", "rb+"))==NULL)//opening the file storing information on first time display.
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(1);
    }   
    rewind(fconf);//move to beginnning of the file
    fread(&num_test,sizeof(char),1,fconf);  
    if(num_test==0)//checking to see if its 0 that is found in the file.
    {
        printf("%s\n", "WELCOME!!!, It appears you're opening this program for the first time\n");
        rewind(fconf);
        num_test=1;
        fwrite(&num_test,sizeof(char),1,fconf);
    }
    if(fclose(fconf)!=0)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(2);
    }
}

//0=message config, 1=mode config, 2=block confi , 3=sound config, 4: user text config
extern char read_myown_config(void)//num_value is used to record settings for random and standard play
{
    char num_value;
    FILE *fconf;//file pointer to configuration file
    if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }
    fseek(fconf,4L,SEEK_SET);
    fread(&num_value,sizeof(char),1,fconf);
    if(fclose(fconf))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }
    return num_value;
}

extern void write_myown_config(char n)//r is used to record settings for random and standard play
{
    FILE *fconf;
    if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }
    fseek(fconf,4L,SEEK_SET);
    fwrite(&n,sizeof(char),1,fconf);
    if(fclose(fconf))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }
}


extern void fget_ignore_newline(char *arr_no_newline)
{
    int i=0;
    while(arr_no_newline[i]!='\0')
    {
        if(arr_no_newline[i]=='\n')
        {
            arr_no_newline[i]='\0';
            break;
        }
        i++;
    }
}

/*works with fgets to make it work like scanf if, ending string storage after a space character.*/
extern void fgets_one_name(char *arr_no_newline)
{
    int i=0;
    while(arr_no_newline[i]!='\0')
    {
        if(arr_no_newline[i]==' ')
        {
            arr_no_newline[i]='\0';
            break;
        }
        i++;
    }
}

void get_only_char(char *n)
{
    char ch='&';//for flushing
    printf("%s", "");
    scanf("%c", n);
    char f;
    f=getchar();//f will get \n when n is gotten
    while((*n!='n'&&*n!='y')||f!='\n')//making sure only n and y or \n (in f) are entered
    {
        if(f=='\n')//special case when n is found
        {
            printf("Invalid [y/n]:");
            //while((ch=getchar())!='\n');//flushing the buffer
            scanf("%c", n);
            f=getchar();
        }
        else
        {
            printf("Invalid [y/n]:");
            while((ch=getchar())!='\n');//flushing the buffer
            scanf("%c", n);
            f=getchar();
        }

    }

}

     /*prevent echoing of characters from the buffer*/
extern int getche(void)
        {
            struct termios oldattr, newattr;
            int ch;
            tcgetattr( STDIN_FILENO, &oldattr );
            newattr = oldattr;
            newattr.c_lflag &= ~( ICANON | ECHO);//shell out to kill echo
            tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
            system("stty echo");//shell out to kill echo
            ch = getchar();
            system("stty echo");
            tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
            return ch;
        }

void edit_name(void)
{	
	FILE *fp;
	if((fp=fopen("user.info","r+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}	
	fseek(fp,select_user(),SEEK_SET);
	write_to_line(new_name,fp);//writes user name to the line which has been selected by select_user() function
	if(fclose(fp))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
	}
	
}

void remove_ext_ascii(void)
{
	srand((unsigned)time(NULL));
	FILE *fp;
	if((fp=fopen(file_to_read,"r+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	rewind(fp);
	char ch,f;
	while((ch=getc(fp))!=EOF)
	{
		if(ch!='\n')
			if(!(isascii(ch)))
			{
				ch=rand()%15+33;
				//fprintf(stderr, "%c", ch);
				//f=getchar();
				fseek(fp,-1L,SEEK_CUR);
				putc(ch,fp);
			}
	}
	if(fclose(fp))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
	}
}

/*used to remove all non standard ascii codes from user text*/

float my_pow(float base, int exp)//mickmicking the pow function
{
    float temp;
    if( exp == 0)
       return 1;
    temp = my_pow(base, exp/2);       
    if (exp%2 == 0)
        return temp*temp;
    else
    {
        if(exp > 0)
            return base*temp*temp;
        else
            return (temp*temp)/base;
    }
}

//micking atoi function (returns integer from string) 
int my_atoi(const char* snum)
{
    int idx, str_idx = 0, accum = 0, num_is_neg = 0;
    const unsigned int NUMLEN = (int)strlen(snum);

    /* Check if negative number and flag it. */
    if(snum[0] == 0x2d)
        num_is_neg = 1;
    for(idx = NUMLEN - 1; idx >= 0; idx--)
    {
        /* Only process numbers from 0 through 9. */
        if(snum[str_idx] >= 0x30 && snum[str_idx] <= 0x39)
            accum += (snum[str_idx] - 0x30) * my_pow(10, idx);
        str_idx++;
    }

    /* Check flag to see if originally passed -ve number and convert result if so. */
    if(!num_is_neg)
        return accum;
    else
        return accum * -1;
}

void swap_modify_name(int length_of_string)//swaps new name with former name and catenates the former name with new name details
{
    int i=0;
    //301, is just an exiting value 
    while(i<=301)
    {
        int j=0;
        if(user_info[i]=='.')
        {
            while(j<=301)
            {
                //strcat(new_name,user_info[j+1]);
                new_name[length_of_string+j]=user_info[j+i];
                if(j==strlen(user_info)-i)
                {
                    j=300;//value to help for an exit since the length of the sring is never more than 81
                    i=300;
                }
                j++;
            }
        }
        i++;
    }
    new_name[strlen(new_name)]='\n';    
    new_name[strlen(new_name)]='\0';    
}


char *upper_case(char *name)
{
	unsigned short int i=0;
	while(i<strlen(name))
	{
		name[i]=toupper(name[i]);
		i++;
	}
	name[i]='\0';
	return name;
}

char *cat_name(char *name)//catenating \n to a pointer to .
{
	char trick_name[SIZE_NAME];//trick string for name catenating.	
	strcpy(trick_name,name);
	strcat(trick_name,"\n");
	strcpy(name,trick_name);
	return name;
}

void valid_range(int num_to_convert)//Ensures correct range is entered
{
	while(num_to_convert!=1||num_to_convert!=0)
	{
		printf("\n%s", "Continue?: 1:Yes 0:No");
		scanf("%d",&num_to_convert);
		//get_int(&num_to_convert);
	}
}

void cpy_2d_string( char *destination[],const char *source[],int argc)//source=argv from command line
{
	int i;//counter for the number of elements in the strings
	for(i=1;i<=argc;i++)
		strcpy(destination[i],source[i]);
}

void write_to_line(char* to_write, FILE* fp)
{
	int i=0;
	char ch;

	//while((ch=fgetc(fp))!='\n')//Ensuring the end of file is not reached
	//{

		if((strlen(new_name))>=strlen(user_info))//starts printing in the first position of the line		
			fprintf(fp, "%s", to_write);//write name
		else
		{
			fprintf(fp, "%s", to_write);
			while((ch=getc(fp))!='\n')
			{
				fseek(fp,-1L,SEEK_CUR);
				fprintf(fp, "%c", ' ');
			}
			if((ch=getc(fp))!='\n'&&ch!=' ')
			fseek(fp,-1L,SEEK_CUR);//moving backward one space since getc above had moved one space ahead
									//so as to write over the data existing.
			//fprintf(fp, "%s", " ");
			if(ch=='\n')
			{
				fseek(fp,-1L,SEEK_CUR);
				fprintf(fp, "%c", '\n');//writing newline at the end of file since it had been replaced with a space string
				break;//escaping since the end of the line has been reached
			}			
		}
	//	i++;		
	//}
}

/*Sleep function for both linux and windows, passing the number of seconds as a parameter*/
extern void sleepf(int time_to_sleep)//implementing a sleep function 
	{
		#ifdef _WIN32
        Sleep(time_to_sleep);
        #else
        sleep(time_to_sleep);
        #endif 
	}
void make_current(FILE* file_to_remove_from)
{
    
    char ch;
    fseek(file_to_remove_from,-300L,SEEK_END);  
    while((ch=getc(file_to_remove_from))!=EOF)
    {
        if(ch=='-'||ch=='|'||ch=='+')
        {
            fseek(file_to_remove_from,-1L,SEEK_CUR);
            fputc(' ',file_to_remove_from);//over written current lesson with new one to become current
        }
    }
}

/*Ensures atleast one user account exist*/
extern void user_test(void)
    {
        FILE *fp;
        if((fp=fopen("./speed/user_speed.info","r"))==NULL)
        {
            fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
            exit(EXIT_FAILURE);
        }
        rewind(fp);
        char ch=getc(fp);
        if(ch==EOF)//checking if at the beginning of a character there is a charater, if not exist
        {
            fprintf(stderr, "%s\n", "No user exists yet, use <command mkuser \"username\"> to add new user");
            exit(EXIT_FAILURE);
        }
        if(fclose(fp))
        {
            fprintf(stderr, "%s\n", "Unable to close lesson file");
            exit(EXIT_FAILURE);
        }
    }


//modifies the manner in which sesson speed is displayed
//5 is the accepted average number of letters in a word 
void session_style(unsigned int session_time, unsigned short wrongly_typed,float typed)
{
    float raw_speed=0.0,adj_speed=0.0;
    raw_speed= ((float) typed*60.0f)/(float)session_time;
    adj_speed= (float) ((typed-wrongly_typed)*60.0)/(float)session_time;
    char time_conversion[36];//stores converted time by seconds_hms()
    printf(""RESET"\n%s\n", "For better speed follow up, consult \"user_speed.info\" file in speed directory");
    puts("-------------------------------+-----------+------------------------------------");
    puts("-------------------------------SESSION SPEED------------------------------------");//printing session heading
    puts("-------------------------------+-----------+------------------------------------");
    printf("**************                                                     *************\n");
    fprintf(stdout, "\t+------------------%s %s %s----------------------+\n", __DATE__,"at",__TIME__);//printing date and time when the test is done
    seconds_to_hms(session_time,time_conversion);
    //fprintf(fp, "\t|%d%s TIME: %s\n",wrongly_typed,(wrongly_typed==0)? "(NO Error)":(wrongly_typed==1)? "ERROR":"ERRORS",time_conversion);
    raw_speed= ((float) typed*60.0f)/(float)session_time;
    adj_speed= (float) ((typed-wrongly_typed)*60.0)/(float)session_time;        
    fprintf(stdout, "\t|ERROR(s):"RED"%d"RESET" TIME: "SPEED_COLOR"%s"RESET" Accuracy: "SPEED_COLOR"%.2f%%"RESET"\n",wrongly_typed,time_conversion,((float) typed-(float)wrongly_typed)/(float) typed*100.0f);
    fprintf(stdout, "\t|%s"SPEED_COLOR"%.2f"RESET"CPM ~= "GREEN"%.2f"RESET"WPM \n", "AVERAGE SPEED: ",adj_speed,adj_speed/5);
    fprintf(stdout, "%s\n\n", "\t+---------------------------------------------------------------+");
}

extern void write_conf_block_read(unsigned int n)//r is used to record settings for random and standard play
{
    FILE *fconf;
    if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }
    fseek(fconf,2L,SEEK_SET);
    fwrite(&n,sizeof(char),1,fconf);
    if(fclose(fconf))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }
}

extern void sound_config_write(unsigned int n)//r is used to record settings for random and standard play
{
    FILE *fconf;
    if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }
    fseek(fconf,3L,SEEK_SET);
    fwrite(&n,sizeof(char),1,fconf);
    if(fclose(fconf))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }
}

//helps to adapt to version by solving problem of erasing a character
//writes one or 
extern char adapt_to_ver(void)//num_value is used to record settings for random and standard play
{
    char num_value,n;
    FILE *fconf;
    if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }
    fseek(fconf,5L,SEEK_SET);
    fread(&num_value,sizeof(char),1,fconf);
    fseek(fconf,-1,SEEK_CUR);
    //num_value=2;//first time value writing, to be commented
    if(num_value==1)
    {
        num_value=2;
        fwrite(&num_value,sizeof(char),1,fconf);
    }
    else if(num_value==2)
    {
        num_value=1;
        fwrite(&num_value,sizeof(char),1,fconf);
    }
    if(fclose(fconf))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }
    return num_value;
}

extern char adapt_to_ver_read(void)//num_value is used to record settings for random and standard play
{
    char num_value;
    FILE *fconf;
    if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }
    fseek(fconf,5L,SEEK_SET);
    fread(&num_value,sizeof(char),1,fconf);
    if(fclose(fconf))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }
    return num_value;
}

int range_verifier(int n)
{
    if(n<0||n>15)
    {
        fprintf(stderr, "%s\n", "Lesson number does not exist");
        exit(EXIT_FAILURE);
    }
    return n;
}

//writing message configuration to config file
extern void write_message_conf(char n)//r is used to record settings for random and standard play
{
    if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }
    rewind(fconf);
    fwrite(&n,sizeof(char),1,fconf);
    if(fclose(fconf))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }
}

/*This function opens a binary file on which zero was initally written, it then checks if the zero is still there, 
if yes then it is the first time the program is being opened  and then replaces the zero with 1*/
extern void read_message_conf(void)//Function for first time message display
{
    FILE *fconf;
    char num_test=8;//value different from 0 or 1
    if((fconf=fopen("cmdtypist.conf", "rb+"))==NULL)//opening the file storing information on first time display.
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(1);
    }   
    rewind(fconf);//move to beginnning of the file
    fread(&num_test,sizeof(char),1,fconf);  
    if(num_test==0)//checking to see if its 0 that is found in the file.
    {
        system("clear");
        printf("%s\n", "      ============================WELCOME!!!============================      \n");
        rewind(fconf);
        num_test=1;
        fwrite(&num_test,sizeof(char),1,fconf);
        printf("\ncmd_typist: an extreme fast terminal typing tutor/meter designed to work on ubuntu and other linux distros "
        "<cmd_typist v 1.0>  Copyright (C) <*****>  by Prince Noslac"

        "\n\nThis program is free software: you can redistribute it and/or modify "
        "it under the terms of the GNU General Public License as published by "
        "the Free Software Foundation, either version 3 of the License, or "
        "(at your option) any later version."

        "\n\nThis program is distributed in the hope that it will be useful, "
        "but WITHOUT ANY WARRANTY; without even the implied warranty of "
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
        "GNU General Public License for more details.\n");
        printf("\n%s\n","Do you want to view full license[y/n]:" );
        if(fclose(fconf)!=0)
        {
            fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
            exit(2);
        }
        if(get_only_char()=='y')
        {
            if((fconf=fopen("LICENSE","r"))==NULL)
                fprintf(stderr, "%s\n", "GNU GPL license not found in program directory, visit <http://www.gnu.org/licenses/>");
            else
            {
                char ch;
                while((ch=getc(fconf))!=EOF)
                    putchar(ch);
            }
            if(fclose(fconf)!=0)
            {
                fprintf(stderr, "%s\n", "Fatal Error, license file is corrupted\n");
                exit(2);
            }
        }
        printf("%s\n", "ENTER to continue");
        while(ch=getchar()!='\n');//remains here until enter key.
    }   
}

void test_new_user(char *name)//used to create new user name
{
    strcat(upper_case(name),"\n");
    if(strlen(name)<3)
    {
        fprintf(stderr, "%s %s\n", name,"too short, cannot be a user name");//exiting when a wrong value is entered
        exit(EXIT_FAILURE);
    }
    //char ch='z';//setting a value so that the value initialized by default is never y or n
    printf("WARNING: All saved data will be erased <copy and save ./speed/user_speed.info file if you would need it in future>\n"
        "Do you want to continue: [y/n]:");
    if(get_only_char()=='n')
        exit(EXIT_FAILURE);
    FILE *fp;
    if((fp=fopen("./speed/user_speed.info","w"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }
    rewind(fp);
    fprintf(fp, "%s\n", name);
    if(fclose(fp))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }
}

long int read_file_size(FILE* name_to_read)
    {
        char ch;

        int size=0;
        rewind(name_to_read);
        while((ch=getc(name_to_read))!=EOF)
           size++;
        return size;
    }


/*Selects the user playing based on the name sent to it via command line*/
long int select_user(void)
{
    if((user_ptr=fopen("user.info","r+"))==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
        exit(EXIT_FAILURE);
    }   
    int get_count=0;//used to regulate first user since there is no newline before the first user
    char ch;
    rewind(user_ptr);
    u=0;
    int i=0;
    while(u!=369)
    {
        get_user_name();
        get_count++;
        strcpy(temp_name,user_info);
        u=0;
        while(u!=369)
        {
            if((char)temp_name[u]=='.')
                break;
            u++;
        }
        temp_name[u+1]='\0';
        if(strcmp(temp_name,user_name)==0)
        {           
            //fseek(user_ptr,select_user(),SEEK_CUR);//Moving back to start reading from the correct position
            break;
        }
        //else;     
        i++;
        if(i==3000)
        {
            fprintf(stderr, "%s\n", "The account name you entered is incorrect, <try again>");
            exit(EXIT_FAILURE);
        }
    }
    if(get_count==1)
        rewind(user_ptr);
    else
    {
        fseek(user_ptr,-2L,SEEK_CUR);//Moving backward twice (escape new ling and string terminator)
        while((ch=fgetc(user_ptr))!='\n'&&ch!=EOF)      
        fseek(user_ptr,-2L,SEEK_CUR);//moving backward twice since the while statement causes a single forward movement
                                    //to prevent reading of just one character that leads to infinite loop
    }   
    fflush(user_ptr);//needed to clear buffer to prevnet ftell from reading wrong values from text files.
    return ftell(user_ptr);
    if(fclose(user_ptr))
    {
        fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
        exit(EXIT_FAILURE);
    }

}