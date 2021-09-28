#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
using namespace std;
struct Node
{
    int vertex_2;
    int length;
    Node *next;
    Node(int vertex_2_1, int length_1) : vertex_2(vertex_2_1), length(length_1), next(nullptr)
    {
    }
};
struct List_realisation // реализация структуры списка
{
    Node *first;
    Node *last;
    List_realisation() : first(nullptr), last(nullptr)
    {
    }
    bool is_empty()
    {
        return (first == nullptr);
    }
    void push_back(int vertex_2, int length) // фукнция добавления в список
    {
        Node *p = new Node(vertex_2, length);
        if (is_empty())
        {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }
    void print() // функция вывода списка на экран
    {
        if (is_empty())
        {
            return;
        }
        Node *p = first;
        while (p)
        {
            cout << "вершина " << p->vertex_2 << " расстояние до вершины " << p->length;
            p = p->next;
            cout << endl;
        }
    }
    int weight_vertex_for_list_realisation(int second_vertex) // функция, которая возвращает вес нужной вершины
    {
        Node *node = first;
        while (node)
        {
            if (node->vertex_2 == second_vertex)
            {
                return node->length;
            }
            node = node->next;
        }
        return 0;
    }
};
class Base_class // базовый класс с виртуальной функцией для возвращения веса нужной вершины
{
public:
    virtual int weight_for_vertex(int start_vertex, int vertex)
    {
    }
};
class Matrix : public Base_class
{
private:
    int flag_for_regex_search = 0;              // переменная для проверки регулярного выражения
    int matrix_dimension;                       // размерность матрицы смежности
    int vertex_1;                               // вершина, из которой может идти пользователь
    string stroka_matrix;                       // переменная необходимая для считывания информации из файла
    string dop_stroka_matrix;                   // переменная необходимая для записи вершин в массив
    int vertex_2;                               // вершина, в которую может попасть пользователь
    int length;                                 // расстояние между вершинами
    int **matrix;                               // двумерный массив для хранения матрицы смежности
    regex regexp{("\\:|\\(|\\)|\\,|\\->|\\s")}; // регулярное выражение для поиска номера вершины в строке для взвешенного графа
    smatch m;
    regex regexp_2{("\\,")};

public:
    int get_dimension()
    {
        return matrix_dimension;
    }
    void set_dimension(int dimension)
    {
        matrix_dimension = dimension;
    }
    ~Matrix()
    {
        for (int i = 0; i < matrix_dimension; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void functions(ifstream &stream)
    {
        matrix = new int *[matrix_dimension];
        for (int i = 0; i < matrix_dimension; i++)
        {
            matrix[i] = new int[matrix_dimension];
        }
        for (int i = 0; i < matrix_dimension; i++)
        {
            for (int j = 0; j < matrix_dimension; j++)
            {
                matrix[i][j] = 0;
            }
        }
        while (!stream.eof())
        {
            getline(stream, stroka_matrix);
            cout << stroka_matrix << endl;
            if (regex_search(stroka_matrix, regexp_2) == true)
            {
                flag_for_regex_search = 1;
            }
            if (flag_for_regex_search == 1)
            {
                while (regex_search(stroka_matrix, m, regexp))
                {
                    for (auto x : m)
                    {
                        int start = m.position();
                        for (int i = 0; i <= start; i++)
                        {
                            if (i == start)
                            {
                                int flag = 0;
                                if (x == ':')
                                {
                                    vertex_1 = stoi(dop_stroka_matrix);
                                    dop_stroka_matrix.clear();
                                }
                                if (x == ',')
                                {
                                    vertex_2 = stoi(dop_stroka_matrix);
                                    dop_stroka_matrix.clear();
                                }
                                if (x == ')')
                                {
                                    length = stoi(dop_stroka_matrix);
                                    dop_stroka_matrix.clear();
                                    flag = 1;
                                }
                                if (flag == 1)
                                {
                                    matrix[vertex_1][vertex_2] = length;
                                }
                                flag = 0;
                            }
                            else
                            {
                                dop_stroka_matrix += stroka_matrix[i];
                            }
                        }
                    }
                    stroka_matrix = m.suffix().str();
                }
            }
            else
            {
                while (regex_search(stroka_matrix, m, regexp))
                {
                    {
                        for (auto x : m)
                        {
                            int start = m.position();
                            for (int i = 0; i <= start; i++)
                            {
                                if (i == start)
                                {
                                    int flag = 0;
                                    if (x == ':')
                                    {
                                        vertex_1 = stoi(dop_stroka_matrix);
                                        dop_stroka_matrix.clear();
                                    }
                                    if (x == "->")
                                    {
                                        flag = 1;
                                        vertex_2 = stoi(dop_stroka_matrix);
                                        dop_stroka_matrix.clear();
                                    }
                                    if (flag == 1)
                                    {
                                        matrix[vertex_1][vertex_2] = 1;
                                    }
                                    flag = 0;
                                }
                                else
                                {
                                    dop_stroka_matrix += stroka_matrix[i];
                                }
                            }
                        }
                        stroka_matrix = m.suffix().str();
                    }
                }
            }
        }
        for (int i = 0; i < matrix_dimension; i++)
        {
            for (int j = 0; j < matrix_dimension; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    int weight_for_vertex(int first_vertex, int second_vertex)
    {
        return matrix[first_vertex][second_vertex];
    }
};
class List : public Base_class
{
private:
    List_realisation *list;
    int flag_for_regex_search = 0;
    int list_dimension;                         // размерность матрицы смежности
    int vertex_1;                               // вершина, из которой может идти пользователь
    string stroka_list;                         // переменная необходимая для считывания информации из файла
    string dop_stroka_list;                     // переменная необходимая для записи вершин в список
    int vertex_2;                               // вершина, в которую может попасть пользователь
    int length;                                 // расстояние между вершинами
    regex regexp{("\\:|\\(|\\)|\\,|\\->|\\s")}; // регулярное выражение для поиска номера вершины в строке для взвешенного графа
    smatch m;
    regex regexp_2{("\\,")};

public:
    int get_dimension()
    {
        return list_dimension;
    }
    void set_dimension(int dimension)
    {
        list_dimension = dimension;
    }
    void functions(ifstream &stream)
    {
        list = new List_realisation[list_dimension];
        while (!stream.eof())
        {
            getline(stream, stroka_list);
            if (regex_search(stroka_list, regexp_2) == true)
            {
                flag_for_regex_search = 1;
            }
            if (flag_for_regex_search == 1)
            {
                while (regex_search(stroka_list, m, regexp))
                {
                    for (auto x : m)
                    {
                        int start = m.position();
                        for (int i = 0; i <= start; i++)
                        {
                            if (i == start)
                            {
                                int flag = 0;
                                if (x == ':')
                                {
                                    vertex_1 = stoi(dop_stroka_list);
                                    dop_stroka_list.clear();
                                }
                                if (x == ',')
                                {
                                    vertex_2 = stoi(dop_stroka_list);
                                    dop_stroka_list.clear();
                                }
                                if (x == ')')
                                {
                                    length = stoi(dop_stroka_list);
                                    dop_stroka_list.clear();
                                    flag = 1;
                                }
                                if (flag == 1)
                                {
                                    list[vertex_1].push_back(vertex_2, length);
                                }
                                flag = 0;
                            }
                            else
                            {
                                dop_stroka_list += stroka_list[i];
                            }
                        }
                    }
                    stroka_list = m.suffix().str();
                }
            }
            else
            {
                while (regex_search(stroka_list, m, regexp))
                {
                    {
                        for (auto x : m)
                        {
                            int start = m.position();
                            for (int i = 0; i <= start; i++)
                            {
                                if (i == start)
                                {
                                    int flag = 0;
                                    if (x == ':')
                                    {
                                        vertex_1 = stoi(dop_stroka_list);
                                        dop_stroka_list.clear();
                                    }
                                    if (x == "->")
                                    {
                                        flag = 1;
                                        vertex_2 = stoi(dop_stroka_list);
                                        dop_stroka_list.clear();
                                    }
                                    if (flag == 1)
                                    {
                                        length = 1;
                                        list[vertex_1].push_back(vertex_2, length);
                                    }
                                    flag = 0;
                                }
                                else
                                {
                                    dop_stroka_list += stroka_list[i];
                                }
                            }
                        }
                        stroka_list = m.suffix().str();
                    }
                }
            }
        }
        for (int i = 0; i < list_dimension; i++)
        {
            cout << i << endl;
            list[i].print();
        }
    }
    int weight_for_vertex(int first_vertex, int second_vertex)
    {
        return list[first_vertex].weight_vertex_for_list_realisation(second_vertex);
    }
};
void destra_algorithm(int dimension, int start_vertex, int number_final_vertex, Base_class *base)
{
    vector<int> vec_help;               // вспомогательный вектор для вывода кратчайшего пути
    int count_of_visit_vertex = 0;      // Кол-во посещенных вершин
    int min_weight_vertex;              // номер вершины, облададающей минимальным весом
    int vertex_weight[dimension];       // вес вершины
    bool visit_vertex[dimension];       // посещение вершины
    for (int i = 0; i < dimension; i++) // всем вершинам, кроме стартовой присваивается большой вес (10000)
    {
        if (i == start_vertex)
        {
            vertex_weight[i] = 0;   // вес стартовой вершины равен 0
            visit_vertex[i] = true; // только стартовая  вершина выделена
            count_of_visit_vertex++;
        }
        else
        {
            vertex_weight[i] = 10000;
            visit_vertex[i] = false; // все вершины не выделены
        }
    }
    for (int i = 0; i < dimension; i++) // замена значений весов вершин, смежных со стартовой вершиной
    { 
        int weight_vertex_for_graph = base->weight_for_vertex(start_vertex, i);
        if (weight_vertex_for_graph != 0)
        {
            if ((visit_vertex[i] == false) && (vertex_weight[start_vertex] + weight_vertex_for_graph < vertex_weight[i]))
            {
                vertex_weight[i] = vertex_weight[start_vertex] + weight_vertex_for_graph;
            }
        }
    }
    while (count_of_visit_vertex != dimension)
    {
        int min = 10000;
        for (int i = 0; i < dimension; i++) // нахождение индекса вершины с минимальным весом 
        {
            if ((visit_vertex[i] == false) && (vertex_weight[i] < min))
            {
                min = vertex_weight[i];
                min_weight_vertex = i;
            }
        }
        for (int i = 0; i < dimension; i++) // замена значений весов вершин, смежных с вершиной, которая обладает минимальным весом
        {
            int weight_vertex_for_graph = base->weight_for_vertex(min_weight_vertex, i);
            if (weight_vertex_for_graph != 0)
            {
                if ((visit_vertex[i] == false) && (vertex_weight[min_weight_vertex] + weight_vertex_for_graph < vertex_weight[i]))
                {
                    vertex_weight[i] = vertex_weight[min_weight_vertex] + weight_vertex_for_graph;
                }
            }
        }
        visit_vertex[min_weight_vertex] = true; // вершина с минимальным весом обозначается пройденной 
        count_of_visit_vertex++; // кол- во пройденных вершин увеличивается
    }
    if (vertex_weight[number_final_vertex]==10000)
    {
        cout<<" НЕТ ПУТИ"<<endl;
        return;
    }
    else
    {
    cout << "vertex_weight ";
    cout << vertex_weight[number_final_vertex] << endl;
    } // вывод расстояния до финальной вершины
    for (int i = dimension - 1; i >= 0; i--) // вывод кратчайшего пути от стартовой до финальной вершины
    { // пробегаемся по вершинам в обратном порядке
        int weight_vertex_for_graph = base->weight_for_vertex(i, number_final_vertex);
        if (weight_vertex_for_graph != 0)
        {
            if (vertex_weight[number_final_vertex] - weight_vertex_for_graph == vertex_weight[i]) // если из разность веса финальной вершины и длины смежных в нее вершин равна весу смежной вершины, то вершина пуш бэк в вектор
            {
                vec_help.push_back(number_final_vertex);
                int number = i;
                vec_help.push_back(number);
                while (number != start_vertex)
                {
                    for (int i = dimension - 1; i >= 0; i--)
                    {
                        int weight_vertex_for_number = base->weight_for_vertex(i, number);
                        if (weight_vertex_for_number != 0)
                        {
                            if (vertex_weight[number] - weight_vertex_for_number == vertex_weight[i])
                            {
                                number = i;
                                vec_help.push_back(number);
                            }
                        }
                    }
                }
                reverse(vec_help.begin(), vec_help.end());
                for (unsigned int i = 0; i < vec_help.size(); i++)
                {
                    for (unsigned int i = 0; i < vec_help.size(); i++)
                    {
                        cout << vec_help[i];
                        if (i != vec_help.size() - 1)
                        {
                            cout << "->";
                        }
                    }
                    cout << endl;
                    vec_help.clear();
                }
            }
        }
    }
}
int main(int argc, char *argv[])
{
    Base_class *base;
    List lis;
    Matrix matr;
    int start_vertex;
    int number_final_vertex;
    string stroka_dimension; // строка, хранящая размерность матрицы смежности
    int dimension;
    string type;
    string file_name;
    ifstream stream;
    if (argc == 2)
    {
        file_name = argv[1];
    }
    else
    {
        cout << "Введите имя файла" << endl;
        cin >> file_name;
    }
    cout << "Введите с какой вершины посчитать путь " << endl;
    cin >> start_vertex;
    cout << "Введите до какой вершины посчитать путь" << endl;
    cin >> number_final_vertex;
    stream.open(file_name);
    if (stream.is_open())
    {
        getline(stream, type);
        getline(stream, stroka_dimension);
        dimension = stoi(stroka_dimension);
        if (start_vertex <0 || number_final_vertex<0||number_final_vertex>=dimension)
        {
            cout <<"uncorrect"<<endl;
            return 1; 
        }
        if (type == "matrix")
        {
            matr.set_dimension(dimension);
            matr.functions(stream);
            base = &matr;
        }
        else
        {
            lis.set_dimension(dimension);
            lis.functions(stream);
            base = &lis;
        }
        destra_algorithm(dimension, start_vertex, number_final_vertex, base);
    }
    return 0;
}