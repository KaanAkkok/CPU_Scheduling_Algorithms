#include<stdio.h>

void FCFSnp();
void SJFnp();
void RRobin();
void SJFp();

int main() {
	int scheduler;
	printf("\n        -> FCFS [1]\n"
		"        -> SJF [2]\n"
       		"        -> RR [3]\n"
       		"        -> SJF (preemptive) [4]\n"
       		"\nPlease choose a scheduling algorithm: ");
	scanf("%d", &scheduler);
	if(scheduler == 1) {
		FCFSnp();
	}
	else if(scheduler == 2) {
		SJFnp();
	}
	else if(scheduler == 3) {
		RRobin();
	}
	else if(scheduler == 4) {
		SJFp();
	}
	return 0;
}

void FCFSnp() {
	int proc_num;
	printf("\nEnter the number of processes: ");
	scanf("%d", &proc_num);

	int burst_time[proc_num], waiting_time[proc_num], turnaround_time[proc_num];
	int total_waiting_time = 0, total_turnaround_time = 0;

	printf("\n");
	for(int i=0; i<proc_num; i++) {
		printf("Enter burst time for process [%d]: ", i);
		scanf("%d", &burst_time[i]);
	}
	
	waiting_time[0] = 0;

	for(int i=1; i<proc_num; i++) {
		waiting_time[i] = waiting_time[i-1] + burst_time[i-1];
		total_waiting_time += waiting_time[i];
	}
	
	for(int i=0; i<proc_num; i++) {
		turnaround_time[i] = waiting_time[i] + burst_time[i];
		total_turnaround_time += turnaround_time[i];
	}

	printf("\nProcesses\t\tburst time\twaiting time\tturnaround time\n");
	for(int i=0; i<proc_num; i++) {
		printf("Process[%d]\t\t%d\t\t%d\t\t%d\n", i, burst_time[i], waiting_time[i], turnaround_time[i]);
	}
	printf("\nAverage waiting time: %.2f", (float)total_waiting_time/proc_num);
	printf("\nAverage turnaround time: %.2f\n", (float)total_turnaround_time/proc_num);

}

void SJFnp() {
	int proc_num;
	printf("\nEnter the number of processes: ");
	scanf("%d", &proc_num);

	int processId[proc_num], burst_time[proc_num], waiting_time[proc_num], turnaround_time[proc_num];
	int total_waiting_time = 0, total_turnaround_time = 0;

	printf("\n");
	for(int i=0; i<proc_num; i++) {
		printf("Enter burst time for process [%d]: ", i);
		scanf("%d", &burst_time[i]);
		processId[i] = i;
	}
	
	for(int i=0; i<proc_num-1; i++) {
		for(int j=0; j<proc_num-1-i; j++) {
			if(burst_time[j] > burst_time[j+1]) {
				int temp = burst_time[j];
				burst_time[j] = burst_time[j+1];
				burst_time[j+1] = temp;

				temp = processId[j];
				processId[j] = processId[j+1];
				processId[j+1] = temp;
			}
		}
	}

	waiting_time[0] = 0;

	for(int i=1; i<proc_num; i++) {
		waiting_time[i] = waiting_time[i-1] + burst_time[i-1];
		total_waiting_time += waiting_time[i];
	}
	
	for(int i=0; i<proc_num; i++) {
		turnaround_time[i] = waiting_time[i] + burst_time[i];
		total_turnaround_time += turnaround_time[i];
	}

	printf("\nProcesses\t\tburst time\twaiting time\tturnaround time\n");
	for(int i=0; i<proc_num; i++) {
		printf("Process[%d]\t\t%d\t\t%d\t\t%d\n", processId[i], burst_time[i], waiting_time[i], turnaround_time[i]);
	}
	printf("\nAverage waiting time: %.2f", (float)total_waiting_time/proc_num);
	printf("\nAverage turnaround time: %.2f\n", (float)total_turnaround_time/proc_num);
}

void RRobin() {
	int i, limit, total = 0, x, counter = 0, time_quantum; 
      int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10], temp[10]; 
      float average_wait_time, average_turnaround_time;
      printf("\nEnter Total Number of Processes:\t"); 
      scanf("%d", &limit); 
      x = limit; 
      for(i = 0; i < limit; i++) 
      {
            printf("\nEnter Details of Process[%d]\n", i + 1);
            printf("Arrival Time:\t");
            scanf("%d", &arrival_time[i]);
            printf("Burst Time:\t");
            scanf("%d", &burst_time[i]); 
            temp[i] = burst_time[i];
      } 
      printf("\nEnter Time Quantum:\t"); 
      scanf("%d", &time_quantum); 
      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");



      for(total = 0, i = 0; x != 0;) 
      { 
            if(temp[i] <= time_quantum && temp[i] > 0) 
            { 
                  total = total + temp[i]; 
                  temp[i] = 0; 
                  counter = 1; 
            } 
            else if(temp[i] > 0) 
            { 
                  temp[i] = temp[i] - time_quantum; 
                  total = total + time_quantum; 
            } 
            if(temp[i] == 0 && counter == 1) 
            { 
                  x--; 
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burst_time[i], total - arrival_time[i], total - arrival_time[i] - burst_time[i]);
                  wait_time = wait_time + total - arrival_time[i] - burst_time[i]; 
                  turnaround_time = turnaround_time + total - arrival_time[i]; 
                  counter = 0; 
            } 
            if(i == limit - 1) 
            {
                  i = 0; 
            }
            else if(arrival_time[i + 1] <= total) 
            {
                  i++;
            }
            else 
            {
                  i = 0;
            }
      } 
      average_wait_time = wait_time * 1.0 / limit;
      average_turnaround_time = turnaround_time * 1.0 / limit;
      printf("\n\nAverage Waiting Time:\t%f", average_wait_time); 
      printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);
}

void SJFp() {
	int arrival_time[10], burst_time[10], temp[10];
      int i, smallest, count = 0, time, limit;
      double wait_time = 0, turnaround_time = 0, end;
      float average_waiting_time, average_turnaround_time;
      printf("\nEnter the Total Number of Processes:\t");
      scanf("%d", &limit); 
      printf("\nEnter Details of %d Processes\n", limit);
      for(i = 0; i < limit; i++)
      {
            printf("\nEnter Arrival Time:\t");
            scanf("%d", &arrival_time[i]);
            printf("Enter Burst Time:\t");
            scanf("%d", &burst_time[i]); 
            temp[i] = burst_time[i];
      }



      burst_time[9] = 9999;  
      for(time = 0; count != limit; time++)
      {
            smallest = 9;
            for(i = 0; i < limit; i++)
            {
                  if(arrival_time[i] <= time && burst_time[i] < burst_time[smallest] && burst_time[i] > 0)
                  {
                        smallest = i;
                  }
            }
            burst_time[smallest]--;
            if(burst_time[smallest] == 0)
            {
                  count++;
                  end = time + 1;
                  wait_time = wait_time + end - arrival_time[smallest] - temp[smallest];
                  turnaround_time = turnaround_time + end - arrival_time[smallest];
            }
      }



      average_waiting_time = wait_time / limit; 
      average_turnaround_time = turnaround_time / limit;
      printf("\n\nAverage Waiting Time:\t%lf\n", average_waiting_time);
      printf("Average Turnaround Time:\t%lf\n", average_turnaround_time);
}
