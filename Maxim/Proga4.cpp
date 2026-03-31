#include <iostream>  // для ввода/вывода
#include <fstream>   // для работы с файлами (ofstream, ifstream)
#include <string>    // для работы со строками
#include <algorithm> // для сортировки
#include <cmath>     // для модуля числа
using namespace std;

// Структура, описывающая одну запись (банковский счет)
struct Account {
    string surname;   // фамилия владельца
    string number;    // номер счета
    double sum;       // сумма на счете
    string date;      // дата последнего изменения
};

// Массив структур для хранения таблицы записей
Account table[100];
// Переменная для хранения текущего количества записей в таблице
int n = 0;

// 1. Функция ввода новой записи с клавиатуры
void input() {
    // Проверка: не превышен ли лимит таблицы
    if (n >= 100) {
        cout << "Таблица полна\n";
        return;
    }
    // Ввод данных с клавиатуры
    cout << "Фамилия: "; cin >> table[n].surname;
    cout << "Номер счета: "; cin >> table[n].number;
    cout << "Сумма: "; cin >> table[n].sum;
    cout << "Дата: "; cin >> table[n].date;
    // Увеличиваем счетчик записей
    n++;
}

// 2. Функция сохранения таблицы в текстовый файл
void save() {
    string file;
    cout << "Имя файла: "; cin >> file;
    
    // Создаем объект для записи в файл
    ofstream f(file);
    
    // Сначала сохраняем количество записей
    f << n << endl;
    
    // Затем сохраняем каждую запись (каждое поле на отдельной строке)
    for (int i = 0; i < n; i++) {
        f << table[i].surname << endl;
        f << table[i].number << endl;
        f << table[i].sum << endl;
        f << table[i].date << endl;
    }
    
    // Закрываем файл
    f.close();
    cout << "Сохранено " << n << " записей\n";
}

// 3. Функция загрузки таблицы из текстового файла
void load() {
    string file;
    cout << "Имя файла: "; cin >> file;
    
    // Создаем объект для чтения из файла
    ifstream f(file);
    
    // Сначала читаем количество записей
    f >> n;
    
    // Затем читаем каждую запись (каждое поле из отдельной строки)
    for (int i = 0; i < n; i++) {
        f >> table[i].surname;
        f >> table[i].number;
        f >> table[i].sum;
        f >> table[i].date;
    }
    
    // Закрываем файл
    f.close();
    cout << "Загружено " << n << " записей\n";
}

// 4. Функция просмотра всей таблицы
void view() {
    // Если таблица пуста, сообщаем об этом
    if (n == 0) {
        cout << "Таблица пуста\n";
        return;
    }
    
    // Выводим все записи с нумерацией
    for (int i = 0; i < n; i++) {
        cout << i+1 << ". " << table[i].surname << " " 
             << table[i].number << " " 
             << table[i].sum << " " 
             << table[i].date << endl;
    }
}

// 5. Функция сортировки таблицы по выбранному полю (по возрастанию)
void sort() {
    int f;
    cout << "Сортировать по (1-фамилия,2-номер,3-сумма,4-дата): ";
    cin >> f;
    
    // Используем стандартную функцию sort
    if (f == 1)
        // Сортировка по фамилии (алфавитный порядок)
        sort(table, table+n, [](Account a, Account b) { return a.surname < b.surname; });
    if (f == 2)
        // Сортировка по номеру счета
        sort(table, table+n, [](Account a, Account b) { return a.number < b.number; });
    if (f == 3)
        // Сортировка по сумме (от меньшей к большей)
        sort(table, table+n, [](Account a, Account b) { return a.sum < b.sum; });
    if (f == 4)
        // Сортировка по дате
        sort(table, table+n, [](Account a, Account b) { return a.date < b.date; });
    
    cout << "Сортировка выполнена\n";
}

