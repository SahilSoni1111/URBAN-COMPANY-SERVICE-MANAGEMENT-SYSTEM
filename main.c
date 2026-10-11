#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "customer.h"
#include "service.h"
#include "professional.h"
#include "request.h"

void FreeAllLists(CustomerNode *Chead, ServiceNode *Shead,
                  ProfessionalNode *Phead, RequestNode *Rhead){
    RequestNode *Rtemp=NULL;
    CustomerNode *Ctemp=NULL;
    ServiceNode *Stemp=NULL;
    ProfessionalNode *Ptemp=NULL;

    while(Rhead!=NULL){
        Rtemp=Rhead;
        Rhead=Rhead->next;
        free(Rtemp);
    }

    while(Chead!=NULL){
        Ctemp=Chead;
        Chead=Chead->next;
        free(Ctemp);
    }

    while(Shead!=NULL){
        Stemp=Shead;
        Shead=Shead->next;
        free(Stemp);
    }

    while(Phead!=NULL){
        Ptemp=Phead;
        Phead=Phead->next;
        free(Ptemp);
    }

    printf("All lists freed successfully.\n");
}

void LoadTestData(CustomerNode **Chead, ServiceNode **Shead,
                  ProfessionalNode **Phead){
    ServiceNode *Snode=NULL;
    CustomerNode *Cnode=NULL;
    ProfessionalNode *Pnode=NULL;

    Snode=CreateService(101,"Plumbing",500.0);
    *Shead=InsertService(*Shead,Snode);

    Snode=CreateService(102,"Electrical Repair",400.0);
    *Shead=InsertService(*Shead,Snode);

    Snode=CreateService(103,"Cleaning",300.0);
    *Shead=InsertService(*Shead,Snode);

    Snode=CreateService(104,"Painting",1000.0);
    *Shead=InsertService(*Shead,Snode);

    Snode=CreateService(105,"Carpentry",600.0);
    *Shead=InsertService(*Shead,Snode);

    Cnode=CreateCustomer(301,"Rahul",440001,"9876543210");
    *Chead=InsertCustomer(*Chead,Cnode);

    Cnode=CreateCustomer(302,"Amit",440002,"9876543211");
    *Chead=InsertCustomer(*Chead,Cnode);

    Cnode=CreateCustomer(303,"Priya",440001,"9876543212");
    *Chead=InsertCustomer(*Chead,Cnode);

    Pnode=CreateProfessional(201,"Ramesh",440001,"9876500001");
    if(Pnode!=NULL){
        AddServicetoProfessional(Pnode,FindService(*Shead,101));
        AddServicetoProfessional(Pnode,FindService(*Shead,102));
        *Phead=InsertProfessional(*Phead,Pnode);
    }

    Pnode=CreateProfessional(202,"Suresh",440002,"9876500002");
    if(Pnode!=NULL){
        AddServicetoProfessional(Pnode,FindService(*Shead,103));
        AddServicetoProfessional(Pnode,FindService(*Shead,104));
        *Phead=InsertProfessional(*Phead,Pnode);
    }

    Pnode=CreateProfessional(203,"Mahesh",440003,"9876500003");
    if(Pnode!=NULL){
        AddServicetoProfessional(Pnode,FindService(*Shead,101));
        AddServicetoProfessional(Pnode,FindService(*Shead,105));
        *Phead=InsertProfessional(*Phead,Pnode);
    }

    printf("Test data loaded successfully.\n");
}

