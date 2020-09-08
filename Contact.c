/* Peter Silano
This program keeps track of a contacts, allowing you to add or remove a contact
and allowing you to add or remove information.
*/

#include "contact.h"

// add a new contact to your list of contacts
//	   1. Make sure a contact by that name does not exist (print an error message and exit if it exists)
//	   2. Add a new contact with that name (add-at-front)
Contact* addContact(Contact *myContacts, char *contactName) {

	for (Contact *current = myContacts; current != NULL; current = current->next) {
		if (strcmp(current->name, contactName) == 0) {
			printf("Error: Contact already exists.\n");
			return myContacts;
		}
	}

	Contact *newContact = malloc(sizeof(Contact));
	newContact->name = malloc(strlen(contactName)+1);
	strcpy(newContact->name, contactName);
	newContact->next = myContacts;
	newContact->information = NULL;
	return newContact;
}

// adds a new piece of information to the specified contact
//   1. Make sure a contact by that name exists (so you can add information to it)
//   2. If the informational ≥/item already exists, update the information's value to the new value
//   3. Otherwise, add the piece of information to the end of the contact's information list (add-at-end)

void addInformation(Contact *myContacts, char *contactName, char *infoName, char *infoValue) {

	if (myContacts == NULL) {
		printf("Error: Contact list empty.\n");
		return;
	}

	for (Contact *current = myContacts; current != NULL; current = current->next) {
		if (strcmp(current->name, contactName) == 0) {

			Info *infoNew = malloc(sizeof(Info));
			infoNew->name = malloc(strlen(infoName)+1);
			strcpy(infoNew->name, infoName);
			infoNew->value = malloc(strlen(infoValue)+1);
			strcpy(infoNew->value, infoValue);
			infoNew->next = NULL;

			if (current->information == NULL) {  // special case
				current->information = infoNew;
			}

			for (Info *temp = current->information; temp != NULL; temp = temp->next) {
				if (strcmp(temp->name, infoNew->name) == 0) {
					temp->value = infoNew->value;
					return;
				}
				if (temp->next == NULL) {
					temp->next = infoNew;
					return;
				}
			}
		}
	}
	printf("Error: Name does not exist.\n");
	return;
}

// prints all the information for a given contact
//	1. Make sure a contact with that name exists
//	2. Print the name of the contact
//	3. print all the informational items <name|value> associated with that contact
void printContact(Contact *myContacts, char *contactName) {  // AFTER 3 CONTACTS SEG FAULT
	if (myContacts == NULL) {
		printf("Error: Contact list empty.\n");
		return;
	}

	for (Contact *current = myContacts; current != NULL; current = current->next) {
		if (strcmp(current->name, contactName) == 0) {
			printf("%s\n", current->name);

			Info *temp = current->information;
			while (temp != NULL) {
				printf("<%s|%s>\n", temp->name, temp->value);
				temp = temp->next;
			}
			return;
		}
	}

	printf("Error: Name does not exist.\n");
	return;
}

// returns the size of a given contact list
//	Iterate through the contact list to count the number of contacts, return that count
int count(Contact *myContacts) {
	int countContacts = 0;
	while (myContacts != NULL) {
		countContacts++;
		myContacts = myContacts->next;
	}
	return countContacts;
}

// prints all your contacts
//	For each contact
//	   a.  Print the name of the contact
//	   b.  Print all the <information name|information value> pairs in that contact
//	Note: this code can call other functions as needed
void print(Contact *myContacts) {
	for (Contact *current = myContacts; current != NULL; current = current->next) {
		printContact(current, current->name);
	}
	return;
}

// add a new contact (in alphabetical order)
//	1. Make sure a contact by that name does not exist
//	2. Add a new contact with that name (add-in-order)
Contact *addContactOrdered(Contact *myContacts, char *contactName) {
	Contact *newContact;
	for (newContact = myContacts; newContact != NULL; newContact = newContact->next) {
		if (strcmp(newContact->name, contactName) == 0) {
			printf("Error: Contact already exists.\n");
			return myContacts;
		}
	}

	newContact = malloc(sizeof(Contact));
	newContact->name = malloc(strlen(contactName)+1);
	strcpy(newContact->name, contactName);
	newContact->information = NULL;
	newContact->next = NULL;

	if (myContacts == NULL)				//special case #1
		return newContact;

	if (strcmp(contactName, myContacts->name) < 0) {		//special case #2
		newContact->next = myContacts;
		return newContact;
	}

	Contact *previous = myContacts;
	Contact *current = myContacts->next;
	while (current && strcmp(current->name, contactName) < 0) {
		previous = current;
		current = current->next;
	}
	previous->next = newContact;
	newContact->next = current;

	return myContacts;
}

