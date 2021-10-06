#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define True 1
#define False 0
/*TODO
maybe reduce main size
finish comments

DONE
everything else
*/

int length(char str[])
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

int compare_str(char str1[], char str2[])
{
    int error = False;
    int i = 0;
    if (length(str1) != length(str2))
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

//will return a password back, if meets the conditions
int level1(char str[])
{
    int lower_case = False;
    int upper_case = False;
    for (int i = 0; i < length(str); i++) //loop to check the string for upper/lower case letters       
    {
        if (str[i] > 96 && str[i] < 123)
        {
            lower_case = True;
        }
        else if (str[i] > 64 && str[i] < 91)
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
    int groupD = False; //check for simpler way
    for (int i = 0; i < length(str); i++) //loop to check the string for upper/lower case letters
    {
        if (str[i] > 32 && str[i] < 127)
        {
            if (str[i] > 96 && str[i] < 123)
            {
                groupA = True;
            } 
            else if (str[i] > 64 && str[i] < 91)
            {
                groupB = True;
            }
            else if (str[i] > 47 && str[i] < 58)
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
    char a;     //variables to compare str[i] to str[i+1], for better visibility
    char b;
    long long count = 1;
    long long max_count = 0;
    for (int i = 0; i < (length(str)); i++)
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
	for (int i = 0; i < length(str) - parameter + 1; i++)
	{
        //Moving the string that is being compared to the original one
        for (int z = 0; z < length(str) - 1 - i; z++)
        {
            error_count = 0;
            //comparing all the substrings
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

int Collect_chars(char str[])
{
    static int chars[128];
    static int current;
    for (int i = 0; i < length(str); i++)
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


int main(int argc, char *argv[])
{
    //variables used in the main part
    if (argc > 4 || argc < 3)
    {
        fprintf(stderr, "Zadany spatny pocet argumentu\n");
        return 1;
    }
    char *ptr, *ptr2;
    int security = strtol(argv[1], &ptr, 10); 
    long long param = strtoll(argv[2], &ptr2, 10);
    if (*ptr || *ptr2|| security < 1 || security > 4 || param < 1 || !compare_str(argv[3], "--stats"))
    {
        fprintf(stderr, "spatne zadane argumenty");
        return 1;
    }
    char str[102] = ""; //for password
    //variables used for stats
    int stats = False;
    int min = 101;
    int total_count = 0;
    int total_length = 0;
    double avg;
    int number_of_chars;
    
    if (compare_str(argv[3], "--stats"))
    {
        stats = True;
    }
    while (fgets(str, 103, stdin) != NULL)
    {
        // length check
        if (length(str) > 100)
        {
            fprintf(stderr, "Zadane heslo presahuje 100 znakov\n");
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
        //stats part
        if (stats == True)
        {
            total_count += 1;
            total_length += length(str);
            //check for min length
            if (length(str) < min)
            {
                min = length(str);
            }
            avg = (double)total_length/(double)total_count; //avg length
            number_of_chars = Collect_chars(str);
        }
    }
    if (stats == True)
    {
        printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", number_of_chars, min, avg);
    }
    return 0;
}

  
