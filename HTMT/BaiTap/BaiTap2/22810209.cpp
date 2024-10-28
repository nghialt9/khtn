#include <iostream>
#include <stdio.h>
#include <stdint.h>

using namespace std;

const string fail = "Tràn số";
// Hàm xuất số nguyên từ string bit
int binToDecimal(string bin, bool isMulti = false) {
    int result = 0;
    bool isNegative = (bin[0] == '1');
    int len = bin.length() - 1;
    if (bin.empty() == false)
    {
        for (int i = 0; i <= len; i++)
        {  
            //result |= ((bin[i] - '0') << (len - i));
            result = (result << 1) | (bin[i] - '0');
        }

        // Nếu là số âm, thực hiện phép bù 2
        if (isNegative && isMulti == false) {
            result -= (1 << bin.length());
        }
    }

    return result;
}

// Hàm xuất dãy bit nhị phân của một số nguyên size bit
string printBinary(int32_t number, int size, bool isFormat = false) {
    string result;

    for (int i = size - 1; i >= 0; i--) {
        result += to_string((number >> i) & 1);  // Lấy bit tại vị trí i
        if (i % 4 == 0 && isFormat) {
            result += " ";  // Thêm khoảng trắng mỗi 4 bit
        }
    }

    return result;
}

//Hàm xuất số nguyên từ array 32 bit
int32_t createNumberFromArray(int bitArray[32]) {
    int32_t number = 0;
    for (int i = 0; i < 32; i++) {
        number |= (bitArray[i] << (31 - i));
    }

    return number;
}

// Hàm cộng hai dãy bit
string addBitStrings(string a, string b, char &carry, bool isMulti = false) {
    carry = 0;
    string result = "";
    bool isNegativeA = (a[0] == '1');
    bool isNegativeB = (b[0] == '1');
    int len = a.length() - 1;

    for (int i = len; i >= 0; i--) {
        char bitA = a[i] - '0'; //mã ASCII của 0 là 48, 1 là 49 => bit là 0 hoặc 1
        char bitB = b[i] - '0';

        char sum = bitA + bitB + carry;
        result = char(sum % 2 + '0') + result;
        carry = sum / 2;
    }

    bool isNegativeResult = (result[0] == '1');

    if (isMulti == false && ((isNegativeA && isNegativeB && isNegativeResult == false)
        || (isNegativeA == false && isNegativeB == false && isNegativeResult)))
    {
        return result + " => " + fail;
    }
    
    return result;
}

// Hàm đảo dấu
string invert(string bin){
    int numB = binToDecimal(bin);
    numB = ~numB + 1;
    return printBinary(numB, 8);
}

// Hàm trừ hai dãy bit (a - b)
string subtractBitStrings(string a, string b) {
    // Đổi dấu b (tìm bù 2 của b)
    /* cách 1
    for (int i = 0; i < 8; i++) {
        b[i] = b[i] == '0' ? '1' : '0';
    }
    b = addBitStrings(b, "00000001"); // Thêm 1 để tạo bù 2
    //*/

    //* cách 2
    b = invert(b);
    //*/
    char carry;

    return addBitStrings(a, b, carry); // Cộng a và bù 2 của b
}

// Hàm nhân hai dãy bit bằng thuật toán CAQ * M
string multiplyBitStrings(string a, string b) {
    bool isNegativeA = (a[0] == '1');
    bool isNegativeB = (b[0] == '1');
    if(isNegativeA)
    {
        a = invert(a);
    }
    if(isNegativeB)
    {
        b = invert(b);
    }
    char carry = 0; // dùng để nhớ => C
    string carryStr;
    string temp = "00000000"; // dùng để cộng với b <=> A
    string resultStr = printBinary(carry, 8) + temp + a; // a <=> Q, b <=> M
    int resultInt = binToDecimal(resultStr, true);
    
    int len = b.length() - 1;
    for (int i = len; i >= 0; --i) {
        //xét bit cuối của Q là 1
        if (a.back() == '1') {
            // cộng A với M
            temp = addBitStrings(temp, b, carry, true);
            //tạo ra CAQ
            resultStr = printBinary(carry, 8) + temp + a;
            resultInt = binToDecimal(resultStr, true);     
        }

        //dịch phải 1 CAQ
        resultInt = resultInt >> 1;
        //chuyển sang bit
        resultStr = printBinary(resultInt, 24);
        // tạo lại A Q
        temp = resultStr.substr(8,8);
        a = resultStr.substr(16, 8);
    }

    string result  = resultStr.substr(8, 16);
    if (isNegativeA != isNegativeB)
    {
        resultInt = binToDecimal(result);
        resultInt = ~resultInt + 1;
        result = printBinary(resultInt, 16);
    }
    
    return result;
}

