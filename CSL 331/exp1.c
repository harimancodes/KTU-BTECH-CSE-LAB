#include<stdio.h>
#include<stdlib.h>
#define MAX 20

int p[MAX],a_time[MAX]={0},b_time[MAX]={0},t_time[MAX]={0},w_time[MAX]={0},c_time[MAX]={0};
int n;
float avg_w_time=0.0,avg_t_time=0.0;

int queue[MAX];
int front=-1,rear=-1;

void enqueue(int p){
	if(rear==MAX-1)
		printf("Queue full");
		
	if(front==-1&&rear==-1){
		front=rear=0;			
		queue[rear]=p;	
	}else{
			rear++;
			queue[rear]=p;		
		}

}

int dequeue(){
	if(front==-1 && rear==-1)
		return -1;
	if(front==rear){
		int r=queue[front];
		front=rear=-1;
		return r;			
	}else{
		return queue[front++];	
	}
}

int exists_in_q(int p){
	for(int i=front;i<=rear;i++){
		if(queue[i]==p)
			return 1;
	}return 0;
}

void avg_time(float w,float t,int n){
	printf("\nAverage Waiting Time : %.2f",w/n);
	printf("\nAverage Turnaround Time : %.2f",t/n);
}

void sort(int p[],int a_time[],int b_time[],int n){
	for(int i=1;i<n;i++){
		for(int j=0;j<n-i;j++){
			if(a_time[j]>a_time[j+1]){
				int temp=p[j];
				p[j]=p[j+1];
				p[j+1]=temp;
				
				temp=a_time[j];
				a_time[j]=a_time[j+1];
				a_time[j+1]=temp;

				temp=b_time[j];
				b_time[j]=b_time[j+1];
				b_time[j+1]=temp;
			}
		}
	}
}

void fcfs(){
	int timer=0;
	
	printf("\t\t\tFCFS");
	printf("\n\t\t\t----");
	
	printf("\nEnter the no.of processes : ");
	scanf("%d",&n);
	
	for(int i=0;i<n;i++){
		p[i]=i+1;
		printf("\nEnter the arrival time of P%d : ",p[i]);
		scanf("%d",&a_time[i]);
		
		printf("\nEnter the burst time of P%d : ",p[i]);
		scanf("%d",&b_time[i]);
		
	}
	
	sort(p,a_time,b_time,n);
	
	c_time[0]=b_time[0];
	timer=c_time[0];
	for(int i=1;i<n;i++){
		if(a_time[i]>timer)
			timer=a_time[i];
		c_time[i]=timer+b_time[i];
		timer=c_time[i];
	}	
	for(int i=0;i<n;i++){
	
		t_time[i]=c_time[i]-a_time[i];
		w_time[i]=t_time[i]-b_time[i];
		avg_w_time+=w_time[i];
		avg_t_time+=t_time[i];
	}
	
	printf("\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
	for(int i=0;i<n;i++){
		printf("P%d\t%d\t%d\t%d\t\t%d\t\t%d\n",p[i],a_time[i],b_time[i],c_time[i],t_time[i],w_time[i]);
	}
	
	avg_time(avg_w_time,avg_t_time,n);
}

void sjf(){

	printf("\t\t\tSJF");
	printf("\n\t\t\t---");

	printf("\nEnter the total no.of processes<maximum 20> : ");
	scanf("%d",&n);

	printf("\nEnter Process Burst Time\n");
	for(int i=0;i<n;i++){
		printf("P[%d] : ",i+1);
		scanf("%d",&b_time[i]);
		p[i]=i+1;	
		
	}
	sort(p,b_time,a_time,n);
	
	c_time[0]=b_time[0];
	for(int i=1;i<n;i++){
		c_time[i]=c_time[i-1]+b_time[i];
	}
		
	for(int i=0;i<n;i++){
		t_time[i]=c_time[i]-a_time[i];
		w_time[i]=t_time[i]-b_time[i];
		avg_w_time+=w_time[i];
		avg_t_time+=t_time[i];
	}	
	
	printf("\nProcess\t\tBurst Time\tWaiting Time\tTurnaround Time\n");
	for(int i=0;i<n;i++){
		printf("P[%d]\t\t%d\t\t%d\t\t%d\n",p[i],b_time[i],w_time[i],t_time[i]);
	}
	avg_time(avg_w_time,avg_t_time,n);
}

void priority(){
	int prio[MAX];
	

	printf("\t\t\tPRIORITY");
	printf("\n\t\t\t-------");

	printf("\nEnter the total no.of processes<maximum 20> : ");
	scanf("%d",&n);

	for(int i=0;i<n;i++){
		p[i]=i+1;
		
		printf("\nEnter the burst time of P%d : ",p[i]);
		scanf("%d",&b_time[i]);
		
		printf("\nEnter the priority of P%d : ",p[i]);
		scanf("%d",&prio[i]);
	}
	sort(p,prio,b_time,n);
	
	c_time[0]=b_time[0];
	for(int i=1;i<n;i++){
		c_time[i]=c_time[i-1]+b_time[i];
	}
		
	for(int i=0;i<n;i++){
		t_time[i]=c_time[i]-a_time[i];
		w_time[i]=t_time[i]-b_time[i];
		avg_w_time+=w_time[i];
		avg_t_time+=t_time[i];
	}	
	
	
	printf("\nProcess\t\tPriority\tBurst Time\tWaiting Time\tTurnaround Time\n");
	for(int i=0;i<n;i++){
		printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i],prio[i],b_time[i],w_time[i],t_time[i]);
	}
	avg_time(avg_w_time,avg_t_time,n);
}

