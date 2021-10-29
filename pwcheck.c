#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Returns a string length
int str_length(char str[]) {
    int len = 0;
    while (str[len] != '\0' && str[len] != '\n') {
        len++;
    }
    return len;
}

// A function to compare whether two strings are the same
bool compare_str(char str1[], char str2[]) {
    bool error = false;
    int i = 0;
    if (str_length(str1) != str_length(str2)) {
        return false;
    }
    while (str1[i] != '\0' || str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            error = true;
            break;
        } else {
            i++;
        }
    }
    return !error;
}

// Block of functions that handle single security levels
bool level1(char str[]) {
    bool lower_case = false;
    bool upper_case = false;
    // Loop to check the string for upper/lower case letters
    for (int i = 0; i < str_length(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            lower_case = true;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            upper_case = true;
        }
    }
    if (lower_case == true && upper_case == true) {
        return true;
    } else {
        return false;
    }
}

bool level2(char str[], long parameter) {
    bool groupA = false;
    bool groupB = false;
    bool groupC = false;
    bool groupD = false;
    if (parameter > 4) {
        parameter = 4;
    }
    // Loop to check the string for each of the character groups
    for (int i = 0; i < str_length(str); i++) {
        if (str[i] >= ' ' && str[i] <= '~') {
            if (str[i] >= 'a' && str[i] <= 'z') {
                groupA = true;
            } else if (str[i] >= 'A' && str[i] <= 'Z') {
                groupB = true;
            } else if (str[i] >= '0' && str[i] <= '9') {
                groupC = true;
            } else {
                groupD = true;
            }
        }
    }
    // Checks if number of met conditions is >= than the parameter
    if ((groupA + groupB + groupC + groupD) >= parameter) {
        return level1(str);
    } else {
        return false;
    }
}

bool level3(char str[], long parameter) {
    // Variables to compare str[i] to str[i+1], for better visibility
    char a, b;
    int count = 1;
    int max_count = 0;
    for (int i = 0; i < (str_length(str)); i++) {
        a = str[i];
        b = str[i + 1];
        if (a == b) {
            // counts the length of the sequence of the same chars
            count++;
        } else {
            if (count > max_count) {
                max_count = count;
            }
            count = 1;
        }
    }
    if (max_count < parameter) {
        return level2(str, parameter);
    } else {
        return false;
    }
}

bool level4(char str[], int parameter) {
    int error_count;
    char temp[102] = {'0'};
    // Moves the original substring of parameter length through the password
    for (int org_str_iter = 0; org_str_iter < str_length(str) - parameter;
         org_str_iter++) {
        // Moving the string that is being compared to the substring
        for (int substr_iter = 1;
             substr_iter < str_length(str) - parameter - org_str_iter + 1;
             substr_iter++) {
            error_count = 0;
            for (long temp_iter = 0; temp_iter < parameter; temp_iter++) {
                temp[temp_iter] = str[substr_iter + org_str_iter + temp_iter];
                if (str[org_str_iter + temp_iter] == temp[temp_iter]) {
                    error_count++;
                }
                // If error_count >= parameter, that means the equal substrings
                // length is same/bigger than the parameter => password doesn't
                // pass this test
                if (error_count == parameter) {
                    return false;
                }
            }
        }
    }
    return level3(str, parameter);
}

// Keeps track of unique chars used in passwords
void collect_chars(char str[], int chars[], int *current) {
    for (int i = 0; i < str_length(str); i++) {
        bool appears = false;
        // Loops through the array of chars, if str[i] is already there, then
        // it's not needed to be added
        for (int j = 0; j < 128; j++) {
            if (str[i] == chars[j]) {
                appears = true;
            }
        }
        // If the char in str[i] isn't in the array, it's added here and count
        // of chars already added is incremented
        if (!appears) {
            chars[*current] = str[i];
            *current += 1;
        }
    }
}

// Keeps track of passwords length
void length_stats(char str[], double *pw_count, double *total_length,
                  int *curr_min) {
    *pw_count += 1;
    *total_length += str_length(str);

    // Compares length of current password to the current minimum
    if (*curr_min > str_length(str)) {
        *curr_min = str_length(str);
    }
}

