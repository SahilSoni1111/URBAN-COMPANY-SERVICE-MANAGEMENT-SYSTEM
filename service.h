#ifndef SERVICE_H
#define SERVICE_H
#include "common.h"
typedef struct SERVICE_NODE{
    int serviceId;
    char serviceName[NAME_SIZE];
    float basePrice;

    struct SERVICE_NODE*next;
} ServiceNode;

ServiceNode* CreateService(int, const char*, float);
ServiceNode* InputServices(ServiceNode* head, ServiceNode* Snode);
ServiceNode* Insertservice(ServiceNode*, ServiceNode*);
void DisplayService(ServiceNode*);
ServiceNode* RegisterService(ServiceNode*head);
#endif