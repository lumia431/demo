#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;

pthread_mutex_t mtx1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx3 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx4 = PTHREAD_MUTEX_INITIALIZER;

void* routine1(void* arg) {

	pthread_mutex_lock(&mtx1);
	sleep(1);
	pthread_mutex_lock(&mtx2);

	pthread_mutex_unlock(&mtx2);
	pthread_mutex_unlock(&mtx1);

}

void* routine2(void* arg) {

	pthread_mutex_lock(&mtx2);
	sleep(1);
	pthread_mutex_lock(&mtx1);

	pthread_mutex_unlock(&mtx1);
	pthread_mutex_unlock(&mtx2);

}

void* routine3(void* arg) {

}

void* routine4(void* arg) {


}





int main() {

	pthread_t tid1, tid2, tid3, tid4;

	pthread_create(&tid1, NULL, routine1, NULL);
	pthread_create(&tid2, NULL, routine2, NULL);
	pthread_create(&tid3, NULL, routine3, NULL);
	pthread_create(&tid4, NULL, routine4, NULL);


	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
	pthread_join(tid4, NULL);
	cout << "over" << endl;
	return 0;
}
