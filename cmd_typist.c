//cmdtypist: the main of cmdtypist

/*
Program title: CMDTYPIST
Author: Chiatiah Calson
License: GPL 3 or later versions
Date and Time: 5 July 2017 @ 10:40PM
Program Size: 2.8MB
*/

#include<math.h>
#include<stdio.h>	
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include <unistd.h>

//cmdtypist.c: Implementing the main 
#include"functions_for_cmd_typist.h"//function prototypes and global variables.
#include"display.h"//display fixing
#include"utils.h"//useful functions
#include"files.h"//file manipulations
#include"config.h"//configuration
#include"terminal.h"//manipulating the terminal

char argv[5][18];
int main(int argc, char **argv)//argc=command line counter, argv=pointer to pointer to character(command line arguments)
{
	redirect();
	lmt_pg_size();
	name_display();
	read_message_conf();//welcome message for first time users.
	int lesson_choice=1;//global variable to hold the number corresponding to the chosen lesson.
	//char commands[][10]={"0ls","1edituser","2myown","3--help","4man","5mkuser","6mkrand","7mkstd", "8select","9chblk","10sound","11--off","12--on","13cch","14reset","15timeset","16atv","17raw"};
	char commands[][10]={"ls","edituser","myown","--help","man","mkuser","mkrand","mkstd", "select","chblk","sound","--off","--on","cch","reset","timeset","atv","raw"};

	if(argc<1||argc>3)
	{
		fprintf(stderr, "%s\n", "Invalid number of arguments to cmdtypist");
		exit(EXIT_FAILURE);
	}
	switch(argc)//switching command depending on the number of command line arguments.
	{
		case 1:
		if(read_myown_config()!=0)
		{
			lesson_list();//list all lessons present.
			select_lesson(argc,&lesson_choice);
		}
		main_play(argc,&lesson_choice);
		break;

		case 2:
		if(strcmp(argv[1],commands[2])==0)
		{
			write_myown_config(0);
			main_play(argc,&lesson_choice);
		}
		else if(strcmp(argv[1],commands[13])==0)
		{
			write_myown_config(1);
			lesson_list();
			select_lesson(argc,&lesson_choice);
			system("clear");
			main_play(argc,&lesson_choice);	
		}
		else if(strcmp(argv[1],commands[3])==0)
		{
			FILE *fp;
			if((fp=fopen("help.md","r"))==NULL)
			{
				fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
				exit(EXIT_FAILURE);
			}
			while((ch=getc(fp))!=EOF)
				printf("%c", ch);
			puts("");
			if(fclose(fp))
			{
				fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
			    exit(EXIT_FAILURE);
			}
		}
		else if(strcmp(argv[1],commands[4])==0)
		{
			FILE *fp;
			if((fp=fopen("Readme.txt","r"))==NULL)
			{
				fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
				exit(EXIT_FAILURE);
			}
			while((ch=getc(fp))!=EOF)
				printf("%c", ch);
		}
		else if(strcmp(argv[1],commands[6])==0)
			write_conf_mode(0);
		else if(strcmp(argv[1],commands[7])==0)
			write_conf_mode(1);
		else if(strcmp(argv[1],commands[14])==0)
		{
			printf("%s","Will reset to default; continue? [y/n]:");
			if(get_only_char()=='n')
				exit(EXIT_SUCCESS);
			reset_default_config(argv[2],argc);
			printf("%s\n","Settings reset to default");
			exit(EXIT_SUCCESS);
		}
		else if(strcmp(argv[1],commands[16])==0)
		{
			adapt_to_ver();
			exit(EXIT_SUCCESS);
		}
		else if(strcmp(argv[1],commands[0])==0)
		{
			lesson_list();
			select_lesson(argc,&lesson_choice);
			main_play(argc,&lesson_choice);
		}
		else fprintf(stderr, "%s\n", "Ensure the second argument is corrrectly spelled");
		break;

		case 3:
		if(strcmp(argv[1],commands[5])==0)
		{
			test_new_user(argv[2]);
			lesson_list();
			select_lesson(argc,&lesson_choice);
			main_play(argc,&lesson_choice);
		}
		else if(strcmp(argv[1],commands[14])==0&&strcmp(argv[2],commands[17])==0)
		{
			reset_default_config(argv[2],argc);
			exit(EXIT_SUCCESS);
		}
		else if(strcmp(argv[1],commands[8])==0)
		{
			if(read_myown_config()==1)
				lesson_choice = range_verifier(is_integral(argv[2],argc));
			else 
				{
					lesson_choice=1;
					fprintf(stderr, "%s\n\n", "You have been redirected here because you are typing in \"myown\"");
				}
			main_play(argc,&lesson_choice);
		}
		/*
		else if((strcmp(argv[1],"sound")==0)&&strcmp(argv[2],"--on")==0)//modifying system sound
		{
			sound_config_write(1);
			exit(EXIT_SUCCESS);
		}
		else if((strcmp(argv[1],"sound")==0)&&strcmp(argv[2],"--off")==0)
		{
			sound_config_write(0);
			exit(EXIT_SUCCESS);
		}*/
		else if((strcmp(argv[1],commands[10])==0))//modifying system sound	
		{
			if(strcmp(argv[2],commands[12])==0)
			{
				sound_config_write(1);
				exit(EXIT_SUCCESS);
			}
			else if(strcmp(argv[2],commands[11])==0)
			{
				sound_config_write(0);
				exit(EXIT_SUCCESS);
			}
			else
			{
				fprintf(stderr, "%s\n", "Check argument 3 for errors, can be \"--on or --off\"");
				exit(EXIT_SUCCESS);
			}
		}
		else if(strcmp(argv[1],commands[9])==0)		
		{		
			write_conf_block_read(is_integral(argv[2],argc));
			exit(EXIT_SUCCESS);
		}	
		break;

		/*case 4://later update
		if((strcmp(argv[1],"timeset")==0))//testing if user wants to play for specific amount of time.	
		{
			if(strcmp(argv[2],"--on")==0)
			{
				time_set=1;
				main_play();
			}
			else
			{
				fprintf(stderr, "%s\n", "Argument 3 invalid or not recognized");
				exit(EXIT_SUCCESS);
			}
		}*/
		default:
		  fprintf(stderr, "%s\n", "Argument is invalid, use \"help\" to find out more");
		  break;
	}
	return 0;	
}

