//============================================================================
// Name        : SchedulingB2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include <vector>
class SchedulingAlgorithm
{
public:
    int n;
    int *Arrival;
    int *Process;
    int *Burst;
    SchedulingAlgorithm()
    {
        cout << "Enter the number of processes : ";
        cin >> n;
        cout << "Enter the Arrival time of Each process :\n";
        Arrival = new int[n];
        Burst = new int[n];
        Process = new int[n];
        for (int i = 0; i < n; i++)
        {
            Process[i] = i + 1;
            cout << "Enter the arrival time for process " << i + 1 << endl;
            cin >> Arrival[i];
            cout << "Enter the Burst time for process " << i + 1 << endl;
            cin >> Burst[i];
        }
    }
    void Priority()
    {
        int * priority = new int[n];
        int * Ct = new int[n];
        vector<int>Arr;
        cout<<"Enter the priority of the processes"<<endl;
        for(int i=0; i<n ;i++)
        {
            cout<<"Priority of Process "<<i+1<<" : ";
            cin>>priority[i];
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n-1;j++)
            {
                if (Arrival[j] > Arrival[j + 1])
                {
                    int temp = Arrival[j];
                    Arrival[j] = Arrival[j + 1];
                    Arrival[j + 1] = temp;

                    int temp1 = Burst[j];
                    Burst[j] = Burst[j + 1];
                    Burst[j + 1] = temp1;

                    int temp2 = priority[j];
                    priority[j] = priority[j+1];
                    priority[j+1] = temp2;

                    int temp3 = Process[j];
                    Process[j] = Process[j + 1];
                    Process[j + 1] = temp3;
                }
                else if((Arrival[j] == Arrival[j+1]) && (priority[j] > priority[j+1]))
                {
                    int temp = Arrival[j];
                    Arrival[j] = Arrival[j + 1];
                    Arrival[j + 1] = temp;

                    int temp1 = Burst[j];
                    Burst[j] = Burst[j + 1];
                    Burst[j + 1] = temp1;

                    int temp2 = priority[j];
                    priority[j] = priority[j+1];
                    priority[j+1] = temp2;

                    int temp3 = Process[j];
                    Process[j] = Process[j + 1];
                    Process[j + 1] = temp3;
                }
            }
        }
        int t = Burst[0];
        int pt = 100;
        int iCnt = 1;
        Ct[0] = t;
        cout<<"Gannt Chart"<<endl;
        cout<<"P"<<Process[0]<<" ( "<<t<<" ) "<<"->";
        priority[0] = 100;
        while(true)
        {
            Arr.clear();
            for(int i=0;i<n;i++)
            {
                if(Arrival[i] <= t)
                {
                    Arr.push_back(i);
                }
            }
            int min = -1;
            int pt = 100;
            for(int j=0;j<Arr.size();j++)
            {
                if(priority[Arr[j]] < pt)
                {
                    min = Arr[j];
                    pt = priority[Arr[j]];
                }
            }
            // cout<<min<<endl;
            t = t + Burst[min];
            Ct[min] = t;
            cout<<"P"<<Process[min]<<" ( "<<t<<" ) "<<"->";
            priority[min] = 100;
            iCnt++;
            if(iCnt == n)
            {
                break;
            }
        }
        cout<<endl;
        int *TAT = new int[n];
        for (int i = 0; i < n; i++)
        {
            TAT[i] = Ct[i] - Arrival[i];
        }

