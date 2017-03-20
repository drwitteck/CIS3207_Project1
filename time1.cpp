/*
 * --Name:				Derek Witteck
 * --Assignment:		Lab 1
 * --Version:			1
 * --Date:				January 23rd, 2017
 * --Due Date:			February 7th, 2017
 * --Section:			3207-002
 * --Instructor:		Professor Kwatny
 * --Lab Instructor:	Graeme Copeland
 * --Description:		This application will get the time of day, fork the current process and replace it with application.cpp.
 *                      The time of day pre-fork will be subtracted from the time of day taken right when application.cpp
 *                      process starts. This will give us the process startup time of application.cpp.
 * --File Name:			time1.cpp
 * --Functions:			main()
 */

#include "time1.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/time.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

/*
 * --Function name:     main
 * --Description:       Starts a while loop with a counter to run this process multiple times. This will give multiple
 *                      startup times to be used for comparison. A pid variable is created and the fork function is called
 *                      creating a child process. The current time in microseconds from the Linux epoch is logged into
 *                      a file and the exec function is called, replacing the child processes code with its own.
 * --Inputs:            None.
 * --Outputs:           None.
 * --Globals:           None.
 * --Returns:           1.
 */
int main(){

    int count = 0;

    while(count < 100) {

        struct timeval tv;

        //Fork the current process using the pid data type, generating a pid number and creating a child process.
        pid_t pid = fork();

        if (pid == -1) {
            cout << "Fork failed!" << endl;
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {

            FILE *timer;
            gettimeofday(&tv, NULL);

            //Write the time before the fork() call to a file for easier access when computing time results
            timer = fopen("time1.csv", "a");
            fprintf(timer, "%d\n", (int) tv.tv_usec);
            fclose(timer);

            execlp("application", "application", NULL);
        } else {
            waitpid(pid, NULL, 0);
        }
        count++;

    }

    return EXIT_SUCCESS;
}

