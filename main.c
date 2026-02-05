#include "contact.h"

int main()
{
    int choice;
    AddressBook s1;
    
    load_contact(&s1);
    if (s1.contactCount == 0) {
        populate_contact(&s1);
    }

    do {
        printf("\n1. Create contact\n");
        printf("2. Edit contact\n");
        printf("3. Search contact\n");
        printf("4. Delete contact\n");
        printf("5. List contact\n");
        printf("6. Save and Exit\n");
        printf("Enter your choice (between 1 and 6): \n");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Create contact is selected\n");
                createContact(&s1);
                break;
            case 2:
                printf("Edit contact is selected\n");
                editContact(&s1); 
                break;
            case 3:
                printf("Search contact is selected\n");
                searchContact(&s1);
                break;
            case 4:
                printf("Delete contact is selected\n");
                deleteContact(&s1); 
                break;
            case 5:
                printf("List contact is selected\n");
                listContact(&s1);
                break;
            case 6:
                printf("Save and Exit is selected\n");
                saveContact(&s1);
                break;
            default:
                printf("Invalid choice, enter number between 1 to 6\n");
        }
    } while (choice != 6);

    return 0;
}
