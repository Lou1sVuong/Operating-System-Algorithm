#include <stdio.h>
#include <stdlib.h>
void SRTF()
{
    int at[10], bt[10], temp[10];
    int i, smallest, count = 0, time, limit, end;
    double wt = 0, tat = 0;
    float awt, atat;

    printf("Enter the total number of processes:\n");
    scanf("%d", &limit);
    printf("Enter details of the processes:\n");
    for (i = 0; i < limit; i++)
    {
        printf("Enter the arrival time for process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }

    int completed[10] = {0};
    int prev_smallest = 0;
    int t = 0;
    while (count != limit)
    {
        smallest = -1;
        for (i = 0; i < limit; i++)
        {
            if (at[i] <= t && !completed[i])
            {
                if (smallest == -1 || bt[i] < bt[smallest])
                {
                    smallest = i;
                }
            }
        }
        if (smallest == -1)
        {
            t++;
            continue;
        }
        bt[smallest]--;
        t++;
        if (bt[smallest] == 0)
        {
            completed[smallest] = 1;
            count++;
            end = t;
            wt += end - at[smallest] - temp[smallest];
            tat += end - at[smallest];
        }
    }

    awt = wt / limit;
    atat = tat / limit;
    printf("Avg waiting time: %f\n", awt);
    printf("Avg turn around time: %f\n", atat);
}

void RoundRobin()
{
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;
    printf("Enter the number of process: ");
    scanf("%d", &NOP);
    y = NOP;

    for (i = 0; i < NOP; i++)
    {
        printf("Enter the arrival time and burst time of process %d:\n", i + 1);
        scanf("%d", &at[i]);
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }

    printf("Enter the time quantum:\n");
    scanf("%d", &quant);
    printf("process_no     burst time       turn around time      wait time\n");
    for (sum = 0, i = 0; y != 0;)
    {
        if (temp[i] <= quant && temp[i] > 0)
        {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        }
        else if (temp[i] > 0)
        {
            temp[i] = temp[i] - quant;
            sum += quant;
        }

        if (temp[i] == 0 && count == 1)
        {
            y--;
            printf("\n[%d]\t\t%d\t\t%d\t\t%d\n", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt += sum - at[i] - bt[i];
            tat += sum - at[i];
            count = 0;
        }
        if (i == NOP - 1)
        {
            i = 0;
        }
        else if (at[i + 1] <= sum)
        {
            i++;
        }
        else
        {
            i = 0;
        }
    }
    avg_wt = wt * 1.0 / NOP;
    avg_tat = tat * 1.0 / NOP;
    printf("Average Turnaround Time: %f\n", avg_tat);
    printf("Average Waiting Time: %f\n", avg_wt);
}

int main()
{
    // SRTF();
    RoundRobin();
    return 0;
}