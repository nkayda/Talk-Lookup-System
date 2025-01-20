// Name: Natalie Kayda
// Student ID:
// Computing ID:

#include "a3_talklib.h"

/*QUESTION CITATIONS:

- main() code is my a3 submission

- helper functions in a3_talklib.c is what was provided in
    the assignment page

- ASCII art for the scroll was based on:
    https://www.asciiart.eu/art-and-design/borders
    (5th from the top)

- file opening/reading code is based on lect live coding demo code

- learned more about reading from a file through:
https://www.learnc.net/c-tutorial/c-read-text-file/

- figured out while loop from live coding demo, and do-while loop from:
https://www.w3schools.com/cpp/cpp_do_while_loop.asp

- fixed fopen() issue with:
https://stackoverflow.com/questions/13127020/why-is-my-file-pointer-causing-an-undefined-symbol-error

- to understand the returned value of fopen():
https://www.w3resource.com/c-programming/stdio/c_library_method_fopen.php

- for more info on qsort():
https://www.tutorialspoint.com/c_standard_library/c_function_qsort.htm
https://www.educative.io/answers/what-is-the-qsort-function-in-c

- to understand how to access struct variables when passing their struct as a parameter:
https://stackoverflow.com/questions/53465147/writing-a-compare-function-for-a-structure-for-qsort
https://stackoverflow.com/questions/6105513/need-help-using-qsort-with-an-array-of-structs

- info on using getchar() after scanf() to let fgets work, and how to use fgets():
https://www.sololearn.com/Discuss/2154299/why-fgets-gets-skipping-the-1st-input-string

- to understand that to remove the last element in an array i must make a new one where the size
is one less
https://stackoverflow.com/questions/32933042/remove-the-last-element-inside-an-array

- info on strcmp():
https://www.programiz.com/c-programming/library-function/string.h/strcmp 

*/

