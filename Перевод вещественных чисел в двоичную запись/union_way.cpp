#include <iostream>
#include <cstdlib>
using namespace std;
int main(int argc, char *argv[])
{
    string str;
    string type;
    int count;
    int exp;
    int mantissa;
    const int mantissa_for_float=23;
    const int mantissa_for_double=52;
    const int exp_for_float=8;
    const int exp_for_double=11;
    const int count_for_double=8;
    const int count_for_float=4;
    int j=0;
    if (argc >= 3)
    {
        str = argv[1];
        type = argv[2];
    }
    else
    {
        cout << "Введите число " << endl;
        cin >> str;
        cout << "Введите тип" << endl;
        cin >> type;
    }
    union juistice
    {
        float cislo_float;
        double cislo_double;
        char cf[sizeof(float)];
        char cd[sizeof(double)];
    };
    juistice league;
    if (type == "double")
    {
        league.cislo_double = stod(str);
        count = count_for_double;
        exp = exp_for_double;
        mantissa = mantissa_for_double;
    }
    else if (type == "float")
    {
        league.cislo_float = stof(str);
        count = count_for_float;
        exp = exp_for_float;
        mantissa = mantissa_for_float;
    }
    int byte[128];
    for (int i = 0; i < count; i++)
    {
        int k = 128;
        j = exp + mantissa + 1 - 8 * (1 + i);
        while (k > 0)
        {
            if (type == "float")
            {
                byte[j] = bool(league.cf[i] & k);
                cout << bool(league.cf[i] & k);
            }
            else
            {
                byte[j] = bool(league.cd[i] & k);
                cout << bool(league.cd[i] & k);
            }
            j++;
            k = k >> 1;
        }
    }
    cout<<endl;
    for (int k = 0; k < (exp+mantissa+1); k++)
    {
        if (k==1)
        {
            cout<<"[";
        }
        cout<<byte[k];
        if (k==exp)
        {
            cout<<"]";
        }
    }
    cout << endl;
    return 0;
}