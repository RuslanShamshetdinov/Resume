/* Motorboat */

#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

struct Motorboat
{
    char *name;               /* the name of the motorboat */
    unsigned int speed;       /* the speed of the motorboat(km per hour) */
    unsigned int movement;    /* the movement of the motorboat (0-start moving, 1-moving forward, 2 - moving back, 3 - moving right, 4 - moving left, 5 - stop moving) */
    unsigned int time;        /*motorboat travel time (hour) */
    int additional_equipment; /* active component mark */
    union {
        char name_equipment[256];  /* mark =0 */
        int radio_range;           /* mark =1 */
        bool navigation_equipment; /* mark =2 */
    };
};

/* initialization of the motorboat */
void init(Motorboat *motorboat,
          char *name = "Yamaha 12X",
          unsigned int speed = 120,
          unsigned int movement = 1,
          unsigned int time = 2,
          int additional_equipment = 0)

{
    motorboat->name = name;
    motorboat->speed = speed;
    motorboat->movement = movement;
    motorboat->time = time;
    motorboat->additional_equipment = additional_equipment;
    switch (additional_equipment)
    {
    case 0:
        strcpy(motorboat->name_equipment, "sounder");
        break;
    case 1:
        motorboat->radio_range = 400;
        break;
    case 2:
        motorboat->navigation_equipment = true;
        break;
    default:
        motorboat->additional_equipment = 0;
        strcpy(motorboat->name_equipment, "sounder");
        break;
    }
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
    printf("The additional equipment includes:\n");
    switch (motorboat->additional_equipment)
    {
    case 0:
        printf("%s\n", motorboat->name_equipment);
        break;
    case 1:
        printf("- radio communication\n");
        printf("the radio communication range = %d\n", motorboat->radio_range);
        break;
    case 2:
        printf("- navigation equipment\n");
        break;
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
    init(&UsualMotorboat, "Yamaha 12Y", 60, 2, 4, 1);
    view(&UsualMotorboat);
    moving(&UsualMotorboat);

    init(&UsualMotorboat, "Yamaha 12Z", 60, 3, 4, 2);
    printf("%c", '\n');
    view(&UsualMotorboat);
    moving(&UsualMotorboat);
    return 0;
}