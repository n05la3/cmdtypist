//files.h: file manipulations
/*
Program title: CMDTYPIST
Author: Chiatiah Calson
License: GPL 3 or later versions
Date and Time: 5 July 2017 @ 10:40PM
Program Size: 2.8
*/

void test_new_user(char *name)//used to create new user name
{
	if(first_time()!=0)//if a user exist
	{
		//char ch='z';//setting a value so that the value initialized by default is never y or n
		printf("\nWARNING: All saved data will be erased <copy and save user_speed.info file if you would need it in future>\n"
			"Do you want to continue: [y/n]:");
		if(get_only_char()=='n')
			exit(EXIT_FAILURE);
	}
	confirm_user_exist();
	strcat(upper_case(name),"\n");
		if(strlen(name)<3)
		{
			fprintf(stderr, "%s %s\n", name,"too short, cannot be a user name");//exiting when a wrong value is entered
			exit(EXIT_FAILURE);
		}
	FILE *fp;
	if((fp=fopen("./speed/user_speed.info","w"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	rewind(fp);
	fprintf(fp, "%s\n", name);
	fget_ignore_newline(name);
	printf("\n%s %s\n",name,"written with success");
	if(fclose(fp))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
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

void write_user_speed(unsigned int session_time,int wrongly_typed, float typed)//Elapsed time is time taken to type
{
	time_t timer = time(NULL);
	char time_nw[18];
	strcpy(time_nw, ctime(&timer));
	short i=0;
	/*
	*removing trailing newline
	*/
	while(i<=200){
		if(time_nw[i]=='\n'){
			time_nw[i] = '\0';
			break;
		}
		i++;
	}
	FILE* fp;
	char time_conversion[36];//stores converted time by seconds_hms()
	if((fp=fopen("./speed/user_speed.info","r+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	float raw_speed=0;//holds the speed when not ajusted.
	float adj_speed=0;//holds the adjusted speed
	make_current(fp);
	fseek(fp,0L,SEEK_END);//moving to end of file
	fprintf(fp, "\t+------------------ %s -------------------+\n",time_nw);//printing date and time when the test is done
	seconds_to_hms(session_time,time_conversion);
	//fprintf(fp, "\t|%d%s TIME: %s\n",wrongly_typed,(wrongly_typed==0)? "(NO Error)":(wrongly_typed==1)? "ERROR":"ERRORS",time_conversion);
	raw_speed= ((float)typed*60.0f)/(float)session_time;
	adj_speed= (float) (((float)typed-wrongly_typed)*60.0f)/(float)session_time;		
	fprintf(fp, "\t|ERROR(s):%u TIME: %s SPEED: ~%.3fWPM Accuracy: %.2f%%\n",wrongly_typed,time_conversion,raw_speed/5.0f,(adj_speed/raw_speed)*100.0f);
	fprintf(fp, "\t|%s%.2fCPM ~= %.2fWPM \n", "AVERAGE SPEED: ",adj_speed,adj_speed/5.0);
	fprintf(fp, "%s\n\n", "\t+---------------------------------------------------------------+");	
	if(fclose(fp))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
	}
}

/*Reads user information already opened by main, writes to it the name with which the user
wants to create an account with. Also reads system time and date and wite agains that user name*/ 
void accounts_create(void)
	{

		FILE *fp;
		if((fp=fopen("user.info","a+"))==NULL)
		{
			fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
			exit(EXIT_FAILURE);
		}

		strcpy(user_info,user_name); 	
		strcat(user_info,__DATE__);
		strcat(user_info,__TIME__);
		user_info[strlen(user_info)]='\n'; 
		user_info[strlen(user_info)]='\0'; 

		fprintf(fp, "%s", user_info);
		if(fclose(fp))
		{
			fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
		    exit(EXIT_FAILURE);
		}
	}


/*
*Reads pariticular user information and stores in a global static variable user_info
*using the fact that the end of each user information ends in new line
*/ 
char get_user_name(char *user_name)
{
	char name_ch;
	int i=0;
	char ch;
	FILE *fp;
	if((fp=fopen("./speed/user_speed.info","r"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	rewind(fp);
	while((name_ch=getc(fp))!='\n'&&name_ch!=EOF){
		//putchar(name_ch);
		user_name[i] = name_ch; 
		i++;
	}
	user_name[i]='\0';	
	if(fclose(fp))
		{
			fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
		    exit(EXIT_FAILURE);
		}
}
/*Selects the user playing based on the name sent to it via command line*/
long int select_user(void)
{
	FILE *user_ptr;
	if((user_ptr=fopen("user.info","r+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}	
	int get_count=0;//used to regulate first user since there is no newline before the first user
	char ch;
	rewind(user_ptr);
	unsigned short int u;
	int i=0;
	while(u!=369)
	{
		char *user_name;
		get_user_name(user_name);
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

//Initial settings of cmdtypist.
void reset_default_config(char *raw, int argc_cmd)
{
	write_myown_config(1);
	write_conf_mode(1);
	write_conf_block_read(4);
	sound_config_write(0);
	write_message_conf(0);
	if(argc_cmd==3)
	{
		if(strcmp(raw,"raw")==0)
		{
			printf("%s", "Raw reset, resets everything including speed history; continue? [y/n]:");
			if(get_only_char()=='n')
				exit(EXIT_SUCCESS);
			else
			{
				FILE *fp;
				if((fp=fopen("./speed/user_speed.info","w+"))==NULL)
				{
					fprintf(stderr, "%s\n", "Could not reset, some files are missing");
					exit(EXIT_FAILURE);
				}
				fclose(fp);
				if((fp=fopen("my_own.txt","w+"))==NULL)
				{
					fprintf(stderr, "%s\n", "Could not reset, some files are missing");
					exit(EXIT_FAILURE);
				}
				fclose(fp);
				printf("%s\n", "User settings reset to default");
			}
		}
	}
	else printf("%s\n", "Soft reset successful");
}


/*Function takes the name of a file, and appends .txt to it, then tries to read it from external storage 
and determine the total number of characters it contains"*/

long int read_file_size(FILE* name_to_read)
	{
		char ch;

		int size=0;
		rewind(name_to_read);
		while((ch=getc(name_to_read))!=EOF)
		   size++;
		return size;
	}

/*Writes the string that is given to it as a parameter, replaces 
every other string on the line to which it is writing to space 
and finally writes a newline to the end of the line*/
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
			/*if((ch=getc(fp))!='\n'&&ch!=' ')
			fseek(fp,-1L,SEEK_CUR);//moving backward one space since getc above had moved one space ahead
									//so as to write over the data existing.
			//fprintf(fp, "%s", " ");
			/*if(ch=='\n')
			{
				fseek(fp,-1L,SEEK_CUR);
				fprintf(fp, "%c", '\n');//writing newline at the end of file since it had been replaced with a space string
				break;//escaping since the end of the line has been reached
			}	*/		
		}
	//	i++;		
	//}
}

void swap_modify_name(int length_of_string)
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

/*Opens the user file and over writes former name with new name,
uses a new array already containing the new name and writes to it the date and time for the former user,
it then writes this new array to the user info file*/

void edit_name(void)
{	
	FILE *fp;
	if((fp=fopen("user.info","r+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}	
	fseek(fp,select_user(),SEEK_SET);
	write_to_line(new_name,fp);
	if(fclose(fp))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
	}
	
}
/*used to remove all non standard ascii codes from user text*/

extern void remove_ext_ascii(void)
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
/*
*Limit the size of speed file to 10KB; occurs after 429 rounds
*/
extern void lmt_pg_size()//limit page size
{
	FILE *fp;
	char user_name[81];
	if((fp=fopen("./speed/user_speed.info","r"))==NULL){
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	fseek(fp,0,SEEK_END);
	if(ftell(fp) >= 100000){
		fprintf(stderr, "%s\n", "speed.info file in ~/cmtypist/speed has grown too large, copy and save if you wish to preserve it\n");
		printf("\n:The speed.info file will be cleared, continue: [y/n]:");
		if(get_only_char()!='n'){
			get_user_name(user_name);
			if((fp = freopen("./speed/user_speed.info","w+", fp))==NULL){
				fprintf(stderr, "%s\n", "unable to reset speed.info file, alternatively run 'cmdtypist rest raw to fix this'\n");
				exit(EXIT_FAILURE);
			}
			rewind(fp);
			fputs(user_name,fp);
			fputc('\n',fp);
			rewind(fp);
		}
	}
	if(fclose(fp)){
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    	exit(EXIT_FAILURE);
	}
}

/**
 * @param void
 * performs a test to make sure cmdtypist has been installed to home directory
 * installed? true: it changes the current directory the the home/cmdTypist directory
 * false: it gives a warning message with possible fixes and continues
 */
extern void redirect(void)
{	
	char idir[62] = "";
	if(getenv("HOME") != NULL)
	{		
		strncpy(idir,getenv("HOME"), 50);
		strcat(idir, "/cmdTypist");//installation directory
		printf("%s\n", idir);
	}
	// exit(0);
	FILE *fp;
		//call script that verifies if program is installed to $home/cmdTypist
	char test_dir[60] = "";
	strncpy(test_dir, idir, 50);
	strcat(test_dir, "/files.h");
	if((fp=fopen(test_dir,"r")) == NULL)
	{
		fprintf(stderr, "%s\n", "Program not installed to $HOME/cmdTypist directory\n");
		fprintf(stderr, "\t- %s\n", "Navigate to cmdtypist directory manually, before running it\n");
		fprintf(stderr, "\t- %s\n", "OR uninstall and reinstall a fresh copy\n");
		return;
	}else{
		//system(idir); //navigate to installation directory
		//change directory
		if(chdir(idir) == -1){
			fprintf(stderr, "%s\n", "Error changing directory to $HOME/cmdTypist");
			exit(EXIT_FAILURE);
		}
	}

	if(fclose(fp)){
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    	exit(EXIT_FAILURE);
	}
}