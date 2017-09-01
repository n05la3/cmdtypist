//functions_for_cmd_typist.h: Contains all function prototypes, constants and global variables.

/*
Program title: CMDTYPIST
Author: Chiatiah Calson
License: GPL 3 or later versions
Date and Time: 5 July 2017 @ 10:40PM
Program Size: 2.8
*/

char get_only_char();
char time_set=0;
char file_to_read[19];//name of lesson file to read from
unsigned short int block_length;
//#include<math.h>
#define SIZE_NAME 81//variable to hold the name of the user. 
char mode=8;//mode of play, could be random or standard, setting it defined amount to prevent it from being initialised to 0
char ch;//used for character input and testing.
#define RED "\x1B[31m"//bash script for red color
#define GREEN "\x1B[32m"//bash script for Green color
#define SPEED_COLOR "\x1B[36m"//printing speed color
#define TIP_COLOR "\x1B[35m"//bash script for Green color
#define LAST_LINE_BLUE "\x1B[34m"//Green color
#define RESET "\x1B[0m"//color reset to normal (black)
#if defined(_WIN32)//checking if the system on which the program is running is windows
#include<Windows.h>//and including the windows header file.
#elif defined(__linux__)//if machine is linux
#include<unistd.h>//include the linux header file
#include<termios.h>//a linux header file for echo, works with getche()
#endif
//char firstarg[8];//global variable to hold the "select argument"

//function prototypes
void main_play(int argc_cmd,int* lesson_choice);//prototype for the main play, main play board
void select_lesson(int argc_cmd, int* user_choice);
void lesson_position(long* read_this_length,long* point_to,int* my_choice);//prototype for lesson selection, selects from list of lessons


void make_current(FILE *file_to_remove_from);
extern void name_display(void);//functions for display control, location: display.c
//functions for program configuration, location: config.c
extern char read_myown_config(void);
extern void write_myown_config(char n);
extern char read_conf_mode(void);//num_value is used to record settings for random and standard play
extern void write_conf_mode(char n);//r is used to record settings for random and standard play
extern char read_conf_block_read(void);//num_value is used to record settings for random and standard play
extern void write_conf_block_read(unsigned int n);//r is used to record settings for random and standard play
extern char sound_config_read(void);//num_value is used to record settings for random and standard play
extern void sound_config_write(unsigned int n);//r is used to record settings for random and standard play

extern char adapt_to_ver(void);//num_value is used to record settings for random and standard play
extern char adapt_to_ver_read(void);//num_value is used to record settings for random and standard play
extern unsigned int is_integral(char number[], int argc_cmd);
extern int range_verifier(int n);
extern void write_message_conf(char n);//r is used to record settings for random and standard play
extern void read_message_conf(void);//Function for first time message display
//terminal manipulation and control, location in utils.c
static void fget_ignore_newline(char* arr_no_newline);
extern char get_only_char();
void valid_range(int num_to_convert);//Ensures correct range is entered
char* upper_case(char* name);
static char* cat_name(char* name);//catenating \n to a pointer to .
void test_new_user(char* name);//used to create new user name
void name_modify(char* name);
extern void letter_clear(int n);
extern int getche(void);
extern void sleepf(int time_to_sleep);//implementing a sleep function
extern void waiting(char* wait_style);//style in waiting for input.
extern void lesson_list(void);
void seconds_to_hms(long int time_in_seconds, char* time);
void session_style(unsigned int session_time,int wrongly_typed,float typed);
extern void user_test(void);
void make_current(FILE* file_to_remove_from);
void write_user_speed(unsigned int session_time,int wrongly_typed, float typed);//Elapsed time is time taken to type
char get_user_name(char *user_name);
void accounts_create(void);
void write_to_line(char* to_write, FILE* fp);
long int select_user(void);
long int read_file_size(FILE* name_to_read);
void swap_modify_name(int length_of_string);
void edit_name(void);
extern void remove_ext_ascii(void);
static int my_atoi(const char* snum);
void reset_default_config(char* raw, int argc_cmd);
extern short unsigned first_time(void);//check if 0 is wrritten to first position of config file
extern void confirm_user_exist(void);
char new_name[81];//global variable for name modification.
int last_user_ptr;
int avg_speed;//average typing speed.
char user_name[SIZE_NAME];//holds the name of the user.
char user_info[360]; //string to store user details.
char temp_name[360];//temporary store for user name













