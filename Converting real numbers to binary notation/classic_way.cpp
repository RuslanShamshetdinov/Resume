#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
    int flag=0;
    int flag_1=0;
    int count = 0;
    string str;
    string str1;
    string type;
    int cel;
    double cislo;
    double drob;
    int mod_cel[128];
    int mod_drob[128];
    vector<int> vec;
    int count_modcel = 0;
    int count_moddrob = 0;
    int count_exp;
    const int count_exp_for_double = 11;
    const int count_exp_for_float = 8;
    int mantissa;
    const int mantissa_for_double = 52;
    const int mantissa_for_float = 23;
    int exp;
    int mod_exp[128];
    int bit_znak;
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
    cout << str << endl;
    cout << type << endl;
    if (type == "double")
    {
        mantissa = mantissa_for_double;
        count_exp = count_exp_for_double;
    }
    else if (type == "float")
    {
        mantissa = mantissa_for_float;
        count_exp = count_exp_for_float;
    }
    auto pos = str.find(".");
    if (str[0] != '-')
    {
        if (pos != string::npos)
        {
            str1 = str.substr(0, pos);
        }
        bit_znak = 0;
    }
    else if (str[0] == '-')
    {
        if (pos != string::npos)
        {
            str1 = str.substr(1, pos);
        }
        bit_znak = 1;
    }

    cel = stoi(str1);
    cislo = stod(str);
    drob = fabs(cislo) - cel;
    if (cel == 0)
    {
        mod_cel[count_modcel] = 0;
        count_modcel++;
        exp = 0;
        flag=1;
    }
    if (cel==1)
    {
        exp = 0;
        flag=1;
        flag_1=1;
        mod_cel[count_modcel]=1;
        count_modcel++;
    } 
    if (flag==0)
    {
        while (cel != 0)
        {
            mod_cel[count_modcel] = cel % 2;
            cel /= 2;
            count_modcel++;
        }
        exp = count_modcel - 1;
    }
    for (int i = count_modcel - 1; i >= 0; i--)
    {
        vec.push_back(mod_cel[i]);
    }
    while (drob != 1.0)
    {
        drob *= 2.0;
        mod_drob[count_moddrob] = drob;
        if (drob > 1.0)
        {
            drob = drob - int(drob);
            drob = floor(drob * 100000 + 0.5) / 100000.0;
        }
        count_moddrob++;
        if (count_moddrob == mantissa)
        {
            break;
        }
    }
    if ((exp != 0)||(flag_1==1))
    {
        for (int j = 0; j < count_moddrob; j++)
        {
            vec.push_back(mod_drob[j]);
        }
        for (unsigned int i = 0; i < vec.size(); i++)
        {
            auto begin = vec.cbegin();
            if (vec[i] == 1)
            {
                vec.erase(begin + i);
                break;
            }
        }
    }
    if ((exp == 0)&&(flag_1==0))
    {
        for (int j = 0; j < count_moddrob; j++)
        {
            if (mod_drob[j] == 1)
            {
                break;
            }
            else
            {
                count += 1;
            }
        }
        exp = -(count + 1);
        while (drob != 1.0)
        {
            drob *= 2.0;
            mod_drob[count_moddrob] = drob;
            if (drob > 1.0)
            {
                drob = drob - int(drob);
                drob = floor(drob * 100000 + 0.5) / 100000.0;
            }
            count_moddrob++;
            if (count_moddrob == mantissa + count + 1)
            {
                break;
            }
        }
    for (int j = 0; j < count_moddrob; j++)
    {
        vec.push_back(mod_drob[j]);
    }
    auto begin = vec.cbegin();
    vec.erase(begin, begin + count + 2);
    }
    if ((exp == 0) && (count_moddrob != mantissa))
    {
        exp = -count_moddrob;
    }
    if (type == "double")
    {
        exp += 1023;
    }
    else
    {
        exp += 127;
    }
    for (int j = 0; j < count_exp; j++)
    {
        mod_exp[j] = exp % 2;
        exp /= 2;
    }
    cout << bit_znak << "[";
    for (int s = count_exp - 1; s >= 0; s--)
    {
        cout << mod_exp[s];
    }
    cout << "]";
    for (int k = 0; k < mantissa; k++)
    {
        vec[vec.size() + k] = 0;
        cout << vec[k];
    }
    cout << endl;
    return 0;
}