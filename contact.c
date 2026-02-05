#include "contact.h"
#include <string.h>

void listContact(AddressBook *addressBook) {
    printf("----------------------------------------------------------\n");
    printf("              ENTERED INTO List CONTACT\n");
    printf("----------------------------------------------------------\n");
    printf("\n");
    printf("---------------------------------------------------------\n");
    printf("Name\t\tPhone\t\tEmail\n");
    printf("---------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++){
        printf("%s\t%s\t%s\n", addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
    }
}

void createContact(AddressBook *addressBook) {

    printf("----------------------------------------------------------\n");
    printf("              ENTERED INTO CREATE CONTACT\n");
    printf("----------------------------------------------------------\n");
    printf("\n");
    
    if(addressBook->contactCount >= MAX_CONTACTS){
        printf("Address book is full!\n");
        return;
    }
    printf("Enter Name:\n");
    scanf("%[^\n]", addressBook->contacts[addressBook->contactCount].name);

    int unique;
    do {
        unique = 1;
        printf("Enter Phone Number:\n");
        scanf("%s", addressBook->contacts[addressBook->contactCount].phone);

        if (strlen(addressBook->contacts[addressBook->contactCount].phone) != 10) {
            printf("Invalid phone number! Must be 10 digits.\n");
            unique = 0;
            continue;
        }

        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].phone,
                       addressBook->contacts[addressBook->contactCount].phone) == 0) {
                printf("This phone number already exists! Please enter a different one.\n");
                unique = 0;
                break;
            }
        }
    } while (!unique);

    do {
        unique = 1;
        printf("Enter Email:\n");
        scanf("%s", addressBook->contacts[addressBook->contactCount].email);

        if (strstr(addressBook->contacts[addressBook->contactCount].email, "@gmail.com") == NULL) {
            printf("Invalid email! Must contain @gmail.com.\n");
            unique = 0;
            continue;
        }

        for (int i = 0; i < addressBook->contactCount; i++) {
            if (strcmp(addressBook->contacts[i].email,
                       addressBook->contacts[addressBook->contactCount].email) == 0) {
                printf("This email already exists! Please enter a different one.\n");
                unique = 0;
                break;
            }
        }
    } while (!unique);

    FILE *file = fopen("contacts.txt", "a");
    if(file){
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,
                addressBook->contacts[addressBook->contactCount].email);
        fclose(file);
    }

    addressBook->contactCount++;
    printf("Contact saved successfully!\n");
}
void searchContact(AddressBook *addressBook) 
{
    printf("----------------------------------------------------------\n");
    printf("              ENTERED INTO SEARCH CONTACT\n");
    printf("----------------------------------------------------------\n\n");

    int choice;
    char searchName[50];
    printf("Search By:\n");
    printf("1. Name\n2. Phone number\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: printf("Search the name: "); break;
        case 2: printf("Search the phone number: "); break;
        case 3: printf("Search the email: "); break;
        default: printf("Invalid choice!\n"); return;
    }
    scanf("%[^\n]", searchName);  

    int found = 0;
    for (int i = 0; i < addressBook->contactCount; i++) {
        int match = 0;

        if ((choice == 1 && strcmp(addressBook->contacts[i].name, searchName) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, searchName) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, searchName) == 0)) {
            match = 1;
        }

        if (match) {
            printf("\nContact Found:\n");
            printf("Name  : %s\n", addressBook->contacts[i].name);
            printf("Phone : %s\n", addressBook->contacts[i].phone);
            printf("Email : %s\n", addressBook->contacts[i].email);
            found = 1;
        }
    }

    if (!found) {
        printf("\nNo contact found for: %s\n", searchName);
    }
}

void editContact(AddressBook *addressBook) 
{
    printf("----------------------------------------------------------\n");
    printf("              ENTERED INTO EDIT CONTACT\n");
    printf("----------------------------------------------------------\n\n");

    int choice;
    char searchName[50];
    printf("Search By:\n");
    printf("1. Name\n2. Phone number\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); 

    switch (choice) {
        case 1: printf("Enter the name to edit: "); break;
        case 2: printf("Enter the phone number to edit: "); break;
        case 3: printf("Enter the email to edit: "); break;
        default: printf("Invalid choice!\n"); return;
    }
    scanf("%[^\n]", searchName);

    int found[100], Count = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, searchName) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, searchName) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, searchName) == 0)) {
            found[Count++] = i;
        }
    }

    if (Count == 0) {
        printf("No contact found with: %s\n", searchName);
        return;
    }

    int selectedIndex = found[0];
    if (Count > 1) {
        printf("Multiple contacts found:\n");
        for (int j = 0; j < Count; j++) {
            int k = found[j];
            printf("%d. Name: %s | Phone: %s | Email: %s\n", 
                   j + 1, addressBook->contacts[k].name, 
                   addressBook->contacts[k].phone, 
                   addressBook->contacts[k].email);
        }
        int choiceIndex;
        printf("Enter the number of the contact you want to edit: ");
        scanf("%d", &choiceIndex);
        if (choiceIndex < 1 || choiceIndex > Count) {
            printf("Invalid choice.\n");
            return;
        }
        selectedIndex = found[choiceIndex - 1];
    }

   
    switch (choice) {
        case 1: {
            char newName[50];
            printf("Enter new name: ");
            getchar();
            scanf("%[^\n]", newName);
            strcpy(addressBook->contacts[selectedIndex].name, newName);
            //printf("Name updated successfully!\n");
            printf("Do you also edit phone and gmail\n");
            printf("1.Yes\n2.No\n");
            int select;
            printf("Enter 1 or 2 according your choice:");
            scanf("%d",&select);
            switch(select){
                case 1:{
                    char newPhone[20];
                    printf("Enter new phone number: ");
                    getchar();
                    scanf("%[^\n]", newPhone);
                    char newEmail[50];
                    printf("Enter new email: ");
                    getchar();
                    scanf("%[^\n]", newEmail);
                    strcpy(addressBook->contacts[selectedIndex].phone, newPhone);
                    strcpy(addressBook->contacts[selectedIndex].email, newEmail);
                    printf("Phone and Email updated successfully!\n");
                    break;
                }
                case 2:{
                    printf("Only Name updated successfully!\n");
                }
            }
            break;
        }
        case 2: {
            char newPhone[20];
            printf("Enter new phone number: ");
            getchar();
            scanf("%[^\n]", newPhone);
            strcpy(addressBook->contacts[selectedIndex].phone, newPhone);
            printf("Phone number updated successfully!\n");
            break;
        }
        case 3: {
            char newEmail[50];
            printf("Enter new email: ");
            getchar();
            scanf("%[^\n]", newEmail);
            strcpy(addressBook->contacts[selectedIndex].email, newEmail);
            printf("Email updated successfully!\n");
            break;
        }
    }
}


