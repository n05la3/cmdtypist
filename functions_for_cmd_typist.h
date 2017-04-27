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

