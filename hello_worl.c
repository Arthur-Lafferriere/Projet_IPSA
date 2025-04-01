#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "unistd.h"
#include "windows.h"

HANDLE semaphore;

DWORD WINAPI ThreadFunction(LPVOID lpParam) {
	int threadNum = *(int*)lpParam;
    printf("Il y a %d Thread(s) en attente d'acces...\n",threadNum);

    // Attente de l'acquisition du sémaphore
    WaitForSingleObject(semaphore, INFINITE);
    
    printf("Thread %d a acquis le semaphore et travaille maintenant...\n",threadNum); 
    printf("Hello World\n");
    sleep(5*threadNum);

    // Libère le sémaphore
    ReleaseSemaphore(semaphore, 1, NULL);
    printf("Thread %d a libere le semaphore.\n",threadNum);

    return 0;
}


void task5(int a){
	int number=a;
	int* lien=&a;
	printf("task 5 : La valeur entrer est de %d et son adresse est '%p'",number,lien);
	printf("\n\n");
}



void Sort(int *a,int taille){
	int i=0;
	int j=0;

	while(i<(taille-1)){
		j=0;
		while(j<(taille-1)){
			if(a[j]>a[j+1]){
				int value=a[j];
				a[j]=a[j+1];
				a[j+1]=value;
			}
			j++;
		}
		i++;
	}

}

void Selection_sort_ascending(int *a, int taille) {
    for (int i = 0; i < taille - 1; i++) {
        int indice_min = i; // Supposons que le min est à i
        for (int j = i + 1; j < taille; j++) { // Parcours de la partie non triée
            if (a[j] < a[indice_min]) { // Trouver l'élément min
                indice_min = j;
            }
        }
        // Échange l'élément min trouvé avec la première position non triée
        int temp = a[i];
        a[i] = a[indice_min];
        a[indice_min] = temp;
    }
}

void Selection_sort_descending(int *a, int taille) {
    for (int i = taille - 1; i > 0; i--) {
        int indice_max = i; // Supposons que le max est à i
        for (int j = i - 1; j >= 0; j--) { // Parcours de la partie non triée
            if (a[j] > a[indice_max]) { // Trouver l'élément max
                indice_max = j;
            }
        }
        // Échange l'élément max trouvé avec la dernière position non triée
        int temp = a[i];
        a[i] = a[indice_max];
        a[indice_max] = temp;
    }
}

double get_time() {
    LARGE_INTEGER frequency, start;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    return (double)start.QuadPart * 1000.0 / frequency.QuadPart;
}


int Binary_Search(int *a, int taille, int loocking_value){
    int debut = 0;
    int fin = taille - 1;

    while (debut <= fin) {
        int milieu = debut + (fin - debut) / 2;

        if (a[milieu] == loocking_value) {
            return milieu; // Valeur trouvée
        }

        if (a[milieu] < loocking_value) {
            debut = milieu + 1; // Cherche à droite
        } else {
            fin = milieu - 1; // Cherche à gauche
        }
    }

    return -1; // Valeur non trouvée
}

float task6(float a,float b){
	return a+b;
}


