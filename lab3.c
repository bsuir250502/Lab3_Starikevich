#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mylib.h"

#define MAXLENGTH 64

typedef struct {
	int x;
	int y;
} coordinate_t;

typedef struct person {
	char surname[MAXLENGTH];
	coordinate_t location;
	struct person *next;
} person_t;
	
typedef struct hospital {
	int hospital_number;
	int places_number;
	int free_places_number;
	int (*dist) (coordinate_t, coordinate_t);
	coordinate_t location;
	person_t *head_p;
	person_t *last_p;
	struct hospital *next;
} hospital_t;

char myget_arg(int, char**);
int create_hospital_list(hospital_t**, hospital_t**);
int print_hospital_list(hospital_t*);
int create_person(hospital_t*);
int find_nearest_hospital(hospital_t*, person_t*);
int bind_person_to_hospital(hospital_t*, person_t*, int);
int discharge_patients(hospital_t*);
int calculate_distance(coordinate_t, coordinate_t);
// ------------------------------------------
int main(int argc, char **argv) {
	
	hospital_t *head_h = NULL;
	hospital_t *last_h = NULL;
	
	if(myget_arg(argc, argv) == 'h') {
		print_manual();
		return 0;
	}
	create_hospital_list(&head_h, &last_h);
	printf("Would you like to print hospital list? (y/n) ");
	if(confirm_choice()) {	
		print_hospital_list(head_h);
	}
	if(create_person(head_h)) {
		printf("\n--->>>> Unable to create person...");
	}

	printf("\nWould you like to print hospital list again? (y/n) ");
	if(confirm_choice()) {	
		print_hospital_list(head_h);
	}
	
	printf("\n\n--->>>> Shutting down...\n");
	return 0;
}
// ------------------------------------------
char myget_arg(int argc, char **argv) {
	if(argc >= 2) {
		if(!(strcmp(argv[1], "-h"))) return 'h';
		else {
			printf("Please, enter the correct argument:\n");
			printf("[-h] to print README file\n");
		}
	}
		
	return '0';
}
// ------------------------------------------
int create_hospital_list(hospital_t **head_h, hospital_t **last_h) {
	hospital_t *hospital = NULL;
	int i=0;
	
	while(1) {
		if(!(hospital = (hospital_t*)malloc(sizeof(hospital_t)))) {
			printf("Out of memory...");
			return 1;
		}
		i++;
		printf("\n[%dth hospital]", i);
		printf("\nEnter the hospital #: ");
		hospital->hospital_number = myget_int();
		printf("Enter the hospital's location...\n");
		printf("x: ");
		hospital->location.x = myget_int_range(1, 300);
		printf("y: ");
		hospital->location.y = myget_int_range(1, 300);
		printf("Enter the number of places: ");
		hospital->places_number = myget_int();
		while(1) {
			printf("Enter the number of free places (n<=%d): ", hospital->places_number);
			hospital->free_places_number = myget_int();
			if((hospital->free_places_number)>(hospital->places_number)) continue;
			else break;
		}
		hospital->dist = calculate_distance;
		
		if(!*head_h) {
			(*head_h) = hospital;
		} else {
			(*last_h)->next = hospital;
		}
		(*last_h) = hospital;
		
		printf("\nWould you like to add one more hospital? (y/n) ");
		if(!confirm_choice()) break;
	}
	
	return 0;
}
// ------------------------------------------
int print_hospital_list(hospital_t *hospitals) {
	
	while(hospitals) {
		printf("\n\n[Hospital #%d]", hospitals->hospital_number);
		printf("\nPlaces: %d", hospitals->places_number);
		printf("\nFree places: %d", hospitals->free_places_number);
		printf("\nLocation (x,y): %d,%d", hospitals->location.x, hospitals->location.y);
		if(hospitals->head_p) {
			printf("\nPatients:\n");
			while(hospitals->head_p) {
				printf("------> %s\n", hospitals->head_p->surname);
				hospitals->head_p = hospitals->head_p->next;
			}
		}
		hospitals = hospitals->next;
	}
	
	return 0;
}
// ------------------------------------------
int create_person(hospital_t *hospitals) {

	person_t *person = NULL;
	int i=0, nearest_hospital_number=0;
	
	while(1) {
		if(!(person = (person_t*)malloc(sizeof(person_t)))) {
			printf("Out of memory...");
			return 1;
		}
		i++;
		printf("\n\n[%dth patient]", i);
		printf("\nEnter the surname: ");
		mygets(person->surname);
		printf("Enter the patient's location...\n");
		printf("x: ");
		person->location.x = myget_int_range(1, 300);
		printf("y: ");
		person->location.y = myget_int_range(1, 300);

		nearest_hospital_number = find_nearest_hospital(hospitals, person);
		if(!nearest_hospital_number) {
			return 1;
		}
		bind_person_to_hospital(hospitals, person, nearest_hospital_number);

		printf("\n\nWould you like to add one more patient? (y/n) ");
		if(!confirm_choice()) break;
	}
	return 0;
}
// ------------------------------------------
int find_nearest_hospital(hospital_t *hospitals, person_t *person) {
	int nearest_hospital_number=0 , shortest=0, distance=0;
	
	while(1) {
		while(hospitals) {
			if(hospitals->free_places_number == 0) {
				printf("\n--->>>> Nearest hospital is #%d, but there is no free places!", hospitals->hospital_number);
				printf("\nSearching for other nearby hospitals...");
				hospitals = hospitals->next;
				continue;
			} else {
				distance = hospitals->dist(hospitals->location, person->location);
				if(distance<shortest || shortest == 0) {
					shortest = distance;
					nearest_hospital_number = hospitals->hospital_number;
				}
				hospitals = hospitals->next;
			}
		}
		if(!nearest_hospital_number) {
			printf("\n\n--->>>> ALL hospitals is full!");
			return 0;
		} else {
			printf("\nNearest available hospital is #%d", nearest_hospital_number);
			return nearest_hospital_number;
			break;
		}
	}
	return 0;
}
// ------------------------------------------
int bind_person_to_hospital(hospital_t *hospitals, person_t *person, int nearest_hospital_number) {

	int success = 0;
	if(!hospitals) {
		printf("\n--->>>> Out of memory...");
	}
	while(hospitals) {
		if(hospitals->hospital_number == nearest_hospital_number) {
			if(!(hospitals->head_p)) {
				hospitals->head_p = person;
			} else {
				hospitals->last_p->next = person;
			}
			hospitals->last_p = person;
			printf("\nBinding successful! [Person '%s', Hospital #%d]", hospitals->last_p->surname, hospitals->hospital_number);
			hospitals->free_places_number--;
			success = 1;
			break;
		}
		hospitals = hospitals->next;
	}
	if(!success) {
		printf("\n--->>>> Error! Unable to bind this person to nearest hospital...");
		return 1;
	}

	return 0;
}
// ------------------------------------------
int calculate_distance(coordinate_t a, coordinate_t b) {
	double distance = sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
	int result = (int)(distance);

	return result;
}
// ------------------------------------------
#ifdef __cplusplus
}
#endif