void round_robin(){
	int time_slice,rem_b_time[MAX]={0},sum_bt=0,completed[MAX]={0};
	printf("\t\t\tRound Robin");
	printf("\n\t\t\t----------");
	
	printf("\nEnter the total no.of processes<maximum 20> : ");
	scanf("%d",&n);
	
	for(int i=0;i<n;i++){
		p[i]=i+1;
		printf("\nEnter the arrival time of P%d : ",p[i]);
		scanf("%d",&a_time[i]);
		printf("\nEnter the burst time of P%d : ",p[i]);
		scanf("%d",&b_time[i]);
		rem_b_time[i]=b_time[i];
		sum_bt+=b_time[i];
	}
	printf("Enter the time slice : ");
	scanf("%d",&time_slice);
	
	sort(p,a_time,b_time,n);
	
	int timer=0;
	enqueue(p[0]-1);
	
	for(timer=a_time[0];timer<sum_bt;){
		int i=dequeue();
		
		if(rem_b_time[i]>time_slice){
			rem_b_time[i]-=time_slice;
			timer+=time_slice;
			for(int j=0;j<n;j++){
				if(a_time[j]<=timer && completed[p[j]-1]!=1 && i!=(p[j]-1) && exists_in_q(p[j]-1)==0){
					enqueue(p[j]-1);
				}
			}
				enqueue(i);	
		}else{
			timer+=rem_b_time[i];
			rem_b_time[i]=0;
			completed[i]=1;
			for(int j=0;j<n;j++){
				if(a_time[j]<=timer && completed[p[j]-1]!=1 && exists_in_q(p[j]-1)==0){
					enqueue(p[j]-1);
				}
			}
			c_time[p[i]-1]=timer;
		}	
	}
	for(int i=0;i<n;i++){
		t_time[i]=c_time[i]-a_time[i];
		w_time[i]=t_time[i]-b_time[i];
	}
	for(int i=0;i<n;i++){
		avg_w_time+=w_time[i];
		avg_t_time+=t_time[i];
	}
	
	printf("\nProcess\t\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
	for(int i=0;i<n;i++){
		printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i],a_time[i],b_time[i],c_time[i],w_time[i],t_time[i]);
	}
	
	avg_time(avg_w_time,avg_t_time,n);
}

int main(){
	int choice;
	printf("1)FCFS\n2)SJF\n3)ROUND ROBIN\n4)PRIORITY\n5)EXIT");
	while(1){
		printf("\nChoose the algorithm : ");
		scanf("%d",&choice);
		
		switch(choice){
			case 1:fcfs();
				break;
			case 2:sjf();
				break;
			case 3:round_robin();
				break;
			case 4:priority();
				break;
			case 5:return 0;
			default :printf("Wrong choice!");
		}
		
	}
}
