#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
using namespace std;
int main(int argc, char *argv[])
{
    string stroka;
    string razdeliteli;
    string main_words;
    ifstream stream_for_stroka;
    ifstream stream_for_words;
    vector <string> vec;
    vector <string> vec_razdeliteli;
    vector <string> vec_main_words;
    vector <string> vec_loss_words;
    vector <int> vec_index_words;
    string file_name_stroka;
    string file_name_words;
    string dop_stroka_1;
    string dop_stroka_2;
    int number_words = 0;
    int index;
    if (argc >= 3)
    {
        file_name_words = argv[1];
        file_name_stroka = argv[2];
    }
    else
    {
        cout << "Введите имя файла, в котором записаны ключевые слова и разделители" << endl;
        cin >> file_name_words;
        cout << "Введите имя файла, в котором записан код" << endl;
        cin >> file_name_stroka;
    }
    stream_for_words.open(file_name_words);
    if (stream_for_words.is_open())
    {
        getline(stream_for_words, main_words);
        string delimetr = " ";
        size_t pos = 0;
        string token;
        string token_razdeliteli;
        while ((pos = main_words.find(delimetr)) != string::npos)
        {
            token = main_words.substr(0, pos);
            main_words.erase(0, pos + delimetr.length());
            vec_main_words.push_back(token);
        }
        getline(stream_for_words, razdeliteli);
        while ((pos = razdeliteli.find(delimetr)) != string::npos)
        {
            token_razdeliteli = razdeliteli.substr(0, pos);
            razdeliteli.erase(0, pos + delimetr.length());
            vec_razdeliteli.push_back(token_razdeliteli);
        }
    }
    else
    {
        cout << "uncorrect file name for main words and razdeliteli" << endl;
        return 1;
    }
    cout << "MAIN WORDS " << endl;
    for (unsigned int i = 0; i < vec_main_words.size(); i++)
    {
        cout << vec_main_words[i] << " ";
    }
    cout << endl;
    cout << "------------------------------------------------" << endl;
    cout << "RAZDELITELI" << endl;
    for (unsigned int j = 0; j < vec_razdeliteli.size(); j++)
    {
        cout << vec_razdeliteli[j] << " ";
    }
    cout << endl;
    cout << "-------------------------------------------------" << endl;
    stream_for_words.close();
    for (unsigned int i = 0; i < vec_razdeliteli.size(); i++)
    {
        dop_stroka_2 = dop_stroka_2 + "\\" + vec_razdeliteli[i];
        if (i != vec_razdeliteli.size())
        {
            dop_stroka_2 += "|";
        }
    }
    const regex regexp(dop_stroka_2 + "\\s");
    smatch m;
    stream_for_stroka.open(file_name_stroka);
    if (stream_for_stroka.is_open())
    {
        while (!stream_for_stroka.eof())
        {
            getline(stream_for_stroka, stroka);
            vec.push_back(stroka);
            while (regex_search(stroka, m, regexp))
            {
                for (auto x : m)
                {
                    int start = m.position();
                    for (int i = 0; i <= start; i++)
                    {
                        if (i == start)
                        {
                            int flag = 0;
                            for (unsigned int l = 0; l < vec_main_words.size(); l++)
                            {
                                if (dop_stroka_1 == vec_main_words[l])
                                {
                                    flag = 1;
                                    index = 1;
                                    vec_index_words.push_back(index);
                                    vec_index_words.push_back(l);
                                    cout << "Найдено ключевое слово " << dop_stroka_1 << " Код лексемы: (" << index << ", " << l << ")" << endl;
                                    dop_stroka_1.clear();
                                }
                            }
                            if ((flag == 0) && (dop_stroka_1 != "\0"))
                            {
                                index = 2;
                                vec_index_words.push_back(index);
                                vec_index_words.push_back(number_words);
                                vec_loss_words.push_back(dop_stroka_1);
                                cout << "Найдено слово " << dop_stroka_1 << " Код лексемы: (" << index << ", " << number_words << ")" << endl;
                                dop_stroka_1.clear();
                                number_words++;
                            }
                        }
                        else
                        {
                            dop_stroka_1 += stroka[i];
                        }
                    }
                    for (unsigned int k = 0; k < vec_razdeliteli.size(); k++)
                    {
                        if (x == vec_razdeliteli[k])
                        {
                            index = 0;
                            vec_index_words.push_back(index);
                            vec_index_words.push_back(k);
                            cout << "Найден разделитель " << x << " Код лексемы: (" << index;
                            cout << ", " << k << ")" << endl;
                        }
                    }
                }
                stroka = m.suffix().str();
            }
        }
    }
    else
    {
        cout << "uncorrect file name for code" << endl;
        return 1;
    }
    cout << "-------------------------------" << endl;
    cout << "исходный код программы:" << endl;
    for (unsigned int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << endl;
    }
    cout << "код программы, разбитый на коды лексем:" << endl;
    for (unsigned int i = 0; i < vec_index_words.size(); i++)
    {
        if (i % 2 == 0)
        {
            cout << "(";
            cout << vec_index_words[i] << " ";
        }
        if (i % 2 == 1)
        {
            cout << vec_index_words[i];
            cout << ") ";
        }
    }
    cout << endl;
    return 0;
}