#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <queue>
#include <regex>
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
    int flag_1=0;
    int flag_2=0;
    int flag = 0;
    int flag_3=0;
    int count = 0;
    const string file_name = "file1.txt";
    string stroka;
    string dop_stroka;
    ofstream stream;
    ifstream stream_1;
    queue<string> q;
    stack<string> st;
    string stroka_for_q;
    double cislo;
    stack <double> st_for_cislo;
    int prioritet;
    int prioritet_for_first_element;
    regex regexp("\\+|\\-|\\*|\\/|\\(|\\)");
    regex regexp_1("-\\d");
    smatch m;
    smatch m_1;
    if (argc >= 2)
    {
        stroka = argv[1];
    }
    else
    {
        cout << "Введите математическое выражение" << endl;
        cin >> stroka;
    }
    auto pos = stroka.find("=");
    if (pos != string::npos)
    {
        stream.open(file_name, ios::app);
        if (stream.is_open())
        {
            stream << stroka << endl;
            stream.close();
        }
    }
    else
    {
        stream_1.open(file_name, ios::in);
        cout << stroka << endl;
        while (!stream_1.eof())
        {
            string stroka_2;
            getline(stream_1, stroka_2);
            if (stroka_2.length() == 0)
            {
                break;
            }
            else
            {
                auto pos_2 = stroka_2.find("=");
                string str1 = stroka_2.substr(0, pos_2);
                string str2 = stroka_2.substr(pos_2 + 1, stroka_2.size());
                size_t pos_3 = 0;
                while ((pos_3 = stroka.find(str1, pos_3)) != string::npos)
                {
                    stroka.replace(pos_3, str1.size(), str2);
                    pos_3 += str2.size();
                }
            }
        }
        stream_1.close();
    }
    cout << stroka << endl;
    if (regex_search(stroka, m, regexp))
    {
        while (regex_search(stroka, m, regexp))
        {
            for (auto x : m)
            {
                int start = m.position();
                if ((start==0)&&(flag_3==0)&&(x=="-"))
                {
                    flag_1=1;
                    for(unsigned int i=1;i<stroka.size();i++)
                    {
                        dop_stroka+=stroka[i];
                        if (regex_search(dop_stroka,m_1,regexp)==true)
                        {
                            int end=m_1.position();
                            dop_stroka.clear();
                            for(int j=start;j<=end;j++)
                            {
                            dop_stroka+=stroka[j];
                            }
                            break;
                        }   
                    }
                        q.push(dop_stroka);
                        size_t pos;
                        pos=stroka.find(dop_stroka);
                        stroka.erase(pos,dop_stroka.size());
                        dop_stroka.clear(); 
                        flag_3++;
                }
                else if(flag_2==1)
                {
                    flag_1=1;
                    for(unsigned int i=1;i<stroka.size();i++)
                    {
                        dop_stroka+=stroka[i];
                        if (regex_search(dop_stroka,m_1,regexp)==true)
                        {
                            int end=m_1.position();
                            dop_stroka.clear();
                            for(int j=start;j<=end;j++)
                            {
                            dop_stroka+=stroka[j];
                            }
                            break;
                        }   
                    }
                        q.push(dop_stroka);
                        size_t pos;
                        pos=stroka.find(dop_stroka);
                        stroka.erase(pos,dop_stroka.size());
                        dop_stroka.clear(); 
                        flag_2=0;                   
                }
                if (flag_1==0)
                {
                for (int i = 0; i <= start; i++)
                {
                    if (i == start)
                    {
                        if (dop_stroka.length()!=0)
                        {
                        q.push(dop_stroka);
                        dop_stroka.clear();
                        }
                    }
                    else
                    {
                        dop_stroka += stroka[i];
                    }
                }
                
                if ((x == "*") || (x == "/"))
                {
                    prioritet = 3;
                }
                else if ((x == "+") || (x == "-"))
                {
                    prioritet = 2;
                }
                if ((x=="(") || (x==")"))
                {
                    prioritet=1;
                }
                if (st.empty() == true)
                {
                    flag = 1;
                    st.push(x);
                    count += 1;
                }
                if ((st.top() == "+") || (st.top() == "-"))
                {
                    prioritet_for_first_element = 2;
                }
                if ((st.top() == "*") || (st.top() == "/"))
                {
                    prioritet_for_first_element = 3;
                }
                if ((st.top() == "(") || (st.top() == ")"))
                {
                    prioritet_for_first_element = 1;
                }
                if (flag==0)
                {
                if (x == "(")
                {   
                    st.push(x);
                    count += 1;
                    for (unsigned int i=0;i<stroka.size();i++)
                    {
                        if (stroka[start+1]=='-')
                        {
                            flag_2=1;
                        }
                    }
                }
                else if (x == ")")
                {
                    st.push(x);
                    count += 1;
                    st.pop();
                    while (st.top() !="(")
                    {
                        q.push(st.top());
                        st.pop();
                    }
                    if(st.top()=="(")
                    {
                        st.pop();
                    }
                }
                    if (prioritet_for_first_element < prioritet)
                    {
                        st.push(x);
                        count += 1;
                    }
                    else if ((prioritet_for_first_element >= prioritet) && (x != "(") && (x!=")"))
                    {
                        q.push(st.top());
                        st.pop();
                        st.push(x);
                        count += 1;
                    }
                }
                flag = 0;
                stroka = m.suffix().str();
                }
                flag_1=0;
            if ((regex_search(stroka, regexp) == false)&&(stroka.length()!=0))
            {
                dop_stroka += stroka;
                q.push(dop_stroka);
            }
            }
        }
    }
    while (st.empty() != true)
    {
        q.push(st.top());
        st.pop();
    }
    while (!q.empty())
    {
        string val = q.front();
        if (regex_search(val,regexp)==false)
        {
            cislo=stod(val);
            st_for_cislo.push(cislo);
        }
        else if (regex_search(val,regexp)==true)
        {
            if (regex_search(val,regexp_1)==true)
            {
            cislo=stod(val);
            st_for_cislo.push(cislo);
            }
            double result;
            int count_for_cislo=0;
                if (val == "+")
                {
                    result=st_for_cislo.top();
                    st_for_cislo.pop();
                    while (count_for_cislo!=1)
                    {
                        result =st_for_cislo.top()+result;
                        st_for_cislo.pop();
                        count_for_cislo++;
                    }
                    st_for_cislo.push(result);
                } 
                if (val == "-")
                {
                    result=st_for_cislo.top();
                    st_for_cislo.pop();
                    while (count_for_cislo!=1)
                    {
                        result =st_for_cislo.top()-result;
                        st_for_cislo.pop();
                        count_for_cislo++;
                    }
                    st_for_cislo.push(result);
                }
                if (val == "*")
                {
                    result=st_for_cislo.top();
                    st_for_cislo.pop();
                    while (count_for_cislo!=1)
                    {
                        result =st_for_cislo.top()*result;
                        st_for_cislo.pop();
                        count_for_cislo++;
                    }
                    st_for_cislo.push(result);
                }
                if (val== "/")
                {
                    result=st_for_cislo.top();
                    st_for_cislo.pop();
                    while (count_for_cislo!=1)
                    {
                        result =st_for_cislo.top()/result;
                        st_for_cislo.pop();
                        count_for_cislo++;
                    }
                    st_for_cislo.push(result);
                }
        }
        stroka_for_q =stroka_for_q+val+" ";
        q.pop();
    }
    cout<<stroka_for_q<<endl; 
    cout<<"result = "<<st_for_cislo.top()<<endl;
    return 0;
}