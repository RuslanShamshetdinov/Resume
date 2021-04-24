/* Motorboat */
#include <iostream>
#include <string>
using namespace std;
class Motorboat
{
    unsigned int movement; /* the movement of the motorboat (0-start moving, 1-moving forward, 2 - moving back, 3 - moving right, 4 - moving left, 5 - stop moving) */
    unsigned int speed;    /* the speed of the motorboat(km per hour) */
    unsigned int time;     /* motorboat travel time (hour) */
    int count_of_name;
    string *name; /* the name of the motorboat */
public:
    /* default constructor */
    Motorboat(unsigned int movement = 1,
              unsigned int speed = 120,
              unsigned int time = 2,
              int count_of_name = 2,
              string name_1 = "Yamaha 12X",
              string name_2 = "Yamaha 12Y") : movement(movement),
                                              speed(speed),
                                              time(time),
                                              count_of_name(count_of_name)
    {
        name = new string[count_of_name];
        switch (count_of_name)
        {
        case 1:
        {
            name[0] = name_1;
            break;
        }
        case 2:
        {
            name[0] = name_1;
            name[1] = name_2;
            break;
        }
        }
    }
    /*copy constructor */
    Motorboat(const Motorboat &motorboat) : movement(motorboat.movement),
                                            speed(motorboat.speed),
                                            time(motorboat.time),
                                            count_of_name(motorboat.count_of_name)

    {
        name = new string[motorboat.count_of_name];
        switch (motorboat.count_of_name)
        {
        case 1:
        {
            name[0] = motorboat.name[0];
            break;
        }
        case 2:
        {
            name[0] = motorboat.name[0];
            name[1] = motorboat.name[1];
            break;
        }
        }
    }
    /* destructor */
    ~Motorboat()
    {
        delete[] name;
    }
    /* options of the motorboat traffic */
    void moving();
    /* visualization of the motorboat */
    friend ostream &operator<<(ostream &, Motorboat);
};
void Motorboat::moving()
{
    switch (movement)
    {
    case 0:
        cout << "motorboat start moving" << endl;
        break;
    case 1:
        cout << "motorboat moving forward" << endl;
        break;
    case 2:
        cout << "motorboat moving back" << endl;
        break;
    case 3:
        cout << "motorboat moving right" << endl;
        break;
    case 4:
        cout << "motorboat moving left" << endl;
        break;
    case 5:
        cout << "motorboat stop moving" << endl;
        break;
    }
}
/* visualization of the motorboat */
ostream &operator<<(ostream &stream, Motorboat motorboat)
{
    switch (motorboat.count_of_name)
    {
    case 1:
        stream << "the motorboat name = " << motorboat.name[0] << "\n";
        break;
    case 2:
        stream << "the motorboat name = " << motorboat.name[0] << " and " << motorboat.name[1] << "\n";
        break;
    }
    stream << "the motorboat speed = " << motorboat.speed << " (km per hour)\n";
    stream << "the motorboat travel time = " << motorboat.time << " (hour)\n";
    if (motorboat.movement > 5)
    {
        stream << "The motorboat cant be moving\n";
    }
    else
    {
        stream << "The motorboat can be moving\n";
    }
    return stream;
}
int main()
{
    Motorboat SportMotorboat;
    cout << SportMotorboat;
    SportMotorboat.moving();
    cout << endl;

    Motorboat UsualMotorboat_1(2, 60, 4, 1, "Yamaha 12Z");
    cout << UsualMotorboat_1;
    UsualMotorboat_1.moving();
    cout << endl;

    Motorboat UsualMotorboat_2(UsualMotorboat_1);
    cout << UsualMotorboat_2;
    UsualMotorboat_2.moving();
    cout << endl;
    return 0;
}
