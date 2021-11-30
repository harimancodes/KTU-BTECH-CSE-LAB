#include <stdio.h>
#include <stdlib.h>
#define MAX 20

struct process
{
    int pnum;
    int at, bt, wt, tt, rbt, ct;
    int priority;
    int completed;
} p[MAX];

int n;
float avg_w_time = 0.0, avg_t_time = 0.0;

int queue[MAX];
int front = -1, rear = -1;

void enqueue(int p)
{
    if (rear == MAX - 1)
        printf("Queue full");

    if (front == -1 && rear == -1)
    {
        front = rear = 0;
        queue[rear] = p;
    }
    else
    {
        rear++;
        queue[rear] = p;
    }
}

int dequeue()
{
    if (front == -1 && rear == -1)
        return -1;
    if (front == rear)
    {
        int r = queue[front];
        front = rear = -1;
        return r;
    }
    else
    {
        return queue[front++];
    }
}

int exists_in_Queue(int p)
{
    for (int i = front; i <= rear; i++)
    {
        if (queue[i] == p)
            return 1;
    }
    return 0;
}

void avg_time(float w, float t, int n)
{
    printf("\nAverage Waiting Time : %.2f", w / n);
    printf("\nAverage Turnaround Time : %.2f", t / n);
}

void sort_by_arrival()
{
    struct process temp;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (p[j].at > p[j + 1].at)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void fcfs()
{
    int timer = 0;

    printf("\t\t\tFCFS");
    printf("\n\t\t\t----");

    printf("\nEnter the no.of processes : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i].pnum = i + 1;
        printf("\nEnter the arrival time of P%d : ", p[i].pnum);
        scanf("%d", &p[i].at);

        printf("\nEnter the burst time of P%d : ", p[i].pnum);
        scanf("%d", &p[i].bt);
    }

    sort_by_arrival();

    timer = p[0].ct;
    for (int i = 0; i < n; i++)
    {
        if (p[i].at > timer)
            timer = p[i].at;
        p[i].ct = timer + p[i].bt;
        timer = p[i].ct;
    }
    for (int i = 0; i < n; i++)
    {

        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        avg_w_time += p[i].wt;
        avg_t_time += p[i].tt;
    }

    printf("\nProcess\t\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pnum, p[i].at, p[i].bt, p[i].wt, p[i].tt);
    }

    avg_time(avg_w_time, avg_t_time, n);
}

void sjf()
{

    printf("\t\t\tSJF");
    printf("\n\t\t\t---");

    printf("\nEnter the total no.of processes<maximum 20> : ");
    scanf("%d", &n);

    printf("\nEnter Process Burst Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d] : ", i + 1);
        scanf("%d", &p[i].bt);
        p[i].pnum = i + 1;
    }
    //sort by burst time
    struct process temp;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (p[j].bt > p[j + 1].bt)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    p[0].ct = p[0].bt;
    for (int i = 1; i < n; i++)
    {
        p[i].ct = p[i - 1].ct + p[i].bt;
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        avg_w_time += p[i].wt;
        avg_t_time += p[i].tt;
    }

    printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\n", p[i].pnum, p[i].bt, p[i].wt, p[i].tt);
    }
    avg_time(avg_w_time, avg_t_time, n);
}

void priority()
{
    printf("\t\t\tPRIORITY");
    printf("\n\t\t\t-------");

    printf("\nEnter the total no.of processes<maximum 20> : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        p[i].pnum = i + 1;

        printf("\nEnter the burst time of P%d : ", p[i]);
        scanf("%d", &p[i].bt);

        printf("\nEnter the priority of P%d : ", p[i]);
        scanf("%d", &p[i].priority);
    }

    //sort by burst time
    struct process temp;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
        {
            if (p[j].priority > p[j + 1].priority)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    p[0].ct = p[0].bt;
    for (int i = 1; i < n; i++)
    {
        p[i].ct = p[i - 1].ct + p[i].bt;
    }

    for (int i = 0; i < n; i++)
    {
        p[i].tt = p[i].ct - p[i].at;
        p[i].wt = p[i].tt - p[i].bt;
        avg_w_time += p[i].wt;
        avg_t_time += p[i].tt;
    }

    printf("\nProcess\t\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pnum, p[i].priority, p[i].bt, p[i].wt, p[i].tt);
    }
    avg_time(avg_w_time, avg_t_time, n);
}

void round_robin()
{
    int time_slice, sum_bt = 0;
    printf("\t\t\tRound Robin");
    printf("\n\t\t\t----------");

    printf("\nEnter no of processes(Maximum 20): ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        p[i].pnum = i + 1;
        printf("\nEnter the arrival time of P%d : ", p[i].pnum);
        scanf("%d", &p[i].at);
        printf("\nEnter the busrt time of P%d : ", p[i].pnum);
        scanf("%d", &p[i].bt);
        p[i].rbt = p[i].bt;
        p[i].completed = 0;
        sum_bt += p[i].bt;
    }

    printf("\nEnter the time slice:");
    scanf("%d", &time_slice);

    sort_by_arrival();
    enqueue(0);

    int timer = p[0].at;
    while (1)
    {
        int i = dequeue();
        if (i == -1)
            break;

        if (p[i].rbt <= time_slice)
        {

            timer += p[i].rbt;
            p[i].rbt = 0;
            p[i].completed = 1;

            p[i].wt = timer - p[i].at - p[i].bt;
            p[i].tt = timer - p[i].at;

            avg_t_time += p[i].tt;
            avg_w_time += p[i].wt;

            for (int j = 0; j < n; j++)
            {
                if (p[j].at <= timer && p[j].completed != 1 && exists_in_Queue(j) != 1)
                {
                    enqueue(j);
                }
            }
        }
        else
        {
            timer += time_slice;
            p[i].rbt -= time_slice;

            for (int j = 0; j < n; j++)
            {
                if (p[j].at <= timer && p[j].completed != 1 && i != j && exists_in_Queue(j) != 1)
                {
                    enqueue(j);
                }
            }
            enqueue(i);
        }
    }
    printf("\nProcess\t\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pnum, p[i].at, p[i].bt, p[i].wt, p[i].tt);
    }

    avg_time(avg_w_time, avg_t_time, n);
}

int main()
{
    int choice;
    printf("1)FCFS\n2)SJF\n3)ROUND ROBIN\n4)PRIORITY\n5)EXIT");
    while (1)
    {
        printf("\nChoose the algorithm : ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fcfs();
            break;
        case 2:
            sjf();
            break;
        case 3:
            round_robin();
            break;
        case 4:
            priority();
            break;
        case 5:
            return 0;
        default:
            printf("Wrong choice!");
        }
    }
}
