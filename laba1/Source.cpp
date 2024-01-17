#include <iostream>
#include <fstream> //для потока ввода/вывода в файл
#include <sstream> //для потока ввода/вывода в строку
using namespace std;

void CountNumbersAndReplaceLetters(char oldLetter, char newLetter) {
    ifstream input("number1.txt");
    ofstream output("number3.txt");
    ofstream output2("number2.txt", ios_base::app); // открыть для добавления
    string line;
    int counts[1001] = { 0 }; // для подсчета чисел

    while (getline(input, line)) {
        stringstream ss(line);
        int number;
        while (ss >> number)
            if (number >= 0 && number <= 1000)
                counts[number]++;
    }

    int distinctCount = 0;
    for (int i = 0; i <= 1000; i++) {
        if (counts[i] > 0) {
            output << "Number " << i << " : " << counts[i] << "\n";
            cout << "Number " << i << " : " << counts[i] << "\n";
            distinctCount++;
        }
    }

    output2 << "Result = " << distinctCount << "\n";
    cout << "Result = " << distinctCount << "\n";

    input.close();
    output.close();
    output2.close();

    // Замена букв в файле text1.txt
    ifstream inputText("text1.txt");
    ofstream outputText("text2.txt");
    while (getline(inputText, line)) {
        for (char& c : line)
            if (c == oldLetter)
                c = newLetter;
        outputText << line << "\n";
    }

    inputText.close();
    outputText.close();
}

int Fill_file(int n) {
    int number, m, str = 0;
    ofstream output;
    // n чисел		в диапазоне -100..100	пишутся в строки, где чисел от 0 до 10
    output.open("number1.txt");
    if (!output.is_open())
        cout << "Error of open File!" << endl;
    else
        while (n > 0) {
            str++; //кол-во строк в файле
            m = rand() % 11; //кол-во чисел в строке   /   остаток от деления на 11 -- даёт диапазон 0..10
            if (m > n) m = n;
            for (int i = 0; i < m; i++) {
                number = -100 + rand() % 201; //текущее число
                output << number << "\t"; //к -100 прибавляем остаток от деления на 201 -- даёт диапазон -100..100
                cout << number << "\t";
                n -= 1;
            }
            output << endl;
            cout << endl;
        }
    cout << endl;
    output.close(); // закрыли поток ввода "F"
    return str;
}

//Обратить все строки файла text1.txt и вывести их в файл text2.txt.
void Reversed_Line() {
    ifstream input("text1.txt");
    ofstream output("text2.txt");
    string line;
    while (getline(input, line)) { //rbegin читает с обратной стороны
        string reversedLine(line.rbegin(), line.rend()); // Переворачиваем строку
        output << reversedLine << endl;
    }
}

//Функция для выравнивания текста по правому краю
string rightAlign(const string& line, int width) { // & - это ссылка. Мы передаём параметр по ссылке, когда хотим,
    // чтобы он изменялся и в главной функции main()
    if (line.length() >= width)
        return line;
    else {
        return string(width - line.length(), ' ') + line;
    }
}

// Функция для выравнивания текста по центру
string centerAlign(const string& text, int width) {
    if (text.length() >= width)
        return text;
    else {
        int left_offset = (width - text.length()) / 2;
        int right_offet = width - text.length() - left_offset;
        return string(left_offset, ' ') + text + string(right_offet, ' ');
    }
}

int main()
{
    int n;
    char oldLetter, newLetter;
    cout << "Amount of numbers: ";
    cin >> n;
    cout << "Enter the letter to be replaced: ";
    cin >> oldLetter;
    cout << "Enter the new letter: ";
    cin >> newLetter;
    int str = Fill_file(n); //кол-во строк в файле
    
    CountNumbersAndReplaceLetters(oldLetter, newLetter);//Выполняет задание 20 варианта

    ofstream fout;
    fout.open("number2.txt", ios::app); //запись в конец файла
    fout << " Result = " << str;
    cout << "\nResult = " << str << endl;
    fout.close();

     //Обратить все строки файла text1.txt и вывести их в файл text2.txt.

    ifstream input_number("number2.txt");
    ifstream input_text("text2.txt");
    ofstream output("total.txt");
    string line;
    // Записываем элементы из number2.txt, выровненные по правому краю
    output << "Elements from number2.txt (right-aligned):\n";
    cout << "Elements from number2.txt (right-aligned):\n";
    while (getline(input_number, line)) {
        output << rightAlign(line, 150) << "\n"; // Здесь 100 - ширина всего окна
        cout << rightAlign(line, 150) << "\n";
    }
    //Записываем элементы из text2.txt, выровненные по центру
    output << "\nElements from text2.txt (center-aligned):\n";
    cout << "\nElements from text2.txt (center-aligned):\n";
    while (getline(input_text, line)) {
        output << centerAlign(line, 100) << "\n";
        cout << centerAlign(line, 100) << "\n";
    }
    input_number.close();
    input_text.close();
    output.close();

    //Переименование файла total.txt
    string newFileName;
    cout << "\nEnter a new file name (including extension, e.g. new_total.txt): ";//ввод имени включая расширение, типа New_File.txt
    cin >> newFileName;
    newFileName += ".txt";
    if (rename("total.txt", newFileName.c_str()) == 0)
        cout << "The total.txt file has been successfully renamed to " << newFileName << endl;
    else {
        cerr << "Failed to rename file." << endl;//вывод ошибки, если не удалось
        return 1;
    }

    return 0;
}