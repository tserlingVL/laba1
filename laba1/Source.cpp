#include <iostream>
#include <fstream> //для потока ввода/вывода в файл
#include <sstream> //для потока ввода/вывода в строку
using namespace std;


void CountNumbers(int counts[]) { //первая функция считает какие чисела встречаются и сколько
    ifstream input("number1.txt");
    string line;

    while (getline(input, line)) {// если число попадается, в counts в ячейку по индексу этого числа прибавляется единичка
        stringstream ss(line);
        int number;
        while (ss >> number)
            if (number >= 0 && number <= 1000)
                counts[number]++;
    }

    input.close(); // функция ничего не возвращает, меняет исходный counts, состоящих из одних нулей
}

void WriteCountsToFile(int counts[]) { // функция записывает числа, которые встречались больше 1 раза
    ofstream output("number3.txt");
    ofstream output2("number2.txt", ios_base::app); // открыть для добавления

    int distinctCount = 0;
    for (int i = 0; i <= 1000; i++) { // цикл перебирает по индексам члены массива, если больше одного - записывает индекс(число) и значение(сколько раз встретилось)
        if (counts[i] > 1) {
            output << "Number " << i << " : " << counts[i] << "\n";
            cout << "Number " << i << " : " << counts[i] << "\n";
            distinctCount++;
        }
    }

    output2 << "Result = " << distinctCount << "\n";
    cout << "Result = " << distinctCount << "\n";

    output.close();
    output2.close();
}

void ReplaceLetters(char oldLetter, char newLetter) { // функция берет текст из text1.txt, меняет заданную пользователем букву на другую и записывает полученный текст в text2.txt
    ifstream inputText("text1.txt");
    ofstream outputText("text2.txt"); // так как text2.txt не был создан, программа его создает сама
    string line;

    while (getline(inputText, line)) { // цикл перебирает каждый символ в строке, если находит старую букву - меняет на новую
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
    int counts[1001] = { 0 }; // для подсчета чисел

    // Сначала считаем числа
    CountNumbers(counts);

    // Затем запишем результат в файлы
    WriteCountsToFile(counts);
    ReplaceLetters(oldLetter, newLetter);


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
