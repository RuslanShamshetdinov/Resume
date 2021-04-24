#include <iostream>
#include <string>
using namespace std;
/* Base class */
class Water_transport
{
protected:
    unsigned int tonnage;
    unsigned int passengers_capacity;
    /* default constructor */
    Water_transport(unsigned int tonnage = 530) : tonnage(tonnage)

    {
        passengers_capacity = tonnage / 100;
    }
    /* copy constructor */
    Water_transport(const Water_transport &water_transport) : tonnage(water_transport.tonnage),
                                                              passengers_capacity(water_transport.passengers_capacity)
    {
    }
    /* destructor */
    virtual ~Water_transport()
    {
    }
};
/* Derived Class */
class Motorboat : public Water_transport
{
    string name;           /* the name of the motorboat */
    unsigned int speed;    /* the speed of the motorboat(km per hour) */
    unsigned int movement; /* the movement of the motorboat (0-start moving, 1-moving forward, 2 - moving back, 3 - moving right, 4 - moving left, 5 - stop moving) */
    unsigned int time;     /* motorboat travel time (hour) */

public:
    /* default constructor */
    Motorboat(unsigned int tonnage = 530,
              string name = "Yamaha 12X",
              unsigned int speed = 120,
              unsigned int movement = 1,
              unsigned int time = 2) : Water_transport(tonnage),
                                       name(name),
                                       speed(speed),
                                       movement(movement),
                                       time(time)
    {
    }
    /* copy constructor */
    Motorboat(const Motorboat &motorboat) : name(motorboat.name),
                                            speed(motorboat.speed),
                                            movement(motorboat.movement),
                                            time(motorboat.time)
    {
        this->tonnage=motorboat.tonnage;
        this->passengers_capacity=motorboat.passengers_capacity;
    }
    /* destructor */
    ~Motorboat()
    {
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
    stream << "the tonnage of the motorboat = " << motorboat.tonnage << " kg\n";
    stream << "the passengers capasity of the motorboat = " << motorboat.passengers_capacity << "\n";
    stream << "the motorboat name = " << motorboat.name << "\n";
    stream << "the motorboat speed = " << motorboat.speed << " (km per hour)\n";
    stream << "the motorboat travel time = " << motorboat.time << " (hour)\n";
    if (motorboat.movement > 5)
    {
        stream << "the motorboat cant be moving\n";
    }
    else
    {
        stream << "the motorboat can be moving\n";
    }
    return stream;
}
int main()
{
    Motorboat SportMotorboat;
    cout << SportMotorboat;
    SportMotorboat.moving();
    cout << endl;

    Motorboat UsualMotorboat_1(475,"Yamaha 12Y", 60, 2, 4);
    cout << UsualMotorboat_1;
    UsualMotorboat_1.moving();
    cout << endl;
    return 0;
}