#include <iostream>
#include <time.h>
#include <Windows.h>


int counts[3];

void increment() {
    int i = 0;
    while (true) {
        i++;
        Sleep(1000);
    }
}

void febonaci() {
    auto start = 0;
    auto second = 1;
    std::cout << start << std::endl;
    std::cout << second << std::endl;
    while (true) {
        std::cout << start + second << std::endl;
        auto tmp = start;
        start = second;
        second += tmp;
        Sleep(1000);
    }
}

void fact() {
    int num = 0;
    int fact = 1;
    while (true) {
        num++;
        fact *= num;
        std::cout << num << std::endl;
        Sleep(1000);
    }
}


int main()
{
    HANDLE threads[3];
    DWORD IDthread[3];

    IDthread[0] = 111;
    IDthread[1] = 121;
    IDthread[2] = 131;

    threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)increment, NULL, NULL, &IDthread[0]);
    threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)febonaci, NULL, NULL, &IDthread[1]);
    threads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)fact, NULL, NULL, &IDthread[2]);

    if (!SetPriorityClass(threads[0], IDLE_PRIORITY_CLASS)) {
        std::cout << "Ошибка" << std::endl;
    }
    if (!SetPriorityClass(threads[1], NORMAL_PRIORITY_CLASS)) {
        std::cout << "Ошибка" << std::endl;
    }
    if (!SetPriorityClass(threads[2], HIGH_PRIORITY_CLASS)) {
        std::cout << "Ошибка" << std::endl;
    }


    WaitForSingleObject(threads[0], INFINITE);
    WaitForSingleObject(threads[1], INFINITE);
    WaitForSingleObject(threads[2], INFINITE);
}
