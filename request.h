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

RequestNode* CreateRequest(int,CustomerNode*,ServiceNode*,ProfessionalNode*,const char*,const char*);
RequestNode* InsertRequest(RequestNode*,RequestNode*);
RequestNode* FindRequest(RequestNode*,int);
RequestNode* AssignPendingRequest(RequestNode*,ProfessionalNode*);
RequestNode* CreateServiceRequest(RequestNode*, ProfessionalNode*, ServiceNode*, CustomerNode*);
RequestNode* CompleteRequest(RequestNode*, ProfessionalNode*);
RequestNode* CancelRequest(RequestNode*,CustomerNode*);
void FindRequestsByCustomer(RequestNode*Rhead,CustomerNode*Chead);
void DisplayPendingRequests(RequestNode*Rhead);
void DisplayServiceHistory(RequestNode*Rhead,ProfessionalNode*Phead);
#endif