int main(void){
    CustomerNode *Chead=NULL;
    ServiceNode *Shead=NULL;
    ProfessionalNode *Phead=NULL;
    RequestNode *Rhead=NULL;

    int choice=0;
    int subChoice=0;

    LoadTestData(&Chead,&Shead,&Phead);

    while(choice!=4){
        printf("\n====================================\n");
        printf(" URBAN COMPANY SERVICE MANAGEMENT\n");
        printf("====================================\n");
        printf("1. Customer Mode\n");
        printf("2. Professional Mode\n");
        printf("3. Admin Mode\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                subChoice=-1;
                while(subChoice!=0){
                    printf("\n----------- CUSTOMER MENU -----------\n");
                    printf("1. Register Customer\n");
                    printf("2. Create Service Request\n");
                    printf("3. Cancel Service Request\n");
                    printf("4. View Customer Requests\n");
                    printf("0. Back\n");
                    printf("Enter your choice: ");
                    scanf("%d",&subChoice);

                    switch(subChoice){
                        case 1:
                            Chead=RegisterCustomer(Chead);
                            break;

                        case 2:
                            Rhead=CreateServiceRequest(Rhead,Phead,Shead,Chead);
                            break;

                        case 3:
                            Rhead=CancelRequest(Rhead,Phead,Chead);
                            break;

                        case 4:
                            FindRequestsByCustomer(Rhead,Chead);
                            break;

                        case 0:
                            break;

                        default:
                            printf("Invalid choice.\n");
                    }
                }
                break;

            case 2:
                subChoice=-1;
                while(subChoice!=0){
                    printf("\n--------- PROFESSIONAL MENU ---------\n");
                    printf("1. View Services Offered\n");
                    printf("2. Complete Service Request\n");
                    printf("3. View Service History\n");
                    printf("0. Back\n");
                    printf("Enter your choice: ");
                    scanf("%d",&subChoice);

                    switch(subChoice){
                        case 1:
                            FindServicesByProfessional(Phead);
                            break;

                        case 2:
                            Rhead=CompleteRequest(Rhead,Phead);
                            break;

                        case 3:
                            DisplayServiceHistory(Rhead,Phead);
                            break;

                        case 0:
                            break;

                        default:
                            printf("Invalid choice.\n");
                    }
                }
                break;
            case 3:
                subChoice=-1;
                while(subChoice!=0){
                    printf("\n------------- ADMIN MENU ------------\n");
                    printf("1. Add Service\n");
                    printf("2. Register Customer\n");
                    printf("3. Register Professional\n");
                    printf("4. Display All Services\n");
                    printf("5. Display All Professionals\n");
                    printf("6. Find Professionals by Service\n");
                    printf("7. Find Services by Professional\n");
                    printf("8. Find Requests by Customer\n");
                    printf("9. Display Pending Requests\n");
                    printf("10. Display Service History\n");
                    printf("11. Service Demand Report\n");
                    printf("12. Professional Activity Report\n");
                    printf("0. Back\n");
                    printf("Enter your choice: ");
                    scanf("%d",&subChoice);

                    switch(subChoice){
                        case 1:
                            Shead=InputService(Shead);
                            break;

                        case 2:
                            Chead=RegisterCustomer(Chead);
                            break;

                        case 3:
                            Phead=RegisterProfessional(Phead,Shead);
                            break;

                        case 4:
                            DisplayService(Shead);
                            break;

                        case 5:
                            DisplayProfessionals(Phead);
                            break;

                        case 6:
                            FindProfessionalsByService(Phead,Shead);
                            break;

                        case 7:
                            FindServicesByProfessional(Phead);
                            break;

                        case 8:
                            FindRequestsByCustomer(Rhead,Chead);
                            break;

                        case 9:
                            DisplayPendingRequests(Rhead);
                            break;

                        case 10:
                            DisplayServiceHistory(Rhead,Phead);
                            break;

                        case 11:
                            ServiceDemandReport(Shead,Rhead);
                            break;

                        case 12:
                            ProfessionalActivityReport(Phead,Rhead);
                            break;

                        case 0:
                            break;

                        default:
                            printf("Invalid choice.\n");
                    }
                }
                break;

            case 4:
                printf("Exiting the program.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    }

    FreeAllLists(Chead,Shead,Phead,Rhead);

    return 0;
}