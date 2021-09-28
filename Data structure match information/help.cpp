#include "help.h"
using namespace std;
void help::showmenu()
{
    cout << "Футбольное расписание" << endl;
    cout << "1. Добавить матч" << endl;
    cout << "2. Посмотреть расписание матчей" << endl;
    cout << "3. Найти матч по командам" << endl;
    cout << "4. Найти матч по времени" << endl;
    cout << "5. Найти матч по дате" << endl;
    cout << "6. Удалить матч" << endl;
    cout << "7. Выход" << endl;
    cout << ">";
}
bool help::isvalid(int ch)
{
    if ((ch < 1) || (ch > MAX_MENU_NUMBER))
    {
        cout << "Неверное значение" << endl;
        cout << "Введите еще раз" << endl;
        return false;
    }
    else
        return true;
}