// Checks the arguments whether they're valid
bool check_args(int argc, int **security, long **param) {
    if (argc > 6) {
        return false;
    }
    if (**security < 1 || **security > 4) {
        return false;
    }
    if (**param < 1) {
        return false;
    }
    return true;
}

// Checks if the arguments are valid compared to the base argument parsing
// template
bool arg_handler(int argc, char *argv[], int *security, long *param,
                 bool *stats) {
    if (argc < 3 || argc > 4) {
        return false;
    }
    // To check whether arguments are numbers followed by other chars
    char *ptr_;
    char *ptr2_;
    *security = strtol(argv[1], &ptr_, 10);
    *param = strtol(argv[2], &ptr2_, 10);
    if (*ptr_ || *ptr2_) {
        return false;
    }
    // Compares each of the arguments to the template
    if (argc > 3) {
        if (!(compare_str(argv[3], "--stats") == true && argv[3] != NULL)) {
            return false;
        } else if (compare_str(argv[3], "--stats")) {
            *stats = true;
        }
    }
    // Called to check if the values gotten here are valid
    if (!check_args(argc, &security, &param)) {
        return false;
    }
    return true;
}

// Checks if the arguments are valid compared to the bonus argument parsing
// template
bool bonus_arg_handler(int argc, char *argv[], int *security, long *param,
                       bool *stats) {
    // To check whether arguments are numbers followed by other chars
    char *ptr3_;
    char *ptr4_;
    bool security_done = false;
    bool param_done = false;
    bool stats_done = false;
    // Compares each of the arguments to the bonus template
    for (int i = 1; i < argc; i++) {
        if (compare_str(argv[i], "-l") == true && !security_done &&
            ((i + 1) < argc)) {
            *security = strtol(argv[i + 1], &ptr3_, 10);
            i++;
            security_done = true;
            if (*ptr3_) {
                return false;
            }
        } else if (compare_str(argv[i], "-p") == true && !param_done &&
                   ((i + 1) < argc)) {
            *param = strtol(argv[i + 1], &ptr4_, 10);
            i++;
            param_done = true;
            if (*ptr4_) {
                return false;
            }
        } else if (compare_str(argv[i], "--stats") == true && !stats_done) {
            stats_done = true;
            *stats = true;
        } else {
            return false;
        }
    }
    // Called to check if the values gotten here are valid
    if (!check_args(argc, &security, &param)) {
        return false;
    }
    return true;
}

void print_correct_pw(char str[], long param, int security) {
    bool passed = false;
    switch (security) {
        case 1:
            passed = level1(str);
            break;
        case 2:
            passed = level2(str, param);
            break;
        case 3:
            passed = level3(str, param);
            break;
        case 4:
            passed = level4(str, param);
            break;
    }
    if (passed == true) {
        printf("%s", str);
    }
}

int main(int argc, char *argv[]) {
    int security;
    long param;
    bool stats = false;
    // First checks if base template works
    bool check_args = arg_handler(argc, argv, &security, &param, &stats);
    // If not, resets the values to default and checks if bonus template works
    if (check_args == false) {
        security = 1;
        param = 1;
        stats = false;
    }
    bool check_bonus_args =
        bonus_arg_handler(argc, argv, &security, &param, &stats);
    // Returns error if neither of the templates work
    if (check_args == false && check_bonus_args == false) {
        fprintf(stderr, "Wrong command line arguments");
        return 1;
    }
    char str[102] = "";
    // Variables used for stats
    int curr_min = 101;
    double total_length;
    double pw_count;
    int chars[255] = {-1};
    int current = 0;
    // 103 because of how my str_length() works
    while (fgets(str, 102, stdin) != NULL) {
        if (str_length(str) > 100) {
            fprintf(stderr, "The password exceeds the maximal length!\n");
            return 2;
        }
        print_correct_pw(str, param, security);
        if (stats == true) {
            collect_chars(str, chars, &current);
            length_stats(str, &pw_count, &total_length, &curr_min);
        }
    }
    if (stats == true) {
        printf(
            "Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna "
            "delka: %.1f\n",
            current, curr_min, total_length / pw_count);
    }
    return 0;
}

