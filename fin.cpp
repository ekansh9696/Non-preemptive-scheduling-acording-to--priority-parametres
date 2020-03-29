#include<bits/stdc++.h>
#include<conio.h>
using namespace std;
struct process 
{
	int p_id;
	int bt;
	int at;
	int wait;
	float priority;
	int tat;
};
int main() 
{
	int n;
	printf("Specify number of processes \n");
	scanf("%d",&n);
	if(n<=0) 
	{
		printf("Invalid input , exiting");
		return 0;
	}
	
	vector<process> list; //easy manipulation
	
	// input process details
	
	printf("Enter arrival time and then burst time for every process\n");
	for(int i=0;i<n;++i) 
	{
		int atinp,btinp;
		scanf("%d",&atinp);
		scanf("%d",&btinp);
		if(atinp<0 or btinp<0) 
		{
			printf("Invalid input, exiting");
			return 0;
		}
		process flag;
		flag.p_id = i+1;
		flag.bt = btinp;
		flag.at = atinp;
		flag.wait = 0;
		flag.priority = 0;
		flag.tat = btinp;
		list.push_back(flag);
	}
	for(int i=0;i<list.size();++i)
		{
			printf("%d ",list[i].p_id);
		}
	// Sorting with respect to arrival time
	
	for(int i=0;i<list.size();++i) 
	{
		for(int j=0;j<list.size()-i-1;++j) 
		{
			if(list[j].at>list[j+1].at) 
			{
				process temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
	cout<<endl;
	for(int i=0;i<list.size();++i)
	{
		printf("%d ",list[i].p_id);
	}
	vector<process> running; //each process waiting is stored here
	vector<process> completed;//each process completed is stored here
	vector<process> incpu;
	int timer=0;
	do
	{
		//removing processes to be executed from list and adding to running 
		for(;!list.empty() && list[0].at==timer ;)
			{
			running.push_back(list[0]);
			list.erase(list.begin());	
			}
		if(running.empty() && incpu.empty())
		{
			timer++;
			continue;
		}
		//sorting on basis of priority	
		for(int i=0;i<running.size();++i) 
			{
			for(int j=0;j<running.size()-i-1;++j) 
				{
				if(running[j].priority<running[j+1].priority) 
					{
					process temp = running[j];
					running[j] = running[j+1];
					running[j+1] = temp;
					}
				}
			}
		//if no process in cpu then add one from the running prosesses
		if(incpu.empty() && !running.empty())
		{
			incpu.push_back(running[0]);
			running.erase(running.begin());
		}
		if(incpu[0].bt==1)
		{
			incpu[0].bt-=1;
			//std::for_each(running.begin()+1, running.end(), [](process& f){ f.wait +=1; f.priority = 1+(f.wait/f.bt);});
			for(int i=0;i<running.size();i++)
			{
				running[i].wait+=1;
				running[i].priority=1+(running[i].wait/running[i].bt);
			}
			completed.push_back(incpu[0]);
			incpu.erase(incpu.begin());
		}
		else
		{
			incpu[0].bt-=1;
			//std::for_each(running.begin()+1, running.end(), [](process& f){ f.wait +=1; f.priority = 1+(f.wait/f.bt);});
			for(int i=0;i<running.size();i++)
			{
				running[i].wait+=1;
				running[i].priority=1+(running[i].wait/running[i].bt);
			}
		}
		timer++;
	}
	while(!running.empty() || !list.empty() || !incpu.empty());
		
	getch();
	printf("\n\n\nexecution order ==>\n\n\n");
	float tatavg=0,waitavg=0;
		for(int i=0;i<completed.size();++i)
		{
		printf("%d ==> ",completed[i].p_id);
		completed[i].bt+=completed[i].tat;
		completed[i].tat+=completed[i].wait;
		tatavg+=completed[i].tat;
		waitavg+=completed[i].wait;
		}	
		printf("END\n\n\n========================================================\n\n\n");
		printf("PROCESS\t\tARRIVAL TIME\t\tBURST TIME\t\tWAIT TIME\t\tTURNAROUND TIME");
		for(int i=0;i<completed.size();++i)
		{
		printf("\nP%d\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d ",completed[i].p_id,completed[i].at,completed[i].bt,completed[i].wait,completed[i].tat);
		}
		printf("\n\n\nAverage turn around time: %.2f\nAverage wait time:%.2f",tatavg/completed.size(),waitavg/completed.size());
}
