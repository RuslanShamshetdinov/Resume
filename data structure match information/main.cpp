#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "match_information.h"
#include "help.h"
using namespace std;
int main(int argc, char *argv[])
{
    string file_name;
    ifstream rf;
    int curr_match;
    int i = 0;
    int number;
    match_information *array;
    unsigned int poisk_hour;
    unsigned int poisk_minutes;
    unsigned int poisk_day;
    unsigned int poisk_month;
    unsigned int poisk_year;
    string poisk_s1;
    string poisk_s2;
    int choice;
    help hlpob;
    if (argc >= 2)
    {
        file_name = string(argv[1]);
        rf.open(argv[1], ios::binary | ios::in);
    }
    else
    {
        cout << "Введите имя файла\n";
        cin >> file_name;
        rf.open(file_name, ios::binary | ios::in);
    }
    if (!rf)
    {
        cout << "Cannot open file!" << endl;
        return 1;
    }
    int size_array = 1;
    rf.read((char *)&size_array, sizeof(size_array));
    if (!rf.gcount())
    {
        size_array = 1;
    }
    array = new match_information[size_array];
    while (!rf.eof())
    {
        rf.read((char *)&array[i].hour, sizeof(unsigned int));
        if (rf.gcount())
        {
            rf.read((char *)&array[i].minutes, sizeof(unsigned int));
            rf.read((char *)&array[i].day, sizeof(unsigned int));
            rf.read((char *)&array[i].month, sizeof(unsigned int));
            rf.read((char *)&array[i].year, sizeof(unsigned int));
            size_t size1;
            rf.read((char *)&size1, sizeof(size1));
            array[i].team_one.resize(size1);
            rf.read((char *)(array[i].team_one.c_str()), size1);
            size_t size2;
            rf.read((char *)&size2, sizeof(size2));
            array[i].team_two.resize(size2);
            rf.read((char *)(array[i].team_two.c_str()), size2);
            i++;
        }
    }
    curr_match = i;
    rf.close();
    for (;;)
    {
        hlpob.showmenu();
        do
        {
            cin >> choice;
        } while (!hlpob.isvalid(choice));
        if (choice == MAX_MENU_NUMBER)
            break;
        cout << endl;
        switch (choice)
        {
        case 1:
        {
            if (size_array <= curr_match)
            {
                match_information *new_array = new match_information[2 * size_array];
                copy_n(array, size_array, new_array);
                delete[] array;
                array = new_array;
                size_array *= 2;
            }
            cout << "first team" << endl;
            cin >> array[curr_match].team_one;
            cout << "second team" << endl;
            cin >> array[curr_match].team_two;
            cout << "hour" << endl;
            cin >> array[curr_match].hour;
            cout << "minutes" << endl;
            cin >> array[curr_match].minutes;
            cout << "day" << endl;
            cin >> array[curr_match].day;
            cout << "month" << endl;
            cin >> array[curr_match].month;
            cout << "year" << endl;
            cin >> array[curr_match].year;
            cout << "succesfully" << endl;
            curr_match++;
        }
        break;
        case 2:
        {
            for (int i = 0; i < curr_match; ++i)
            {
                cout << "Match #" << i + 1 << endl;
                cout << array[i] << endl;
            }
        }
        break;
        case 3:
        {
            int flag = 0;
            cout << "Введите первую команду" << endl;
            cin >> poisk_s1;
            cout << "Введите вторую команду" << endl;
            cin >> poisk_s2;
            for (int i = 0; i < curr_match; i++)
            {
                if ((array[i].team_one == poisk_s1) && (array[i].team_two == poisk_s2))
                {
                    cout << "Match #" << i + 1 << endl;
                    cout << array[i] << endl;
                    flag = 1;
                }
            }
            if (flag == 0)
            {
                cout << "Ничего не найдено" << endl;
            }
        }
        break;
        case 4:
        {
            int flag1 = 0;
            cout << "Введите час" << endl;
            cin >> poisk_hour;
            cout << "Введите минуту" << endl;
            cin >> poisk_minutes;
            for (int i = 0; i < curr_match; i++)
            {
                if ((array[i].hour == poisk_hour) && (array[i].minutes == poisk_minutes))
                {
                    cout << "Match #" << i + 1 << endl;
                    cout << array[i] << endl;
                    flag1 = 1;
                }
            }
            if (flag1 == 0)
            {
                cout << "Ничего не найдено" << endl;
            }
        }
        break;
        case 5:
        {
            int flag2 = 0;
            cout << "Введите день" << endl;
            cin >> poisk_day;
            cout << "Введите месяц" << endl;
            cin >> poisk_month;
            cout << "Введите год" << endl;
            cin >> poisk_year;
            for (int i = 0; i < curr_match; i++)
            {
                if ((array[i].day == poisk_day) && (array[i].month == poisk_month) && (array[i].year == poisk_year))
                {
                    cout << "Match #" << i + 1 << endl;
                    cout << array[i] << endl;
                    flag2 = 1;
                }
            }
            if (flag2 == 0)
            {
                cout << "Ничего не найдено" << endl;
            }
            flag2 = 0;
        }
        break;
        case 6:
        {
            cout << "Введите номер матча, который удаляем" << endl;
            cin >> number;
            while ((number < 0) || (number > curr_match))
            {
                cout << "Неверное значение" << endl;
                cout << "Пожалуйста, выберите другое" << endl;
                cin >> number;
            }
            array[number - 1].team_one = array[curr_match - 1].team_one;
            array[number - 1].team_two = array[curr_match - 1].team_two;
            array[number - 1].hour = array[curr_match - 1].hour;
            array[number - 1].minutes = array[curr_match - 1].minutes;
            array[number - 1].day = array[curr_match - 1].day;
            array[number - 1].month = array[curr_match - 1].month;
            array[number - 1].year = array[curr_match - 1].year;
            curr_match = curr_match - 1;
        }
        break;
        }
        cout << endl;
    }
    ofstream wf;
    wf.open(file_name, ios::binary | ios::out);
    wf.write((char *)&size_array, sizeof(size_array));
    for (int i = 0; i < curr_match; i++)
    {
        wf.write((char *)&array[i].hour, sizeof(unsigned int));
        wf.write((char *)&array[i].minutes, sizeof(unsigned int));
        wf.write((char *)&array[i].day, sizeof(unsigned int));
        wf.write((char *)&array[i].month, sizeof(unsigned int));
        wf.write((char *)&array[i].year, sizeof(unsigned int));
        size_t size1 = array[i].team_one.size();
        wf.write((char *)&size1, sizeof(size1));
        wf.write((array[i].team_one.c_str()), size1);
        size_t size2 = array[i].team_two.size();
        wf.write((char *)&size2, sizeof(size2));
        wf.write((array[i].team_two.c_str()), size2);
    }
    wf.close();
    delete[] array;
    return 0;
}