// 6. Функция поиска записи
void search() {
    int f;
    cout << "Искать по (1-фамилия,2-номер,3-сумма): ";
    cin >> f;
    
    if (f == 1) {
        // Поиск по точному совпадению фамилии
        string s;
        cout << "Фамилия: "; cin >> s;
        bool found = false;
        for (int i = 0; i < n; i++)
            if (table[i].surname == s) {
                cout << table[i].surname << " " << table[i].number << " " << table[i].sum << " " << table[i].date << endl;
                found = true;
            }
        if (!found) cout << "Не найдено\n";
    }
    else if (f == 2) {
        // Поиск по точному совпадению номера счета
        string num;
        cout << "Номер: "; cin >> num;
        bool found = false;
        for (int i = 0; i < n; i++)
            if (table[i].number == num) {
                cout << table[i].surname << " " << table[i].number << " " << table[i].sum << " " << table[i].date << endl;
                found = true;
            }
        if (!found) cout << "Не найдено\n";
    }
    else if (f == 3) {
        // Поиск ближайшего значения по сумме
        double s;
        cout << "Сумма: "; cin >> s;
        int idx = 0;
        double min = abs(table[0].sum - s);  // модуль разницы для первой записи
        for (int i = 1; i < n; i++) {
            double d = abs(table[i].sum - s);  // модуль разницы для текущей записи
            if (d < min) {  // если разница меньше, запоминаем индекс
                min = d;
                idx = i;
            }
        }
        cout << "Ближайший по сумме: " << table[idx].surname << " " 
             << table[idx].number << " " << table[idx].sum << " " << table[idx].date << endl;
    }
}

// 7. Функция удаления записи по номеру
void del() {
    if (n == 0) {
        cout << "Таблица пуста\n";
        return;
    }
    
    int k;
    view();  // показываем все записи для выбора
    cout << "Номер записи для удаления: "; cin >> k;
    k--;  // переводим в индекс массива
    
    // Сдвигаем все элементы влево, начиная с удаляемого
    for (int i = k; i < n-1; i++)
        table[i] = table[i+1];
    
    // Уменьшаем счетчик записей
    n--;
    cout << "Запись удалена\n";
}

// 8. Функция редактирования записи
void edit() {
    if (n == 0) {
        cout << "Таблица пуста\n";
        return;
    }
    
    int k;
    view();  // показываем все записи для выбора
    cout << "Номер записи для редактирования: "; cin >> k;
    k--;  // переводим в индекс массива
    
    // Вводим новые данные для выбранной записи
    cout << "Новая фамилия: "; cin >> table[k].surname;
    cout << "Новый номер: "; cin >> table[k].number;
    cout << "Новая сумма: "; cin >> table[k].sum;
    cout << "Новая дата: "; cin >> table[k].date;
    cout << "Запись изменена\n";
}

// 9. Функция вычисления общей суммы по всем счетам
void sum() {
    if (n == 0) {
        cout << "Таблица пуста, общая сумма = 0\n";
        return;
    }
    
    double total = 0;
    // Суммируем все суммы на счетах
    for (int i = 0; i < n; i++)
        total += table[i].sum;
    
    cout << "Общая сумма на всех счетах: " << total << endl;
    cout << "Количество счетов: " << n << endl;
}

// main
int main() {
    int choice;
    
    // Бесконечный цикл меню, пока не выберут 0
    do {
        // Вывод меню
        cout << "\n1-ввод 2-сохранить 3-загрузить 4-просмотр 5-сортировка 6-поиск 7-удаление 8-редактирование 9-общая сумма 0-выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        
        // Вызов соответствующей функции в зависимости от выбора
        if (choice == 1) input();
        else if (choice == 2) save();
        else if (choice == 3) load();
        else if (choice == 4) view();
        else if (choice == 5) sort();
        else if (choice == 6) search();
        else if (choice == 7) del();
        else if (choice == 8) edit();
        else if (choice == 9) sum();
        else if (choice == 0) cout << "Выход из программы\n";
        else cout << "Неверный выбор\n";
        
    } while (choice != 0);  // Повторяем, пока не выберут 0
    
    return 0;
}