void select_lesson(int argc_cmd, int* user_choice)
	{
		char firstarg[81];//
		if(argc_cmd>0&&argc_cmd<4)//checking on the command line argument.
		{				
			char ch;//
			printf("%s", "Enter command >>");
			while(scanf("%s",firstarg)!=1||(scanf("%d",&*user_choice))!=1||*user_choice<1||*user_choice>15||strncmp(firstarg,"select",6)!=0)//Ensuring that "select" 
			{       						//is entered accurately and the selected value is within the correct range.
				                   
			    if((strncmp(firstarg,"se",2)==0||strcmp(firstarg,"sel")==0||strcmp(firstarg,"sele")==0||strcmp(firstarg,"selec")==0)&&strcmp(firstarg,"select")!=0)
			    											//Making suggestion to help user prevent errors.
						fprintf(stderr, "\n%s\n%s", "Did you mean \"select usernumber\"","Enter command >>");
				else if(ch!=1&&strcmp(firstarg,"select")==0)
				  printf("%s%s", "Lesson number cannot contain symbols or alphas\n","Enter command >>");
				else if((*user_choice<1||*user_choice>20)&&strcmp(firstarg,"select")==0)
					fprintf(stderr, "%s %d\n", "No lesson entry for ",*user_choice);
				else printf("%s\nEnter command >>", "Command not found");
				while(ch=getchar()!='\n');//disposing off wrong input string.
			}
		}
		else
		{
			fprintf(stderr, "%s\n", "Invalid number of arguments, consult \"cmdtypist --help\" for more");
			exit(EXIT_FAILURE);
		}
			/*
			if(argc_cmd==3)
				if(strncmp(argv[2],"select",6)!=0||lesson_choice<1||lesson_choice>20)
				{
					fprintf(stderr, "%s\n", "Command not found\n");
					if(strncmp(argv[2],"se",2))
						fprintf(stderr, "%s\n", "Did you mean \"select\"");
					else if(lesson_choice<1||lesson_choice>20)
						fprintf(stderr, "%s %d\n", "No lesson entry for ",lesson_choice);
					//else if(ch!=1)
				        printf("%s", "Lesson number cannot contain symbols or alpha letters.\n");
					exit(EXIT_FAILURE);
				}*/
		printf("\n");
	}

