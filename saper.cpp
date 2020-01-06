// Сделать игру сапер

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>

using namespace std;

bool Sapper(int k, char** A, char** B, int n, int flagCount) // функция игры
{
    int i, j;
    int x, y;
    char act;
    if (k == 0 && flagCount == 0)
    {
        cout << "Ты крутой сапер" << endl;
        return true;
    }
    else
    {
        while (1) // вводим x,y
        {
            cout << " Введи x и y, смотри не промахнись" << endl;
            cin >> x >> y;
            if (x >= 0 && x < n && y >= 0 && y < n)
                break;
            else
                cout << "Введите правильные значения" << endl;
        }
        while (1) // вводим действие
        {
            cout << " Введи действие\n '?'- пометить бомбу\n '0'- тут пусто " << endl;
            cin >> act;
            if (act == '?' || act == '0')
                break;
            else
                cout << " Введите правильное действие " << endl;
        }
        if (act == '?' && A[x][y] == '*') // если угадываем место бомбы
        {
            B[x][y] = '?';
            flagCount--;
            for (i = 0; i < n; i++)
            {
                for (j = 0; j < n; j++)
                    cout << ' ' << B[i][j];
                cout << endl;
            }
            Sapper(k - 1, A, B, n, flagCount);
        }
        else
        {
            if (act == '0' && A[x][y] == '*') // если попадаем на бомбу
            {
                cout << "Ты подорвался" << endl;
                return false;
            }
            else
            {
                if (act == '0' && A[x][y] != '*') // открываем клетки без бомб
                {
                    if (B[x][y] == '?')
                        flagCount++;
                    B[x][y] = A[x][y];
                    for (i = 0; i < n; i++)
                    {
                        for (j = 0; j < n; j++)
                            cout << ' ' << B[i][j];
                        cout << endl;
                    }

                    Sapper(k, A, B, n, flagCount);
                }
                else // отмечаем вопросом свободную клетку
                {
                    B[x][y] = '?';
                    flagCount--;
                    for (i = 0; i < n; i++)
                    {
                        for (j = 0; j < n; j++)
                            cout << ' ' << B[i][j];
                        cout << endl;
                    }
                    Sapper(k, A, B, n, flagCount);
                }
            }
        }
    }

}
char** CreateUserField(int n)
{
    int i, j;
    char** Array; // создание массива

    Array = new char* [n]; // выделение памяти под массив

    for (i = 0; i < n; i++)
        Array[i] = new char[n];

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            Array[i][j] = '+'; // проверка и ввод элементов массива

    return Array;
}
char** CreateGameField(int n, int k)
{
    int i, j, a, b;
    int xBomb, yBomb;
    char** Array; // создание массива

    Array = new char* [n]; // выделение памяти под массив

    for (i = 0; i < n; i++)
        Array[i] = new char[n];


    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            Array[i][j] = '0'; // проверка и ввод элементов массива


    for (i = 0; i < k; i++)
    {
        xBomb = rand() % n;
        yBomb = rand() % n;

        if (Array[xBomb][yBomb] != '*')
        {
            Array[xBomb][yBomb] = '*';
            for (a = xBomb - 1; a <= xBomb + 1; a++) {
                for (b = yBomb - 1; b <= yBomb + 1; b++) {
                    // проверка на выход за границы массива
                    // и проверка на то, что обрабатываемая ячейка не равна изначальной ячейке
                    if (0 <= a && a < n && 0 <= b && b < n && (a != xBomb || b != yBomb)) {  // любая операция с соседним элементом
                        switch (Array[a][b])
                        {
                        case '0':
                            Array[a][b] = '1';
                            break;
                        case '1':
                            Array[a][b] = '2';
                            break;
                        case '2':
                            Array[a][b] = '3';
                            break;
                        case '3':
                            Array[a][b] = '4';
                            break;
                        case '4':
                            Array[a][b] = '5';
                            break;
                        case '5':
                            Array[a][b] = '6';
                            break;
                        case '6':
                            Array[a][b] = '7';
                            break;
                        case '7':
                            Array[a][b] = '8';
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
        }
    }
    return Array;
}
int main()
{
    srand(time(NULL)); 
    setlocale(LC_ALL, "Russian");
    cout << " Игра Сапёр " << endl;
    int n, k;
    int i, j;
    char** GameArray;
    char** UserArray;
    int flagCount;
    while (1)
    {
        cout << "Введите размерность поля n(от 4 до 20) " << endl;
        cin >> n;
        if (n >= 4 && n < 20)
            break;
        else
            cout << "Введите правильное значение" << endl;
    }

    k = n * n / 10;
    flagCount = k; //вопросы, необходимые для победы
    GameArray = CreateGameField(n, k); // создаем главное игровое поле и генерируем бомбы

    /*for (i = 0; i < n; i++) // для дебаггинга
    {
        for (j = 0; j < n; j++)
            cout << ' ' << GameArray[i][j];
        cout << endl;
    }*/
    UserArray = CreateUserField(n); // создаем поле для пользователя
    if (Sapper(k, GameArray, UserArray, n, flagCount) == true)
        cout << " Поздравляем с победой" << endl;
    else
        cout << " Увы " << endl;
    system("pause");
    return 0;
}
