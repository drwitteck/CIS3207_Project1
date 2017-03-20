/*
 * --Name:				Derek Witteck
 * --Assignment:		Lab 1
 * --Version:			1
 * --Date:				January 23rd, 2017
 * --Due Date:			February 7th, 2017
 * --Section:			3207-002
 * --Instructor:		Professor Kwatny
 * --Lab Instructor:	Graeme Copeland
 * --Description:		Develop a C/C++ program in Linux that will create and open a file to be filled with
 * 						10 randomly generated records, each record with 120 fptr. This program will loop for a few
 * 						minutes, pulling out a random index and comparing it to what was saved in memory.
 * --File Name:			application.cpp
 * --Functions:			main(), fileOperations()
 */

//HEADER FILES
#include "application.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <sys/wait.h>
#include <cstring>

using namespace std;

//GLOBAL CONSTANTS
const int ROW_SIZE = 10;
const int COL_SIZE = 120;

//FUNCTION DECLARATIONS
char fileOperations();
char fileOperations2();

/*
 * --Function name:     fileOperations
 * --Description:       Creates a random array with 10 rows and 120 columns and fills it with random lower case fptr.
 *                      A data file is created and the random array is written to the data file. A random index is chosen
 *                      from the random array and is copied into a separate array that will be used to comparision with
 *                      the same index from the random array that was written to the file. This will all be wrapped in a
 *                      loop that will run continuously for a minute or two. This will allow the process to be running
 *                      while another process is started and running.
 * --Inputs:            None.
 * --Outputs:           None.
 * --Globals:           ROW_SIZE - the set row size for the random array.
 *                      COL_SIZE - the set column size for the random array.
 * --Returns:           Nothing.
 */
char fileOperations(){

    srand((unsigned int) time(NULL));
    int loopCount = 0;
    int i;
    FILE *fptr;


    //Write the records to a text file and repeat multiple times to allow the operation to run for a few minutes.
    while(loopCount < 1){

        //Initialize and fill an array with randomly generated lower case letters.
        char record[ROW_SIZE][COL_SIZE];
        for(i = 0; i < ROW_SIZE; ++i) {
            for(int j = 0; j < COL_SIZE; ++j) {
                record[i][j] = (char) (rand() % 26 + 'a');
            }
        }

        //Write the record to a file
        fptr = fopen("randomCharacters.txt", "w+");
        fwrite(record, sizeof(char), sizeof(record), fptr);
        fclose(fptr);

        //Generate a starting point for an index that will be randomly chosen from the record.
        int randomRecordIndex = (rand() % 10);

        //Initialize and fill an array to hold the 120 characters from the randomly selected index from record.
        char* indexToCompare = record[randomRecordIndex];
        for (i = 0; i < sizeof(indexToCompare); ++i) {
            indexToCompare[i] = record[randomRecordIndex][i];
        }

        //Find the spot in randomCharacters.txt where the random index starts
        int fileIndex = randomRecordIndex * 120;

        //Set a starting point in the data file to begin reading back a random index of 120 fptr
        fptr = fopen("randomCharacters.txt", "r");
        fseek(fptr, fileIndex, SEEK_SET);

        //Counter to start reading indexToCompare array from the beginning
        int indexToCompareStart = 0;

        //Read the random characters from the indexToCompare array and compare it with the same index from the randomCharacters.txt file
        for(i = fileIndex; i < (fileIndex + 120); i++) {
            char current = (char) fgetc(fptr);
            //cout << "Current character being read by file reader: " << current << endl;
            if (current != indexToCompare[indexToCompareStart]) {
                cout << "Character does not match" << endl;
                return 0;
            } else {
                //cout << "Current character being read from indexToCompare array: " << indexToCompare[indexToCompareStart] << endl;
                indexToCompareStart++;
                cout << "Comparison successful!" << endl;
                continue;
            }
        }

        cout << "File operation complete" << endl;
        cout << "********************************************************************************" << endl;

        fclose(fptr);
        ++loopCount;

    }

    return (EXIT_SUCCESS);
}

