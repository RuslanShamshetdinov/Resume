/* Motorboat */

#include <cstdio>
#include <iostream>
using namespace std;

struct Motorboat
{
    char *name;            /* the name of the motorboat */
    unsigned int speed;    /* the speed of the motorboat(km per hour) */
    unsigned int movement; /* the movement of the motorboat (0-start moving, 1-moving forward, 2 - moving back, 3 - moving right, 4 - moving left, 5 - stop moving) */
    unsigned int time;     /*motorboat travel time (hour) */
};

/* initialization of the motorboat */
void init(Motorboat *motorboat,
          char *name = "Yamaha 12X",
          unsigned int speed = 60,
          unsigned int movement = 0,
          unsigned int time = 3)

{
    motorboat->name = name;
    motorboat->speed = speed;
    motorboat->movement = movement;
    motorboat->time = time;
}

/* visualization of the motorboat */
void view(Motorboat *motorboat)
{
    printf("the motorboat name = %s \n", motorboat->name);
    printf("the motorboat speed = %d (km per hour)\n", motorboat->speed);
    printf("the motorboat travel time = %d (hour)\n", motorboat->time);
    if (motorboat->movement > 5)
    {
        printf("The motorboat cant be moving\n");
    }
    else
    {
        printf("The motorboat can be moving\n");
    }
}

/* options of motorboat traffic */
void moving(Motorboat *motorboat)
{
    switch (motorboat->movement)
    {
    case 0:
        printf("motorboat start moving\n");
        break;
    case 1:
        printf("motorboat moving forward\n");
        break;
    case 2:
        printf("motorboat moving back\n");
        break;
    case 3:
        printf("motorboat moving right\n");
        break;
    case 4:
        printf("motorboat moving left\n");
        break;
    case 5:
        printf("motorboat stop moving\n");
        break;
    }
}

int main()
{
    Motorboat SportMotorboat;
    init(&SportMotorboat);
    view(&SportMotorboat);
    moving(&SportMotorboat);
    printf("%c", '\n');

    Motorboat UsualMotorboat;
    init(&UsualMotorboat, "Yamaha 12Y", 90, 10, 5);
    view(&UsualMotorboat);
    moving(&UsualMotorboat);
    return 0;
}