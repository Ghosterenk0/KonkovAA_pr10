#include <iostream>
#include <time.h>
#include <Windows.h>


int counts[3]{ 0, 0, 0 };

HANDLE threads[3];
HANDLE logThread;
HANDLE userThread;
HANDLE loader;

void increment() {
    int i = 0;
    while (true) {
        i++;
        counts[0]++;
    }
}

void febonaci() {
    auto start = 0;
    auto second = 1;
    while (true) {
        auto tmp = start;
        start = second;
        second += tmp;
        counts[1]++;
    }
}

void fact() {
    int num = 0;
    int fact = 1;
    while (true) {
        num++;
        fact *= num;
        counts[2]++;
    }
}
void loaderF() {
    if (!SetThreadPriority(loader, THREAD_PRIORITY_HIGHEST))
        std::cout << "Ошибка" << std::endl;
    SetThreadPriorityBoost(loader, FALSE);
    //SetThreadPriority(loader, THREAD_PRIORITY_HIGHEST);
    Sleep(3000);
    if (!SetThreadPriority(threads[0], THREAD_PRIORITY_IDLE))
        std::cout << "Ошибка" << std::endl;
    if (!SetThreadPriority(threads[1], THREAD_PRIORITY_IDLE))
        std::cout << "Ошибка" << std::endl;
    if (!SetThreadPriority(threads[2], THREAD_PRIORITY_IDLE))
        std::cout << "Ошибка" << std::endl;
    
    SetThreadPriorityBoost(loader, TRUE);
}
void count_iter(HANDLE thread, int id) {

    SuspendThread(thread);
    if (id == 0) {
        std::cout << "Поток " << id << " - кол-во итерцаий: " << counts[0] << std::endl;
        counts[0] = 0;
    }
    else if (id == 1) {
        std::cout << "Поток " << id << " - кол-во итерцаий: " << counts[1] << std::endl;
        counts[1] = 0;
    }
    else if (id == 2) {
        std::cout << "Поток " << id << " - кол-во итерцаий: " << counts[2] << std::endl;
        counts[2] = 0;
    }
    ResumeThread(thread);

}
void users() {
    int user = 0;
    bool f = true;
    while (f) {
        std::cin >> user;
        switch (user)
        {
        case 0:
            TerminateThread(threads[0], 0);
            TerminateThread(threads[1], 0);
            TerminateThread(threads[2], 0);
            TerminateThread(logThread, 0);
            TerminateThread(userThread, 0);
            f = false;
            break;
        case 1:
            if (!SetThreadPriority(threads[0], THREAD_PRIORITY_IDLE))
                std::cout << "Ошибка" << std::endl;
            break;
        case 2:
            if (!SetThreadPriority(threads[1], THREAD_PRIORITY_IDLE))
                std::cout << "Ошибка" << std::endl;
            break;
        case 3:
            if (!SetThreadPriority(threads[2], THREAD_PRIORITY_IDLE))
                std::cout << "Ошибка" << std::endl;
            break;
        case 4:
            if (!SetThreadPriority(threads[0], THREAD_PRIORITY_NORMAL))
                std::cout << "Ошибка" << std::endl;
            break;
        case 5:
            if (!SetThreadPriority(threads[1], THREAD_PRIORITY_NORMAL))
                std::cout << "Ошибка" << std::endl;
            break;
        case 6:
            if (!SetThreadPriority(threads[2], THREAD_PRIORITY_NORMAL))
                std::cout << "Ошибка" << std::endl;
            break;
        case 7:
            if (!SetThreadPriority(threads[0], THREAD_PRIORITY_HIGHEST))
                std::cout << "Ошибка" << std::endl;
            break;
        case 8:
            if (!SetThreadPriority(threads[1], THREAD_PRIORITY_HIGHEST))
                std::cout << "Ошибка" << std::endl;
            break;
        case 9:
            if (!SetThreadPriority(threads[2], THREAD_PRIORITY_HIGHEST))
                std::cout << "Ошибка" << std::endl;
            break;
        case 11:
            loader = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)loaderF, NULL, NULL, NULL);
            if (!SetThreadPriority(loader, THREAD_PRIORITY_HIGHEST))
                std::cout << "Ошибка" << std::endl;
            if (GetThreadPriority(threads[0]) == -15 && GetThreadPriority(threads[1]) == -15 && GetThreadPriority(threads[2]) == -15) {
                if (!SetThreadPriority(loader, THREAD_PRIORITY_NORMAL))
                    std::cout << "Ошибка" << std::endl;
            }
            break;
        default:
            break;
        }
    }
}

