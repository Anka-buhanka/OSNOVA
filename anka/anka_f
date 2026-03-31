#include <iostream>
#include <string>
using namespace std;

class LongInt {
private:
    int low;      // младшие 9 цифр
    int high;     // старшие 9 цифр
    bool sign;    //false - плюс, true - минус
    static const int BASE = 1000000000;

public:
    LongInt() {                 //конструктор без параметров
        low = 0;
        high = 0;
        sign = false;
        cout << "Default constructor: " << this << " = 0" << endl;
    }

    LongInt(string str) {         //конструктор из строки
        sign = false;
        if (str[0] == '-') {
            sign = true;
            str = str.substr(1);
        }

        if (str.length() <= 9) {
            high = 0;
            low = stoi(str);
        }
        else {
            string highStr = str.substr(0, str.length() - 9);
            string lowStr = str.substr(str.length() - 9);
            high = stoi(highStr);
            low = stoi(lowStr);
        }
        cout << "String constructor: " << this << " = " << toString() << endl;
    }

    LongInt(const LongInt& other) {  //конструктор копирования
        high = other.high;
        low = other.low;
        sign = other.sign;
        cout << "Copy constructor: " << this << " copy of " << &other << endl;
    }

    ~LongInt() {            //деструктор
        cout << "Destructor: " << this << endl;
    }

    string toString() {           //преобразвоние в строку
        string result;
        if (high == 0) {
            result = to_string(low);
        }
        else {
            string lowStr = to_string(low);
            while (lowStr.length() < 9) lowStr = "0" + lowStr;
            result = to_string(high) + lowStr;
        }
        if (sign && (high != 0 || low != 0)) result = "-" + result;
        return result;
    }

    void print() {                 //вывод
        cout << toString();
    }

    int getLow() { return low; }        //доступ к компонентам
    int getHigh() { return high; }
    bool getSign() { return sign; }

    void setLow(int l) { low = l; }
    void setHigh(int h) { high = h; }
    void setSign(bool s) { sign = s; }
};

void testFunc(LongInt obj) {   //функция для демонстрации передачи по значению
    cout << "In function: ";
    obj.print();
    cout << endl;
}

LongInt global("1000000000");    //глобальный объект

int main() {
    cout << "START\n";

    LongInt a;                 //локальные объекты
    LongInt b("123456789");
    LongInt c = b;

    cout << "\na = "; a.print(); cout << endl;
    cout << "b = "; b.print(); cout << endl;
    cout << "c = "; c.print(); cout << endl;

    cout << "\nb: high=" << b.getHigh() << ", low=" << b.getLow() << endl;  //доступ к компонентам
    b.setHigh(999);
    cout << "b after change: "; b.print(); cout << endl;

    cout << "\nDynamic:\n";   //динамический объект
    LongInt* p = new LongInt("-555");
    delete p;

    cout << "\nArray:\n";  //массив
    LongInt arr[2] = { LongInt("1"), LongInt("2") };

    cout << "\nPass by value:\n";  //передача по значению
    testFunc(b);

    cout << "\nEND\n";
    return 0;
}
