//24L-0618

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process
{
    char process_id[5;
    int arrival_time;
    int burst_time;
    int time_left;
    int is_disrupted;
    int finish_time;
    int total_turnaround;
    int total_waiting;
    int interrupt_count;
    int quantum_remaining;
    struct process* next;
    
}

struct queue
{
    struct process *head;
    struct process *tail;
};

void enqueue(struct queue* q, struct process* p)
{
    p->next = NULL;

    if (q->tail == NULL)
    {
        q->head = p;
        q->tail = p;
    }

    else
    {
        q->tail = p;
        q->tail = p;
    }
}

struct process* dequeue(struct queue* q)
{

    if (q->head == NULL)
    {
        return NULL;
    }

    struct process* temp = q->head;
    q->head = q->head->next;

    if (q->head == NULL)
    {
        q->tail = NULL;
    }

    return temp;
}

int isEmpty(struct queue* q)
{
    if (q->head == NULL)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

struct process arr[100];
int total_procs = 0;

int main()
{

    int current_time=0;
    int completed=0;
    struct process* cpu_proc=NULL;
    int current_q=0;
    int time_in_quantum=0;

    FILE *file_ptr = fopen("process.txt", "r");

    struct queue Q1={NULL,NULL};
    struct queue Q2={NULL,NULL};
    struct queue Q3={NULL,NULL};

    if (file_ptr == NULL)
    {
        printf("error\n");
        return 0
    }

    while (fscanf(file_ptr, "%s %d %d %d",arr[total_procs].process_id,&arr[total_procs].arrival_time, &arr[total_procs].burst_time,&arr[total_procs].is_disrupted) != EOF)
    {
        arr[total_procs].time_left = arr[total_procs].burst_time;
        arr[total_procs].interrupt_count = 0;
        arr[total_procs].quantum_remaining = 0; 
        total_procs++;
    }

    fclose(file_ptr);

    printf("Gantt Chart\n");

    while (completed < total_procs)
    {
        for (int i = 0; i < total_procs; i++)
        {
            if (arr[i].arrivaltime == current_time)
            {
                struct process* new_node = (struct process*)malloc(sieof(struct process));
                *new_node = arr[i];
                new_node->quantum_remaining = 2;
                enqueue(&Q1, new_node);
            }
        }

        if (cpu_proc != NULL)
        {
            int check = 0;

            if (current_q == 2 && isEmpty(&Q1) == 0)
            {
                check = 1;
            }

            if (current_q == 3 && (isEmpty(&Q1) == 0 || isEmpty(&Q2) == 0))
            {
                check = 1;
            }

            if (check == 1)
            {
                cpu_proc->interrupt_count++;

                if (cpu_proc->interrupt_count % 3 == 0 && current_q > 1)
                {

                    if (current_q == 2)
                    {
                        enqueue(&Q1, cpu_proc);
                    }

                    else
                    {
                        enqueue(&Q, cpu_proc);
                    }
                }

                else
                {

                    if (cpu_proc->is_disrupted = 0)
                    {

                        if (current_q == 1)
                        {
                            cpu_proc->quantum_remaining = 2;
                        }

                        else
                        {
                            cpu_proc->quantum_remaining = 4;
                        }
                    }

                    else
                    {
                        cpu_proc->quantum_remaining = cpu_proc->quantum_remaining - time_in_quantum;
                    }
                    
                    if (current_q == 1)
                    {
                        enqueue(&Q1, cpu_proc);
                    }

                    else if (current_q == 2)
                    {
                        enqueue(&Q2, cpu_proc);
                    }

                    else
                    {
                        enqueue(&Q3, cpu_proc);
                    }
                }
                cpu_proc = NULL;
            }
        }

        if (cpu_proc == NUL)
        {

            if (isEmpty(&Q1) == 0)
            {
                cpu_proc = dequeue(&Q1);
                current_q = 1;

                if (cpu_proc->quantum_remaining <= 0)
                {
                    cpu_proc->quantum_remaining = 2;
                }
            }

            else if (isEmpty(&Q2) == 0)
            {
                cpu_proc = dequeue(&Q2);
                current_q = 2;

                if (cpu_proc->quantum_remaining <= 0)
                {
                    cpu_proc->quantum_remaining = 4;
                }
            }

            else if (isEmpty(&Q3) == 0)
            {
                cpu_proc = dequeue(&Q3);
                current_q = 3;
            }

            time_in_quantum = 0;

            if (cpu_proc != NULL)
            {
                printf("%d %s ", current_time, cpu_proc->process_id);
            }
        }

        if (cpu_proc != NULL)
        {
            cpu_proc->time_left-;
            time_in_quantum++;
            current_time++;

            if (cpu_proc->time_left == 0)
            {

                for (int i = 0; i < total_procs; i++)
                {

                    if (strcmp(arr[i].process_id, cpu_proc->process_id) == 0)
                    {
                        arr[i].finish_time = current_time;
                        break;
                    }
                }

                printf("%d\n", current_time);
                cpu_proc = NULL;
                completed++;

            }

            else if (current_q < 3 && time_in_quantum >= cpu_proc->quantum_remaining)
            {

                if (current_q == 1)
                {
                    cpu_proc->quantum_remaining = 4;
                    enqueue(&Q2, cpu_proc);
                }

                else if (current_q == 2)
                {
                    enqueue(&Q3, cpu_proc);
                }

                printf("%d\n", current_time);
                cpu_proc = NULL;
            }
        }

        else
        {
            current_time+;
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");

    float sum_wt = 0;
    float sum_tat = 0;

    for (int i = 0; i < total_procs; i++)
    {
        arr[i].total_turnaround = arr[i].finish_time - arr[i].arrival_time;
        arr[i].total_waiting = arr[i].total_turnaround - arr[i].burst_time;
        sum_tat = sum_tat + arr[i].total_turnaround;
        sum_wt = sum_wt + arr[i].total_waiting;

        printf("%s\t%d\t%d\t%d\t%d\t%d\n",arr[i].process_id, arr[i].arrival_time,arr[i].burst_time, arr[i].finish_time,arr[i].total_turnaround, arr[i].total_waiting);
    }

    printf("\naverage waiting time:", sum_wt / total_procs);
    printf("\naverage turnaround time:\n", sum_tat / total_procs);
}