void statusThread() {
    std::cout << "1 Поток - " << GetThreadPriority(threads[0]) << std::endl;
    std::cout << "2 Поток - " << GetThreadPriority(threads[1]) << std::endl;
    std::cout << "3 Поток - " << GetThreadPriority(threads[2]) << std::endl;
    std::cout << "Нагрузчик - " << GetThreadPriority(loader) << std::endl;
    /*if (GetThreadPriority(loader) == 0 || GetThreadPriority(loader) == 2) 
        std::cout << "Нагрузчик - " << GetThreadPriority(loader) << std::endl;
    else 
        std::cout << "Нагрузчик - неактивен" << std::endl;*/
}

void logs() {
    int user = 0;
    userThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)users, NULL, NULL, NULL);
    if (!SetThreadPriority(logThread, THREAD_PRIORITY_IDLE))
        std::cout << "Ошибка" << std::endl;
    while (true) {
        Sleep(1000);
        system("cls");
        statusThread();
        std::cout << "Лог: " << std::endl;
        count_iter(threads[0], 0);
        count_iter(threads[1], 1);
        count_iter(threads[2], 2);
        std::cout << "Выберете действие: " << std::endl;
        std::cout << "1. Поток 1 фоновый приоритет" << std::endl;
        std::cout << "2. Поток 2 фоновый приоритет" << std::endl;
        std::cout << "3. Поток 3 фоновый приоритет" << std::endl;
        std::cout << std::endl;
        std::cout << "4. Поток 1 нормальный приоритет" << std::endl;
        std::cout << "5. Поток 2 нормальный приоритет" << std::endl;
        std::cout << "6. Поток 3 нормальный приоритет" << std::endl;
        std::cout << std::endl;
        std::cout << "7. Поток 1 высокий приоритет" << std::endl;
        std::cout << "8. Поток 2 высокий приоритет" << std::endl;
        std::cout << "9. Поток 3 высокий приоритет" << std::endl;
        std::cout << std::endl;
        std::cout << "11. Вызывать нагрузчик" << std::endl;
        std::cout << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << std::endl;

    }
    WaitForSingleObject(userThread, INFINITE);
}

int main() {

    setlocale(LC_ALL, "ru");

    threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)increment, NULL, NULL, NULL);
    threads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)febonaci, NULL, NULL, NULL);
    threads[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)fact, NULL, NULL, NULL);
    logThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)logs, NULL, NULL, NULL);    

    if (!SetThreadPriority(threads[0], THREAD_PRIORITY_BELOW_NORMAL))
        std::cout << "Ошибка" << std::endl;
    if (!SetThreadPriority(threads[1], THREAD_PRIORITY_LOWEST))
        std::cout << "Ошибка" << std::endl;
    if (!SetThreadPriority(threads[2], THREAD_PRIORITY_NORMAL))
        std::cout << "Ошибка" << std::endl;
    if (!SetThreadPriority(logThread, THREAD_PRIORITY_IDLE))
        std::cout << "Ошибка" << std::endl;



    WaitForSingleObject(threads[0], INFINITE);
    WaitForSingleObject(threads[1], INFINITE);
    WaitForSingleObject(threads[2], INFINITE);
    WaitForSingleObject(logThread, INFINITE);
}
