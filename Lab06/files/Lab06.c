#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

static int intcmp(const int x, const int y){
	return (x > y) ? 1 : (x == y) ? 0 : -1;
}

struct listing {
	int id, host_id, minimum_nights, number_of_reviews, calculated_host_listings_count,availability_365;
	char *host_name, *neighbourhood_group, *neighbourhood, *room_type;
	float latitude, longitude, price;
};

struct listing getfields(char* line){
	struct listing item;

	item.id = atoi(strtok(line, ","));
	item.host_id = atoi(strtok(NULL, ","));
	item.host_name = strdup(strtok(NULL, ","));
	item.neighbourhood_group = strdup(strtok(NULL, ","));
	item.neighbourhood = strdup(strtok(NULL, ","));
	item.latitude = atof(strtok(NULL, ","));
	item.longitude = atof(strtok(NULL, ","));
	item.room_type = strdup(strtok(NULL, ","));
	item.price = atof(strtok(NULL, ","));
	item.minimum_nights = atoi(strtok(NULL, ","));
	item.number_of_reviews = atoi(strtok(NULL, ","));
	item.calculated_host_listings_count = atoi(strtok(NULL, ","));
	item.availability_365 = atoi(strtok(NULL, ","));
	
	return item;
}

void displayStruct(struct listing item) {
	printf("ID : %d\n", item.id);
	printf("Host ID : %d\n", item.host_id);
	printf("Host Name : %s\n", item.host_name);
	printf("Neighbourhood Group : %s\n", item.neighbourhood_group);
	printf("Neighbourhood : %s\n", item.neighbourhood);
	printf("Latitude : %f\n", item.latitude);
	printf("Longitude : %f\n", item.longitude);
	printf("Room Type : %s\n", item.room_type);
	printf("Price : %0.2f\n", item.price);
	printf("Minimum Nights : %d\n", item.minimum_nights);
	printf("Number of Reviews : %d\n", item.number_of_reviews);
	printf("Calculated Host Listings Count : %d\n", item.calculated_host_listings_count);
	printf("Availability_365 : %d\n\n", item.availability_365);
}

static int sort_host_name(const void *item1, const void *item2){
	struct listing *list1 = (struct listing *)item1;
	struct listing *list2 = (struct listing *)item2;
  return strcmp(list1->host_name, list2->host_name);
}

static int sort_price(const void *item1, const void *item2){
	struct listing *list1 = (struct listing *)item1;
	struct listing *list2 = (struct listing *)item2;
  return intcmp(list1->price, list2->price);
}

void write_to_file(struct listing *list_items, int size, char *write_file){
	FILE *write_pointer = fopen(write_file, "w");
	if(write_pointer == NULL){
		printf("Error reading input file listings.csv\n");
		exit (-1);
	}
	fprintf(write_pointer, "id,host_id,host_name,neighbourhood_group,neighbourhood,latitude,longitude,room_type,price,minimum_nights,number_of_reviews,calculated_host_listings_count,availability_365\n");
	for(int i = 0; i < size; i++){
		struct listing cur_item = list_items[i];
		fprintf(write_pointer, "%d,%d,%s,%s,%s,%f,%f,%s,%f,%d,%d,%d,%d\n", 
			cur_item.id, cur_item.host_id, cur_item.host_name,
			cur_item.neighbourhood,
			cur_item.neighbourhood_group,
			cur_item.latitude,
			cur_item.longitude,
			cur_item.room_type,
			cur_item.price,
			cur_item.minimum_nights,
			cur_item.number_of_reviews,
			cur_item.calculated_host_listings_count,
			cur_item.availability_365);
	}
	fclose(write_pointer);
}

int main(int argc, char* args[]) {
	struct listing list_items[22555];
	char line[LINESIZE];
	int i, count;

	FILE *fptr = fopen("listings.csv", "r");
	if(fptr == NULL){
		printf("Error reading input file listings.csv\n");
		exit (-1);
	}

	count = 0;
	while (fgets(line, LINESIZE, fptr) != NULL){
		list_items[count++] = getfields(line);
	}
	fclose(fptr);


  qsort(list_items, count, sizeof(struct listing), sort_host_name);
  for(i = 0; i < count; i++)
		displayStruct(list_items[i]);
  printf("END\n");

	write_to_file(list_items, count, "sorted_by_host_name.txt");

	qsort(list_items, count, sizeof(struct listing), sort_price);
	for (i=0; i<count; i++)
		displayStruct(list_items[i]);

	write_to_file(list_items, count, "sorted_by_price.txt");
	
	return 0;
}