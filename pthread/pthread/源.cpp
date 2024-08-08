#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void* myThreadID1(void*)
{
    cout << "thread_ID1" << "\n";
}

void* myThreadID2(void*)
{
    cout << "thread_ID2" << "\n";
}

int main()
{
    int i = 0, ret = 0;
    pthread_t id1, id2;//声明线程ID

    ret = pthread_create(&id1, NULL, myThreadID1, NULL); //创建并执行线程id1
    if (ret == -1) {
        printf("Create pthread error!\n");
        return 1;
    }

    ret = pthread_create(&id2, NULL, myThreadID2, NULL); //创建并执行线程id2
    if (ret == -1) {
        printf("Create pthread error!\n");
        return 1;
    }

    pthread_join(id1, NULL);  //阻塞主线程，直到id1结束才接触，
    pthread_join(id2, NULL);

    cout << "all thread done!"<<endl;
    return 0;
}

