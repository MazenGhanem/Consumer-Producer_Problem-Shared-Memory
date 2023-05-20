#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <unistd.h>
#include <deque>
#include <chrono>
#include <thread>

using namespace boost;
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;


#define MAX_COMMODITY_NAME_LENGTH 10
#define PROJ_ID 70
#define LAST_LINE 16

struct commodity
{
    char name[MAX_COMMODITY_NAME_LENGTH];
    double price;
};

static int st_idx;
static int end_idx;

commodity *get_shm_ptr(int N)
{
    st_idx = 0;
    end_idx = -1;
    // ftok to generate unique key
    key_t key = ftok("sharedmemory", PROJ_ID);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(commodity) * N, 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    return (commodity *)shmat(shmid, 0, 0);
}



struct consumer
{

    double price;
    double avg_price;

}; 


int main(int argc,char *argv[])
{
    commodity *shm_ptr = get_shm_ptr(atoi(argv[1]));
int sem;
int sem_id = 1;
key_t key;
key = ftok("/virtualpathtosemaphore", 1);
sem = semget(key, 1, IPC_CREAT);
semctl(sem_id, 0, IPC_RMID);
struct sembuf semopinc = {
  .sem_num = 0,
  .sem_op = 1,
  .sem_flg = 0
};    
/* decrement semaphore, may block */
struct sembuf semopdec = {
  .sem_num = 0,
  .sem_op = -1,
  .sem_flg = 0
}; 

    for(int i=0;i<atoi(argv[1]);i++)
    {
        strcpy(shm_ptr[i].name,"XXXXXXXXXX");
    }

    printf("\033[2;0H+-------------------------------------+\n");
    printf("\033[3;0H| Currency    |   Price   | AvgPrice  |\n");
    printf("\033[4;0H+-------------------------------------+\n");

   /*  printf("| %-14s| \033[1;36m%7.2lf\033[0m  | \033[1;36m%7.2lf\033[0m  |\n"); */
   /*  printf("\033[5;0H\033[1;36m| Gold \033[0m         \033[5;15H| %7.2lf     \033[5;27H| %7.2lf    \033[5;39H|\n",t,t); */
    double t;
     printf("\033[5;0H| ALUMINIUM   \033[5;15H| \033[1;36m%7.2lf \033[0m    \033[5;27H| \033[1;36m%7.2lf \033[0m    \033[5;39H|\n",t,t) ;
     printf("\033[6;0H| COPPER      \033[6;15H| \033[1;36m%7.2lf \033[0m    \033[6;27H| \033[1;36m%7.2lf \033[0m    \033[6;39H|\n",t,t) ;
     printf("\033[7;0H| COTTON      \033[7;15H| \033[1;36m%7.2lf \033[0m    \033[7;27H| \033[1;36m%7.2lf \033[0m    \033[7;39H|\n",t,t) ;
     printf("\033[8;0H| CRUDEOIL    \033[8;15H| \033[1;36m%7.2lf \033[0m    \033[8;27H| \033[1;36m%7.2lf \033[0m    \033[8;39H|\n",t,t) ;
     printf("\033[9;0H| GOLD        \033[9;15H| \033[1;36m%7.2lf \033[0m    \033[9;27H| \033[1;36m%7.2lf \033[0m    \033[9;39H|\n",t,t) ;
    printf("\033[10;0H| LEAD        \033[10;15H| \033[1;36m%7.2lf \033[0m   \033[10;27H| \033[1;36m%7.2lf \033[0m   \033[10;39H|\n",t,t);
    printf("\033[11;0H| MENTHAOIL   \033[11;15H| \033[1;36m%7.2lf \033[0m   \033[11;27H| \033[1;36m%7.2lf \033[0m   \033[11;39H|\n",t,t);
    printf("\033[12;0H| NATURALGAS  \033[12;15H| \033[1;36m%7.2lf \033[0m   \033[12;27H| \033[1;36m%7.2lf \033[0m   \033[12;39H|\n",t,t);
    printf("\033[13;0H| NICKEL      \033[13;15H| \033[1;36m%7.2lf \033[0m   \033[13;27H| \033[1;36m%7.2lf \033[0m   \033[13;39H|\n",t,t);
    printf("\033[14;0H| SILVER      \033[14;15H| \033[1;36m%7.2lf \033[0m   \033[14;27H| \033[1;36m%7.2lf \033[0m   \033[14;39H|\n",t,t);
    printf("\033[15;0H| ZINC        \033[15;15H| \033[1;36m%7.2lf \033[0m   \033[15;27H| \033[1;36m%7.2lf \033[0m   \033[15;39H|\n",t,t);
    printf("\033[16;0H+-------------------------------------+\n");





    double Goldprice[5]={0.0,0.0,0.0,0.0,0.0} ;int goldcounter=0;double Goldmean;double PrevGoldmean;double PrevGoldprice;
    double silverprice[5]={0.0,0.0,0.0,0.0,0.0};int silvercounter=0;double silvermean;double Prevsilvermean;double Prevsilverprice;
    double CRUDEOILprice[5]={0.0,0.0,0.0,0.0,0.0};int CRUDEOILcounter=0;double CRUDEOILmean;double PrevCRUDEOILmean;double PrevCRUDEOILprice;
    double NATURALGASprice[5]={0.0,0.0,0.0,0.0,0.0};int NATURALGAScounter=0;double NATURALGASmean;double PrevNATURALGASmean;double PrevNATURALGASprice;
    double ALUMINIUMprice[5]={0.0,0.0,0.0,0.0,0.0};int ALUMINIUMcounter=0;double ALUMINIUMmean;double PrevALUMINIUMmean;double PrevALUMINIUMprice;
    double COPPERprice[5]={0.0,0.0,0.0,0.0,0.0};int COPPERcounter=0;double COPPERmean;double PrevCOPPERmean;double PrevCOPPERprice;
    double NICKELprice[5]={0.0,0.0,0.0,0.0,0.0};int NICKELcounter=0;double NICKELmean;double PrevNICKELmean;double PrevNICKELprice;
    double LEADprice[5]={0.0,0.0,0.0,0.0,0.0};int LEADcounter=0;double LEADmean;double PrevLEADmean;double PrevLEADprice;
    double ZINCprice[5]={0.0,0.0,0.0,0.0,0.0};int ZINCcounter=0;double ZINCmean;double PrevZINCmean;double PrevZINCprice;
    double MENTHAOILprice[5]={0.0,0.0,0.0,0.0,0.0};int MENTHAOILcounter=0;double MENTHAOILmean;double PrevMENTHAOILmean;double PrevMENTHAOILprice;
    double COTTONprice[5]={0.0,0.0,0.0,0.0,0.0};int COTTONcounter=0;double COTTONmean;double PrevCOTTONmean;double PrevCOTTONprice;

    while(1)
    {  semop(sem, &semopdec, 1);
        for(int i=atoi(argv[1]);i>=0;i--)
        {
            printf("\033[1:0HChecking index =%d \n",i);
            usleep(10000);

            if(  !strcmp(shm_ptr[i].name,"GOLD")   )
            {
                i=0;
                if(shm_ptr[i].price==PrevGoldprice){break;}
                if(goldcounter>=5){Goldprice[0]=Goldprice[1];Goldprice[1]=Goldprice[2];Goldprice[2]=Goldprice[3];Goldprice[3]=Goldprice[4];Goldprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    
                    if(Goldprice[j]==0.0)
                    {
                     Goldprice[j]=shm_ptr[i].price;
                     Goldmean=(Goldprice[0]+Goldprice[1]+Goldprice[2]+Goldprice[3]+Goldprice[4])/5.0;
                     if(shm_ptr[i].price>PrevGoldprice)
                     {printf("\033[9;0H| GOLD         \033[9;15H| \033[1;32m%7.2lf↑ \033[0m      ",Goldprice[j]);}
                     else if(shm_ptr[i].price<PrevGoldprice)
                     {printf("\033[9;0H| GOLD        \033[9;15H| \033[1;31m%7.2lf↓ \033[0m       ",Goldprice[j]);}
                     if(Goldmean>PrevGoldmean)
                     {printf("\033[9;27H| \033[1;32m%7.2lf↑ \033[0m \033[9;39H| ",Goldmean);}
                     else if(Goldmean<PrevGoldmean)
                     {printf("\033[9;27H| \033[1;31m%7.2lf↓ \033[0m  \033[9;39H| ",Goldmean);}
                     goldcounter++;
                     PrevGoldmean=Goldmean;
                     PrevGoldprice=Goldprice[j];
                     break;
                    }
                }
            }
            

           
             if(!strcmp(shm_ptr[i].name,"SILVER"))
            {
                i=2;
                if(shm_ptr[i].price==Prevsilverprice){break;}
                if(silvercounter>=5){silverprice[0]=silverprice[1];silverprice[1]=silverprice[2];silverprice[2]=silverprice[3];silverprice[3]=silverprice[4];silverprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(silverprice[j]==0.0)
                    {
                     silverprice[j]=shm_ptr[i].price;
                     silvermean=(silverprice[0]+silverprice[1]+silverprice[2]+silverprice[3]+silverprice[4])/5.0;
                     if(shm_ptr[i].price>Prevsilverprice)
                     {printf("\033[14;0H| SILVER         \033[14;15H| \033[1;32m%7.2lf↑ \033[0m       ",silverprice[j]);}
                     else if(shm_ptr[i].price<Prevsilverprice)
                     {printf("\033[14;0H| SILVER        \033[14;15H| \033[1;31m%7.2lf↓ \033[0m      ",silverprice[j]);}
                     if(silvermean>Prevsilvermean)
                     {printf("\033[14;27H| \033[1;32m%7.2lf↑ \033[0m \033[14;39H| ",silvermean);}
                     else if (silvermean<Prevsilvermean)
                     {printf("\033[14;27H| \033[1;31m%7.2lf↓ \033[0m   \033[14;39H| ",silvermean);}
                     silvercounter++;
                     Prevsilvermean=silvermean;
                     Prevsilverprice=silverprice[j];
                      
                     break;
                    }
                }
            }

            if(!strcmp(shm_ptr[i].name,"CRUDEOIL"))
            {
                i=4;
                if(shm_ptr[i].price==PrevCRUDEOILprice){break;}
                if(CRUDEOILcounter>=5){CRUDEOILprice[0]=CRUDEOILprice[1];CRUDEOILprice[1]=CRUDEOILprice[2];CRUDEOILprice[2]=CRUDEOILprice[3];CRUDEOILprice[3]=CRUDEOILprice[4];CRUDEOILprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(CRUDEOILprice[j]==0.0)
                    {
                     CRUDEOILprice[j]=shm_ptr[i].price;
                     CRUDEOILmean=(CRUDEOILprice[0]+CRUDEOILprice[1]+CRUDEOILprice[2]+CRUDEOILprice[3]+CRUDEOILprice[4])/5.0;
                     if(shm_ptr[i].price>PrevCRUDEOILprice)
                     {printf("\033[8;0H| CRUDEOIL         \033[8;15H| \033[1;32m%7.2lf↑ \033[0m       ",CRUDEOILprice[j]);}
                     else if(shm_ptr[i].price<PrevCRUDEOILprice)
                     {printf("\033[8;0H| CRUDEOIL        \033[8;15H| \033[1;31m%7.2lf↓ \033[0m      ",CRUDEOILprice[j]);}
                     if(CRUDEOILmean>PrevCRUDEOILmean)
                     {printf("\033[8;27H| \033[1;32m%7.2lf↑ \033[0m \033[8;39H| ",CRUDEOILmean);}
                     else if (CRUDEOILmean<PrevCRUDEOILmean)
                     {printf("\033[8;27H| \033[1;31m%7.2lf↓ \033[0m   \033[8;39H| ",CRUDEOILmean);}
                     CRUDEOILcounter++;
                     PrevCRUDEOILmean=CRUDEOILmean;
                     PrevCRUDEOILprice=CRUDEOILprice[j];
                      
                     break;
                    }
                }
            }


            if(!strcmp(shm_ptr[i].name,"NATURALGAS"))
            {
                i=6;
                if(shm_ptr[i].price==PrevNATURALGASprice){break;}
                if(NATURALGAScounter>=5){NATURALGASprice[0]=NATURALGASprice[1];NATURALGASprice[1]=NATURALGASprice[2];NATURALGASprice[2]=NATURALGASprice[3];NATURALGASprice[3]=NATURALGASprice[4];NATURALGASprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(NATURALGASprice[j]==0.0)
                    {
                     NATURALGASprice[j]=shm_ptr[i].price;
                     NATURALGASmean=(NATURALGASprice[0]+NATURALGASprice[1]+NATURALGASprice[2]+NATURALGASprice[3]+NATURALGASprice[4])/5.0;
                     if(shm_ptr[i].price>PrevNATURALGASprice)
                     {printf("\033[12;0H| NATURALGAS         \033[12;15H| \033[1;32m%7.2lf↑ \033[0m       ",NATURALGASprice[j]);}
                     else if(shm_ptr[i].price<PrevNATURALGASprice)
                     {printf("\033[12;0H| NATURALGAS        \033[12;15H| \033[1;31m%7.2lf↓ \033[0m      ",NATURALGASprice[j]);}
                     if(NATURALGASmean>PrevNATURALGASmean)
                     {printf("\033[12;27H| \033[1;32m%7.2lf↑ \033[0m \033[12;39H| ",NATURALGASmean);}
                     else if (NATURALGASmean<PrevNATURALGASmean)
                     {printf("\033[12;27H| \033[1;31m%7.2lf↓ \033[0m   \033[12;39H| ",NATURALGASmean);}
                     NATURALGAScounter++;
                     PrevNATURALGASmean=NATURALGASmean;
                     PrevNATURALGASprice=NATURALGASprice[j];
                      
                     break;
                    }
                }
            }


            if(!strcmp(shm_ptr[i].name,"ALUMINIUM"))
            {
                i=8;
                if(shm_ptr[i].price==PrevALUMINIUMprice){break;}
                if(ALUMINIUMcounter>=5){ALUMINIUMprice[0]=ALUMINIUMprice[1];ALUMINIUMprice[1]=ALUMINIUMprice[2];ALUMINIUMprice[2]=ALUMINIUMprice[3];ALUMINIUMprice[3]=ALUMINIUMprice[4];ALUMINIUMprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(ALUMINIUMprice[j]==0.0)
                    {
                     ALUMINIUMprice[j]=shm_ptr[i].price;
                     ALUMINIUMmean=(ALUMINIUMprice[0]+ALUMINIUMprice[1]+ALUMINIUMprice[2]+ALUMINIUMprice[3]+ALUMINIUMprice[4])/5.0;
                     if(shm_ptr[i].price>PrevALUMINIUMprice)
                     {printf("\033[5;0H| ALUMINIUM         \033[5;15H| \033[1;32m%7.2lf↑ \033[0m       ",ALUMINIUMprice[j]);}
                     else if(shm_ptr[i].price<PrevALUMINIUMprice)
                     {printf("\033[5;0H| ALUMINIUM        \033[5;15H| \033[1;31m%7.2lf↓ \033[0m      ",ALUMINIUMprice[j]);}
                     if(ALUMINIUMmean>PrevALUMINIUMmean)
                     {printf("\033[5;27H| \033[1;32m%7.2lf↑ \033[0m \033[5;39H| ",ALUMINIUMmean);}
                     else if (ALUMINIUMmean<PrevALUMINIUMmean)
                     {printf("\033[5;27H| \033[1;31m%7.2lf↓ \033[0m   \033[5;39H| ",ALUMINIUMmean);}
                     ALUMINIUMcounter++;
                     PrevALUMINIUMmean=ALUMINIUMmean;
                     PrevALUMINIUMprice=ALUMINIUMprice[j];
                      
                     break;
                    }
                }
            }


            if(!strcmp(shm_ptr[i].name,"COPPER"))
            {
                i=10;
                if(shm_ptr[i].price==PrevCOPPERprice){break;}
                if(COPPERcounter>=5){COPPERprice[0]=COPPERprice[1];COPPERprice[1]=COPPERprice[2];COPPERprice[2]=COPPERprice[3];COPPERprice[3]=COPPERprice[4];COPPERprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(COPPERprice[j]==0.0)
                    {
                     COPPERprice[j]=shm_ptr[i].price;
                     COPPERmean=(COPPERprice[0]+COPPERprice[1]+COPPERprice[2]+COPPERprice[3]+COPPERprice[4])/5.0;
                     if(shm_ptr[i].price>PrevCOPPERprice)
                     {printf("\033[6;0H| COPPER         \033[6;15H| \033[1;32m%7.2lf↑ \033[0m       ",COPPERprice[j]);}
                     else if(shm_ptr[i].price<PrevCOPPERprice)
                     {printf("\033[6;0H| COPPER        \033[6;15H| \033[1;31m%7.2lf↓ \033[0m      ",COPPERprice[j]);}
                     if(COPPERmean>PrevCOPPERmean)
                     {printf("\033[6;27H| \033[1;32m%7.2lf↑ \033[0m \033[6;39H| ",COPPERmean);}
                     else if (COPPERmean<PrevCOPPERmean)
                     {printf("\033[6;27H| \033[1;31m%7.2lf↓ \033[0m   \033[6;39H| ",COPPERmean);}
                     COPPERcounter++;
                     PrevCOPPERmean=COPPERmean;
                     PrevCOPPERprice=COPPERprice[j];
                      
                     break;
                    }
                }
            }


            if(!strcmp(shm_ptr[i].name,"NICKEL"))
            {
                i=12;
                if(shm_ptr[i].price==PrevNICKELprice){break;}
                if(NICKELcounter>=5){NICKELprice[0]=NICKELprice[1];NICKELprice[1]=NICKELprice[2];NICKELprice[2]=NICKELprice[3];NICKELprice[3]=NICKELprice[4];NICKELprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(NICKELprice[j]==0.0)
                    {
                     NICKELprice[j]=shm_ptr[i].price;
                     NICKELmean=(NICKELprice[0]+NICKELprice[1]+NICKELprice[2]+NICKELprice[3]+NICKELprice[4])/5.0;
                     if(shm_ptr[i].price>PrevNICKELprice)
                     {printf("\033[13;0H| NICKEL         \033[13;15H| \033[1;32m%7.2lf↑ \033[0m       ",NICKELprice[j]);}
                     else if(shm_ptr[i].price<PrevNICKELprice)
                     {printf("\033[13;0H| NICKEL        \033[13;15H| \033[1;31m%7.2lf↓ \033[0m      ",NICKELprice[j]);}
                     if(NICKELmean>PrevNICKELmean)
                     {printf("\033[13;27H| \033[1;32m%7.2lf↑ \033[0m \033[13;39H| ",NICKELmean);}
                     else if (NICKELmean<PrevNICKELmean)
                     {printf("\033[13;27H| \033[1;31m%7.2lf↓ \033[0m   \033[13;39H| ",NICKELmean);}
                     NICKELcounter++;
                     PrevNICKELmean=NICKELmean;
                     PrevNICKELprice=NICKELprice[j];
                      
                     break;
                    }
                }
            }


            if(!strcmp(shm_ptr[i].name,"LEAD"))
            {
                i=14;
                if(shm_ptr[i].price==PrevLEADprice){break;}
                if(LEADcounter>=5){LEADprice[0]=LEADprice[1];LEADprice[1]=LEADprice[2];LEADprice[2]=LEADprice[3];LEADprice[3]=LEADprice[4];LEADprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(LEADprice[j]==0.0)
                    {
                     printf("\033[20;0H\n");
                     LEADprice[j]=shm_ptr[i].price;
                     LEADmean=(LEADprice[0]+LEADprice[1]+LEADprice[2]+LEADprice[3]+LEADprice[4])/5.0;
                     if(shm_ptr[i].price>PrevLEADprice)
                     {printf("\033[10;0H| LEAD         \033[10;15H| \033[1;32m%7.2lf↑ \033[0m       ",LEADprice[j]);}
                     else if(shm_ptr[i].price<PrevLEADprice)
                     {printf("\033[10;0H| LEAD        \033[10;15H| \033[1;31m%7.2lf↓ \033[0m      ",LEADprice[j]);}
                     if(LEADmean>PrevLEADmean)
                     {printf("\033[10;27H| \033[1;32m%7.2lf↑ \033[0m \033[10;39H| ",LEADmean);}
                     else if (LEADmean<PrevLEADmean)
                     {printf("\033[10;27H| \033[1;31m%7.2lf↓ \033[0m   \033[10;39H| ",LEADmean);}
                     LEADcounter++;
                     PrevLEADmean=LEADmean;
                     PrevLEADprice=LEADprice[j];
                      
                     break;
                    }
                }
            }


            if(!strcmp(shm_ptr[i].name,"ZINC"))
            {
                i=16;
                if(shm_ptr[i].price==PrevZINCprice){break;}
                if(ZINCcounter>=5){ZINCprice[0]=ZINCprice[1];ZINCprice[1]=ZINCprice[2];ZINCprice[2]=ZINCprice[3];ZINCprice[3]=ZINCprice[4];ZINCprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(ZINCprice[j]==0.0)
                    {
                     ZINCprice[j]=shm_ptr[i].price;
                     ZINCmean=(ZINCprice[0]+ZINCprice[1]+ZINCprice[2]+ZINCprice[3]+ZINCprice[4])/5.0;
                     if(shm_ptr[i].price>PrevZINCprice)
                     {printf("\033[15;0H| ZINC         \033[15;15H| \033[1;32m%7.2lf↑ \033[0m       ",ZINCprice[j]);}
                     else if(shm_ptr[i].price<PrevZINCprice)
                     {printf("\033[15;0H| ZINC        \033[15;15H| \033[1;31m%7.2lf↓ \033[0m      ",ZINCprice[j]);}
                     if(ZINCmean>PrevZINCmean)
                     {printf("\033[15;27H| \033[1;32m%7.2lf↑ \033[0m \033[15;39H| ",ZINCmean);}
                     else if (ZINCmean<PrevZINCmean)
                     {printf("\033[15;27H| \033[1;31m%7.2lf↓ \033[0m   \033[15;39H| ",ZINCmean);}
                     ZINCcounter++;
                     PrevZINCmean=ZINCmean;
                     PrevZINCprice=ZINCprice[j];
                      
                     break;
                    }
                }
            }


            if(!strcmp(shm_ptr[i].name,"MENTHAOIL"))
            {
                i=18;
                if(shm_ptr[i].price==PrevMENTHAOILprice){break;}
                if(MENTHAOILcounter>=5){MENTHAOILprice[0]=MENTHAOILprice[1];MENTHAOILprice[1]=MENTHAOILprice[2];MENTHAOILprice[2]=MENTHAOILprice[3];MENTHAOILprice[3]=MENTHAOILprice[4];MENTHAOILprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(MENTHAOILprice[j]==0.0)
                    {
                     MENTHAOILprice[j]=shm_ptr[i].price;
                     MENTHAOILmean=(MENTHAOILprice[0]+MENTHAOILprice[1]+MENTHAOILprice[2]+MENTHAOILprice[3]+MENTHAOILprice[4])/5.0;
                     if(shm_ptr[i].price>PrevMENTHAOILprice)
                     {printf("\033[11;0H| MENTHAOIL         \033[11;15H| \033[1;32m%7.2lf↑ \033[0m       ",MENTHAOILprice[j]);}
                     else if(shm_ptr[i].price<PrevMENTHAOILprice)
                     {printf("\033[11;0H| MENTHAOIL        \033[11;15H| \033[1;31m%7.2lf↓ \033[0m      ",MENTHAOILprice[j]);}
                     if(MENTHAOILmean>PrevMENTHAOILmean)
                     {printf("\033[11;27H| \033[1;32m%7.2lf↑ \033[0m \033[11;39H| ",MENTHAOILmean);}
                     else if (MENTHAOILmean<PrevMENTHAOILmean)
                     {printf("\033[11;27H| \033[1;31m%7.2lf↓ \033[0m   \033[11;39H| ",MENTHAOILmean);}
                     MENTHAOILcounter++;
                     PrevMENTHAOILmean=MENTHAOILmean;
                     PrevMENTHAOILprice=MENTHAOILprice[j];
                      
                     break;
                    }
                }
            }


            if(!strcmp(shm_ptr[i].name,"COTTON"))
            {
                i=20;
                if(shm_ptr[i].price==PrevCOTTONprice){break;}
                if(COTTONcounter>=5){COTTONprice[0]=COTTONprice[1];COTTONprice[1]=COTTONprice[2];COTTONprice[2]=COTTONprice[3];COTTONprice[3]=COTTONprice[4];COTTONprice[4]=0.0;}
                for(int j=0;j<5;j++)
                {
                    if(COTTONprice[j]==0.0)
                    {
                     COTTONprice[j]=shm_ptr[i].price;
                     COTTONmean=(COTTONprice[0]+COTTONprice[1]+COTTONprice[2]+COTTONprice[3]+COTTONprice[4])/5.0;
                     if(shm_ptr[i].price>PrevCOTTONprice)
                     {printf("\033[7;0H| COTTON         \033[7;15H| \033[1;32m%7.2lf↑ \033[0m       ",COTTONprice[j]);}
                     else if(shm_ptr[i].price<PrevCOTTONprice)
                     {printf("\033[7;0H| COTTON        \033[7;15H| \033[1;31m%7.2lf↓ \033[0m      ",COTTONprice[j]);}
                     if(COTTONmean>PrevCOTTONmean)
                     {printf("\033[7;27H| \033[1;32m%7.2lf↑ \033[0m \033[7;39H| ",COTTONmean);}
                     else if (COTTONmean<PrevCOTTONmean)
                     {printf("\033[7;27H| \033[1;31m%7.2lf↓ \033[0m   \033[7;39H| ",COTTONmean);}
                     COTTONcounter++;
                     PrevCOTTONmean=COTTONmean;
                     PrevCOTTONprice=COTTONprice[j];
                      
                     break;
                    }
                }
            }


        }

     
              semop(sem, &semopinc, 1);
    }

    
    return 0;
}