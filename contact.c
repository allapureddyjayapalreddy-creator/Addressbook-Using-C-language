#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include "validate.h"

// Displays all contacts in a formatted table
void listContacts(AddressBook *addressBook, int sortCriteria)
{
    // Check if the address book is empty
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts found!\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    printf("------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-15s | %-25s |\n", "S.No", "Name", "Phone", "Email");
    printf("------------------------------------------------------------\n");

    // Display all stored contacts in a structured table
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-5d | %-20s | %-15s | %-25s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("------------------------------------------------------------\n");
    printf("Total contacts: %d\n", addressBook->contactCount);
}

// Initializes the address book and loads existing contacts from file
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;

    // Load contacts from file when the program starts
    loadContactsFromFile(addressBook);
}

// Saves data to file and exits the program
void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);
    exit(EXIT_SUCCESS);
}

// Creates a new contact and stores it in the address book
void createContact(AddressBook *addressBook)
{
    char names[20];
    char phones[10];
    char emails[30];

    printf("Enter the name: ");
    getchar(); // Clear leftover newline
    scanf(" %[^\n]", names);

    // Validate name input
    while (!valid_name(names))
    {
        printf("Invalid name!\nPlease enter a valid name: ");
        scanf(" %[^\n]", names);
    }
    strcpy(addressBook->contacts[addressBook->contactCount].name, names);

    printf("Enter the phone number: ");
    scanf("%s", phones);

    // Validate phone number
    while (!valid_phone(phones, addressBook))
    {
        printf("Invalid phone number!\nPlease enter a valid phone number: ");
        scanf("%s", phones);
    }
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phones);

    printf("Enter the email: ");
    scanf("%s", emails);

    // Validate email
    while (!valid_email(emails, addressBook))
    {
        printf("Invalid email!\nPlease enter a valid email: ");
        scanf("%s", emails);
    }
    strcpy(addressBook->contacts[addressBook->contactCount].email, emails);

    printf("Contact created successfully!\n");

    // Increase the total contact count
    addressBook->contactCount++;
}

// Searches for a contact by name, phone, or email
void searchContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts available to search.\n");
        return;
    }

    int choice;
    char query[50];

    printf("Search by:\n1. Name\n2. Phone\n3. Email\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // Search by name
        printf("Enter name to search: ");
        scanf(" %[^\n]", query);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcasecmp(addressBook->contacts[i].name, query) == 0)
            {
                printf("\nContact Found:\n");
                printf("  Name : %s\n", addressBook->contacts[i].name);
                printf("  Phone: %s\n", addressBook->contacts[i].phone);
                printf("  Email: %s\n", addressBook->contacts[i].email);
                return;
            }
        }
        printf("No contact found with that name.\n");
        break;

    case 2: // Search by phone
        printf("Enter phone to search: ");
        scanf("%s", query);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].phone, query) == 0)
            {
                printf("\nContact Found:\n");
                printf("  Name : %s\n", addressBook->contacts[i].name);
                printf("  Phone: %s\n", addressBook->contacts[i].phone);
                printf("  Email: %s\n", addressBook->contacts[i].email);
                return;
            }
        }
        printf("No contact found with that phone number.\n");
        break;

    case 3: // Search by email
        printf("Enter email to search: ");
        scanf("%s", query);

        for (int i = 0; i < addressBook->contactCount; i++)
        {
            if (strcmp(addressBook->contacts[i].email, query) == 0)
            {
                printf("\nContact Found:\n");
                printf("  Name : %s\n", addressBook->contacts[i].name);
                printf("  Phone: %s\n", addressBook->contacts[i].phone);
                printf("  Email: %s\n", addressBook->contacts[i].email);
                return;
            }
        }
        printf("No contact found with that email.\n");
        break;

    default:
        printf("Invalid choice.\n");
        break;
    }
}

// Edits a contact using phone number as the identifier
void editContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to edit!\n");
        return;
    }

    char search[50];
    printf("Enter phone number of the contact to edit: ");
    scanf("%s", search);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, search) == 0)
        {
            printf("\nContact Found:\n");
            printf("  Name : %s\n", addressBook->contacts[i].name);
            printf("  Phone: %s\n", addressBook->contacts[i].phone);
            printf("  Email: %s\n", addressBook->contacts[i].email);

            int choice;
            printf("\nWhat do you want to edit?\n");
            printf("1. Name\n2. Phone\n3. Email\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case 1:
                do
                {
                    printf("Enter new name: ");
                    scanf(" %[^\n]", addressBook->contacts[i].name);
                    if (!valid_name(addressBook->contacts[i].name))
                        printf("Invalid name. Try again.\n");
                } while (!valid_name(addressBook->contacts[i].name));
                break;

            case 2:
                do
                {
                    printf("Enter new phone: ");
                    scanf("%s", addressBook->contacts[i].phone);
                    if (!valid_phone(addressBook->contacts[i].phone, addressBook))
                        printf("Invalid phone. Try again.\n");
                } while (!valid_phone(addressBook->contacts[i].phone, addressBook));
                break;

            case 3:
                do
                {
                    printf("Enter new email: ");
                    scanf("%s", addressBook->contacts[i].email);
                    if (!valid_email(addressBook->contacts[i].email, addressBook))
                        printf("Invalid email. Try again.\n");
                } while (!valid_email(addressBook->contacts[i].email, addressBook));
                break;

            default:
                printf("Invalid choice.\n");
                return;
            }

            printf("Contact updated successfully!\n");
            return;
        }
    }

    printf("No contact found with that phone number.\n");
}

// Deletes a contact using phone number
void deleteContact(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf("\nNo contacts available to delete!\n");
        return;
    }

    char phone[20];
    printf("Enter phone number of the contact to delete: ");
    scanf("%s", phone);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("\nContact Found:\n");
            printf("  Name : %s\n", addressBook->contacts[i].name);
            printf("  Phone: %s\n", addressBook->contacts[i].phone);
            printf("  Email: %s\n", addressBook->contacts[i].email);

            char confirm;
            printf("\nAre you sure you want to delete this contact? (y/n): ");
            scanf(" %c", &confirm);

            if (confirm == 'y' || confirm == 'Y')
            {
                // Shift all contacts left by one position
                for (int j = i; j < addressBook->contactCount - 1; j++)
                {
                    addressBook->contacts[j] = addressBook->contacts[j + 1];
                }
                addressBook->contactCount--;
                printf("Contact deleted successfully!\n");
            }
            else
            {
                printf("Deletion cancelled.\n");
            }
            return;
        }
    }

    printf("No contact found with that phone number.\n");
}