/*
 * --Function name:     fileOperations2
 * --Description:       Creates a random array with 10 rows and 120 columns and fills it with random lower case fptr.
 *                      A data file is created, separate from fileOperations.cpp and the random array is written to the
 *                      data file. A random index is chosen from the random array and is copied into a separate array that
 *                      will be used to comparision with the same index from the random array that was written to the file.
 *                      This will all be wrapped in a loop that will run continuously for a minute or two. This will allow
 *                      the process to be running while another process is started and running.
 * --Inputs:            None.
 * --Outputs:           None.
 * --Globals:           ROW_SIZE - the set row size for the random array.
 *                      COL_SIZE - the set column size for the random array.
 * --Returns:           Nothing.
 */
char fileOperations2(){

    srand((unsigned int) time(NULL));
    int loopCount = 0;
    int i;
    FILE *fptr;


    //Write the records to a text file and repeat multiple times to allow the operation to run for a few minutes.
    while(loopCount < 1){

        //Initialize and fill an array with randomly generated lower case letters.
        char record[ROW_SIZE][COL_SIZE];
        for(i = 0; i < ROW_SIZE; ++i) {
            for(int j = 0; j < COL_SIZE; ++j) {
                record[i][j] = (char) (rand() % 26 + 'a');
            }
        }

        //Write the record to a file
        fptr = fopen("randomCharacters2.txt", "w+");
        fwrite(record, sizeof(char), sizeof(record), fptr);
        fclose(fptr);

        //Generate a starting point for an index that will be randomly chosen from the record.
        int randomRecordIndex = (rand() % 10);

        //Initialize and fill an array to hold the 120 characters from the randomly selected index from record.
        char* indexToCompare = record[randomRecordIndex];
        for (i = 0; i < sizeof(indexToCompare); ++i) {
            indexToCompare[i] = record[randomRecordIndex][i];
        }

        //Find the spot in randomCharacters.txt where the random index starts
        int fileIndex = randomRecordIndex * 120;

        //Set a starting point in the data file to begin reading back a random index of 120 fptr
        fptr = fopen("randomCharacters.txt", "r");
        fseek(fptr, fileIndex, SEEK_SET);

        //Counter to start reading indexToCompare array from the beginning
        int indexToCompareStart = 0;

        //Read the random characters from the indexToCompare array and compare it with the same index from the randomCharacters.txt file
        for(i = fileIndex; i < (fileIndex + 120); i++) {
            char current = (char) fgetc(fptr);
            //cout << "Current character being read by file reader: " << current << endl;
            if (current != indexToCompare[indexToCompareStart]) {
                cout << "Character does not match" << endl;
                return 0;
            } else {
                //cout << "Current character being read from indexToCompare array: " << indexToCompare[indexToCompareStart] << endl;
                indexToCompareStart++;
                cout << "Comparison successful!" << endl;
                continue;
            }
        }

        cout << "File operation complete" << endl;
        cout << "********************************************************************************" << endl;

        fclose(fptr);
        ++loopCount;

    }

    return (EXIT_SUCCESS);
}

/*
 * --Function name:     main
 * --Description:       Takes in an argument value in argc. A conditional statement is used to execute the appropriate code
 *                      based on the argument passsed in
 * --Inputs:            argc - value passed from exec call in time2.cpp
 * --Outputs:           None.
 * --Globals:           ROW_SIZE - the set row size for the random array.
 *                      COL_SIZE - the set column size for the random array.
 * --Returns:           0.
 */
int main(int argc, char **argv){

    struct timeval tv;
    FILE *timer;

    gettimeofday(&tv, NULL);

    //Write to processStartup2 and call fileOperations2 or processStartup and call fileOperations depending on the
    //argument passed back from the exec calls in the time 1.cpp or time2.cpp.
    if(argc == 2){
        gettimeofday(&tv, NULL);
        timer = fopen("processStartup2.csv", "a");
        fprintf(timer, "%d\n", (int)tv.tv_usec);
        fclose(timer);

        fileOperations2();
    } else{
        gettimeofday(&tv, NULL);
        timer = fopen("processStartup.csv", "a");
        fprintf(timer, "%d\n", (int)tv.tv_usec);
        fclose(timer);

        fileOperations();
    }
        //{timer = fopen(argc == 2 ? "processStartup2.csv" : "processStartup.csv", "a");
        //fprintf(timer, "%d\n", (int)tv.tv_usec);
        //fclose(timer);

        //fileOperations();
    //}

    //remove("randomCharacters.txt");
    //remove("randomCharacters2.txt");

    return EXIT_SUCCESS;

}