        int *Wt = new int[n];
        for (int i = 0; i < n; i++)
        {
            Wt[i] = TAT[i] - Burst[i];
        }
        int AvgTAT = 0;
        int AvgWT = 0;
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i < n; i++)
        {
            sum1 = sum1 + TAT[i];
            sum2 = sum2 + Wt[i];
        }
        AvgTAT = sum1 / n;
        AvgWT = sum2 / n;

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "PID" << "\t | \t" << "AT" << "\t | \t" << "BT" << "\t | \t" << "CT" << "\t | \t" << "TAT" << "\t | \t" << "WT" << "\t | \t" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "P" << Process[i] << "\t | \t" << Arrival[i] << "\t | \t" << Burst[i] << "\t | \t" << Ct[i] << "\t | \t" << TAT[i] << "\t | \t" << Wt[i] << " \t | \t" << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
        }
        cout << "The Average Total Around Time required by using First Come First Serve Algorithm is : " << AvgTAT << endl;
        cout << "The Average Waiting Time required by using First Come First Serve Algorithm is : " << AvgWT << endl;
    }
    void RR()
    {
        int quantum = 0;
        int t = 0;
        vector<bool> isFinished(n, false);
        cout << "Enter the time quantum : " << endl;
        cin >> quantum;
        int *temp = new int[n];
        int *Ct = new int[n];
        for (int i = 0; i < n; i++)
        {
            temp[i] = Burst[i];
            Ct[i] = 0;
        }
        int flag = 0;
        bool idle = false;
        int iCnt = 0;
        while (1)
        {
            flag = 1;
            idle = true;
            for (int i = 0; i < n; i++)
            {
                if (Arrival[i] <= t  && temp[i]>0)
                {
                    idle = false;
                    flag = 0;
                    if (temp[i] > quantum)
                    {
                        temp[i] = temp[i] - quantum;
                        Ct[i] = t + quantum;
                        t = t + quantum;
                        cout << "P" << i + 1 << " ( " << t << " ) " << "->";
                    }
                    else
                    {
                        Ct[i] = t + temp[i];
                        t = t + temp[i];
                        temp[i] = 0;
                        isFinished[i] = true;
                        cout << "P" << i + 1 << " ( " << t << " ) " << "->";
                        iCnt++;
                    }
                }
            }
            if(iCnt == n)
            {
                break;
            }
            if(idle)
            {
                flag = 0;
                cout<<"idle"<<"->";
                int nextArrival = t;
                for (int i = 0; i < n; i++)
                {
                    if (Arrival[i] > t)
                    {
                        nextArrival = Arrival[i];
                        break;
                    }
                }
                t = nextArrival;
            }
            if (flag == 1)
            {
                break;
            }
        }
        cout << endl;
        int *TAT = new int[n];
        for (int i = 0; i < n; i++)
        {
            TAT[i] = Ct[i] - Arrival[i];
        }

        int *Wt = new int[n];
        for (int i = 0; i < n; i++)
        {
            Wt[i] = TAT[i] - Burst[i];
        }
        int AvgTAT = 0;
        int AvgWT = 0;
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i < n; i++)
        {
            sum1 = sum1 + TAT[i];
            sum2 = sum2 + Wt[i];
        }
        AvgTAT = sum1 / n;
        AvgWT = sum2 / n;

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "PID" << "\t | \t" << "AT" << "\t | \t" << "BT" << "\t | \t" << "CT" << "\t | \t" << "TAT" << "\t | \t" << "WT" << "\t | \t" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "P" << Process[i] << "\t | \t" << Arrival[i] << "\t | \t" << Burst[i] << "\t | \t" << Ct[i] << "\t | \t" << TAT[i] << "\t | \t" << Wt[i] << " \t | \t" << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
        }
        cout << "The Average Total Around Time required by using First Come First Serve Algorithm is : " << AvgTAT << endl;
        cout << "The Average Waiting Time required by using First Come First Serve Algorithm is : " << AvgWT << endl;
    }
    void FCFS()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                if (Arrival[j] > Arrival[j + 1])
                {
                    int temp = Arrival[j];
                    Arrival[j] = Arrival[j + 1];
                    Arrival[j + 1] = temp;

                    int temp1 = Burst[j];
                    Burst[j] = Burst[j + 1];
                    Burst[j + 1] = temp1;

                    int temp2 = Process[j];
                    Process[j] = Process[j + 1];
                    Process[j + 1] = temp2;
                }
            }
        }

        int *Ct = new int[n];
        Ct[0] = Burst[0];
        for (int i = 1; i < n; i++)
        {
            Ct[i] = Ct[i - 1] + Burst[i];
        }

        int *TAT = new int[n];
        for (int i = 0; i < n; i++)
        {
            TAT[i] = Ct[i] - Arrival[i];
        }

        int *Wt = new int[n];
        for (int i = 0; i < n; i++)
        {
            Wt[i] = TAT[i] - Burst[i];
        }

        int AvgTAT = 0;
        int AvgWT = 0;
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i < n; i++)
        {
            sum1 = sum1 + TAT[i];
            sum2 = sum2 + Wt[i];
        }
        AvgTAT = sum1 / n;
        AvgWT = sum2 / n;

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "PID" << "\t | \t" << "AT" << "\t | \t" << "BT" << "\t | \t" << "CT" << "\t | \t" << "TAT" << "\t | \t" << "WT" << "\t | \t" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "P" << Process[i] << "\t | \t" << Arrival[i] << "\t | \t" << Burst[i] << "\t | \t" << Ct[i] << "\t | \t" << TAT[i] << "\t | \t" << Wt[i] << " \t | \t" << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
        }
        cout << "Gantt chart" << endl;
        for (int i = 0; i < n - 1; i++)
        {
            cout << Process[i] << "->";
        }
        cout << Process[n - 1] << endl;
        cout << "The Average Total Around Time required by using First Come First Serve Algorithm is : " << AvgTAT << endl;
        cout << "The Average Waiting Time required by using First Come First Serve Algorithm is : " << AvgWT << endl;
    }

    void SJF()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - 1; j++)
            {
                if (Burst[j] > Burst[j + 1])
                {
                    int temp = Arrival[j];
                    Arrival[j] = Arrival[j + 1];
                    Arrival[j + 1] = temp;

                    int temp1 = Burst[j];
                    Burst[j] = Burst[j + 1];
                    Burst[j + 1] = temp1;
                }
            }
        }

        int *Ct = new int[n];
        Ct[0] = Arrival[0] + Burst[0];
        int sum = Burst[0];
        for (int i = 1; i < n; i++)
        {
            Ct[i] = sum + Burst[i];
            sum = Ct[i];
        }

        int *TAT = new int[n];
        for (int i = 0; i < n; i++)
        {
            TAT[i] = Ct[i] - Arrival[i];
        }

        int *WT = new int[n];
        for (int i = 0; i < n; i++)
        {
            WT[i] = TAT[i] - Burst[i];
        }

        int AvgTAT = 0;
        int AvgWT = 0;
        int sum1 = 0;
        int sum2 = 0;
        for (int i = 0; i < n; i++)
        {
            sum1 = sum1 + TAT[i];
            sum2 = sum2 + WT[i];
        }

        AvgTAT = sum1 / n;
        AvgWT = sum2 / n;

        cout << "-----------------------------------------------------------------------------------------" << endl;
        cout << "PID" << "\t | \t" << "AT" << "\t | \t" << "BT" << "\t | \t" << "CT" << "\t | \t" << "TAT" << "\t | \t" << "WT" << "\t | \t" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "P" << Process[i] << "\t | \t" << Arrival[i] << "\t | \t" << Burst[i] << "\t | \t" << Ct[i] << "\t | \t" << TAT[i] << "\t | \t" << WT[i] << "\t | \t" << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
        }
        cout << "Gantt chart" << endl;
        for (int i = 0; i < n - 1; i++)
        {
            cout << Process[i] << "->";
        }
        cout << Process[n - 1] << endl;
        cout << "The Average of Total Turn Around Time : " << AvgTAT << endl;
        cout << "The Average of Total Waiting Time is : " << AvgWT << endl;
    }
};

int main()
{
    SchedulingAlgorithm obj;
     int ch;
     do{
    cout<<"1.FCFS"<<endl;
    cout<<"2.SJF"<<endl;
    cout<<"3.Round Robin"<<endl;
    cout<<"4.Priority"<<endl;
    cout<<"5.Exit"<<endl;
    cout<<"Enter your choice : "<<endl;
    cin>>ch;
    switch(ch){
    case 1:
    cout << "First Come First Serve Algorithm " << endl;
    obj.FCFS();
    break;

    case 2:
    cout << "Shortest Job First " << endl;
    obj.SJF();
    break;

    case 3:
    cout << "Round Robin Algorithm " << endl;
    obj.RR();
    break;

    case 4:
    cout << "Priority Algorithm " << endl;
        obj.Priority();
        break;

    case 5:
    cout<<"Exiting..."<<endl;
    break;

    default:
    cout<<"Enter valid choice"<<endl;
    break;
    }

     }while(ch!=5);

     return 0;
}


