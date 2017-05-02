/* 
   cmd_typist: an extreme fast terminal typing tutor/meter designed to work on ubuntu and other linux distros
    <cmd_typist>  Copyright (C) <*****>  by Prince Noslac

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