int main()
{
    // header creation
    printf("   ______________________________\n");
    printf("  / \\                             \\\n");
    printf(" |   |                            |\n");
    printf("  \\_ |  ~ Greetings, traveller. ~ |\n");
    printf("     |                            |\n");
    printf("     |    Welcome to Ye Olde CS   |\n");
    printf("     |     Talks Magic Scroll.    |\n");
    printf("     |                            |\n");
    printf("     |         (digitized!)       |\n");
    printf("     |                            |\n");
    printf("     |        Natalie Kayda       |\n");
    printf("     |          301544798         |\n");
    printf("     |         nka85@sfu.ca       |\n");
    printf("     |                            |\n");
    printf("     |   _________________________|___\n");
    printf("     |  /                            /\n");
    printf("     \\_/____________________________/\n");
    printf("\n");

    //------SET UP------

    // init starting capacity
    int capacity = 16;

    // init array that stores each Talk
    Talk **talkArrayTemp = (Talk **)malloc(sizeof(Talk *) * capacity);
    Talk **talkArray;

    // opens txt file
    FILE *filePtr;

    // init buffer for the "===" that separates the entries
    char border[128];

    // init the repeats/size of the talkArray
    int num = 0;

    // buffer for headers in the txt file
    char excessText[128];

    // starting value for duration to ensure the while works correctly
    int duration[] = {-1, -1, -1};

    // stores user input for option selection
    int choice;

    do
    {
        printf("Press number 1-5 for the following options and then enter:\n");
        printf("1) to load a talks file.\n2) to list talks sorted by duration.\n");
        printf("3) to list talks sorted by title.\n4) to look up a talk.\n");
        printf("5) to terminate the program.\nOption: ");
        scanf("%d", &choice);
        getchar(); // handles last \n

        if (choice == 1) // choose a talks file and load entries
        {
            printf("Enter the full name of the talks file (with extension): ");

            // input storage var created, then stores input
            char loadedFile[50];
            scanf("%s", loadedFile);

            // opens given file
            filePtr = fopen(loadedFile, "r");

            // if file found successfully, do code snipper
            if (filePtr != NULL)
            {
                // takes txt file content and adds to talkArray dynamically
                while (duration[0] != 0 && duration[1] != 0 && duration[2] != 0)
                {
                    // reads each entry and store accordingly, same as my A2
                    fgets(excessText, 15, filePtr);
                    duration[0] = 0;
                    duration[1] = 0;
                    duration[2] = 0;
                    fscanf(filePtr, "%d hour, %d minutes, %d seconds%*c", &duration[0],
                           &duration[1], &duration[2]);
                    fgets(excessText, 18, filePtr);
                    char title[128];
                    fgets(title, 128, filePtr);
                    title[strlen(title) - 2] = '\0';
                    fgets(excessText, 15, filePtr);
                    char overview[300];
                    fgets(overview, 300, filePtr);
                    talkArrayTemp[num] = createTalk(duration[0], duration[1], duration[2],
                                                    title, overview);
                    num = num + 1;

                    // accounts for dynamic mem allocation
                    if (num == capacity)
                    {
                        capacity *= 2;
                        talkArrayTemp = (Talk **)realloc(talkArrayTemp, sizeof(Talk *) * capacity);
                    }
                    fscanf(filePtr, "%s\n", border);
                }

                // makes new array exclduing the last, incomplete entry due to reaching EOF
                talkArray = malloc(sizeof(talkArrayTemp));
                memcpy(talkArray, talkArrayTemp, sizeof(Talk *) * (num - 1));

                // specifies the real and valid num of elements in array
                num--;

                printf("%d entries read.\n", num);
                printf("-----------------------------------------\n");
            }
            else if (strstr(".txt", loadedFile) == NULL)
            {
                // if the input does not have the proper extension, error
                printf("Error in opening the file, check if it is available.\n");
                printf("-----------------------------------------\n");
            }
            else
            {
                // if the file cannot be found
                printf("Error in opening the file, check if it is available.\n");
                printf("-----------------------------------------\n");
            }
        }

        else if (choice == 2) // list talks sorted by duration
        {
            if (filePtr == NULL) //if file does not exist/hasnt been loaded
            {
                printf("Error accessing file. No file has been loaded.\nLoad a file to use this option.\n");
                printf("-----------------------------------------\n");
            }
            else
            {
                //sort shortest to longest duration
                qsort(talkArray, num, sizeof(Talk *), compareTalksByDuration);
                printTalks(talkArray, num); // no need for num-1 as printTalk has that built in!
                printf("-----------------------------------------\n");
            }
        }

        else if (choice == 3) // list talks sorted by title
        {
            if (filePtr == NULL)  //if file does not exist/hasnt been loaded
            {
                printf("Error accessing file. No file has been loaded.\nLoad a file to use this option.\n");
                printf("-----------------------------------------\n");
                break;
            }
            else
            {
                qsort(talkArray, num, sizeof(Talk *), compareTalksByTitle);
                printTalks(talkArray, num);
                printf("-----------------------------------------\n");
            }
        }

        else if (choice == 4) // lookup a talk
        {
            // if file not found, indicate error else run option 4
            if (filePtr == NULL)
            {
                printf("Error accessing file. No file has been loaded.\nLoad a file to use this option.\n");
                printf("-----------------------------------------\n");
            }
            else
            {
                // stores input
                char lookUp[51];
                printf("What is the title of the talk, enter in part or as a whole (50 char. max.)?\n");

                // takes user input from terminal then stores in lookUp*
                fgets(lookUp, 50, stdin);

                // finds length of input
                // then adds terminating char to remove extra \n char
                int cut = strlen(lookUp);
                lookUp[cut - 1] = '\0';

                // calls actual lookup function to print found talks
                lookupTalkByTitle(talkArray, num, lookUp);
            }
        }

        // terminates program
        else if (choice == 5)
        {
            printf("Thank you and goodbye!\n");
        }

        // invalid entry error
        else
        {
            printf("Unrecognized selection. Try again.\n");
            printf("-----------------------------------------\n");
        }

    } while (choice != 5); // runs unless input is 5

    // if there is an open file, close it
    if (filePtr != NULL)
    {
        fclose(filePtr);
    }

    // frees talkArray and handles dangling pointer
    for (int i = 0; i < num; i++)
    {
        clearTalk(talkArray[i]);
        free(talkArray[i]);
        talkArray[i] = NULL;
    }

    clearTalk(talkArray[num + 1]);
    free(talkArray[num + 1]);
    talkArray[num + 1] = NULL;

    talkArray = NULL;

    return 0;
}