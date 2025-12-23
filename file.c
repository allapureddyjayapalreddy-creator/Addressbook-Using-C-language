#include <stdio.h>   // For file I/O functions like fopen, fprintf, fscanf, fclose
#include <string.h> // For string functions
#include "file.h"   // Header file where AddressBook struct and prototypes are declared

void saveContactsToFile(AddressBook *addressBook) {
  FILE  *cfile =fopen("contacts.txt","w");
  fprintf(cfile,"#%d\n",addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++){
    fprintf(cfile,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(cfile);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE  *cfile =fopen("contacts.txt","r");
    if (cfile == NULL) {
        // File might not exist yet (first time)
        addressBook->contactCount = 0;
        return;
    }
    fscanf(cfile,"#%d\n",&addressBook->contactCount);
    for (int i = 0; i < addressBook->contactCount; i++){
    fscanf(cfile,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(cfile);
}
