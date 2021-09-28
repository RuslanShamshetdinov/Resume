/*
Implementation of a compiler for an individual grammar variant that performs lexical and syntactic analysis of the input program code
*/
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <map>
using namespace std;
void functions_for_read_words(string file_name_words, vector<string> &vec_razdeliteli, vector<string> &vec_main_words)
{
    ifstream stream_for_words; // поток для открытия файла с ключевыми словами
    string razdeliteli;
    string main_words;
    stream_for_words.open(file_name_words);
    if (stream_for_words.is_open()) //открытие потока считывания для ключевых слов и разделителей и запись их в соответствующие вектора
    {
        getline(stream_for_words, main_words);
        string delimetr = " "; // разделитель между словами в строках файла, все слова и разделители отделены пробелом
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
        return;
    }
    stream_for_words.close();
}
void functions_for_scanner(string file_name_stroka, vector<int> &vec_index_words, vector<string> &vec_main_words, regex regexp, vector<string> &vec_loss_words, vector<string> &vec_razdeliteli)
{
    vector<string> vec;         // вектор для хранения строки исходного кода
    ifstream stream_for_stroka; // поток для открытия файла с исходным кодом
    string dop_stroka_1;        // вспомогательная строка №1 для проверки принадлежности слова к списку ключевых слов
    int number_words = 0;       // переменная для хранения номера слова в списке слов не найденных в ключевых словах и разделителях
    string stroka;              // переменная, хранящая строку кода, которую необходимо разбить на лексемы и проверить
    smatch m;
    int index;
    stream_for_stroka.open(file_name_stroka);
    if (stream_for_stroka.is_open()) // открытие потока считывания для исходного кода и разбиение кода на лексемы
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
}
void functions_for_rules(string file_name_rules, vector<string> &vec_nonterminal_symbols, vector<pair<string, string>> &vec_rules, vector<pair<string, string>> &vec_rules_1, regex regexp, map<string, vector<string>> &map_for_words)
{
    vector<string> vec_help;   // вспомогательный вектор для хранения данных
    ifstream stream_for_rules; // поток для открытия файла с правилами
    int flag = 0;              // переменная для проверки условий
    string stroka_for_rules;   //переменная, хранящая строку с правилом
    smatch m;
    stream_for_rules.open(file_name_rules);
    if (stream_for_rules.is_open()) // открытие потока считывания для записи правил в вектор
    {
        while (!stream_for_rules.eof())
        {
            getline(stream_for_rules, stroka_for_rules);
            if (stroka_for_rules.length() == 0)
            {
                break;
            }
            string delimetr_for_rules = "->"; // разделитель между правой и левой частями правила
            auto pos_for_rules = stroka_for_rules.find(delimetr_for_rules);
            string dop_stroka_rules_1 = stroka_for_rules.substr(0, pos_for_rules);                           // левая часть правила
            string dop_stroka_rules_2 = stroka_for_rules.substr(pos_for_rules + 2, stroka_for_rules.size()); // правая часть правила
            vec_nonterminal_symbols.push_back(dop_stroka_rules_1);
            vec_rules.push_back(make_pair(dop_stroka_rules_1, dop_stroka_rules_2));
            vec_rules_1.push_back(make_pair(dop_stroka_rules_1, dop_stroka_rules_2));
            if (regex_search(dop_stroka_rules_2, m, regexp) == true) // формирование структуры данных для хранения левой части правила и правой части, разбитой на слова
            {
                while (regex_search(dop_stroka_rules_2, m, regexp))
                {
                    if (m.prefix().length() != 0)
                    {
                        vec_help.push_back(m.prefix());
                    }
                    dop_stroka_rules_2 = m.suffix().str();
                    if (regex_search(dop_stroka_rules_2, m, regexp) == false)
                    {
                        vec_help.push_back(dop_stroka_rules_2);
                    }
                }
                for (auto i = map_for_words.begin(); i != map_for_words.end(); i++)
                {
                    if (dop_stroka_rules_1 == i->first)
                    {
                        for (unsigned int k = 0; k < i->second.size(); k++)
                        {
                            vec_help.push_back(i->second[k]);
                        }
                        flag = 1;
                        auto iterator = vec_help.cbegin();
                        for (unsigned int i = 0; i < vec_help.size(); i++)
                        {
                            for (unsigned int l = i + 1; l < vec_help.size(); l++)
                            {
                                if (vec_help[i] == vec_help[l])
                                {
                                    vec_help.erase(iterator + l);
                                }
                            }
                        }
                        map_for_words.erase(dop_stroka_rules_1);
                        map_for_words.insert(make_pair(dop_stroka_rules_1, vec_help));
                        vec_help.clear();
                        break;
                    }
                }
                if (flag == 0)
                {
                    map_for_words.insert(make_pair(dop_stroka_rules_1, vec_help));
                    vec_help.clear();
                }
                flag = 0;
            }
            else
            {
                vec_help.push_back(dop_stroka_rules_2);
                for (auto i = map_for_words.begin(); i != map_for_words.end(); i++)
                {
                    if (dop_stroka_rules_1 == i->first)
                    {
                        flag = 1;
                        for (unsigned int k = 0; k < i->second.size(); k++)
                        {
                            vec_help.push_back(i->second[k]);
                        }
                        map_for_words.erase(dop_stroka_rules_1);
                        auto iterator = vec_help.cbegin();
                        for (unsigned int i = 0; i < vec_help.size(); i++)
                        {
                            for (unsigned int l = i + 1; l < vec_help.size(); l++)
                            {
                                if (vec_help[i] == vec_help[l])
                                {
                                    vec_help.erase(iterator + l);
                                }
                            }
                        }
                        map_for_words.insert(make_pair(dop_stroka_rules_1, vec_help));
                        vec_help.clear();
                        break;
                    }
                }
                if (flag == 0)
                {
                    map_for_words.insert(make_pair(dop_stroka_rules_1, vec_help));
                    vec_help.clear();
                }
                flag = 0;
            }
        }
    }
    else
    {
        cout << "uncorrect file name for rules" << endl;
        return;
    }
}
void functions_for_vector_right_symbols(vector<pair<string, string>> &vec_rules, vector<pair<string, string>> &vec_symbols_plus_right_symbols, regex regexp, vector<string> &vec_nonterminal_symbols)
{
    vector<string> vec_right_symbols; // вектор для хранения первых символов из правил
    smatch m_for_rules;
    int count_right_symbols = 0;
    unsigned int index_for_remove = 0;                             // индекс для удаления из пары векторов нетерминальных символов и первых правых символов
    for (auto it = vec_rules.begin(); it != vec_rules.end(); it++) // формирование вектора первых элементов из правой части правил
    {
        string dop_stroka_right_symbol;
        int start_rules;
        if (regex_search(it->second, m_for_rules, regexp) == true)
        {
            for (auto x_1 : m_for_rules)
            {
                start_rules = m_for_rules.position();
                if ((start_rules == 0) && (x_1.length() != 0))
                {
                    vec_right_symbols.push_back(x_1);
                    count_right_symbols++;
                }
                else
                {
                    dop_stroka_right_symbol = it->second.substr(0, start_rules);
                    vec_right_symbols.push_back(dop_stroka_right_symbol);
                    count_right_symbols++;
                }
            }
        }
        else if (regex_search(it->second, m_for_rules, regexp) == false)
        {
            if ((it->second.size() == 2) && (it->second[1] != '1') && (it->second[0] != '!'))
            {
                if (it->second == "id")
                {
                    dop_stroka_right_symbol = it->second;
                    vec_right_symbols.push_back(dop_stroka_right_symbol);
                }
                else
                {
                    dop_stroka_right_symbol = it->second[0];
                    vec_right_symbols.push_back(dop_stroka_right_symbol);
                }
            }
            else if (it->second[0] != '!')
            {
                vec_right_symbols.push_back(it->second);
            }
            if (it->second[0] == '!')
            {
                dop_stroka_right_symbol = it->second[0];
                vec_right_symbols.push_back(dop_stroka_right_symbol);
            }
            count_right_symbols++;
        }
    }
    for (int i = 0; i < count_right_symbols; i++) // формирование вектора нетерминальных символов и первых символов из правил
    {
        vec_symbols_plus_right_symbols.push_back(make_pair(vec_nonterminal_symbols[i], vec_right_symbols[i]));
    }
    while (index_for_remove < vec_symbols_plus_right_symbols.size()) // удаление пары, когда нетермильный символ равен символу справа
    {
        if (vec_symbols_plus_right_symbols[index_for_remove].first == vec_symbols_plus_right_symbols[index_for_remove].second)
        {
            vec_symbols_plus_right_symbols.erase(vec_symbols_plus_right_symbols.begin() + index_for_remove);
        }
        else
        {
            index_for_remove++;
        }
    }
}
void functions_for_first(vector<pair<string, string>> &vec_symbols_plus_right_symbols, map<string, vector<string>> &map_right_symbols)
{
    string dop_stroka_erase;                                                                              // вспомогательная строка
    vector<string> vec_help;                                                                              // вспомогательный вектор для хранения данных
    int flag = 0;                                                                                         // переменная для проверки условий
    int count = 0;                                                                                        // переменная для отделения 1 пары из мапы
    for (auto i = vec_symbols_plus_right_symbols.begin(); i != vec_symbols_plus_right_symbols.end(); i++) // формирование множества first
    {
        vec_help.push_back(i->second);
        for (auto j = i + 1; j != vec_symbols_plus_right_symbols.end(); j++)
        {
            if ((i->first == j->first) && (i->second != j->second))
            {
                flag = 1;
                vec_help.push_back(j->second);
            }
            else
            {
                break;
            }
        }
        if (flag == 1)
        {
            map_right_symbols.insert(make_pair(i->first, vec_help));
            vec_help.clear();
        }
        else
        {
            map_right_symbols.insert(make_pair(i->first, vec_help));
            vec_help.clear();
        }
        flag = 0;
    }
    for (auto r = map_right_symbols.begin(); r != map_right_symbols.end(); ++r) // замена во множестве first всех нетерминальных символов справа на их соответствующие множества first
    {
        int flag_1 = 0;
        for (unsigned int i = 0; i < r->second.size(); i++)
        {
            vec_help.push_back(r->second[i]);
        }
        for (auto j = map_right_symbols.begin(); j != map_right_symbols.end(); ++j)
        {
            for (unsigned int i = 0; i < j->second.size(); i++)
            {
                if ((r->first == j->second[i]) && (r->first != j->first))
                {
                    flag_1 = 1;
                    unsigned int m = i;
                    count++;
                    if (count > 1)
                    {
                        for (unsigned int s = 0; s < r->second.size(); s++)
                        {
                            vec_help.push_back(r->second[s]);
                        }
                    }
                    for (unsigned int k = 0; k < j->second.size(); k++)
                    {
                        if (k != m)
                        {
                            vec_help.push_back(j->second[k]);
                        }
                    }
                    auto iterator = vec_help.cbegin();
                    for (unsigned int i = 0; i < vec_help.size(); i++)
                    {
                        for (unsigned int l = i + 1; l < vec_help.size(); l++)
                        {
                            if (vec_help[i] == vec_help[l])
                            {
                                vec_help.erase(iterator + l);
                            }
                        }
                    }
                    dop_stroka_erase = j->first;
                    map_right_symbols.erase(dop_stroka_erase);
                    map_right_symbols.insert(make_pair(j->first, vec_help));
                    vec_help.clear();
                    dop_stroka_erase.clear();
                }
            }
        }
        if (flag_1 == 0)
        {
            vec_help.clear();
        }
    }
    cout << "map first" << endl;
    for (auto r = map_right_symbols.begin(); r != map_right_symbols.end(); ++r)
    {
        cout << (*r).first << " -";
        for (unsigned int i = 0; i < r->second.size(); i++)
        {
            cout << (*r).second[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void functions_for_follow(vector<pair<string, string>> &vec_rules, regex regexp, map<string, vector<string>> &map_for_words, map<string, vector<string>> &map_follow, map<string, vector<string>> &map_right_symbols)
{
    string stroka_for_suffix;
    string dop_stroka_erase; // вспомогательная строка
    vector<string> vec_help; // вспомогательный вектор для хранения данных
    int flag = 0;            // переменная для проверки условий
    int count_for_follow = 0;
    smatch m_for_follow_1;
    int flag_2 = 0;
    int flag_1 = 0;
    int flag_3 = 0;
    for (auto j = vec_rules.begin(); j != vec_rules.end(); j++) // формирование множества follow (1 шаг)
    {
        if (flag == 0)
        {
            vec_help.push_back("EPS");
            map_follow.insert(make_pair(j->first, vec_help));
            flag = 1;
            vec_help.clear();
        }
        if (regex_search(j->second, m_for_follow_1, regexp) == true)
        {
            while (regex_search(j->second, m_for_follow_1, regexp) == true)
            {
                for (auto x : m_for_follow_1)
                {
                    dop_stroka_erase = m_for_follow_1.prefix();
                    for (auto i = vec_rules.begin(); i != vec_rules.end(); i++)
                    {
                        if ((dop_stroka_erase == i->first))
                        {
                            flag_3 = 1;
                            if (x != " ")
                            {
                                vec_help.push_back(x);
                            }
                            if (x == " ")
                            {
                                stroka_for_suffix = m_for_follow_1.suffix();
                            }
                            if ((x == " ") && (regex_search(stroka_for_suffix, regexp) == false))
                            {
                                vec_help.push_back(m_for_follow_1.suffix());
                            }
                            if ((x == " ") && (flag_3 == 1))
                            {
                                smatch m_for_follow_2;
                                if (regex_search(stroka_for_suffix, m_for_follow_2, regexp) == true)
                                {
                                    for (auto x_1 : m_for_follow_2)
                                    {
                                        if (x_1 == " ")
                                        {
                                            vec_help.push_back(m_for_follow_2.prefix());
                                        }
                                        else
                                        {
                                            vec_help.push_back(x_1);
                                        }
                                    }
                                }
                            }
                            flag_3 = 0;
                            for (auto r = map_follow.begin(); r != map_follow.end(); r++)
                            {
                                if (i->first == r->first)
                                {
                                    for (unsigned int l = 0; l < r->second.size(); l++)
                                    {
                                        if (x == r->second[l])
                                        {
                                            flag_1 = 1;
                                            flag_2 = 1;
                                        }
                                    }
                                    if (flag_2 == 0)
                                    {
                                        for (unsigned int l = 0; l < r->second.size(); l++)
                                        {
                                            vec_help.push_back(r->second[l]);
                                        }
                                    }
                                    flag_2 = 0;
                                }
                            }
                            if (flag_1 == 0)
                            {
                                map_follow.erase(i->first);
                                map_follow.insert(make_pair(i->first, vec_help));
                                vec_help.clear();
                            }
                            flag_1 = 0;
                            vec_help.clear();
                            break;
                        }
                    }
                }
                j->second = m_for_follow_1.suffix().str();
            }
        }
        else
        {
            dop_stroka_erase = j->second[0];
            stroka_for_suffix = j->second[1];
            if ((j->second.length() == 2) && (stroka_for_suffix != "1"))
            {
                for (auto i = vec_rules.begin(); i != vec_rules.end(); i++)
                {
                    if (i->first == dop_stroka_erase)
                    {
                        vec_help.push_back(stroka_for_suffix);
                        map_follow.insert(make_pair(i->first, vec_help));
                        vec_help.clear();
                    }
                }
            }
        }
    }
    for (auto i = map_for_words.begin(); i != map_for_words.end(); i++) // формирование множества follow (2 шаг)
    {
        string stroka_first_element;
        string stroka_second_element;
        for (auto j = map_for_words.begin(); j != map_for_words.end(); j++)
        {
            if (i != j)
            {
                for (unsigned int k = 0; k < j->second.size(); k++)
                {
                    if (i->first == j->second[k])
                    {
                        stroka_first_element = i->first;
                        stroka_second_element = j->first;
                        unsigned int count = 0;
                        for (auto s = map_follow.begin(); s != map_follow.end(); s++)
                        {
                            if (s->first == stroka_first_element)
                            {
                                flag_1 = 1;
                                for (unsigned int m = 0; m < s->second.size(); m++)
                                {
                                    vec_help.push_back(s->second[m]);
                                }
                            }
                            if (s->first == stroka_second_element)
                            {
                                flag_2 = 1;
                                {
                                    for (unsigned int m = 0; m < s->second.size(); m++)
                                    {
                                        vec_help.push_back(s->second[m]);
                                    }
                                }
                            }
                            if (flag_1 == 1 && flag_2 == 1 && count == map_follow.size() - 1)
                            {
                                flag_3 = 1;
                                map_follow.erase(stroka_first_element);
                                auto iterator = vec_help.cbegin();
                                for (unsigned int i = 0; i < vec_help.size(); i++)
                                {
                                    for (unsigned int l = i + 1; l < vec_help.size(); l++)
                                    {
                                        if (vec_help[i] == vec_help[l])
                                        {
                                            vec_help.erase(iterator + l);
                                        }
                                    }
                                }
                                map_follow.insert(make_pair(stroka_first_element, vec_help));
                                vec_help.clear();
                            }
                            count++;
                            if (flag_3 == 1)
                            {
                                flag_1 = 0;
                                flag_2 = 0;
                            }
                            else if (count == map_follow.size())
                            {
                                vec_help.clear();
                            }
                            flag_3 = 0;
                        }
                        break;
                    }
                }
            }
        }
    }
    while (count_for_follow < 3) // формирование множества follow (3 шаг)
    {
        for (auto i = map_for_words.begin(); i != map_for_words.end(); i++)
        {
            for (auto j = map_for_words.begin(); j != map_for_words.end(); j++)
            {
                for (unsigned int k = 0; k < i->second.size(); k++)
                {
                    for (unsigned int s = 0; s < j->second.size(); s++)
                    {
                        if ((i->second[k] == j->second[s]) && (i->second[k] != j->first))
                        {
                            for (auto r = map_follow.begin(); r != map_follow.end(); r++)
                            {
                                if (j->first == r->first)
                                {
                                    flag_2 = 1;
                                    for (unsigned int m = 0; m < r->second.size(); m++)
                                    {
                                        vec_help.push_back(r->second[m]);
                                    }
                                }
                                if (j->second[s] == r->first)
                                {
                                    flag_3 = 1;
                                    for (unsigned int m = 0; m < r->second.size(); m++)
                                    {
                                        vec_help.push_back(r->second[m]);
                                    }
                                }
                            }
                            if ((flag_3 == 1) && flag_2 == 1)
                            {
                                map_follow.erase(i->second[k]);
                                auto iterator = vec_help.cbegin();
                                for (unsigned int i = 0; i < vec_help.size(); i++)
                                {
                                    for (unsigned int l = i + 1; l < vec_help.size(); l++)
                                    {
                                        if (vec_help[i] == vec_help[l])
                                        {
                                            vec_help.erase(iterator + l);
                                        }
                                    }
                                }
                                map_follow.insert(make_pair(i->second[k], vec_help));
                                vec_help.clear();
                            }
                            if ((flag_3))
                            {
                                auto iterator = vec_help.cbegin();
                                for (unsigned int i = 0; i < vec_help.size(); i++)
                                {
                                    for (unsigned int l = i + 1; l < vec_help.size(); l++)
                                    {
                                        if (vec_help[i] == vec_help[l])
                                        {
                                            vec_help.erase(iterator + l);
                                        }
                                    }
                                }
                                map_follow.insert(make_pair(i->second[k], vec_help));
                                vec_help.clear();
                            }
                            else if (((flag_3 == 0) && (flag_2 == 0)) || ((flag_3 == 0) && (flag_2 == 1)) || ((flag_3 == 1) && (flag_2 == 0)))
                            {
                                vec_help.clear();
                            }
                            flag_2 = 0;
                            flag_3 = 0;
                        }
                    }
                }
            }
        }
        count_for_follow++;
    }
    for (auto i = map_follow.begin(); i != map_follow.end(); i++)
    {
        if (i->first == "F")
        {
            for (unsigned int j = 0; j < i->second.size(); j++)
            {
                vec_help.push_back(i->second[j]);
            }
            map_follow.insert(make_pair("L", vec_help));
            vec_help.clear();
        }
    }
    for (auto i = map_follow.begin(); i != map_follow.end(); i++)
    {
        if (i->first == "D1")
        {
            for (unsigned int j = 0; j < i->second.size(); j++)
            {
                vec_help.push_back(i->second[j]);
            }
            map_follow.insert(make_pair("D", vec_help));
            vec_help.clear();
        }
    }
    for (auto i = map_follow.begin(); i != map_follow.end(); i++) // формирование множества follow (4 шаг)
    {
        for (unsigned int j = 0; j < i->second.size(); j++)
        {
            vec_help.push_back(i->second[j]);
            for (auto k = map_right_symbols.begin(); k != map_right_symbols.end(); k++)
            {
                if (i->second[j] == k->first)
                {
                    auto iterator = vec_help.cbegin();
                    vec_help.erase(iterator + j);
                    flag = 1;
                    for (unsigned int s = 0; s < k->second.size(); s++)
                    {
                        vec_help.push_back(k->second[s]);
                    }
                }
            }
        }
        if (flag == 1)
        {
            map_follow.erase(i->first);
            map_follow.insert(make_pair(i->first, vec_help));
            vec_help.clear();
        }
        else
        {
            vec_help.clear();
        }
        flag = 0;
    }
    cout << "map follow " << endl;
    for (auto r = map_follow.begin(); r != map_follow.end(); ++r)
    {
        cout << (*r).first << " -";
        for (unsigned int i = 0; i < r->second.size(); i++)
        {
            cout << (*r).second[i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void functions_for_translate(vector<string> &vec_for_code,vector<int> &check_rules_vertex,vector<string> &vec_for_stack,vector<pair<string, string>> &vec_rules_1, vector<int> &vec_index_words,vector<string> &vec_razdeliteli,vector<string> &vec_main_words,vector<string> &vec_loss_words)
{
    int count_for_rules=0;
    string stroka;
    for (unsigned int i = 0; i < vec_index_words.size(); i += 2)
    {
        if (vec_index_words[i] == 0)
        {
            for (unsigned int j = 0; j < vec_razdeliteli.size(); j++)
            {
                if (vec_index_words[i + 1] == j)
                {
                    stroka = vec_razdeliteli[j];
                }
            }
        }
        if (vec_index_words[i] == 1)
        {
            for (unsigned int k = 0; k < vec_main_words.size(); k++)
            {
                if (vec_index_words[i + 1] == k)
                {
                    stroka = vec_main_words[k];
                }
            }
        }
        if (vec_index_words[i] == 2)
        {
            stroka = "id";
        }
        for (auto m = vec_rules_1.begin(); m != vec_rules_1.end(); m++)
        {
            if (count_for_rules == 0)
            {
                count_for_rules++;
                vec_for_stack.push_back(m->first);
            }
        }
        vec_for_code.push_back(stroka);
        for (unsigned int i = 0; i < vec_rules_1.size(); i++)
        {
            check_rules_vertex.push_back(0);
        }
        int count_for_rules = 0;
    }
}
void functions_for_parsing(vector<string> &vec_for_help, vector<string> &vec_for_code, vector<pair<string, string>> &vec_rules_1, regex regexp, map<string, vector<string>> &map_right_symbols, vector<string> &vec_for_stack,vector<int> &check_rules_vertex, map<string, vector<string>> &map_follow)
{
                    cout<<"Код ошибки - 2: неверная строка"<<endl;
                    return;
    int count_3 = 0;
    int flag = 0;
    while (flag != 1)
    {
        string suffix_stroka_stack;
        string vertex;
        int flag_for_first = 0;
        int flag_for_follow = 0;
        string stroka_stack;
        string stroka_rules_stack;
        int count = 0;
        smatch m;
        if (vec_for_stack[0].size() == 1)
        {
            stroka_stack = vec_for_stack[0];
        }
        else if (regex_search(vec_for_stack[0], m, regexp) == true)
        {
            for (auto x : m)
            {
                stroka_stack = m.prefix();
                if (count == 0)
                {
                    suffix_stroka_stack.insert(0, x);
                    count++;
                }
                break;
            }
            suffix_stroka_stack += m.suffix();
        }
        int count_2 = 0;
        for (auto i = vec_rules_1.begin(); i != vec_rules_1.end(); i++)
        {
            if (i->first == stroka_stack && stroka_stack == "E")
            {
                count_2++;
            }
            if (count_2 == 3)
            {
                string stroka_2 = i->second;
                size_t pos = 0;
                pos = vec_for_stack[0].find(stroka_stack);
                string stroka_erase = vec_for_stack[0].erase(pos, stroka_stack.size());
                stroka_2 += stroka_erase;
                if (stroka_erase[0] == ' ')
                {
                    stroka_erase.erase(0, 1);
                }
                vec_for_stack.erase(vec_for_stack.begin());
                vec_for_stack.push_back(stroka_2);
                stroka_stack = "E1";
                suffix_stroka_stack = vec_for_stack[0].erase(0, stroka_stack.size());
                break;
            }
        }
        if (stroka_stack == "F" && count_3 == 2)
        {
            return;
        }
        if (stroka_stack == "F")
        {
            count_3++;
        }
        for (auto p = map_right_symbols.begin(); p != map_right_symbols.end(); p++)
        {
            int flag_for_vertex = 0;
            if (p->first == stroka_stack)
            {
                for (unsigned int i = 0; i < p->second.size(); i++)
                {
                    if (vec_for_code[0] == p->second[i])
                    {
                        vertex = p->first;
                        flag_for_vertex = 1;
                        flag_for_first = 1;
                        break;
                    }
                }
                if (flag_for_vertex == 1)
                {
                    break;
                }
            }
        }
        for (auto i = map_follow.begin(); i != map_follow.end(); i++)
        {
            int flag_for_vertex = 0;
            if (i->first == stroka_stack)
            {
                for (unsigned int j = 0; j < i->second.size(); j++)
                {
                    if (vec_for_code[0] == i->second[j])
                    {
                        vertex = i->first;
                        flag_for_vertex = 1;
                        flag_for_follow = 1;
                        break;
                    }
                }
                if (flag_for_vertex == 1)
                {
                    break;
                }
            }
        }
        if (flag_for_first == 1)
        {
            int count_1 = 0;
            for (auto m = vec_rules_1.begin(); m != vec_rules_1.end(); m++)
            {
                if (vertex == m->first && check_rules_vertex[count_1] == 0)
                {
                    string new_stroka_stack;
                    stroka_rules_stack = m->second;
                    if (suffix_stroka_stack.length() != 0)
                    {
                        new_stroka_stack = new_stroka_stack + stroka_rules_stack + suffix_stroka_stack;
                    }
                    else
                    {
                        new_stroka_stack = new_stroka_stack + stroka_rules_stack;
                    }
                    vec_for_help.push_back(stroka_rules_stack);
                    vec_for_stack.erase(vec_for_stack.begin());
                    vec_for_stack.push_back(new_stroka_stack);
                    new_stroka_stack.clear();
                    suffix_stroka_stack.clear();
                    if (count_1 == 27 || count_1 == 40 || count_1 == 31 || count_1 == 35)
                    {
                        check_rules_vertex[count_1] = 0;
                    }
                    else
                    {
                        check_rules_vertex[count_1] = 1;
                    }
                    break;
                }
                count_1++;
            }
        }
        if (flag_for_follow == 1)
        {
            string new_stroka_stack;
            if (suffix_stroka_stack.length() != 0)
            {
                new_stroka_stack = new_stroka_stack + vec_for_code[0] + suffix_stroka_stack;
            }
            else
            {
                new_stroka_stack = new_stroka_stack + vec_for_code[0];
            }
            vec_for_stack.erase(vec_for_stack.begin());
            vec_for_stack.push_back(new_stroka_stack);
            new_stroka_stack.clear();
            suffix_stroka_stack.clear();
        }
        if (flag_for_first == 0 && flag_for_follow == 0)
        {
            int count_rules = 0;
            string start_vertex;
            suffix_stroka_stack.clear();
            for (unsigned int i = 0; i < check_rules_vertex.size(); i++)
            {
                if (check_rules_vertex[i] == 1)
                {
                    count_rules = i;
                }
            }
            if (count_rules == 0)
            {
                cout << "строка неверна" << endl;
                cout << " код ошибки - 1: нет разделителя в начале" << endl;
                return;
            }
            for (auto i = vec_rules_1.begin(); i != vec_rules_1.end(); i++)
            {
                if (i->second == stroka_stack)
                {
                    start_vertex = i->first;
                    size_t pos = 0;
                    pos = vec_for_stack[0].find(stroka_stack);
                    if (pos == 0)
                    {
                        string stroka_stack_erase = vec_for_stack[0].erase(pos, stroka_stack.size());
                        vec_for_stack.erase(vec_for_stack.begin());
                        start_vertex += stroka_stack_erase;
                        vec_for_stack.push_back(start_vertex);
                    }
                    break;
                }
                if (i->second == vec_for_help[vec_for_help.size() - 1])
                {
                    start_vertex = i->first;
                    size_t pos = 0;
                    pos = vec_for_stack[0].find(vec_for_help[vec_for_help.size() - 1]);
                    if (pos == 0)
                    {
                        string stroka_stack_erase = vec_for_stack[0].erase(pos, vec_for_help[vec_for_help.size() - 1].size());
                        vec_for_stack.erase(vec_for_stack.begin());
                        start_vertex += stroka_stack_erase;
                        vec_for_stack.push_back(start_vertex);
                    }
                    break;
                }
            }
            if (stroka_stack.length() == 0)
            {
                cout<<"Код ошибки - 2: неверная строка"<<endl;
                return;
            }
            functions_for_parsing(vec_for_help, vec_for_code, vec_rules_1, regexp, map_right_symbols, vec_for_stack,check_rules_vertex, map_follow);
        }
        flag_for_first = 0;
        flag_for_follow = 0;
        while ((vec_for_stack[0] == vec_for_code[0]) || (vec_for_stack[0].find(vec_for_code[0]) != -1))
        {
            if (vec_for_stack.empty())
            {
                cout << "строка верна" << endl;
                flag = 1;
                return;
            }
            if (vec_for_stack[0] == vec_for_code[0])
            {
                vec_for_stack.erase(vec_for_stack.begin());
                vec_for_code.erase(vec_for_code.begin());
            }
            else if (vec_for_stack[0].find(vec_for_code[0]) != -1)
            {
                size_t pos = 0;
                pos = vec_for_stack[0].find(vec_for_code[0]);
                string stroka_erase = vec_for_stack[0].erase(pos, vec_for_code[0].size());
                if (stroka_erase[0] == ' ')
                {
                    stroka_erase.erase(0, 1);
                }
                vec_for_code.erase(vec_for_code.begin());
                vec_for_stack.erase(vec_for_stack.begin());
                vec_for_stack.push_back(stroka_erase);
            }
        }
    }
}
int main(int argc, char *argv[])
{
    map<string, vector<string>> map_for_words;                   // структура данных, которая хранит нетерминальный символ и все слова из правил этого символа
    map<string, vector<string>> map_right_symbols;               // структура данных, хранящая нетерминальный символ и первые символы из всех его правил (множество first)
    map<string, vector<string>> map_follow;                      // структура данных, хранящая нетерминальный символ и все символы в правилах идущие за ним (множество second)
    vector<string> vec_razdeliteli;                              // вектор для хранения всех разделителей
    vector<string> vec_main_words;                               // вектор для хранения ключевых слов
    vector<string> vec_loss_words;                               // вектор для хранения слов, не относящихся к ключевым словам и разделителям
    vector<int> vec_index_words;                                 // вектор для хранения строки в виде кодов лексем
    vector<string> vec_nonterminal_symbols;                      // вектор для хранения левой части правила
    vector<pair<string, string>> vec_rules;                      // вектор для хранения правил
    vector<pair<string, string>> vec_rules_1;                    // вектор для хранения правил
    vector<pair<string, string>> vec_symbols_plus_right_symbols; // вектор для хранения нетерминальных символов и его ппервых символов
    string file_name_stroka;                                     // имя файла, в котором записан исходный код
    string file_name_words;                                      // имя файла, в котором записаны ключевые слова
    string file_name_rules;                                      // имя файла, в котором записаны правила
    string dop_stroka_2;                                         // вспомогательная строка №2 для формирования регулярного выражения
    vector<string> vec_for_stack;
    vector<int> check_rules_vertex;
    vector<string> vec_for_code;
    vector<string> vec_for_help;
    if (argc >= 4)
    {
        file_name_words = argv[1];
        file_name_stroka = argv[2];
        file_name_rules = argv[3];
    }
    else
    {
        cout << "Введите имя файла, в котором записаны ключевые слова и разделители" << endl;
        cin >> file_name_words;
        cout << "Введите имя файла, в котором записан код" << endl;
        cin >> file_name_stroka;
        cout << "Введите имя файла, в котором записаны правила" << endl;
        cin >> file_name_rules;
    }
    functions_for_read_words(file_name_words, vec_razdeliteli, vec_main_words);
    for (unsigned int i = 0; i < vec_razdeliteli.size(); i++) //  формирование регулярного выражения
    {
        dop_stroka_2 = dop_stroka_2 + "\\" + vec_razdeliteli[i];
        if (i != vec_razdeliteli.size())
        {
            dop_stroka_2 += "|";
        }
    }
    regex regexp(dop_stroka_2 + "\\s"); //регулярное выражение для проверки исходного кода
    functions_for_scanner(file_name_stroka, vec_index_words, vec_main_words, regexp, vec_loss_words, vec_razdeliteli);
    functions_for_rules(file_name_rules, vec_nonterminal_symbols, vec_rules, vec_rules_1, regexp, map_for_words);
    functions_for_vector_right_symbols(vec_rules, vec_symbols_plus_right_symbols, regexp, vec_nonterminal_symbols);
    functions_for_first(vec_symbols_plus_right_symbols, map_right_symbols);
    functions_for_follow(vec_rules, regexp, map_for_words, map_follow, map_right_symbols);
    functions_for_translate(vec_for_code,check_rules_vertex,vec_for_stack,vec_rules_1,vec_index_words,vec_razdeliteli,vec_main_words,vec_loss_words);
    functions_for_parsing(vec_for_help, vec_for_code, vec_rules_1, regexp, map_right_symbols, vec_for_stack,check_rules_vertex, map_follow);
    return 0;
}