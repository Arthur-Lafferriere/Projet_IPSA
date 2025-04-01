// Séance TP3 : Systèmes embarqués
// Semaphores in C

#include <stdio.h>
#include <unistd.h>
#include <windows.h>

// QUESTION 1
/*int main()
{
    // Première ligne
    printf("Premiere ligne : Debut de l'execution\n");

    // Attendre 10 secondes
    sleep(10);

    // Deuxième ligne imprimée après 10 secondes
    printf("Deuxieme ligne : 10 secondes se sont ecoulees\n");

    return 0;
}*/

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
