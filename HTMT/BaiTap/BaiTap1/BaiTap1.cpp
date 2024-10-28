#include <string>
#include <unordered_map>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <algorithm>
#include <cctype>
using namespace std;

class Hexadecimal {
    public:
        static const int zero       ;//= 0;
        static const int one        ;//= 1;
        static const int two        ;//= 2;
        static const int three      ;//= 3;
        static const int four       ;//= 4;
        static const int five       ;//= 5;
        static const int six        ;//= 6;
        static const int seven      ;//= 7;
        static const int eight      ;//= 8;
        static const int nine       ;//= 9;
        static const int ten        ;//= 10;
        static const int eleven     ;//= 11;
        static const int twelve     ;//= 12;
        static const int thirteen   ;//= 13;
        static const int fourteen   ;//= 14;
        static const int fifteen    ;//= 15;

        static const unordered_map<int, string> toString;
        static const unordered_map<string, int> fromString;

        static string getString(int num) {
            auto it = toString.find(num);
            if (it != toString.end()) {
                return it->second;
            }

            return "";
        }

        static int getInt(string num) {
            auto it = fromString.find(num);
            if (it != fromString.end()) {
                return it->second;
            }

            return 0;
        }
};

// Define the static members
const int Hexadecimal::zero = 0;
const int Hexadecimal::one = 1;
const int Hexadecimal::two = 2;
const int Hexadecimal::three = 3;
const int Hexadecimal::four = 4;
const int Hexadecimal::five = 5;
const int Hexadecimal::six = 6;
const int Hexadecimal::seven = 7;
const int Hexadecimal::eight = 8;
const int Hexadecimal::nine = 9;
const int Hexadecimal::ten = 10;
const int Hexadecimal::eleven = 11;
const int Hexadecimal::twelve = 12;
const int Hexadecimal::thirteen = 13;
const int Hexadecimal::fourteen = 14;
const int Hexadecimal::fifteen = 15;

const unordered_map<int, string> Hexadecimal::toString = {
    { zero, "0" },
    { one, "1" },
    { two, "2" },
    { three, "3" },
    { four, "4" },
    { five, "5" },
    { six, "6" },
    { seven, "7" },
    { eight, "8" },
    { nine, "9" },
    { ten, "A" },
    { eleven, "B" },
    { twelve, "C" },
    { thirteen, "D" },
    { fourteen, "E" },
    { fifteen, "F" }
};

const unordered_map<string, int> Hexadecimal::fromString = {
    { "0", zero },
    { "1", one },
    { "2", two },
    { "3", three },
    { "4", four },
    { "5", five },
    { "6", six },
    { "7", seven },
    { "8", eight },
    { "9", nine },
    { "A", ten },
    { "B", eleven },
    { "C", twelve },
    { "D", thirteen },
    { "E", fourteen },
    { "F", fifteen }
};

string toUppercase(const std::string& input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), [](unsigned char c) {
        return toupper(c);
    });
    return result;
}

/* Decimal(10) to Binary(2) or to Hexadecimal(16) */
string decToCoefficient(int num, int coe) {
    string result;
    int len = coe == 2 ? 8 : 4; // 4 for 16 bit

    if (num == 0)
    {
        result = "0";
    }
    else
    {
        while (num > 0)
        {
            int remain = num % coe;
            result = Hexadecimal::getString(remain) + result;
            num /= coe;
        }

        while (result.length() < len) {
            result = "0" + result;
        }
        
    }
    
    return result;
}

/* Hexadecimal(16) to Decimal(10) */
int hexToDecimal(const string& hex) {
    int decimal = 0, base = 1; //16^0

    for (int i = hex.length() - 1; i >= 0; --i)
    {
        decimal += Hexadecimal::getInt(hex.substr(i, 1)) * base;
        base *= 16; //16^1    
    }

    return decimal;
}

/* Hexadecimal(16) to Decimal(10) */
int hexToDecimal2(const string& hex) {
    int decimal = 0, base = 1; //16^0

    for (int i = hex.length() - 1; i >= 0; --i)
    {
        // compare key codes
        if (hex[i] >= '0' && hex[i] <= '9') //to get 0->9
        {
            decimal += (hex[i] - '0') * base;
        } else if (hex[i] >= 'A' && hex[i] <= 'F') //to get 10->15
        {
            decimal += (hex[i] - 'A' + Hexadecimal::ten) * base;
        }
        base *= 16; //16^1
        
    }

    return decimal;
}