// adds a new info to the specified contact (in alphabetical order)
//	1. Make sure a contact by that name exists (so you can add an info to it)
//	2. If the informational item already exists, update the item (replace its value with the new value)
//	3. Otherwise, add the new info to the contact (add-in-order)
void addInformationOrdered(Contact *myContacts, char *contactName, char *infoName, char *infoValue) {

	for (Contact *current = myContacts; current != NULL; current = current->next) {
		if (strcmp(current->name, contactName) == 0) {

			Info *infoNew = malloc(sizeof(Info));
			infoNew->name = malloc(strlen(infoName)+1);
			strcpy(infoNew->name, infoName);
			infoNew->value = malloc(strlen(infoValue)+1);
			strcpy(infoNew->value, infoValue);
			infoNew->next = NULL;

			Info *head = current->information;
			if (head == NULL) {													//special case #1
				current->information = infoNew;
				return;
			}

			if (strcmp(infoName, head->name) < 0) {			//special case #2
				infoNew->next = head;
				current->information = infoNew;
				return;
			}

			for (Info *temp = current->information; temp != NULL; temp = temp->next) {
				if (strcmp(temp->name, infoNew->name) == 0) {
					temp->value = infoNew->value;
					return;
				}
			}

			Info *prev = head;
			Info *curr = head->next;
			while (curr && strcmp(curr->name, infoName) < 0) {
				prev = curr;
				curr = curr->next;
			}
			prev->next = infoNew;
			infoNew->next = curr;

			return;
		}
	}

	printf("Error: Name does not exist.\n");
	return;
}

// remove information from a contact
//	1. Make sure a contact with that name exists
//	2. Make sure the informational item exists in that contact
//	3. Remove that piece of information from the contact

void removeInformation(Contact *myContacts, char *contactName, char *infoName) {
	for (Contact *current = myContacts; current != NULL; current = current->next) {
		if (strcmp(current->name, contactName) == 0) {
			for (Info *temp = current->information; temp != NULL; temp = temp->next) {
				if (strcmp(temp->name, infoName) == 0) {

					Info *head = current->information;
					if (head == NULL) {														//special case #1
						current->information = head;
						return;
					}

					if (strcmp(head->name, infoName) == 0) { 			//special case #2
						Info *temp = head->next;
						free(head);
						current->information = temp;
						return;
					}

					Info *prev = head;
					Info *curr = head->next;

					while (curr && strcmp(curr->name, infoName) != 0) {
						prev = curr;
						curr = curr->next;
					}

					if (curr == NULL) {
						return;
					}

					prev->next = curr->next;
					free(curr);
					return;
				}
			}

			printf("Error: Information does not exist.\n");
			return;
		}
	}

	printf("Error: Name does not exist.\n");
	return;
}

// remove a contact (and all the informational items for that contact)
//	1. Make sure a contact with that name exists
//	2. Remove that contact
Contact *removeContact(Contact *myContacts, char *contactName) {
	for (Contact *current = myContacts; current != NULL; current = current->next) {
		if (strcmp(current->name, contactName) == 0) {

			if (myContacts == NULL) {			// special case #1
				return myContacts;
			}

			if (strcmp(myContacts->name, contactName) == 0) {     // special case #2
				Contact *temp = myContacts->next;
				free (myContacts);
				return temp;
			}

			Contact *previous = myContacts;
			Contact *current = myContacts->next;

			while (current && strcmp(current->name,contactName) != 0) {
				previous = current;
				current = current->next;
			}

			if (current == NULL )
				return myContacts;

			previous->next = current->next;
			free(current);

			return myContacts;
		}
	}

	printf("Error: Name does not exist.\n");
	return myContacts;
}
