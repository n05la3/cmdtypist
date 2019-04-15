//display.h:name and session display

/*
Program title: CMDTYPIST
Author: Chiatiah Calson
License: GPL 3 or later versions
Date and Time: 5 July 2017 @ 10:40PM
Program Size: 2.8
*/

/*implementing a function to display the 
name of the program.*/
extern void name_display(void)
{
	system("clear");
	printf("\n\n\n\t\t%s  %s  %s   %s","+*******", "+**********+", "+****",       "\t+**********+\n");
    printf("\t\t%s  %s  %s %s","|*******", "|**********|", "|***+*",        " \t|**********|\n");
    printf("\t\t%s  %s  %s %s","**", "      **   **   **",  "**   **",      "\t     **\n");
    printf("\t\t%s  %s  %s %s","**", "      **   **   **",  "**    **",     "\t     **\n");
    printf("\t\t%s  %s  %s %s","**", "      **   **   **",  "**    **",     "\t     **\n");
    printf("\t\t%s  %s  %s %s","**", "      **   **   **",  "**    **",     "\t     **\n");
    printf("\t\t%s  %s  %s%s","|*******", "|*   **   *|", "|*******",       "\t     **\n");
    printf("\t\t%s  %s  %s%s","+*******", "+*        *+", "+******",        "\t             ++\n");
    printf("\n\n%s\n\n", "                    cmd typist: Where programmers type!!!");
    sleepf(1);
}

extern short guess(int min, int max)
{
	srand((unsigned)time(NULL));
	return (rand() % min) + max;
}

extern void lesson_list(void)
	{
		unsigned short n = guess(22,0);
		system("clear");
		puts("LESSONS, use command <select 'lesson number' to make a choice: "
			"\n1:  Beginner lessons"
			"\n2:  Shell programming"
			"\n3:  Linux commands"
			"\n4:  Cmd commands"
			"\n5:  Learning numbers"
			"\n6:  Noslac's notes in computing"
			"\n7:  History of Cameroon"
			"\n8:  Getting acquanted to symbols"
			"\n9:  Coding in c"
			"\n10: Coding in java"
			"\n11: Coding in python"
			"\n12: Coding in c++"
			"\n13: Random word typing"
			"\n14: Capital letter training"
			"\n15: Mixed lessons");
		printf(""TIP_COLOR"");
			switch(n)
			{
				case 1:
					printf("%s", ":: Go over your session speed analysis, \'time starts ONLY when you start\'\n");
					break;
				case 2:
					printf("%s",":: All the lessons in this program are informative, type and learn!!!\n");
					break;
				case 3:
					printf("%s",":: When a line in session turns blue, that's last line for that session\n");
					break;
				case 4:
					printf("%s",":: Consult the user_speed.info file to get your saved speed details\n");
					break;
				case 5: 
					printf("%s",":: Use the \"help 'command'\" to get details of any command when in doubt\n");
					break;
				case 6:
					printf("%s\n",":: Use tab key during lesson session to exit and get your instant speed");
					break;
				case 7:
					printf("%s\n",":: Focus much more on your accuracy, you'll get better");
					break;
				case 8:
					printf("%s\n",":: If a novice typist, say the letters as you type. Will help you memorise faster");
					break;
				case 9: 
					printf("%s\n", ":: Writing manually to the user info file distorts display!!!");
					break;
				case 10:
					printf("%s\n", ":: Use ENTER at the end of a line to move to next line");
					break;
				case 11:
					printf("%s\n", ":: Feel free to use backspace key to erase wrongly typed letters");
					break;				
				case 12:
					printf("%s\n", ":: Paste your own lesosn in myown.txt in program directory and type");
					break;
				case 13:
					printf("%s",":: You will only get better if you type more\n" );
					break;
				case 14:
					printf("%s",":: Love cmdtypist? give me a * on github www.github.com/cmd_typist \n" );
					break;
				case 15:
					printf("%s",":: You will get to master symbols mostly used by programmers \n" );
					break;
				case 16:
					printf("%s",":: You will progress only if you type more often \n" );
					break;
				case 17:
					printf("%s",":: With random mode the lessons might no longer make sense ): \n" );
					break;
				case 18:
					printf("%s",":: standard mode: lessons appear as they are in lesson file. random mode: cmdtypist makes a guess and reads anywhere :) \n" );
					break;
				case 19:
					printf("%s",":: 365+ days from now, you can wonder at how slow you were when you started. Analysis store in speed/user_speed.info file\n" );
					break;
				case 20:
					printf("%s",":: Found a bug? you can help fix it or lemme know on github\n" );
					break;
				case 21:
					printf("%s",":: Enjoy cmdtypist? Why not share with your friends\n" );
					break;
				default:
					printf("%s",":: You will only get better if you type more\n" );
					break;
			}		
		printf(""RESET"");	
	}


//modifies the manner in which sesson speed is displayed
//5 is the accepted average number of letters in a word	
void session_style(unsigned int session_time,int wrongly_typed,float typed)
{
	float raw_speed=0.0,adj_speed=0.0;
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
	raw_speed= ((float) typed*60.0f)/(float)session_time;
	adj_speed= (float) ((typed-wrongly_typed)*60.0f)/(float)session_time;
	char time_conversion[36];//stores converted time by seconds_hms()
	system("clear");
	printf(""RESET"\n%s\n", "For better speed follow up, consult \"user_speed.info\" file in speed directory");
	puts("-------------------------------+-----------+------------------------------------");
	puts("-------------------------------SESSION SPEED------------------------------------");//printing session heading
	puts("-------------------------------+-----------+------------------------------------");
	printf("**************                                                     *************\n");
	fprintf(stdout, "\t+----------------- %s --------------------+\n", time_nw);//printing date and time when the test is done
	seconds_to_hms(session_time,time_conversion);
	//fprintf(fp, "\t|%d%s TIME: %s\n",wrongly_typed,(wrongly_typed==0)? "(NO Error)":(wrongly_typed==1)? "ERROR":"ERRORS",time_conversion);
	raw_speed= ((float) typed*60.0f)/(float)session_time;
	adj_speed= (float) ((typed-wrongly_typed)*60.0)/(float)session_time;		
	fprintf(stdout, "\t|ERROR(s):"RED"%u"RESET" TIME: "SPEED_COLOR"%s"RESET" Accuracy: "SPEED_COLOR"%.2f%%"RESET"\n",wrongly_typed,time_conversion,(adj_speed/raw_speed)*100.0f);
	fprintf(stdout, "\t|%s"SPEED_COLOR"%.2fCPM"RESET" ~= "GREEN"%.2fWPM"RESET" \n", "AVERAGE SPEED: ",adj_speed,adj_speed/5.0f);
	fprintf(stdout, "%s\n\n", "\t+---------------------------------------------------------------+");
}


