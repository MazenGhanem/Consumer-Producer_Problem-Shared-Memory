#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <unistd.h>
#include <deque>    
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ctime>
#include <chrono>
#include <thread>

using namespace boost;
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;


#define MAX_COMMODITY_NAME_LENGTH 10
#define PROJ_ID 70

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




struct producer
{
 char name[10];
 double mean;
 double std_dev;
 double sleep;
 int buffer_size;
}; 

std::string now_str()
{
    const boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    const boost::posix_time::time_duration td = now.time_of_day();
    const long hours        = td.hours();
    const long minutes      = td.minutes();
    const long seconds      = td.seconds();
    const long milliseconds = td.total_milliseconds() - ((hours * 3600 + minutes * 60 + seconds) * 1000);
    char buf[40];
    sprintf(buf, "%02ld:%02ld:%02ld.%03ld",hours, minutes, seconds, milliseconds);
    return buf;
}

int main(int argc,char *argv[])
{
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
    commodity *shm_ptr = get_shm_ptr(atoi(argv[5]));

    char s[80];
    time_t t = time(0);
    strftime(s, 80, "%m/%d/%Y", localtime(&t));

    producer p;
        strcpy(p.name, argv[1]);
        p.mean = stod(argv[2]);
        p.std_dev = stod(argv[3]);
        p.sleep = atoi(argv[4]);
        p.buffer_size = atoi(argv[5]);

    int i;
    while (true)
    {
        // Writing in shared memory shm_ptr[i].name="XXXXXXXXXX";
        /* if(i==atoi(argv[5]))
            {
                for(int i=0;i<atoi(argv[5]);i++){strcpy(shm_ptr[i].name,"XXXXXXXXXX");}
                i=0;
            } */
        
        while(i<=atoi(argv[5]))
        {
            semop(sem, &semopdec, 1);
            unsigned time = std::chrono::system_clock::now().time_since_epoch().count();
            std::default_random_engine generator(time);
            if((!strcmp(argv[1],"GOLD"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=0;
                while(i<1)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"SILVER"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=2;
                while( i<3)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"CRUDEOIL"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=4;
                while( i<5)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"NATURALGAS"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=6;
                while( i<7)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }
            
            if((!strcmp(argv[1],"ALUMINIUM"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=8;
                while( i<9)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"COPPER"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=10;
                while( i<11)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"NICKEL"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=12;
                while( i<13)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"LEAD"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=14;
                while( i<15)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"ZINC"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=16;
                while( i<17)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"MENTHAOIL"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=18;
                while( i<19)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }

            if((!strcmp(argv[1],"COTTON"))||( !strcmp(shm_ptr[i].name,"XXXXXXXXXX"))){
                i=20;
                while( i<21)
                {
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::normal_distribution<double> distribution(p.mean, p.std_dev);
                 strcpy(shm_ptr[i].name, p.name);
                 shm_ptr[i].price = abs(distribution(generator));
                 std::cerr << "generating New value ";
                 cout << shm_ptr[i].price << endl;
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 std::cerr << "trying to get mutex on shared buffer\n";
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("placing %1.2lf on shared buffer\n",shm_ptr[i].price);
                 std::cerr <<'['<< s << ' '; 
                 std::cerr << now_str() <<']'; 
                 std::cerr << ' ' << argv[1] << ':'<< ' ';
                 printf("sleeping for %1.0lf ms\n",p.sleep);
                 usleep(p.sleep*1000);
                 break;
                }
            }



        }
        
        semop(sem, &semopinc,1);
    }
    return 0;
} 

