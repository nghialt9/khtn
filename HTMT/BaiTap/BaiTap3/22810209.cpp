#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <cmath>

using namespace std;

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

string floatToBinary(float num) {
    int *p = (int *)&num;
    int n = *p;
    
    int sign = (n >> 31) & 1;
    int exponent = (n >> 23) & 0xFF;
    int mantissa = n & 0x7FFFFF;
    
    return printBinary(sign, 1) + " " + printBinary(exponent, 8) + " " + printBinary(mantissa, 23);
}

// Hàm chuyển từ chuỗi nhị phân thành số nguyên
int binaryToInt(const string& binary, int start, int length) {
    int result = 0;
    for (int i = 0; i < length; i++) {
        result = result * 2 + (binary[start + i] - '0');
    }
    return result;
}

// Hàm chuyển chuỗi nhị phân sang số chấm động theo chuẩn IEEE 754
float binaryToFloat(const string& binary) {
    if (binary.length() != 32) {
        cerr << "Chuỗi nhị phân không hợp lệ. Phải có 32 bit." << endl;
        return 0;
    }

    // 1. Tách dấu (bit đầu tiên)
    int sign = (binary[0] == '0') ? 1 : -1;

    // 2. Tách phần mũ (8 bit tiếp theo)
    int exponent = binaryToInt(binary, 1, 8);
    exponent -= 127;  // Loại bỏ bias 127

    // 3. Tách phần trị (23 bit cuối)
    float mantissa = 1.0;  // Bắt đầu với 1 vì đã chuẩn hóa
    float fraction = 0.5;
    for (int i = 9; i < 32; i++) {  // Phần trị bắt đầu từ bit thứ 9
        if (binary[i] == '1') {
            mantissa += fraction;
        }
        fraction /= 2;
    }

    // 4. Tính số chấm động theo công thức (-1)^sign * (1 + mantissa) * 2^exponent
    return sign * mantissa * pow(2, exponent);
}

void printMenu() {
    cout << "Nhập số tương ứng tính năng cần thực hiện:\n";
    cout << "1. Chuyển đổi số chấm động sang nhị phân (32 bit)\n";
    cout << "2. Chuyển đổi số từ hệ 2 (32 bit) về hệ số chấm động\n";
    cout << "3. Biểu diễn số nhị phân của 1.3E+20\n";
    cout << "4. Biểu diễn số float nhỏ nhất lớn hơn 0\n";
    cout << "5. Kết quả các trường hợp đặc biệt\n";
    cout << "6. Thoát\n";
    cout << "Chọn thao tác (1-6): ";
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

    int choice, num1, result1, i;
    float num, result, x, y, z, f;
    string str;

    while (true)
    {
        printMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Nhập vào số chấm động (32 bit): ";
                cin >> num;
                cout << "Chuyển đổi từ số chấm động với " << num << " sang hệ 2 (32 bit) là: " << floatToBinary(num) << endl;
                cout << "=================================================================\n";
                break;
            
            case 2:
                cout << "Nhập vào số chấm động nhị phân (32 bit): ";
                cin >> str;
                cout << "Chuyển đổi từ số chấm động nhị phân với " << str << " sang số chấm động là: " << binaryToFloat(str) << endl;
                cout << "=================================================================\n";
                break;

            case 3:
                num = 1.3E+20;
                cout << "Chuyển đổi từ số chấm động với " << num << " sang hệ 2 (32 bit) là: " << floatToBinary(num) << endl;
                cout << "=================================================================\n";
                break;

            case 4:
                num = 1.17549435E-38;
                cout << "Chuyển đổi từ số chấm động với " << num << " sang hệ 2 (32 bit) là: " << floatToBinary(num) << endl;
                cout << "=================================================================\n";
                break;

            case 5:
                num = 4.56789;
                num1 = (int)num;
                result = (float)num1;
                cout << "1) Chuyển đổi float: " << num << " -> int: " << num1 << "-> float: " << result << endl;

                num1 = 45678923;
                num = (float)num1;
                result1 = (int)num;
                cout << "2) Chuyển đổi int: " << num1 << " -> float: " << num << "-> int: " << result1 << endl;

                x = y = z = 4.5678;
                cout << "3) Kết quả so sánh phép công kết hợp: (x+y)+z = " << (x + y) + z << " và x+(y+z) =" << x + (y + z) << endl;

                f = 1.3;
                i = (int) (3.14159 * f);
                cout << "4) Kết quả của i = (int) (3.14159 * f) với f = " << f << " là " << i << endl;

                cout << "5) Kết quả của f = f + (float) i với f = " << f << " và i = " << f << " là " << i << endl;

                cout << "6) Kết quả của (i == (int)((float) i)) là " << (i == (int)((float) i)) << endl;
                cout << "7) Kết quả của (i == (int)((double) i)) là " << (i == (int)((double) i)) << endl;
                cout << "8) Kết quả của (f == (float)((int) f)) là " << (f == (float)((int) f)) << endl;
                cout << "9) Kết quả của (f == (double)((int) f)) là " << (f == (double)((int) f)) << endl;

                break;

            case 6:
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
