#ifndef COMMON_H
#define COMMON_H
#define NAME_SIZE 50
#define PHONE_SIZE 15
#define MAX_SERVICES 5
#define DATE_SIZE 10
#define TIME_SIZE 10 
typedef enum{
    FALSE,
    TRUE
}Bool;
typedef enum{
    UNAVAILABLE,
    AVAILABLE
}Availability;
typedef enum{
    PENDING,
    ASSIGNED,
    COMPLETED,
    CANCELLED
}Request_status;
#endif