#ifndef REQUEST_H
#define REQUEST_H
#include "common.h"
#include "customer.h"
#include "service.h"
#include "professional.h"
typedef struct REQUEST_NODE{
    int requestId;
    CustomerNode*customer;
    ServiceNode*service;
    ProfessionalNode*professional;
    char date[DATE_SIZE];
    char time[TIME_SIZE];
    RequestStatus Rstatus;
    struct REQUEST_NODE*next;
}RequestNode;

RequestNode* CreateRequest(int,CustomerNode*,ServiceNode*,const char*,const char*);
RequestNode* InsertRequest(RequestNode*,RequestNode*);
RequestNode* FindRequest(RequestNode*,int);
#endif