/* Binary(2) to Decimal(10) */
int binToDecimal(const string& bin) {
    int result = 0;

    if (bin.empty() == false)
    {
        for (int i = 0; i < bin.length(); i++)
        {  
            const char* num = &bin.substr(i, 1)[0];//get string number then convert to char
            int val = atoi(num) * pow(2, bin.length() - (i + 1));
            result += val;
        }  
    }

    return result;
}

/* Hexadecimal(16) to Binary(10) */
string hexToBinary(const string& hex) {
    int dec = hexToDecimal(hex);

    return decToCoefficient(dec, 2);
}

/* Binary(10) to Hexadecimal(16) */
string binToHexadecimal(const string& bin) {
    int dec = binToDecimal(bin);

    return decToCoefficient(dec, 16);
}

void printMenu() {
    cout << "Nhập số tương ứng tính năng cần thực hiện:\n";
    cout << "1. Chuyển đổi số từ hệ 10 về hệ 2\n";
    cout << "2. Chuyển đổi số từ hệ 10 về hệ 16\n";
    cout << "3. Chuyển đổi số từ hệ 16 về hệ 10\n";
    cout << "4. Chuyển đổi số từ hệ 16 về hệ 2\n";
    cout << "5. Chuyển đổi số từ hệ 2  về hệ 10\n";
    cout << "6. Chuyển đổi số từ hệ 2  về hệ 16\n";
    cout << "7. Thoát\n";
    cout << "Chọn thao tác (1-7): ";
}

void settigFonts() {
    cout << "When run is fail font, please set font with below guide:\n";
    cout << "1. Open Control Panel.\n";
    cout << "2. Click on Region.\n";
    cout << "3. In window You can click on Administrative tab\n";
    cout << "4. Click on Change system locale to see more details.\n";
    cout << "5. Check into checkbox 'Beta: Use Unicode UTF-8 for...' if not checked\n";
    cout << "6. Save and restart computer\n";
    cout << "=================================================================\n";
}

int main() {
    // Set the local
    settigFonts();

    int choice, num;
    string str;

    while (true)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Nhập số nguyên không dấu (8 bit): ";
                cin >> num;
                cout << "Chuyển đổi từ hệ 10 với " << num << " sang hệ 2 là: " << decToCoefficient(num, 2) << endl;
                cout << "=================================================================\n";
                break;
            
            case 2:
                cout << "Nhập số nguyên không dấu (8 bit): ";
                cin >> num;
                cout << "Chuyển đổi từ hệ 10 với " << num << " sang hệ 16 là: " << decToCoefficient(num, 16) << endl;
                cout << "=================================================================\n";
                break;

            case 3:
                cout << "Nhập ký tự hệ 16 không dấu (8 bit): ";
                cin >> str;
                cout << "Chuyển đổi từ hệ 16 với " << str << " sang hệ 10 là: " << hexToDecimal(toUppercase(str)) << endl;
                cout << "=================================================================\n";
                break;

            case 4:
                cout << "Nhập ký tự hệ 16 không dấu (8 bit): ";
                cin >> str;
                cout << "Chuyển đổi từ hệ 16 với " << str << " sang hệ 2 là: " << hexToBinary(toUppercase(str)) << endl;
                cout << "=================================================================\n";
                break;

            case 5:
                cout << "Nhập số nhị phân không dấu (8 bit): ";
                cin >> str;
                cout << "Chuyển đổi từ hệ 2 với " << str << " sang hệ 10 là: " << binToDecimal(str) << endl;
                cout << "=================================================================\n";
                break;

            case 6:
                cout << "Nhập số nhị phân không dấu (8 bit): ";
                cin >> str;
                cout << "Chuyển đổi từ hệ 2 với " << str << " sang hệ 16 là: " << binToHexadecimal(str) << endl;
                cout << "=================================================================\n";
                break;

            case 7:
                cout << "Thoát..." << endl;
                return 0;
            
            default:
                cout << "Vui lòng chọn từ (1-7)." << endl;
                cout << "=================================================================\n";
                break;
        }
    }
    
    return 0;
}