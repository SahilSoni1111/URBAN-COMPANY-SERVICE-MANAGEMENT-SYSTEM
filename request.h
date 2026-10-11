#ifndef REQUEST_H
#define REQUEST_H
#define MAX_REPORT_ITEMS 1000
#include "common.h"
#include "customer.h"
#include "service.h"
#include "professional.h"
typedef struct PROFESSIONAL_COUNT{
    ProfessionalNode *professional;
    int count;
}ProfessionalCount;
typedef struct SERVICE_COUNT{
    ServiceNode *service;
    int count;
}ServiceCount;
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
RequestNode* CancelRequest(RequestNode*Rhead,ProfessionalNode*Phead,CustomerNode*Chead);
void FindRequestsByCustomer(RequestNode*Rhead,CustomerNode*Chead);
void DisplayPendingRequests(RequestNode*Rhead);
void DisplayServiceHistory(RequestNode*Rhead,ProfessionalNode*Phead);
void MergeServiceCount(ServiceCount[],int,int,int);
void MergeSortServiceCount(ServiceCount[],int,int);
void MergeProfessionalCount(ProfessionalCount[],int,int,int);
void MergeSortProfessionalCount(ProfessionalCount[],int,int);
void ServiceDemandReport(ServiceNode*,RequestNode*);
void ProfessionalActivityReport(ProfessionalNode*,RequestNode*);
#endif