void deleteContact(AddressBook *addressBook) 
{
    printf("----------------------------------------------------------\n");
    printf("              ENTERED INTO DELETE CONTACT\n");
    printf("----------------------------------------------------------\n\n");

    int choice;
    char searchName[50];
    printf("Delete By:\n");
    printf("1. Name\n2. Phone number\n3. Email\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); 

    switch (choice) {
        case 1: printf("Enter the name: "); break;
        case 2: printf("Enter the phone number: "); break;
        case 3: printf("Enter the email: "); break;
        default: printf("Invalid choice!\n"); return;
    }
    scanf("%[^\n]", searchName);

    int sameIndex[MAX_CONTACTS], count = 0;

    for (int i = 0; i < addressBook->contactCount; i++) {
        int match = 0;
        if ((choice == 1 && strcmp(addressBook->contacts[i].name, searchName) == 0) ||
            (choice == 2 && strcmp(addressBook->contacts[i].phone, searchName) == 0) ||
            (choice == 3 && strcmp(addressBook->contacts[i].email, searchName) == 0)) {
            match = 1;
        }
        if (match) {
            sameIndex[count++] = i;
        }
    }

    if (count == 0) {
        printf("\nNo contact found matching: %s\n", searchName);
        return;
    }

    int delIndex = -1;

    if (choice == 1 && count > 1) {
        printf("\nMultiple contacts found with the same name:\n");
        for (int i = 0; i < count; i++) {
            int j = sameIndex[i];
            printf("%d. Name: %s | Phone: %s | Email: %s\n",
                   i + 1,
                   addressBook->contacts[j].name,
                   addressBook->contacts[j].phone,
                   addressBook->contacts[j].email);
        }

        char unique[50];
        printf("Enter the phone OR email of the contact to delete: ");
        scanf("%s", unique);

        for (int i = 0; i < count; i++) {
            int j = sameIndex[i];
            if (strcmp(addressBook->contacts[j].phone, unique) == 0 ||
                strcmp(addressBook->contacts[j].email, unique) == 0) {
                delIndex = j;
                break;
            }
        }
        if (delIndex == -1) {
            printf("No matching phone/email found for deletion.\n");
            return;
        }
    } else {
        delIndex = sameIndex[0]; 
    }

    // Show contact before deletion
    printf("\nContact selected for deletion:\n");
    printf("Name: %s\nPhone: %s\nEmail: %s\n",
           addressBook->contacts[delIndex].name,
           addressBook->contacts[delIndex].phone,
           addressBook->contacts[delIndex].email);

    // Ask confirmation
    printf("\nDo you really want to delete this contact?\n");
    printf("1. Yes\n2. No\n");
    int select;
    printf("Enter your choice: ");
    scanf("%d", &select);

    if (select != 1) {
        printf("Deletion cancelled. Contact not deleted.\n");
        return;
    }

    // Perform deletion
    for (int j = delIndex; j < addressBook->contactCount - 1; j++) {
        addressBook->contacts[j] = addressBook->contacts[j + 1];
    }
    addressBook->contactCount--;

    FILE *file = fopen("contacts.txt", "w");
    if (!file) {
        printf("Error updating contacts.txt!\n");
        return;
    }
    for (int k = 0; k < addressBook->contactCount; k++) {
        fprintf(file, "%s,%s,%s\n",
                addressBook->contacts[k].name,
                addressBook->contacts[k].phone,
                addressBook->contacts[k].email);
    }
    fclose(file);

    printf("\nContact deleted successfully and file updated!\n");
}

void saveContact(AddressBook *addressBook) {
    FILE *file = fopen("contacts.txt", "w");
    if (!file) {
        printf("Error saving contacts!\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(file, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

    fclose(file);
    printf("Contacts saved successfully!\n");
}

