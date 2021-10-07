#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define True 1
#define False 0

/*TODO
Bonus points
Finish comments

DONE
Basically everything
*/

//Returns a string length
int str_length(char str[])
{
    if (str == NULL)
    {
        return 0;
    }
    int len = 0;
    while(str[len] != '\0')
    {
        len++;
    }
    return len - 1;
}

//A function to compare whether two strings are the same
int compare_str(char str1[], char str2[])
{
    int error = False;
    int i = 0;
    if (str_length(str1) != str_length(str2))
    {
        return False;
    }
    while (str1[i] != '\0' || str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            error = True;
            break;
        }
        else
        {
            i += 1;
        }
    }
    return !error;
}

//Block of functions that handle single security levels
int level1(char str[])
{
    int lower_case = False;
    int upper_case = False;
    //Loop to check the string for upper/lower case letters
    for (int i = 0; i < str_length(str); i++)        
    {
        if (str[i] >= 'a'  && str[i] <= 'z')
        {
            lower_case = True;
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            upper_case = True;
        }
    }
    if (lower_case == True && upper_case == True)
    {
        return True;
    }
    else
    {
        return False;
    }

}

int level2(char str[], long long parameter)
{
    int groupA = False;
    int groupB = False;
    int groupC = False;
    int groupD = False;
    //Loop to check the string for upper/lower case letters
    for (int i = 0; i < str_length(str); i++)
    {
        if (str[i] >= '!' && str[i] <= '~')
        {
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                groupA = True;
            } 
            else if (str[i] >= 'A' && str[i] <= 'Z')
            {
                groupB = True;
            }
            else if (str[i] >= '0' && str[i] <= '9')
            {
                groupC = True;
            }
            else
            {
                groupD = True;
            }
        }   
    }
    if ((groupA + groupB + groupC + groupD) >= parameter)
    {
        return True;
    }
    else
    {
        return False;
    }

}

int level3(char str[], long long parameter)
{
    //Variables to compare str[i] to str[i+1], for better visibility
    char a, b;
    long long count = 1;
    long long max_count = 0;
    for (int i = 0; i < (str_length(str)); i++)
    {
        a = str[i];
        b = str[i+1];
        if (a == b)
        {
            count += 1;
        }
        else
        {
            if (count > max_count)
            {
                max_count = count;
            }
            count = 1;
        }
    }
    if (max_count < parameter)
    {
        return True;
    }
    else
    {
        return False;
    }
}

int level4(char str[], long long parameter)
{ 
	int error_count;
    char temp[102] = {'0'};
	//Moving the substring
	for (int i = 0; i < str_length(str) - parameter + 1; i++)
	{
        //Moving the string that is being compared to the original one
        for (int z = 0; z < str_length(str) - 1 - i; z++)
        {
            error_count = 0;
            //Comparing all the substrings
            for (long long y = 0; y < parameter; y++)
            {
                if (str[i+y-1] == temp[y])
                {
                    error_count += 1;
                }
                if (error_count == parameter)
                {
                    return False;
                }
            }
            for (long long j = 0; j < parameter; j++)
            {    
                temp[j] = str[j+z+i]; 
            }    
        } 
    }  
    return True;
}

//Keeps track of unique chars used in passwords
int Collect_chars(char str[])
{
    static int chars[128];
    static int current;
    for (int i = 0; i < str_length(str); i++)
    {
        int appears = False;
        for (int j = 0; j < 128; j++)
        {
            if (str[i] == chars[j])
            {
                appears = True;
            }
        }
        if (!appears)
        {
            chars[current] = str[i];
            current += 1;
        }
    }
    return current;
}

//Keeps track of passwords length
void Length_stats(char str[], double *avg, int *min)
{
    static double current;
    static double total_length;
    static int curr_min = 101;

    current += 1;
    total_length += str_length(str);
    *avg = total_length/current;

    if (curr_min > str_length(str))
    {
        curr_min = str_length(str);
    }

    *min = curr_min;
}

int Check_args(int argc, int **security, long long **param)
{
    if (argc > 6)
    {
        return False;
    }
    if (**security < 1 || **security > 4)
    {
        return False;
    }
    if (**param < 1)
    {
        return False;
    }
    return True;
}

int Arg_handler(int argc, char *argv[], int *security, long long *param, int *stats)
{
    if (argc < 3 || argc > 4)
    {
        return False;
    }
    char *ptr_;
    char *ptr2_;
    *security = strtol(argv[1], &ptr_, 10);
    *param = strtoll(argv[2], &ptr2_, 10);
    if (*ptr_ || *ptr2_)
    {
        return False;
    }
    if (argc > 3)
    {
        if (!(compare_str(argv[3], "--stats") == True && argv[3] != NULL))
        {
            return False;
        }
        else if (compare_str(argv[3], "--stats"))
        {
            *stats = True;
        }
    }
    if (!Check_args(argc, &security, &param))
    {
        return False;
    }
    return True;
}

int Bonus_arg_handler(int argc, char *argv[], int *security, long long *param, int *stats)
{
    char *ptr3_;
    char *ptr4_;
    int security_done = False;
    int param_done = False;
    int stats_done = False;
    for (int i = 1; i < argc; i++)
    {
        if (compare_str(argv[i], "-l") == True && !security_done && ((i+1) < argc))
        {
            *security = strtol(argv[i+1], &ptr3_, 10);
            i++;
            security_done = True;
            if (*ptr3_)
            {
                return False;
            }
        }
        else if (compare_str(argv[i], "-p") == True && !param_done && ((i+1) < argc))
        {
            *param = strtoll(argv[i+1], &ptr4_, 10);
            i++;
            param_done = True;
            if (*ptr4_)
            {
                return False;
            }
        }
        else if (compare_str(argv[i], "--stats") == True && !stats_done)
        {
            stats_done = True;
            *stats = True;
        }
        else
        {
            return False;
        }
    }
    if (!Check_args(argc, &security, &param))
    {
        return False;
    }
    return True;
}



int main(int argc, char *argv[])
{
    int security = 1;
    long long param = 1;
    int stats = False;
    int bool_args = Arg_handler(argc, argv, &security, &param, &stats);
    if (!bool_args)
    {
        security = 1;
        param = 1;
        stats = False;
    }
    int bool_bonus_args = Bonus_arg_handler(argc, argv, &security, &param, &stats);
    if (bool_args == False && bool_bonus_args == False)
    {
        fprintf(stderr, "Wrong command line arguments");
        return 1;
    }

    //To store password
    char str[102] = "";  
    //Variables used for stats
    int min;
    double avg;
    int number_of_chars;
    
    while (fgets(str, 103, stdin) != NULL)
    {
        //Length check
        if (str_length(str) > 100)
        {
            fprintf(stderr, "The password exceeds the maximal length!\n");
            return 1;
        } 
        if (security == 1 && level1(str) == True)
        {
            printf("%s", str);
        }
        if (security == 2 && level1(str) == True && level2(str, param) == True)
        {
            printf("%s", str);
        }
        if (security == 3 && level1(str) == True && level2(str, param) && level3(str, param) ==  True)
        {
            printf("%s",str);
        } 
        if (security == 4 && level1(str) == True && level2(str, param) && level3(str, param) ==  True && level4(str, param) == True)
        {
            printf("%s",str);
        }
        //Handling stats
        if (stats == True)
        {            
            number_of_chars = Collect_chars(str);
            Length_stats(str, &avg, &min);
        }
    }
    if (stats == True)
    {
        printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", number_of_chars, min, avg);
    }
    return 0;
}

  
