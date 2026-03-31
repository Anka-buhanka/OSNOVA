#include <iostream>
#include <cstdio>

using namespace std;

class BigInt {   //объявляем класс
private:
    int low;      //младшие 9 цифр
    int high;     //старшие 9 цифр 
    int sign;     //знак: 1 (плюс) или -1 (минус)
    const int BASE = 1000000000;  // 10^9

    //нормализация числа
    void normalize() {
        //перенос переполнения из low в high
        while (low >= BASE) {
            low -= BASE;
            high++;
        }
        //наоборот, занимаем из high
        while (low < 0) {
            low += BASE;
            high--;
        }

        //если high отрицательный, меняем знак и части
        if (high < 0) {
            high = -high;
            sign = -sign;
            if (low > 0) {
                high--;
                low = BASE - low;
            }
        }

        //если число равно 0, знак должен быть положительным
        if (high == 0 && low == 0) {
            sign = 1;
        }
    }

public:
    //конструктор класса
    BigInt(int h = 0, int l = 0, int s = 1) {
        high = h;
        low = l;
        if (s >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }
        normalize();
    }

    //cложение
    void plus(const BigInt& other) {
        if (sign == other.sign) {  //одинаковые знаки
            low += other.low;
            high += other.high;
        } else {
            //разные знаки: вычитание модулей
            BigInt temp = *this;
            if (temp.compareAbs(other) >= 0) {
                low -= other.low;
                high -= other.high;
            } else {
                low = other.low - low;
                high = other.high - high;
                sign = other.sign;
            }
        }
        normalize();
    }

    //вычитание
    void minus(const BigInt& other) {
        BigInt temp(other.high, other.low, -other.sign);
        plus(temp);
    }

    //умножение
    void multiply(const BigInt& other) {
        long long l1 = low, l2 = other.low;
        long long h1 = high, h2 = other.high;

        long long resLow = l1 * l2;
        long long resHigh = h1 * h2;
        long long carry = h1 * l2 + l1 * h2;

        resHigh += resLow / BASE;
        resLow = resLow % BASE;
        resHigh += carry;

        low = (int)resLow;
        high = (int)resHigh;
        sign = sign * other.sign;

        normalize();
    }

    //сравнение модулей (без учёта знака)
    int compareAbs(const BigInt& other) const {
        if (high > other.high) return 1;
        if (high < other.high) return -1;
        if (low > other.low) return 1;
        if (low < other.low) return -1;
        return 0;
    }

    //сравнение с учётом знака
    int compare(const BigInt& other) const {
        if (sign > other.sign) return 1;
        if (sign < other.sign) return -1;
        int cmp = compareAbs(other);
        return (sign == 1) ? cmp : -cmp;
    }

    //сеттеры (методы изменения данных)
    void setLow(int l) { low = l; normalize(); }
    void setHigh(int h) { high = h; normalize(); }
    void setSign(int s) { sign = (s >= 0) ? 1 : -1; normalize(); }

    //геттеры (методы получения данных)
    int getLow() const { return low; }
    int getHigh() const { return high; }
    int getSign() const { return sign; }

    //вывод на экран
    void print() const {
        if (sign == -1 && (high != 0 || low != 0)) cout << "-";
        if (high > 0) {
            cout << high;
            printf("%09d", low);
        } else {
            cout << low;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    BigInt num1(1, 5, 1);   // 1 000000005
    BigInt num2(2, 3, 1);   // 2 000000003

    cout << "\nисходные числа:" << endl;
    cout << "num1 = "; num1.print(); cout << endl;
    cout << "num2 = "; num2.print(); cout << endl;

    cout << "\nсложение: num1 = num1 + num2" << endl;
    num1.plus(num2);
    cout << "pезультат в num1: "; num1.print(); cout << endl;

    BigInt num3(3, 8, 1);   // 3 000000008

    cout << "\nвычитание: num3 = num3 - num2" << endl;
    num3.minus(num2);
    cout << "pезультат в num3: "; num3.print(); cout << endl;

    cout << "\nумножение: num3 = num3 * num2" << endl;
    num3.setHigh(1); num3.setLow(5);  // 1 000000005
    num3.multiply(num2);
    cout << "pезультат в num3: "; num3.print(); cout << endl;

    cout << "\nсравнение num3 и num2:" << endl;
    int cmp = num3.compare(num2);
    if (cmp > 0) cout << "num3 > num2" << endl;
    else if (cmp < 0) cout << "num3 < num2" << endl;
    else cout << "num3 == num2" << endl;

    cout << "\nизменение частей num3:" << endl;
    num3.setHigh(5);
    num3.setLow(123);
    num3.setSign(-1);
    cout << "новый num3: "; num3.print(); cout << endl;

    cout << "\nполучение параметров num3:" << endl;
    cout << "знак: " << num3.getSign() << endl;
    cout << "старшая часть: " << num3.getHigh() << endl;
    cout << "ьладшая часть: " << num3.getLow() << endl;

    return 0;
}
