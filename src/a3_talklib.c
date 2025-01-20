//Name: Natalie Kayda
//Student ID:
//Computing ID:

#include "a3_talklib.h"

// sample solution to the createTalk function
// source: assignment page
Talk *createTalk(short hours, short minutes, short seconds,
                 const char *title, const char *overview)
{
    Talk *newTalk = (Talk *)malloc(sizeof(Talk));

    // only access memeber values if memory is successfully allocated
    if (newTalk != NULL)
    {
        newTalk->hours = hours;
        newTalk->minutes = minutes;
        newTalk->seconds = seconds;
        // create a deep copy of title, don't forget size is lenght+1
        newTalk->title = (char *)malloc(sizeof(char) * (strlen(title) + 1));
        if (newTalk->title != NULL)
        {
            strcpy(newTalk->title, title);
        }
        else
        { // can't allocate enough memory for title, free everything
            free(newTalk);
            return NULL;
        }
        // create a deep copy of overview, don't forget size is length+1
        newTalk->overview = (char *)malloc(sizeof(char) * (strlen(overview) + 1));
        if (newTalk->overview != NULL)
        {
            strcpy(newTalk->overview, overview);
        }
        else
        { // can't allocate enough memory for overview, free everything
            free(newTalk->title);
            free(newTalk);
            return NULL;
        }
    }
    return newTalk;
}

// sample solution to the clearTalk function.
// source: assignment page
void clearTalk(Talk *talk)
{
    if (talk != NULL)
    {
        talk->hours = -1;
        talk->minutes = -1;
        talk->seconds = -1;
        free(talk->title);
        talk->title = NULL;
        free(talk->overview);
        talk->overview = NULL;
    }
}

int *lookupTalkByTitle(Talk **array, int size, const char *title)
{
    // return variable, unused because no return value is truly needed
    int *index = 0;

    // keeps track of how many talks were successfully found
    int count = 0;

    // runs through the elements in the array
    for (int i = 0; i < size; i++)
    {
        // stores location of title in array[i]-> title if there is one
        // stores NULL otherwise
        char *location = strstr(array[i]->title, title);

        if (location != NULL) // if substring successfully found, print talk
        {
            printf("-----------------------------------------\n");
            printf("Talk #%d:\n", count + 1);
            printf("%dh%dm%ds\n", array[i]->hours, array[i]->minutes,
                   array[i]->seconds);
            printf("%s\n", array[i]->title);
            printf("%s", array[i]->overview);

            count++; // adds to success counter
        }
    }

    // if no successes, print
    if (count == 0)
        printf("No such talk on record.\n");

    // divider
    printf("-----------------------------------------\n");

    return index;
}

int compareTalksByDuration(const void *p1, const void *p2)
{
    // creates local variables storing the values given as args
    // by casting p1 and p2 to type Talk** (as that is the type of the array
    // actually passed to qsort) then dereferencing the Talk* stored as an
    // element in talkArray
    Talk* elementOne = *((Talk **)p1);
    Talk* elementTwo = *((Talk **)p2);

    if (elementOne->hours < elementTwo->hours)
    { //compare the hours length
        printf("HOURS: %d comes before %d\n", elementOne->hours, elementTwo->hours);
        return -1; // tell qsort that p1 comes before p2
    }
    else if (elementOne->hours > elementTwo->hours)
    { //compare the hours length
        printf("HOURS: %d comes before %d\n", elementTwo->hours, elementOne->hours);
        return 1;
    }
    else // they have the same hour length
    {
        if (elementOne->minutes < elementTwo->minutes)
        { //compare the minutes length
            printf("MIN: %d comes before %d\n", elementOne->minutes, elementTwo->minutes);
            return -1;
        }
        else if (elementOne->minutes > elementTwo->minutes)
        { //compare the minutes length
            printf("MIN: %d comes before %d\n", elementTwo->minutes, elementOne->minutes);
            return 1;
        }
        else // hours AND minutes are both the same
        {
            if (elementOne->seconds < elementTwo->seconds)
            { //compare the seconds length
                printf("MIN: %d comes before %d\n", elementOne->seconds, elementTwo->seconds);
                return -1;
            } //compare the seconds length
            else if (elementOne->seconds > elementTwo->seconds)
            {
                printf("MIN: %d comes before %d\n", elementTwo->seconds, elementOne->seconds);
                return 1;
            }
        }
    }
    
    //they are the same otherwise
    return 0;
}

int compareTalksByTitle(const void *p1, const void *p2)
{
    // same as above
    Talk *elementOne = *((Talk **)p1);
    Talk *elementTwo = *((Talk **)p2);

    // determines which title field in each Talk struct comes first
    // returns either positive or negative number that can be used by qsort()
    return strcmp(elementOne->title, elementTwo->title);
}

// simply runs though the Talks in the given array and prints each field out
void printTalks(Talk **talkArray, int num)
{
    for (int i = 0; i < num; i++)
    {
        printf("-----------------------------------------\n");
        printf("Talk #%d:\n", i + 1);
        printf("%dh%dm%ds\n", talkArray[i]->hours, talkArray[i]->minutes,
               talkArray[i]->seconds);
        printf("%s\n", talkArray[i]->title);
        printf("%s", talkArray[i]->overview);
    }
}