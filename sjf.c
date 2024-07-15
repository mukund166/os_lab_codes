#include <stdio.h>
#include <limits.h>

struct P{
    int id;
    int bt;
    int at;
    int wt;
    int tat;
    int rt;
    int st;
    int et;
    int v;
};

void main(){
    int n,ct=0;
    float awt=0,atat=0,art=0,tp;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    struct P p[n];
    struct P temp;
    for(int i=0;i<n;i++){
        p[i].id=i+1;
        p[i].v=0;
        printf("Enter Burst Time and Arrival Time of P%d: ",i+1);
        scanf("%d %d",&p[i].bt,&p[i].at);
    }

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(p[i].at>p[j].at){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
            if(p[i].at==p[j].at){
                if(p[i].bt>p[j].bt){
                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
            }
        }
    }

    int cf=p[0].bt, min=INT_MAX,m,count=0;
    p[0].v=1;

    while(count<n-1){
    for(int i=0;i<n;i++){
        if(p[i].at<=cf && p[i].v==0){
            if(p[i].bt<min){
                min=p[i].bt;
                m=i;
            }
        }
    }
    p[m].v=1;
    cf+=p[m].bt;
    min=INT_MAX;

    temp=p[count+1];
    p[count+1]=p[m];
    p[m]=temp;

    count++;
    }

    printf("Process\tWaiting Time\tTurn Around Time\tResponse Time\n");

    for(int i=0;i<n;i++){
        if(p[i].at<ct){
            p[i].st=ct;
        }
        else{
            p[i].st=p[i].at;
        }
        p[i].et=p[i].st+p[i].bt;
        ct+=p[i].bt;

        p[i].tat=p[i].et-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        p[i].rt=p[i].st-p[i].at;

        printf("%d\t\t%d\t\t%d\t\t%d\n",p[i].id,p[i].wt,p[i].tat,p[i].rt);
        awt+=p[i].wt;
        atat+=p[i].tat;
        art+=p[i].rt;
    }

    tp=(float)p[n-1].et/n;
    printf("Average Waiting Time: %.2f\n",awt/n);
    printf("Average Turn Around Time: %.2f\n",atat/n);
    printf("Average Response Time: %.2f\n",art/n);
    printf("Throughput: %.2f",tp);

}
