#ifndef SERVICE_H
#define SERVICE_H
#include "common.h"
typedef struct ServiceNode{
    int serviceId;
    char serviceName[NAME_SIZE];
    float basePrice;

    struct ServiceNode*next;
} ServiceNode;

#endif