#include <iostream>
#include <algorithm>
#include <iomanip>
#include <climits>
using namespace std;

struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
} ps[100];

int main()
{
    int n;
    bool is_completed[100] = {false}, is_first_process = true;
    int current_time = 0;
    int completed = 0;
    cout << "Nhap so luong tien trinh: ";
    cin >> n;
    int sum_tat = 0, sum_wt = 0, sum_rt = 0, total_idle_time = 0, prev = 0, length_cycle;
    float cpu_utilization;
    int max_completion_time, min_arrival_time;

    cout << fixed << setprecision(2);

    for (int i = 0; i < n; i++)
    {
        cout << "\nTien trinh " << i << " Thoi gian den: ";
        cin >> ps[i].at;
        ps[i].pid = i;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "\nTien trinh " << i << " Thoi gian thuc hien: ";
        cin >> ps[i].bt;
    }

    // Mảng lưu trữ thời gian bắt đầu và kết thúc của mỗi quá trình
    int start_times[100] = {0};
    int end_times[100] = {0};

    while (completed != n)
    {
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (ps[i].bt < minimum)
                {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                if (ps[i].bt == minimum)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        minimum = ps[i].bt;
                        min_index = i;
                    }
                }
            }
        }

        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            ps[min_index].start_time = current_time;
            ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
            ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
            ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
            ps[min_index].rt = ps[min_index].wt;

            sum_tat += ps[min_index].tat;
            sum_wt += ps[min_index].wt;
            sum_rt += ps[min_index].rt;
            total_idle_time += (is_first_process == true) ? 0 : (ps[min_index].start_time - prev);

            // Lưu thời gian bắt đầu và kết thúc của quá trình
            start_times[min_index] = ps[min_index].start_time;
            end_times[min_index] = ps[min_index].ct;

            completed++;
            is_completed[min_index] = true;
            current_time = ps[min_index].ct;
            prev = current_time;
            is_first_process = false;
        }
    }

    max_completion_time = INT_MIN;
    min_arrival_time = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        max_completion_time = max(max_completion_time, ps[i].ct);
        min_arrival_time = min(min_arrival_time, ps[i].at);
    }
    length_cycle = max_completion_time - min_arrival_time;

    cout << "\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
        cout << i << "\t\t" << ps[i].at << "\t" << ps[i].bt << "\t\t" << ps[i].ct << "\t" << ps[i].tat << "\t" << ps[i].wt << "\t" << ps[i].rt << endl;
    cout << endl;

    // Xuất sơ đồ Gantt
    cout << "   BIEU DO GANTT:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "|-----";
    }
    cout << "|" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "|  P" << i << " ";
    }
    cout << "|" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "|-----";
    }
    cout << "|" << endl;

    // Xuất thời gian bắt đầu và kết thúc trên biểu đồ Gantt
    for (int i = 0; i < n; i++)
    {
        cout << start_times[i] << "     ";
    }
    cout << end_times[n - 1] << endl;

    cpu_utilization = (float)(length_cycle - total_idle_time) / length_cycle;

    cout << "\nAverage Turn Around time= " << (float)sum_tat / n;
    cout << "\nAverage Waiting Time= " << (float)sum_wt / n;
    cout << "\nAverage Response Time= " << (float)sum_rt / n;
    cout << "\nThroughput= " << n / (float)length_cycle;
    cout << "\nCPU Utilization(Percentage)= " << cpu_utilization * 100;
    return 0;
}
