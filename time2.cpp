/*
 * --Name:				Derek Witteck
 * --Assignment:		Lab 1
 * --Version:			1
 * --Date:				January 23rd, 2017
 * --Due Date:			February 7th, 2017
 * --Section:			3207-002
 * --Instructor:		Professor Kwatny
 * --Lab Instructor:	Graeme Copeland
 * --Description:		This application will fork the current process twice. The time of day pre-fork two will be subtracted
 *                      from the time of day taken right when application.cpp process starts. The application.cpp will
 *                      still be running from the first fork call when the second fork is called. This will allow us to
 *                      see the process startup time while another instance of application.cpp is still running.
 * --File Name:			time2.cpp
 * --Functions:			main()
 */

#include "time2.h"
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
 *                      creating a child process. The time for this first fork call is not logged because we are focused
 *                      on the time in fork 2. After the second fork function is called, the current time in microseconds
 *                      from the Linux epoch is logged into a file and the exec function is called, replacing the child
 *                      processes code with its own. An argument is also sent back to the main function of application.cpp
 *                      which will be used in a conditional statement so that it will be labeled properly using the fprintf
 *                      function when it is written into the file.
 * --Inputs:            None.
 * --Outputs:           None.
 * --Globals:           None.
 * --Returns:           1.
 */
int main() {

    int count = 0;

    while (count < 200) {

        struct timeval tv;

        //Fork the current process, creating a child process.
        pid_t pid = fork();

        if (pid == -1) {
            cout << "Fork failed!" << endl;
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {

            //The application.cpp file is called, replacing the child processes code with application.cpp code.
            execlp("application", "application", NULL);

        } else {

            //If pid does not equal zero we are in the parent process so fork the current process again.
            pid_t pid2 = fork();

            if (pid2 == -1) {
                cout << "Fork failed!" << endl;
                exit(EXIT_FAILURE);
            }
            if (pid2 == 0) {

                FILE *timer;
                gettimeofday(&tv, NULL);

                //Write the time before the fork() call to a file for easier access when computing time results
                timer = fopen("time2.csv", "a");
                fprintf(timer, "%d\n", (int)tv.tv_usec);
                fclose(timer);

                //The application file is called, replacing the child processes code with application.cpp code.
                //The value 2 is passed back as an argument to the main function inside application.cpp,
                // where it will go into a conditional statement and run the corresponding code.
                execlp("application", "application", "2", NULL);

            } else {
                waitpid(pid2, NULL, 0);
            }
            waitpid(pid, NULL, 0);
        }

        count++;


    }
    return 1;
}

