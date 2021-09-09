// Digits.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>

using namespace std; 
// reverse string (for multiplication function)
string rev(string x) {
    string res = "";
    int n = x.length();
    for (int i = n; i >= 0; i--) {
        res += x[i];
    }
    return res; 
}

//addtion
string add(string a, string b, int d) {
    int rem = 0;
    string res = "";
    int n1 = a.length();
    int n2 = b.length();
    if (n1 < n2) { swap(a, b); swap(n1, n2); }
    string x = rev(a);
    string y = rev(b);
    int i = 0;
    while (i < n2) {
        int temp = x[i] - '0' + y[i] - '0' + rem; // add remain;
        rem = 0;
        if (temp > d) rem++; //check whether the partial sum is bigger than the base; 
        res += char(temp % d + '0'); 
        i++;
    }
    // if the indicator hasnt run over all rest of the longer number, continue. 
    while (i < n1){
        int temp = x[i] - '0' + rem;
        rem = 0;
        if (temp > d) rem++; 
        res += char(temp % d + '0');
        i++;
    }
    if (rem > 0) { res += "1"; }
    return rev(res);
}
//multiply with one-digit number 
string multiply_1(string a, char b, int d){
    int n = a.length();
    int rem = 0;
    int x = b - '0';
    string res = "";
     
    for (int i = n; i >= 0; i--) {
        int temp = (int(a[i]) - '0') * x + rem;
        rem = temp / d; //remain = partial product divide to base; 
        res += char(temp % d + '0');
    }
    if (rem > 0) { res += "1"; }
    return rev(res);
}
//multiply with multi-digit number.
string multiply(string a, string b, int d) {
    int n1 = a.length();
    int n2 = b.length(); 
    int i = 0;
    string res = "";

    for (int j = 0; j < n2; j++){
        // multiply with each digit
        string temp = multiply_1(a, b[j], d);
        for (int t = 0; t < j; t++) { temp += "0"; }
        res = add(res, temp, d);
        //add them together
    }
    return res; 
}

//optimization
string fast_multi(string a, string b, int d) {
    int n1 = a.length(); int n2 = b.length();
    int i = 0;
    string x, y, z, t;
    x.append(a.begin(), a.begin() + n1 / 2);
    y.append(a.begin() + n1 / 2 + 1, a.end());
    z.append(b.begin(), b.begin() + n2 / 2);
    t.append(b.begin() + n1 / 2 + 1, b.end());
    int v1 = n1 - x.length(); int v2 = n2 - z.length();
    string l1 = ""; for (int i = 0; i < v1; i++) { l1 += "0";}
    string l2 = ""; for (int i = 0; i < v2; i++) { l2 += "0";}
    string temp1 = multiply(x, z,d) + l1 + l2; string temp2 = add(multiply(x, t,d) + l1 , multiply(y, z,d)+l2,d ); string temp3 = multiply(y, t,d);
    return add(temp1, add(temp2, temp3,d ), d);
}
int main()
{
    string a; string b;
    cin >> a >> b;
    int d; cin >> d;
    cout << a[0] << '\n';
    for (char& i : b) { cout << multiply_1(a, i,d) << '\n'; }
    cout << add(a, b, d) << '\n';
    cout << multiply(a, b, d);
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
