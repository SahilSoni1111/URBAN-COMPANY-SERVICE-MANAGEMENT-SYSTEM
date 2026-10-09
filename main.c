#include <stdio.h>
#include "common.h"
#include "customer.h"
#include "service.h"
#include "professional.h"
#include "request.h"
void FreeAllLists(CustomerNode*Chead,ServiceNode*Shead,ProfessionalNode*Phead,RequestNode*Rhead){
    CustomerNode*Ctemp=NULL;
    ServiceNode*Stemp=NULL;
    ProfessionalNode*Ptemp=NULL;
    RequestNode*Rtemp=NULL;

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

    printf("All linked lists freed successfully.\n");
    printf("----------------------------------------\n");
}
void LoadTestData(CustomerNode**Chead,ServiceNode**Shead,ProfessionalNode**Phead){
    CustomerNode*Cnode=NULL;
    ServiceNode*Snode=NULL;
    ProfessionalNode*Pnode=NULL;

    Snode=CreateService(101,"Home Cleaning",800);
    *Shead=InsertService(*Shead,Snode);

    Snode=CreateService(102,"Plumbing",500);
    *Shead=InsertService(*Shead,Snode);

    Snode=CreateService(103,"Electrical Repair",600);
    *Shead=InsertService(*Shead,Snode);

    Snode=CreateService(104,"AC Servicing",1200);
    *Shead=InsertService(*Shead,Snode);

    Snode=CreateService(105,"Appliance Repair",900);
    *Shead=InsertService(*Shead,Snode);


    Cnode=CreateCustomer(301,"Karan Mehta",440001,"9876500001");
    *Chead=InsertCustomer(*Chead,Cnode);

    Cnode=CreateCustomer(302,"Neha Joshi",440002,"9876500002");
    *Chead=InsertCustomer(*Chead,Cnode);

    Cnode=CreateCustomer(303,"Rohan Gupta",440003,"9876500003");
    *Chead=InsertCustomer(*Chead,Cnode);


    Pnode=CreateProfessional(201,"Rahul Sharma",440001,"9876543210");
    AddServicetoProfessional(Pnode,FindService(*Shead,101));
    AddServicetoProfessional(Pnode,FindService(*Shead,102));
    AddServicetoProfessional(Pnode,FindService(*Shead,103));
    *Phead=InsertProfessional(*Phead,Pnode);

    Pnode=CreateProfessional(202,"Amit Verma",440002,"9876543211");
    AddServicetoProfessional(Pnode,FindService(*Shead,102));
    AddServicetoProfessional(Pnode,FindService(*Shead,104));
    AddServicetoProfessional(Pnode,FindService(*Shead,105));
    *Phead=InsertProfessional(*Phead,Pnode);

    Pnode=CreateProfessional(203,"Priya Patel",440001,"9876543212");
    AddServicetoProfessional(Pnode,FindService(*Shead,101));
    AddServicetoProfessional(Pnode,FindService(*Shead,103));
    AddServicetoProfessional(Pnode,FindService(*Shead,104));
    *Phead=InsertProfessional(*Phead,Pnode);

    printf("Test data loaded successfully.\n");
}
int main(){
    int choice;
    int subchoice;

    CustomerNode*Chead=NULL;
    ServiceNode*Shead=NULL;
    ProfessionalNode*Phead=NULL;
    RequestNode*Rhead=NULL;

    LoadTestData(&Chead,&Shead,&Phead);

    printf("\n");
    printf("============================================\n");
    printf("       URBAN COMPANY SERVICE SYSTEM\n");
    printf("============================================\n");
    printf("Welcome to Urban Company Service Management\n");
    printf("============================================\n");

    do{
        printf("\n============================================\n");
        printf("                 MAIN MENU\n");
        printf("============================================\n");
        printf("1. Customer Mode\n");
        printf("2. Professional Mode\n");
        printf("3. Admin Mode\n");
        printf("0. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        printf("--------------------------------------------\n");

        switch(choice){

            case 1:
                do{
                    printf("\n============================================\n");
                    printf("               CUSTOMER MODE\n");
                    printf("============================================\n");
                    printf("1. Register Customer\n");
                    printf("2. Create Service Request\n");
                    printf("3. Cancel Service Request\n");
                    printf("4. View Customer Requests\n");
                    printf("0. Back to Main Menu\n");
                    printf("--------------------------------------------\n");
                    printf("Enter your choice: ");
                    scanf("%d",&subchoice);
                    printf("--------------------------------------------\n");

                    switch(subchoice){

                        case 1:
                            Chead=RegisterCustomer(Chead);
                            printf("--------------------------------------------\n");
                            break;

                        case 2:
                            Rhead=CreateServiceRequest(Rhead,Phead,Shead,Chead);
                            printf("--------------------------------------------\n");
                            break;

                        case 3:
                            Rhead=CancelRequest(Rhead,Chead);
                            printf("--------------------------------------------\n");
                            break;

                        case 4:
                            FindRequestsByCustomer(Rhead,Chead);
                            printf("--------------------------------------------\n");
                            break;

                        case 0:
                            printf("Returning to Main Menu...\n");
                            printf("============================================\n");
                            break;

                        default:
                            printf("Invalid choice. Try again.\n");
                            printf("--------------------------------------------\n");
                    }

                }while(subchoice!=0);

                break;

            case 2:
                do{
                    printf("\n============================================\n");
                    printf("             PROFESSIONAL MODE\n");
                    printf("============================================\n");
                    printf("1. View Services Offered\n");
                    printf("2. Complete Service Request\n");
                    printf("3. View Service History\n");
                    printf("0. Back to Main Menu\n");
                    printf("--------------------------------------------\n");
                    printf("Enter your choice: ");
                    scanf("%d",&subchoice);
                    printf("--------------------------------------------\n");

                    switch(subchoice){

                        case 1:
                            FindServicesByProfessional(Phead);
                            printf("--------------------------------------------\n");
                            break;

                        case 2:
                            Rhead=CompleteRequest(Rhead,Phead);
                            printf("--------------------------------------------\n");
                            break;

                        case 3:
                            DisplayServiceHistory(Rhead,Phead);
                            printf("--------------------------------------------\n");
                            break;

                        case 0:
                            printf("Returning to Main Menu...\n");
                            printf("============================================\n");
                            break;

                        default:
                            printf("Invalid choice. Try again.\n");
                            printf("--------------------------------------------\n");
                    }

                }while(subchoice!=0);

                break;

            case 3:
                do{
                    printf("\n============================================\n");
                    printf("                 ADMIN MODE\n");
                    printf("============================================\n");
                    printf("1. Add Service\n");
                    printf("2. Register Customer\n");
                    printf("3. Register Professional\n");
                    printf("4. Display All Services\n");
                    printf("5. Find Professionals by Service\n");
                    printf("6. Find Services by Professional\n");
                    printf("7. Find Requests by Customer\n");
                    printf("8. Display Pending Requests\n");
                    printf("9. Display Service History\n");
                    printf("0. Back to Main Menu\n");
                    printf("--------------------------------------------\n");
                    printf("Enter your choice: ");
                    scanf("%d",&subchoice);
                    printf("--------------------------------------------\n");

                    switch(subchoice){

                        case 1:
                            Shead=InputService(Shead);
                            printf("--------------------------------------------\n");
                            break;

                        case 2:
                            Chead=RegisterCustomer(Chead);
                            printf("--------------------------------------------\n");
                            break;

                        case 3:
                            Phead=RegisterProfessional(Phead,Shead);
                            printf("--------------------------------------------\n");
                            break;

                        case 4:
                            DisplayService(Shead);
                            printf("--------------------------------------------\n");
                            break;

                        case 5:
                            FindProfessionalsByService(Phead,Shead);
                            printf("--------------------------------------------\n");
                            break;

                        case 6:
                            FindServicesByProfessional(Phead);
                            printf("--------------------------------------------\n");
                            break;

                        case 7:
                            FindRequestsByCustomer(Rhead,Chead);
                            printf("--------------------------------------------\n");
                            break;

                        case 8:
                            DisplayPendingRequests(Rhead);
                            printf("--------------------------------------------\n");
                            break;

                        case 9:
                            DisplayServiceHistory(Rhead,Phead);
                            printf("--------------------------------------------\n");
                            break;

                        case 0:
                            printf("Returning to Main Menu...\n");
                            printf("============================================\n");
                            break;

                        default:
                            printf("Invalid choice. Try again.\n");
                            printf("--------------------------------------------\n");
                    }

                }while(subchoice!=0);

                break;

            case 0:
                printf("\n============================================\n");
                printf("Thank you for using Urban Company!\n");
                printf("Exiting the application...\n");
                printf("============================================\n");
                break;

            default:
                printf("Invalid choice. Please select again.\n");
                printf("--------------------------------------------\n");
        }

    }while(choice!=0);
    FreeAllLists(Chead,Shead,Phead,Rhead);
    return 0;
}
