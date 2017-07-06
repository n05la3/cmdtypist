//config.h: Configuration settings

/*
Program title: CMDTYPIST
Author: Chiatiah Calson
License: GPL 3 or later versions
Date and Time: 5 July 2017 @ 10:40PM
Program Size: 2.8 
*/

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

extern char read_conf_mode(void)//num_value is used to record settings for random and standard play
{
	char num_value;
	FILE *fconf;
	if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	fseek(fconf,1L,SEEK_SET);
	fread(&num_value,sizeof(char),1,fconf);
	if(fclose(fconf))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
	}
	return num_value;
}

extern void write_conf_mode(char n)//r is used to record settings for random and standard play
{
	FILE *fconf;
	if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	fseek(fconf,1L,SEEK_SET);
	fwrite(&n,sizeof(char),1,fconf);
	if(fclose(fconf))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
	}
}

extern char read_conf_block_read(void)//num_value is used to record settings for random and standard play
{
	char num_value;
	FILE *fconf;
	if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	fseek(fconf,2L,SEEK_SET);
	fread(&num_value,sizeof(char),1,fconf);
	if(fclose(fconf))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
	}
	return num_value;
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

extern char sound_config_read(void)//num_value is used to record settings for random and standard play
{
	char num_value;
	FILE *fconf;
	if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Some files are missing");
		exit(EXIT_FAILURE);
	}
	fseek(fconf,3L,SEEK_SET);
	fread(&num_value,sizeof(char),1,fconf);
	if(fclose(fconf))
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
	    exit(EXIT_FAILURE);
	}
	return num_value;
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

//writing message configuration to config file
extern void write_message_conf(char n)//r is used to record settings for random and standard play
{
	FILE *fconf;
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
extern short unsigned int first_time(void)
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
    return num_test;
    fclose(fconf);
}
extern void confirm_user_exist(void)
{
	char num_test=1;
	FILE *fconf;
	if((fconf=fopen("cmdtypist.conf","rb+"))==NULL)
    {
    	fprintf(stderr, "%s\n", "Unable to read configuration file");
    	exit(EXIT_FAILURE);
    }
    rewind(fconf);
    fwrite(&num_test,sizeof(char),1,fconf);
	if(fclose(fconf)!=0)
	{
		fprintf(stderr, "%s\n", "Fatal Error, Unable to close some files\n");
		exit(2);
	}
}
/*This function opens a binary file on which zero was initally written, it then checks if the zero is still there, 
if yes then it is the first time the program is being opened  and then replaces the zero with 1*/
extern void read_message_conf(void)//Function for first time message display
{		
    if(first_time()==0)//checking to see if its 0 that is found in the file.
    {
    	system("clear");
    	FILE *fconf;
    	printf("%s\n", "      ============================WELCOME!!!============================      \n");
        printf("\n\t\t\t\tCMDTYPIST\n\n It is an extremely fast typing tutor designed to work on ubuntu and other linux distros "
		"\ncmd_typist v 1.0  by Chiatiah Calson Noah on the 5th July 2017 @ 10:40PM "

	    "\n\nThis program is free software: you can redistribute it and/or modify "
	    "it under the terms of the GNU General Public License as published by "
	    "the Free Software Foundation, either version 3 of the License, or "
	    "(at your option) any later version."

	    "\n\nThis program is distributed in the hope that it will be useful, "
	    "but WITHOUT ANY WARRANTY; without even the implied warranty of "
	    "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
	    "GNU General Public License for more details.\n");
	    printf("\n%s\n","Do you want to view full license[y/n]:" );
	    if(get_only_char()=='y')
	    {
	    	if((fconf=fopen("LICENSE.md","r"))==NULL)
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
	    printf("\n%s", "First time tip:\n Enter \"select \"lesson-number\"\" when prompted for a command; lesson-number=valid lesson number"
	    	"\n\n Have a look at the help menu? You can revisit it later using \"cmdtypist --help\" command [y/n]:");
	     if(get_only_char()=='y')
	    {
	    	if((fconf=fopen("help.md","r"))==NULL)
	    		fprintf(stderr, "%s\n", "Error: Unable to find help menu");
	    	else
	    	{
	    		printf("\n\n");
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
	    printf("\n%s\n", "ENTER to continue");
	    while(ch=getchar()!='\n');//remains here until enter key.	    
    }   
}


extern void waiting(char *wait_style)//style in waiting for input.
	{
		    printf("%s",wait_style);
		    fflush(stdout);
			sleepf(1);
			printf("%s","." );
			fflush(stdout);
			sleepf(1);
			printf("%s","." );
			fflush(stdout);
			sleepf(1);
			printf("%s","." );
			letter_clear(3);
		    fflush(stdout);
			sleepf(1);
			printf("%s","." );
			fflush(stdout);
			sleepf(1);
			printf("%s","." );
			fflush(stdout);
			sleepf(1);
			printf("%s","." );			
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
