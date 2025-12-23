#include <stdio.h>
#include <string.h>
#include "contact.h"
#include "validate.h"

//Validate the name
int valid_name(char *str){
    for(int i=0;str[i]!='\0';i++){
        if(str[i]>='A'&&str[i]<='Z'||str[i]>='a'&&str[i]<='z'||str[i]==' '||str[i]=='.'){
            return 1;  //If enter characters are correct return 1
        }else{
            return 0;  //if the characters are not correct return 0
        }
    }
}

//validate the phone number
int valid_phone(char *str,AddressBook *addressBook) {
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        // Check if character is a digit
        if (str[i] < '0' || str[i] > '9') {
            return 0;  // if entered characters are non-digits
        }
        count++;
    }

    // Phone number must be exactly 10 digits
    if (count != 10){
        return 0;  // invalid count of digits
    }
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].phone, str) == 0) {
            return 0; // Invalid  already exists
        }
    }

    return 1; // Valid and unique
}

int valid_email(char *str, AddressBook *addressBook) {
    int atCount = 0, dotAfterAt = 0;

    // Check allowed characters and count '@'
    for (int i = 0; str[i] != '\0'; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
              (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') ||
              str[i] == '@' || str[i] == '.' || str[i] == '_')) {
            return 0; // Invalid character
        }

        if (str[i] == '@') {
            atCount++;
            // check if dot (.) comes after @ somewhere
            for (int j = i + 1; str[j] != '\0'; j++) {
                if (str[j] == '.') {
                    dotAfterAt = 1;
                    break;
                }
            }
        }
    }

    // Must have exactly one '@'
    if (atCount != 1)
        return 0;

    // Must have at least one '.' after '@'
    if (!dotAfterAt)
        return 0;

    // Must end with ".com"
    if (strstr(str, ".com") == NULL)
        return 0;

    // Check duplicate email in address book
    for (int i = 0; i < addressBook->contactCount; i++) {
        if (strcmp(addressBook->contacts[i].email, str) == 0) {
            return 0; // Already exists
        }
    }

    return 1; // Valid email
}
