
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
static int my_atoi(const char* snum)
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

//my library for single character input without echoing, **the conio.h is needed for windows systems.
char get_char_necho()
{
	#if defined(__linux__)
	/*prevent echoing of characters from the buffer*/
    getche();
    #elif defined(_WIN32)
    #include<conio.h>
    getch();
    #endif
}

     /*prevent echoing of characters from the buffer*/
extern int getche(void)//works with linux
        {
            struct termios oldattr, newattr;
            int ch;
            tcgetattr( STDIN_FILENO, &oldattr );
            newattr = oldattr;
            newattr.c_lflag &= ~( ICANON | ECHO);//shell out to kill echo
            tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
            system("stty -echo");//shell out to kill echo
            ch = getchar();
            system("stty echo");
            tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
            return ch;
        }

/*Clears a the number of characters passed to it as parameter n*/
extern void letter_clear(int n)
    {
        int i;
        for(i=1;i<=n;i++)
            printf("\b \b");//implementing a destructive backspace
    }



unsigned int is_integral(char number[], int argc_cmd)
{
    //printf("%s\n", number);
    int i = 0;
    if(number==NULL)
    {
        fprintf(stderr, "%s\n", "Fatal Error: Null argument");
        exit(EXIT_FAILURE);
    }
  /*  if(my_atoi(number)==0)
    {
        fprintf(stderr, "%s\n", "Fatal Error: Lesson number cannot be zero");
        exit(EXIT_FAILURE);
    }*/
    //checking for negative numbers
    if (number[0] == '-')
    {
        fprintf(stderr, "%s\n", "Fatal error: Negative argument");
        exit(EXIT_FAILURE);
    }
    if(argc_cmd==4)
    {
        if(strlen(number)<2||my_atoi(number)<10||my_atoi(number)>900)
        {
            fprintf(stderr, "%s\n", "Fatal Error: Either argument is not in range <45-900> OR argument is invalid");
            exit(EXIT_FAILURE);
        }
    }
    else
    if(strlen(number)>2||my_atoi(number)>50||my_atoi(number)<1)
    {
        fprintf(stderr, "%s\n", "Fatal Error: Argument not in range <1-50> OR invalid");
        exit(EXIT_FAILURE);
    }
    return my_atoi(number);//returns the unsigned integral string entered as argument at terminal
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


//windows virtual command line; produces command line environment while in the program.
//char v_cmd[81][81];//2d virtual array to hold the arguments as they are entered.
//added an argument, to be removed if does not work and line 152 modified
extern int win_cmd_arg(char **v_cmd, char *temp)
{
    printf("%s","%%noslac$>>");
    char win_str[300];
	int i=0,argc=0,j=0,u=0;	
	
	fgets(win_str,250,stdin);//reading arguments, uses \n to flush
	if(strlen(win_str)>177||u>=15)//ensures the arguments are not more than 15 and size does not exceed 177
	{
		fprintf(stderr,"%s\n", "Invalid number of arguments");
		exit(EXIT_FAILURE);
	}
	do
	{
		temp[j]=win_str[i];
		if(temp[j]=='\n'||temp[j]==' ')
		{
			temp[j]='\0';
			j=-1;	
			v_cmd[u]=temp;
		//	printf("u=%d, j=%d, i=%d v_cmd=%s\n",u,j,i,v_cmd[u]);	
			//getchar();
			if(temp[j]=='\n')
				break;	
			u++;
		}
		//printf("temp j=%d\n",j);
		j++;		
		i++;
	}while(win_str[i]!=EOF);	
	return u-1;//first element has index 0
}

