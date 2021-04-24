/* Motorboat */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Motorboat
{
    string name;        /* the name of the motorboat */
    unsigned int speed;    /* the speed of the motorboat(km per hour) */
    unsigned int movement; /* the movement of the motorboat (0-start moving, 1-moving forward, 2 - moving back, 3 - moving right, 4 - moving left, 5 - stop moving) */
    unsigned int time;     /* motorboat travel time (hour) */
    ifstream stream;       /* input file stream */

public:
    /* default constructor */
    Motorboat(const string file_name = "SportMotorboat.txt")
    {
        stream.open(file_name);
        if (stream.is_open())
        {
            getline(stream,name);
            stream >> speed;
            stream >> movement;
            stream >> time;
        }
        else
        {
            /* data member default initialization */
            name = "Yamaha 12Z";
            speed = 60;
            movement = 0;
            time = 3;
        }
    }
    /* copy constructor */
    Motorboat(const Motorboat &motorboat) : name(motorboat.name),
                                            speed(motorboat.speed),
                                            movement(motorboat.movement),
                                            time(motorboat.time)
    {
    }
    /* destructor */
    ~Motorboat()
    {
        if (stream.is_open())
            stream.close();
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
    stream << "the motorboat name = " << motorboat.name << "\n";
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
    Motorboat UsualMotorboat("UsualMotorboat.txt");
    cout << UsualMotorboat;
    UsualMotorboat.moving();
    return 0;
}