// Hàm chia hai dãy bit bằng thuật toán AQ
pair<string, string> divideBitStrings(string dividend, string divisor) {
    string remainder = "00000000"; //A phần dư
    bool isNegativeA = (dividend[0] == '1');
    bool isNegativeB = (divisor[0] == '1');
    if(isNegativeA)
    {
        dividend = invert(dividend);
    }
    if(isNegativeB == false)
    {
        divisor = invert(divisor);
    }
    char carry = 0;
    string resultStr = remainder + dividend; // dividend <=> Q, remainder <=> A
    int resultInt = binToDecimal(resultStr, true);
    int len = divisor.length() - 1;
    for (int i = len; i >= 0; --i) {
        //dịch trái 1 AQ
        resultInt = resultInt << 1;
        resultStr = printBinary(resultInt, 16);
        remainder = resultStr.substr(0,8);
        dividend = resultStr.substr(8, 8);
        remainder = addBitStrings(remainder, divisor, carry, true);
        if(remainder[0] == '1')
        {
            string oldDivisor = invert(divisor);
            remainder = addBitStrings(remainder, oldDivisor, carry, true);
        }
        else {
            dividend = addBitStrings(dividend, "00000001", carry, true);
        }
        resultStr = remainder + dividend; // dividend <=> Q, remainder <=> A
        resultInt = binToDecimal(resultStr, true);
    }

    // xét dấu số chia và dấu số bị chia khác nhau thì đổi dấu kết quả
    if (isNegativeA != isNegativeB)
    {
        dividend = invert(dividend);
    }

    // xét dấu số bị chia và dấu số dư khác nhau thì đổi dấu số dư
    if (isNegativeA != (remainder[0] == '1'))
    {
        remainder = invert(remainder);
    }
    
    return make_pair(dividend, remainder);
}

void addArray(string bit[], int size){
    for (int i = 0; i < size; i++) {
        cout << "Nhập vào dãy 8 bit thứ " << i + 1 << ": ";
        cin >> bit[i];
    }
} 

void printMenu() {
    cout << "Nhập số tương ứng tính năng cần thực hiện:\n";
    cout << "1. Chuyển đổi số từ hệ 10 về hệ 2 (32 bit)\n";
    cout << "2. Chuyển đổi số từ hệ 2 (32 bit) về hệ 10\n";
    cout << "3. Cộng 2 dãy 8 bit\n";
    cout << "4. Trừ 2 dãy 8 bit\n";
    cout << "5. Nhân 2 dãy 8 bit\n";
    cout << "6. Chia  2 dãy 8 bit\n";
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

    int choice, num, bitArray[32];
    string str, bit[2];
    char carry;
    pair<string, string> result;

    while (true)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Nhập số nguyên có dấu (32 bit): ";
                cin >> num;
                cout << "Chuyển đổi từ hệ 10 với " << num << " sang hệ 2 (32 bit) là: " << printBinary(num, 32, true) << endl;
                cout << "=================================================================\n";
                break;
            
            case 2:
                for (int i = 0; i < 32; i++) {
                    cout << "Nhập vào giá trị 0 hoặc 1 cho mảng với vị trí " << i << ": ";
                    //scanf("%d", &bitArray[i]);
                    cin >> bitArray[i];
                    str += to_string(bitArray[i]);
                    if((i + 1) % 4 == 0){
                        str += " ";
                    }
                }
                cout << "Chuyển đổi từ hệ 2 (32 bit) với " << str << " sang hệ 10 là: " << createNumberFromArray(bitArray) << endl;
                cout << "=================================================================\n";
                break;

            case 3:
                addArray(bit, 2);
                str = addBitStrings(bit[0], bit[1], carry);
                str = str.find(fail) != string::npos ? str : str.substr(0, 8);
                cout << "Kết quả cộng dãy bit 1 " << bit[0] << " với dãy bit 2 " << bit[1] << " là: " << str << endl;
                cout << "Kết quả thập phân của dãy bit 1 = " << binToDecimal(bit[0]) << " cộng dãy bit 2 = " << binToDecimal(bit[1]) << " là: " << binToDecimal(str.substr(0, 8)) << endl;
                cout << "=================================================================\n";
                break;

            case 4:
                addArray(bit, 2);
                str = subtractBitStrings(bit[0], bit[1]);
                str = str.find(fail) != string::npos ? str : str.substr(0, 8);
                cout << "Kết quả trừ dãy bit 1 " << bit[0] << " với dãy bit 2 " << bit[1] << " là: " << str << endl;
                cout << "Kết quả thập phân của dãy bit 1 = " << binToDecimal(bit[0]) << " trừ dãy bit 2 = " << binToDecimal(bit[1]) << " là: " << binToDecimal(str.substr(0, 8)) << endl;
                cout << "=================================================================\n";
                break;

            case 5:
                addArray(bit, 2);
                str = multiplyBitStrings(bit[0], bit[1]);
                cout << "Kết quả nhân dãy bit 1 " << bit[0] << " với dãy bit 2 " << bit[1] << " là: " << str << endl;
                cout << "Kết quả thập phân của dãy bit 1 = " << binToDecimal(bit[0]) << " nhân dãy bit 2 = " << binToDecimal(bit[1]) << " là: " << binToDecimal(str) << endl;
                cout << "=================================================================\n";
                break;

            case 6:
                addArray(bit, 2);
                result = divideBitStrings(bit[0], bit[1]);
                cout << "Kết quả chia dãy bit 1 " << bit[0] << " với dãy bit 2 " << bit[1] << " là: " << result.first << " dư " << result.second << endl;
                cout << "Kết quả thập phân của dãy bit 1 = " << binToDecimal(bit[0]) << " chia dãy bit 2 = " << binToDecimal(bit[1]) << " là: " << binToDecimal(result.first) << " dư " << binToDecimal(result.second) << endl;
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
