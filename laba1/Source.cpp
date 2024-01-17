#include <iostream>
#include <fstream> //��� ������ �����/������ � ����
#include <sstream> //��� ������ �����/������ � ������
using namespace std;

void CountNumbersAndReplaceLetters(char oldLetter, char newLetter) {
    ifstream input("number1.txt");
    ofstream output("number3.txt");
    ofstream output2("number2.txt", ios_base::app); // ������� ��� ����������
    string line;
    int counts[1001] = { 0 }; // ��� �������� �����

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

    // ������ ���� � ����� text1.txt
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
    // n �����		� ��������� -100..100	������� � ������, ��� ����� �� 0 �� 10
    output.open("number1.txt");
    if (!output.is_open())
        cout << "Error of open File!" << endl;
    else
        while (n > 0) {
            str++; //���-�� ����� � �����
            m = rand() % 11; //���-�� ����� � ������   /   ������� �� ������� �� 11 -- ��� �������� 0..10
            if (m > n) m = n;
            for (int i = 0; i < m; i++) {
                number = -100 + rand() % 201; //������� �����
                output << number << "\t"; //� -100 ���������� ������� �� ������� �� 201 -- ��� �������� -100..100
                cout << number << "\t";
                n -= 1;
            }
            output << endl;
            cout << endl;
        }
    cout << endl;
    output.close(); // ������� ����� ����� "F"
    return str;
}

//�������� ��� ������ ����� text1.txt � ������� �� � ���� text2.txt.
void Reversed_Line() {
    ifstream input("text1.txt");
    ofstream output("text2.txt");
    string line;
    while (getline(input, line)) { //rbegin ������ � �������� �������
        string reversedLine(line.rbegin(), line.rend()); // �������������� ������
        output << reversedLine << endl;
    }
}

//������� ��� ������������ ������ �� ������� ����
string rightAlign(const string& line, int width) { // & - ��� ������. �� ������� �������� �� ������, ����� �����,
    // ����� �� ��������� � � ������� ������� main()
    if (line.length() >= width)
        return line;
    else {
        return string(width - line.length(), ' ') + line;
    }
}

// ������� ��� ������������ ������ �� ������
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
    int str = Fill_file(n); //���-�� ����� � �����
    
    CountNumbersAndReplaceLetters(oldLetter, newLetter);//��������� ������� 20 ��������

    ofstream fout;
    fout.open("number2.txt", ios::app); //������ � ����� �����
    fout << " Result = " << str;
    cout << "\nResult = " << str << endl;
    fout.close();

     //�������� ��� ������ ����� text1.txt � ������� �� � ���� text2.txt.

    ifstream input_number("number2.txt");
    ifstream input_text("text2.txt");
    ofstream output("total.txt");
    string line;
    // ���������� �������� �� number2.txt, ����������� �� ������� ����
    output << "Elements from number2.txt (right-aligned):\n";
    cout << "Elements from number2.txt (right-aligned):\n";
    while (getline(input_number, line)) {
        output << rightAlign(line, 150) << "\n"; // ����� 100 - ������ ����� ����
        cout << rightAlign(line, 150) << "\n";
    }
    //���������� �������� �� text2.txt, ����������� �� ������
    output << "\nElements from text2.txt (center-aligned):\n";
    cout << "\nElements from text2.txt (center-aligned):\n";
    while (getline(input_text, line)) {
        output << centerAlign(line, 100) << "\n";
        cout << centerAlign(line, 100) << "\n";
    }
    input_number.close();
    input_text.close();
    output.close();

    //�������������� ����� total.txt
    string newFileName;
    cout << "\nEnter a new file name (including extension, e.g. new_total.txt): ";//���� ����� ������� ����������, ���� New_File.txt
    cin >> newFileName;
    newFileName += ".txt";
    if (rename("total.txt", newFileName.c_str()) == 0)
        cout << "The total.txt file has been successfully renamed to " << newFileName << endl;
    else {
        cerr << "Failed to rename file." << endl;//����� ������, ���� �� �������
        return 1;
    }

    return 0;
}