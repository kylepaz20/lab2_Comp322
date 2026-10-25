#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int id;
int arrival;
int total_CPU;
bool done = false;
int start_time;
int end_time;
int turnaround_time;


//variables for table
int number_of_parameters;
int arrival_cycle_array[100000];
int total_cycles_array[100000];
int start_time_array[100000];
int end_time_array[100000];
int turnaround_time_array[100000];

//Procedure to print the contents of the scheduling table
void print_Table(){

    printf("\n");
    printf("\n");
    printf("PID     Arrival     Total       Start       End       Turnaround      \n");
    printf("--------------------------------------------------------------------\n");

    for(int i = 1; i<= number_of_parameters; i++){
        
    printf("%-2d       %-2d            %-2d          %-2d           %-2d              %-2d                  \n", i, arrival_cycle_array[i], total_cycles_array[i], start_time_array[i], end_time_array[i], turnaround_time_array[i]);
    }
}

//Procedure for option 1 (Enter parameters)
void enterParameters(){
    int arrival_cycle;
    int total_cycle;

    printf("Enter total number of processes: \n");
    scanf("%d", &number_of_parameters);
    for(int i = 1; i<= number_of_parameters; i++){
        printf("Enter arrival cycle for process %d:\n", i);
        scanf("%d", &arrival_cycle);
        arrival_cycle_array[i] = arrival_cycle;
        printf("Enter total cycle for process %d:\n", i);
        scanf("%d", &total_cycle);
        total_cycles_array[i] = total_cycle;
    }
    print_Table();
}

//Procedure for option 2(Schedule processes with FIFO algorithm)
void FIFO_Algorithm(){
    
    
    for(int i = 1; i <= number_of_parameters; i++){
            //calculations
            start_time_array[i] = total_cycles_array[i - 1] + start_time_array[i - 1];
            end_time_array[i] = total_cycles_array[i] + start_time_array[i];
            turnaround_time_array[i] = end_time_array[i] - arrival_cycle_array[i];
    }
print_Table();
} //end FIFO_algorithm()



//Procedure for option 3(Schedule processes with SJF algorithm)
void SJF_Algorithm(){

    int done[10000] = {0};
    int scheduled = 0;
    int current_cycle_time = 0;
        while(scheduled < number_of_parameters){
            int lowest_total_cycle = INT_MAX;
            int current_process = -1;
                for(int i = 1; i<= number_of_parameters; i++){
                    //sorts shortest to longest total cycles
                    if(done[i] == 0 &&  total_cycles_array[i] < lowest_total_cycle && arrival_cycle_array[i] <= current_cycle_time){
                        lowest_total_cycle = total_cycles_array[i];
                        current_process = i;
                    }
                }

                
                    //If there is no process available at the beginning
                    if(current_process == -1){
                        int earliest_process = INT_MAX;
                        for(int i = 1; i <= number_of_parameters; i++){
                            if(done[i] == 0 && arrival_cycle_array[i] < earliest_process){
                            earliest_process = arrival_cycle_array[i];
                            //The earliest process is the one with the earliest arrival time
                            }
                        }
                        current_cycle_time = earliest_process;
                        continue;
                    }
                

                    //calculations
                    start_time_array[current_process] = current_cycle_time;
                    end_time_array[current_process] = total_cycles_array[current_process] + start_time_array[current_process];
                    turnaround_time_array[current_process] = end_time_array[current_process] - arrival_cycle_array[current_process];

                    done[current_process] = 1;
                    scheduled++;
                    current_cycle_time = end_time_array[current_process];
                
        
    }
    print_Table();
} // end SJF_Algorithm()


//Procedure for option 4(Schedule processes with SRT algorithm)
void SRT_Algorithm(){
    int done[10000] = {0};
    int total_remaining[10000] = {0};
    int already_started[10000] = {0};
    int scheduled = 0;
    int current_cycle_time = 0;

    for(int i = 1; i <= number_of_parameters; i++){
        total_remaining[i] = total_cycles_array[i];
    }
    while(scheduled < number_of_parameters){
        int lowest_total_remaining = INT_MAX;
        int current_process = -1;
            for(int i = 1; i <= number_of_parameters; i++){
                if(done[i] == 0 && total_remaining[i] < lowest_total_remaining && arrival_cycle_array[i] <= current_cycle_time){
                    current_process = i;
                    lowest_total_remaining = total_remaining[i];
                }
            }

            //If there is no process available in the beginning
            if(current_process == -1){
                current_cycle_time++;
                continue;
            }


            if(already_started[current_process] == 0){
                start_time_array[current_process] = current_cycle_time;
                already_started[current_process] = 1;
                }

            
            total_remaining[current_process]--;
            current_cycle_time++;

            //When there is no time remaining in the process, it is done and current time keeps incrementing
            if(total_remaining[current_process] == 0){
                done[current_process] = 1;

                //Calculates end time and turnaround time when the process is done
                end_time_array[current_process] = current_cycle_time;
                turnaround_time_array[current_process] = end_time_array[current_process] - arrival_cycle_array[current_process];
                scheduled++;
            }
            
        }
    print_Table();
}

//Procedure for option 5(Quit program and free memory)
void quit(){
done = true;
printf("Quitting program");
    
}

//main method
int main(){

    int choice;

    while(done == false){
    printf("\n");
    printf("\n");
    printf("Choices: \n");
    printf("1) Enter parameters\n");
    printf("2) Schedule processes with FIFO algorithm\n");
    printf("3) Schedule processes with SJF algorithm\n");
    printf("4) Schedule processes with SRT algorithm\n");
    printf("5) Quit and free memory\n");
    printf("\n");

    
    printf("Enter selection: \n");
    scanf("%d", &choice);




    while(choice < 1 || choice > 5){
        printf("Invalid choice. Try Again!\n");
        printf("Enter selection: \n");
        scanf("%d", &choice);

        if(scanf("%d", &choice) != -1){
            printf("Invalid input");
            return 0;
        }
    }

    if(choice >= 1 && choice <=5){
        if (choice == 1){
            enterParameters();
        } else if (choice == 2){
            FIFO_Algorithm();
        } else if (choice == 3){
            SJF_Algorithm();
        } else if (choice == 4){
            SRT_Algorithm();
        } else if (choice == 5){
            quit();
            break;
        }
    }
    }

    return 0;
}