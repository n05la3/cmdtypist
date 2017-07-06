//utils.h: basic functions needed

/*
Program title: CMDTYPIST
Author: Chiatiah Calson
License: GPL 3 or later versions
Date and Time: 5 July 2017 @ 10:40PM
Program Size: 2.8
*/

char get_only_char()
{
	char n;
	char ch='&';//for flushing
	printf("%s", "");
	scanf("%c", &n);
	char f;
	f=getchar();//f will get \n when n is gotten
	while((n!='n'&&n!='y')||f!='\n')//making sure only n and y or \n (in f) are entered
	{
		if(f=='\n')//special case when n is found
		{
			printf("Invalid [y/n]:");
			//while((ch=getchar())!='\n');//flushing the buffer
			scanf("%c", &n);
			f=getchar();
		}
		else
		{
			printf("Invalid [y/n]:");
			while((ch=getchar())!='\n');//flushing the buffer
			scanf("%c", &n);
			f=getchar();
		}

	}
	return n;
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

static char *cat_name(char *name)//catenating \n to a pointer to .
{
	char trick_name[SIZE_NAME];//trick string for name catenating.	
	strcpy(trick_name,name);
	strcat(trick_name,"\n");
	strcpy(name,trick_name);
	return name;
}


/*Searching the name for space to replace with |*/
void name_modify(char *name)
{
	short unsigned int i=0;//counter
	while(i<=15)
	{
		if(name[i]==' ')//searching for ' ' in the name string
		{
			name[i]='|';//and replacing with |
			break;
		}
		i++;
	}
	if(i>15)
	{
		fprintf(stderr, "%s\n", "Name too long");
		exit(EXIT_FAILURE);
	}
	strcat(name,".");
}

/*Function converts time passed to it in seconds and stores the converted 
time to hrs, mins and secs, then stores the resulting string to the string argument 
time also passed to it as a second parameter*/
void seconds_to_hms(long int time_in_seconds, char *time)
	{
		long hr, min, t;
		hr = time_in_seconds/3600;
		t = time_in_seconds%3600;
		min = t/60;
		time_in_seconds = t%60;
		if(hr>0)
		sprintf(time,"%ld%s:%ld%s:%ld%s", hr,(hr>1)? "hrs":"hr",min,(min>1)? "mins":"min",time_in_seconds,(time_in_seconds>1)? "secs":"sec");//modify printing display
		else if(min>0)
		sprintf(time,"%ld%s:%ld%s", min,(min>1)? "mins":"min",time_in_seconds,(time_in_seconds>1)? "secs":"sec");
		else 
		sprintf(time,"%ld%s", time_in_seconds,(time_in_seconds>1)? "secs":"sec");
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

void cpy_2d_string( char *destination[],const char *source[],int argc)//source=argv from command line
{
	int i;//counter for the number of elements in the strings
	for(i=1;i<=argc;i++)
		strcpy(destination[i],source[i]);
}

/*This function is used to eliminate eliminate a newline from a string*/
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


/*Sleep function for both linux and windows, passing the number of seconds as a parameter*/
extern void sleepf(int time_to_sleep)//implementing a sleep function 
	{
		#ifdef _WIN32
        Sleep(time_to_sleep);
        #else
        sleep(time_to_sleep);
        #endif 
	}

/*//windows virtual command line, function is used to get arguments from cmtypist
int win_cmd_arg(int win_argc, char** win_argv)
{
	char ch,char_arg[20];
	int i=0,j=0;
	while(ch!='\n')
	{
		short int i=0,j=0;
		while(ch=getchar()!=' '||ch!='\n')
		{
			if(i>=19)
			{
				fprintf(stderr,"%s\n","Argument to cmdtypist is too large, consult the help menu to know what is available");
				exit(EXIT_FAILURE);
			}
			char_arg[i]=ch;
			i++;
		}
		char_arg[i+1]=='\0';
		if(j>4)
		{
			fprintf(stderr,"%s\n","Too many arguments to cmdtypist");
			exit(EXIT_SUCCESS);
		}
		strcpy(win_argv[i],char_arg);//placing the argument gotten in argument value pointer to pointer to char.
		j++;
	}
	return win_argc=j;
}


//windows virtual command line, function is used to get arguments from cmtypist
extern int win_cmd_arg(char *win_str)
{
	int i=0,argc=0,j=0,u=0;
	char exit=0;	
	char store[81][81];
	char new[20];
	fgets(win_str,81,stdin);//uses \n to flush
	do
	{
		new[j]=win_str[i];
		if(new[j]=='\n'||new[j]==' ')
		{
			new[j]='\0';
			j=-1;	
			strcpy(store[u],new);
			printf("%s\n",store[u]);
			getchar();	
			if(new[j]=='\n')
				break;	
			u++;
		}
		j++;		
		i++;
	}while(win_str[i]!=EOF);	
	return i;
}

//windows virtual command line, function is used to get arguments from cmtypist
extern int win_cmd_arg(char *win_str)
{
	int i=0  ,argc=0;
	char exit=0;	
	char store[81][81];
	fgets(win_str,81,stdin);//uses \n to flush
	do
	{
		
		if(win_str[i]==' ')
		{
			store[argc][i]=win_str[i];
			argc++;	
		}
		i++; 
	}while(win_str[i]!='\n');
	printf("%d  %d\n\n", i,argc);
		
/* while(exit==0)
	{
		store[argc][i]=win_str[i];
		if(win_str[i]==' '||win_str[i]=='\n')
		{
			store[argc][i]=='\0';	
			puts(store[argc]);	
			argc++;
			if(win_str[i]=='\n')
				exit=1;
		}
		i++;			
	}

	win_str[i]=='\0';
	return i;
}*/
















