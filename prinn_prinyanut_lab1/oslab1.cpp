//Prinn Prinyanut
//Lab 01 
//Due date Sep 11, 2019

//includes
#include <iostream>
#include <sys/utsname.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

//main func
int main(int argc, char **argv) {

    //PART A --------------------------------------------------
    
    struct utsname data; //create new obj
    if(uname(&data) != 0); //check if empty
    
    //print out all of info
    printf("Lab01: Part A\n");
    printf("System Name - %s\n", data.sysname);
    printf("Nodename - %s\n", data.nodename);
    printf("Release - %s\n", data.release);
    printf("Version - %s\n", data.version);
    printf("Machine - %s\n", data.machine);


    //PART B ---------------------------------------------------

    printf("\nLab01: Part B\n");
	
    //PART 1
	char inputFile[1000]; //this had the inputFile
	sprintf(inputFile, "/proc/stat");
	FILE *f = fopen(inputFile, "r");
	char BT[50];//hold string name
	fscanf(f, "%s", &BT);
	while (strcmp("btime",BT) != 0){
		//point to next until string is found
		fscanf(f, "%s", &BT);
        
    }
	int bootTime;
	fscanf(f, "%d", &bootTime);//store value of boot time
    //simple time calculation
    int minutes = bootTime/ 60;
    int seconds = bootTime % 60;
    int hours = minutes / 60;
    int days = hours / 24;
	int months = days / 30;
    int years = days / 365;
	
    minutes = minutes % 60;
    hours = hours % 24;
    days = days % 30;
    months = months % 12;
    years = years + 1970;
	
    //printhing the b time to console
    printf("Boot time: %d-%d-%d %d:%d:%d\n",years, months, days, hours, minutes, seconds);
    rewind(f);//go back to file
    
    
    //PART 2
    //use this to take in time
    sprintf(inputFile, "/proc/uptime");
    FILE *c = fopen(inputFile, "r"); //open file
    
    int one;
    int two;
    int total;
    fscanf(c, "%d", &one);
    fscanf(c, "%d", &two);
    total = one + two;
	
    //convert this to minutes, seconds and hours
    int Minutes = total / 60;
    int Hours = Minutes / 60;
    int Seconds = total % 60;
   
    Minutes = Minutes % 60;
    int Days = Hours / 24;
    Hours = Hours % 24;
	//print out results
    printf("Time since system was last booted: %d:%d:%d:%d\n",Days, Hours, Minutes, Seconds);
	
	
	//PART 3
    fscanf(f, "%s", &BT);//override BT with CPU
    int userMemory;
    int skip;
    int systemMemory;
    fscanf(f, "%d", &userMemory);
    fscanf(f, "%d", &skip);//skip
    fscanf(f, "%d", &systemMemory);
    fclose(f);
	//print out time spent for user and system mode
    printf("Time spent in user mode: %d seconds\n", userMemory);
	printf("Time spent in system mode: %d seconds\n", systemMemory);
    fclose(c);
    
    //PART 4
    sprintf(inputFile, "/proc/meminfo"); //read in info
    FILE *d = fopen(inputFile, "r"); //open file
    char tot[100];
    char available[100];
    fscanf(d, "%s", &tot); //read in file
    
    //this loop goes through and finds strings
    while (strcmp("MemTotal:",tot) != 0) {
        fscanf(d, "%s", &tot);
    }
    int totalMemory;
    fscanf(d, "%d", &totalMemory);
    printf("Total memory: %d kB\n", totalMemory); //print total memory
    rewind(d);//pointer back at the beginning of file
    fscanf(d, "%s", &available);
    
    while (strcmp("MemAvailable:",available) != 0){
        //point to next until string is found
        fscanf(d, "%s", &available);
    }
    int availableMemory;
    fscanf(d, "%d", &availableMemory);
    printf("Available memory: %d kB\n", availableMemory); //print available memory
    fclose(d);
    
    return 0;
}