int main(void){
	
	printf("task 1 : Hello word \n\n");

	int A = 2;
	int B= 7;

	if (A>B){
		printf("task 2 : La plus grande valeur est %d car %d>%d \n\n",A,A,B);
	}
	else{
		printf("task 2 : La plus grande valeur est %d car %d>%d \n\n",B,B,A);
	}

	printf("task 3 : ");
	for (int i=0;i<=100;i++){
		printf("%d ",i);
	}
	printf("\n\n");

	printf("task 4 : ");
	int i=0;
	while(i<=100){
		printf("%d ",i);
		i++;
	}
	printf("\n\n");


	task5(10);

	float C=task6(A,B);

	printf("task 6 : si on fait la somme de %d et de %d, on obtient %f \n\n",A,B,C);

	printf("task 7 : on a la liste suivante : \n");

	srand(time(NULL));

	int taille_list=20;
	int list[taille_list];
	for (int i=0;i<taille_list;i++){
		list[i]=rand()%101;
	}

	int value = list[rand()%taille_list];

	printf("Liste = ");
	for (int i=0;i<taille_list;i++){
		printf("%d ",list[i]);
	}
	printf("\n");

	Sort(list,taille_list);

	printf("Liste = ");
	for (int i=0;i<taille_list;i++){
		printf("%d ",list[i]);
	}
	printf("\n");
	printf("\n");
	

	printf("task 8 : ");
	int indice= Binary_Search(list,taille_list,value);
	printf("On a trouver la valeur %d pour l'indice %d.\n",value,indice);
	printf("\n");


	printf("task 9 : on vas comparer le temp d'execution entre diffferent alogrythm de trie : \n");
	
	int taille_list2=1000;
	int list2[taille_list2];
	for (int i=0;i<taille_list2;i++){
		list2[i]=rand()%101+5*rand()%26;
	}

	// Bubble Sort
    double begin1 = get_time();
    Sort(list2, taille_list2);
    double end1 = get_time();
    double time_spent1 = end1 - begin1;
    printf("Finished in %.2f ms for bubble sort\n", time_spent1);

    // Tri par sélection croissant
    double begin2 = get_time();
    Selection_sort_ascending(list2, taille_list2);
    double end2 = get_time();
    double time_spent2 = end2 - begin2;
    printf("Finished in %.4f ms for ascending sort\n", time_spent2);

    // Tri par sélection décroissant
    double begin3 = get_time();
    Selection_sort_descending(list2, taille_list2);
    double end3 = get_time();
    double time_spent3 = end3 - begin3;
    printf("Finished in %.2f ms for descending sort\n", time_spent3);

    printf("\n");
    printf("%.4f\n", time_spent1);
    printf("%.4f\n", time_spent2);
    printf("%.4f\n", time_spent3);


    printf("\ntask 10 : Semaphores : \n");
    printf("On affiche une premier ligne maintenant et une autre dans 10 s:\n");
    sleep(10);
    printf("voila !! \n");

    int nombre_semaphore=3;

    semaphore=CreateSemaphore(NULL,2,2,NULL);

    if (semaphore == NULL) {
        printf("Erreur de création du sémaphore\n");
        return 1;
    }

    HANDLE threads[nombre_semaphore];
    int threadNums[nombre_semaphore];

    for (int i = 0; i < nombre_semaphore; i++) {
        threadNums[i] = i + 1;
        threads[i] = CreateThread(NULL,0,ThreadFunction,&threadNums[i],0,NULL);
        if (threads[i] == NULL) {
            printf("Erreur de création du thread %d\n", i + 1);
            return 1;
        }
    }

    WaitForMultipleObjects(nombre_semaphore, threads, TRUE, INFINITE);

    for (int i = 0; i < nombre_semaphore; i++) {
        CloseHandle(threads[i]);
    }
    CloseHandle(semaphore);

    /*
	// QUESTION 2/3/4

HANDLE mutex; // Déclaration du sémaphore

// Fonction du thread 1
DWORD WINAPI Thread1Function(LPVOID lpParam)
{
    WaitForSingleObject(mutex, INFINITE); // Verrouillage du sémaphore

    printf("HELLO WORLD !\n");
    Sleep(5000); // Attendre 5 secondes pour simuler une section critique longue

    ReleaseSemaphore(mutex, 1, NULL); // Libération du sémaphore
    return 0;
}

// Fonction du thread 2
DWORD WINAPI Thread2Function(LPVOID lpParam)
{
    WaitForSingleObject(mutex, INFINITE); // Attendre que Thread1 libère

    printf("GOOD BYE WORLD !\n");
    Sleep(5000); // Attendre 5 secondes pour simuler une section critique longue

    ReleaseSemaphore(mutex, 1, NULL); // Libération du sémaphore
    return 0;
}

// Fonction du thread 3
DWORD WINAPI Thread3Function(LPVOID lpParam)
{
    WaitForSingleObject(mutex, INFINITE); // Attendre que Thread1 libère

    printf("xoxo Gossip girl\n");

    ReleaseSemaphore(mutex, 1, NULL); // Libération du sémaphore
    return 0;
}

int main()
{
    HANDLE thread1, thread2, thread3;

    // Création du sémaphore (valeur initiale = 1, max = 1)
    mutex = CreateSemaphore(NULL, 1, 1, NULL);
    if (mutex == NULL)
    {
        printf("Erreur lors de la creation du sémaphore\n");
        return 1;
    }

    // Création du premier thread
    thread1 = CreateThread(NULL, 0, Thread1Function, NULL, 0, NULL);
    if (thread1 == NULL)
    {
        printf("Erreur de creation du thread1\n");
        CloseHandle(mutex);
        return 1;
    }

    // Création du deuxième thread
    thread2 = CreateThread(NULL, 0, Thread2Function, NULL, 0, NULL);
    if (thread2 == NULL)
    {
        printf("Erreur de creation du thread2\n");
        CloseHandle(mutex);
        CloseHandle(thread1);
        return 1;
    }

    // Création du deuxième thread
    thread3 = CreateThread(NULL, 0, Thread3Function, NULL, 0, NULL);
    if (thread3 == NULL)
    {
        printf("Erreur de creation du thread3\n");
        CloseHandle(mutex);
        CloseHandle(thread2);
        return 1;
    }

    // Attendre la fin des threads
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);
    WaitForSingleObject(thread3, INFINITE);

    // Fermer les handles
    CloseHandle(thread1);
    CloseHandle(thread2);
    CloseHandle(thread3);
    CloseHandle(mutex);

    return 0;
}
    */


    /* sur ubuntu 
    #include <stdio.h>
    #include <pthread.h>
    void* thread(void*arg){
		printf("\Hello World\n");
    }
    int main(){
	pthread_t t1;
	pthread_create(&t1,NULL,thread,NULL);
    }

    */




    return 0;




}