void urs_or_cchl(void)
{
	if(read_myown_config()==0)
	{
		strcpy(file_to_read,"my_own.txt");
		mode=1;
	}
	else if(read_myown_config()==1)
			strcpy(file_to_read,"noslaclessons.txt");
	else
	{
		fprintf(stderr, "%s\n", "Fatal Error, lesson file corrupted or does not exist");
		exit(EXIT_FAILURE);
	}
}

void lesson_position(long *read_this_length,long *point_to,int *my_choice)//setting up the pointer in a position of the file to start reading.
{
	FILE *lesson_point;
	urs_or_cchl();
	if((lesson_point=fopen(file_to_read,"r+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	if(read_myown_config()==0)
	{
		rewind(lesson_point);//return to beginning 
		*read_this_length=read_file_size(lesson_point);
		*point_to=0;
	}
	else
	switch(*my_choice)
		{
			case 1:
				*point_to=0;
				if(read_myown_config()==1)
					*read_this_length=25510;
				break;
			case 2:
				*point_to=25512L;
				*read_this_length=21660;
				break;
			case 3:
				*point_to=39326L;
				*read_this_length=397417;
				break;
			case 4:
				*point_to=444591L;
				*read_this_length=11142;
				break;
			case 5:
				*point_to=455733L;
				*read_this_length=98588;
				break;
			case 6:
				*point_to=554321L;
				*read_this_length=19564;
				break;
			case 7: 
				*point_to=573885L;
				*read_this_length=79999;
				break;
			case 8:
				*point_to=653884L;
				*read_this_length=327523;
				break;
			case 9:
				*point_to=981407L;
				*read_this_length=208614;
				break;
			case 10:
				*point_to=1190021L;
				*read_this_length=400980;
				break;
			case 11:
				*point_to=1591001L;
				*read_this_length=625353;
				break;
			case 12:
				*point_to=2216354L;
				*read_this_length=1132581;
				break;
			default:
				*point_to=0;
	}
	if(fclose(lesson_point))
	{
		fprintf(stderr, "%s\n", "Unable to close lesson file");
		exit(EXIT_FAILURE);
	} 
}

void main_play(int argc_cmd,int *lesson_choice)
{
	//lmt_pg_size();
	char terminate=0;
	long length_to_read;//holds information on how long the text to be read is.
	long move_lesson_to;
	lesson_position(&length_to_read,&move_lesson_to,lesson_choice);
	unsigned short block_count=0;
	user_test();//test if a user already exists or not.
	long num_of_chars_typed=0;
	block_length=read_conf_block_read();
	mode=read_conf_mode();
	urs_or_cchl();//selects file to read from
	remove_ext_ascii();//removes any non ascii 7 bits characters from lesson file.
	unsigned int start_time,elapsed_time=0;//elapsed_time: time used during the typing session measured from start time.
	unsigned short number_of_lines_count=1;//used to count the total number of lines to print.
	const unsigned short chars_to_read=77;//total number of characters to read for each line.
	unsigned int i=0;//counter variable for loop counting.
	char linetype[150];//char array to hold the total number of characters to to read from file per line.
	//lesson_list();
	//fseek(noslac_lessonsp,25531L,SEEK_SET);//places the pointer to the position of the file to read.
	int wrong_letters=0;//sums up the total number of wrong characters entered during program run.
	srand((unsigned)time(NULL));//randomizing seed
	FILE *noslac_lessonsp;//lesson pointer
	if((noslac_lessonsp=fopen(file_to_read,"r"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	fseek(noslac_lessonsp,move_lesson_to,SEEK_SET);
	
	while(block_count <= (int)(length_to_read/((chars_to_read+1) * block_length)))//testing inorder to read the entire lesson chosen.
	{
		num_of_chars_typed=0;
		char time_checker=0;//changes back to zero after every block typing
		/*goes =reads a certain number of characters in the file using a loop determined 
		by the random generator and places the pointer at the end of it's reading. thereby
		making the lesson each time to be random*/
		if(mode==0)
		{
			int u=0;//counter
			while(u<=rand()%(length_to_read-((chars_to_read+1)*block_length))&&(ch=getc(noslac_lessonsp))!=EOF)//program feels new
				u++;
					do
			fseek(noslac_lessonsp,-2L,SEEK_CUR);
			while((ch=getc(noslac_lessonsp))!=' ');//moving backwards from where it is placed
		//to start reading from where there is a space or has found an uppercase letter.
		}
		number_of_lines_count=1;
		while(number_of_lines_count<=block_length)//testing for number of lines to read.
		{
			i=0;
			char endl = guess(14, 33);//endl holds the char to end a line in place of usual '\n'
			char startl = guess(14, 33); //guess generates a random char
			while(i <= chars_to_read)//test on i to get 77 characters. the screen size is exactly 77 characters.
			{
				linetype[i] = getc(noslac_lessonsp);//getting characters and placing in the linetype array.
				if(linetype[0] == ' ')//prevent a the start of a line from ever being a space character
			     	linetype[0] = startl;		//replace with random char
			    if(linetype[chars_to_read] == ' ')//ensuring a line does not end with a space character.
			    	linetype[chars_to_read] = '-';//replacing space character at the end of a line with a -
				if(i > 1)
					if(linetype[i-1] == ' ' && linetype[i] == ' ')//preventing two consecutive space characters since text read is random.
						i -= 2;
				//checking and eliminating newlines to prevent brakes.
				if(linetype[i]=='\n'){

					linetype[i] = endl;
					linetype[++i] = ' ';

				}	
				if(linetype[i]==EOF)//making sure a line does not contain any end of file character by any chance
				{
					fprintf(stderr, "%s\n", "Closed unexpectedly, <possibly a corrupt cmdtypist file OR you haven't placed any text in myown.txt>");
					exit(EXIT_FAILURE);
				}
				i++;	
			}

			linetype[i]='\0';//Adding string terminator and subtracting the number of spaces removed.
			if((number_of_lines_count % (block_length)) == 0 && number_of_lines_count != 0)
				printf(""LAST_LINE_BLUE"");
			else
				printf(""RESET"");
			puts(linetype);//using puts inorder to print the a line and move to the next for the user to follow
			number_of_lines_count++;
			i=0;//setting i to 0 to begin new counting.
			unsigned short error_store[3000], j=0;//error_store: array of ints to note the index of a wrong character.
			while(i <= chars_to_read+1)//adding 1 for the extra enter key after the 77 letters are entered.
			{
				int u=0;//loop counter
				if((ch=getche())!='\n'&&ch!=EOF)//using getche to prevent printing of enter key.
				{
					putchar(ch);
					if(time_checker==0)//Making sure time is initialized only once 
					{
						time_checker=1;
						wrong_letters=0;//setting errors to 0 to start next typing session
						start_time=(unsigned)time(NULL);//to start timing.
					}
				}
				if(ch==EOF)
				{
					fprintf(stderr, "%s\n", "Closed unexpectedly, <an unexpected character keyed in>");
					exit(EXIT_FAILURE);
				}
				
				if(ch == 27 || ch == '\t')/*testing for ESC character or a tab to exit program.
				                               iscntrl ensures a control character is entered to exit the program*/
				{
					terminate=1;
					letter_clear(1);
					puts("\n");
					break;
				}
				if((ch==127 || ch == 8)&& i == 0)//not using '\b' since most terminals are 'cooked' (keys like backspace are handled by terminal driver)  //checking for both delete and backspace.
				  letter_clear(adapt_to_ver_read());        
				else if((ch == 127 || ch == 8) && i > 0)//testing for delete of backspace
				    {
						i--;//decremting the number of characters entered when backspaced is pressed.
						letter_clear(adapt_to_ver_read());
						j=wrong_letters;
						while(j>u)//counting from u to j, to find if there is a wrong character stored in the error_store array of ints.
						{
							//printf("j=%d and u=%d\n", j,u);
							if(error_store[j]==i)//checking through the array for errased wrong charactes initially entered.
							{									  //also ensuring before any decrement, wrong_letters>0
								wrong_letters--;//decrementing the number of wrong letters.
								/*if(wrong_letters<0)
								{
									printf("finally got a case %d\n",wrong_letters);
									wrong_letters=0;									
								}*/
								error_store[j]=-99;//-99 is a value which will never be reached. 
								//this is to mark the erased index as no longer wrong.
								break;//Ensuring that immediately there is a match, the while loop is escaped for speed.
							}
							j--;
						}						
	    		    }
				else if(i==78&&ch!='\n')
				   letter_clear(1);
				else if(ch!=linetype[i])
					{
						if(ch!='\n')//testing for ENTER to prevent its printing by printf which will cause a newline.
						{
							num_of_chars_typed++;
							letter_clear(1);//clearing the wrong character 					
							//printf("\a"RED"%c"RESET"",ch );//to print again with color RED. \a is used to include a beep for wrong charater
							printf("%s%c",(sound_config_read())==1? "\a"RED"":""RED"",ch);//\a is used to include a beep for wrong character entries
			     			wrong_letters++;
			     			error_store[wrong_letters]=i;//recording the index of a wrong letter
			     			u=0;	
			     			j++;	//Incrementing the backspace counter.
			     			i++;     		//incrementing the number of wrong characters entered.
						}
					}
				else 
					{					
						if(ch!='\n')//Preventing printing of newline which causes an escape from current typing position in the console.
						{
							letter_clear(1);
							num_of_chars_typed++;
							printf(""GREEN"%c"RESET"", ch);//changing color of correct character to green.
							i++;
						}
					}
				if(ch=='\n'&&i==78)
					break;//escaping loop when the user keys in an Enter.
			}
			printf("%s","\n" );	//Prints two spaces to ensure the two console spaces left are used, so next printing goes to next line.	Game console is 80 and 78 is being used.
			if(terminate==1||argc_cmd==4)
				break;
		} 
		elapsed_time = (unsigned)time(NULL) - start_time;/*getting the final time and subtracting from the initial 
														to get the elapsed time*/
		block_count++;
		//printf("lines=%d block = %d\n",number_of_lines_count,block_length );
		if(terminate==1)//exiting on tabs and other systme keys
		{
			char user_name[81];
			if(elapsed_time <= 10)
			{
				fprintf(stderr, "%s\n", "Speed not recorded");
				printf(""RESET"\n");
				exit(EXIT_SUCCESS);
			}
			get_user_name(user_name);
			printf(""GREEN"                              ");
			printf("%s", user_name);
			if(wrong_letters<0)//optional statement to reduce proberbility of ever having a -ve wrong_letters.
				wrong_letters=0;
			write_user_speed(elapsed_time,wrong_letters,num_of_chars_typed);
			session_style(elapsed_time,wrong_letters,num_of_chars_typed);
			exit(EXIT_SUCCESS);//display current typing speed and error
		}
		if(((number_of_lines_count-1)%block_length)==0)
		{
			char user_name[81];

			if(wrong_letters<0)//optional statement to reduce proberbility of ever having a -ve wrong_letters.
				wrong_letters=0;
			printf(""GREEN"                              ");
			get_user_name(user_name);//reading user name from file to display in session
			printf("%s", user_name);
			session_style(elapsed_time,wrong_letters,num_of_chars_typed);//printing session speed details
			write_user_speed(elapsed_time,wrong_letters,num_of_chars_typed);//writing user speed to speed file
		}

	}
}


/*Wrong letters algorithm:
if a user is at the first position of the line and presses backspace, then, that backspace is simply cleared and i not incremented
the array error_store[] keeps track of the index(the i position of the wrong character) and increments a counter variable j, which which be used as 
A stop point in a for loop when this stored inex is searched.
When ever backspace keyed in(i!=0), i is first decremented and a search is done through out the loop to see if the decremented i was stored in error store,
if so, then the user is erasing a wrong character, so the wrong_letters is decremented.*/

/*solving the case where wrong_letters shows a messy value
changing it's type to int and making sure it's always greater than 0
*/