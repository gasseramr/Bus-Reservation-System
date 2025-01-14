#include <stdio.h>
#include <string.h>

// Structure Definitions
struct Tour {
    int tour_id;
    char tour_destination[50];
    int num_seats;
    int seats_booked;
    int tour_time;
};

struct Passenger {
    char name[50];
    int age;
    char gender;
    char location[100];
    char dest[100];
    int seat_no;
};

struct Bus {
    char available_trips;
    float prices;
    char category;
    int time;
    int seats_avail;
    int seat_no;
};

// Function Definitions
int List_passengers(struct Passenger passengers[], int num_passengers) {
    if (num_passengers == 0) {
        printf("There are no passengers in the list.\n");
        return -1;
    }
    printf("Passengers:\n");
    for (int i = 0; i < num_passengers; i++) {
        printf("Name: %s - Age: %d - Gender: %c - Location: %s - Destination: %s - Seat No.: %d\n",
               passengers[i].name, passengers[i].age, passengers[i].gender, passengers[i].location, passengers[i].dest, passengers[i].seat_no);
    }
    return 0;
}

int Delete_passenger(struct Passenger passengers[], int *num_passengers, char name[]) {
    for (int i = 0; i < *num_passengers; i++) {
        if (strcmp(passengers[i].name, name) == 0) {
            for (int j = i; j < *num_passengers - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            (*num_passengers)--;
            printf("%s's record has been deleted.\n", name);
            return 0;
        }
    }
    printf("No record found for %s.\n", name);
    return -1;
}

void availabletrips(struct Bus bus[], int n) {
    printf("Available trips are:\n");
    printf("Available seats\t Prices \t Arrival time \t Category \t Seat No.\n");
    printf("-----------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%c \t\t\t %.2f \t\t %d \t\t %c \t\t %d/%d\n",
               bus[i].available_trips, bus[i].prices, bus[i].time, bus[i].category, bus[i].seats_avail, bus[i].seat_no);
    }
}

void editPassenger(struct Passenger *passenger) {
    printf("Enter new seat number: ");
    scanf("%d", &passenger->seat_no);
    printf("Seat number edited successfully.\n");
}

void list_tours(struct Tour tour[], int n) {
    printf("Our tours are:\n");
    printf("Tour Id\t Tour Destination \t Available Seats \t Seats Booked \t Tour time \n");
    for (int i = 0; i < n; i++) {
        printf("%d \t\t %s \t\t\t %d \t\t\t\t %d \t\t\t %d\n",
               tour[i].tour_id, tour[i].tour_destination, tour[i].num_seats, tour[i].seats_booked, tour[i].tour_time);
    }
}

void editTour(struct Tour tours[], int n) {
    int tour_id, found = 0;
    printf("Enter the Tour ID to edit: ");
    scanf("%d", &tour_id);

    for (int i = 0; i < n; i++) {
        if (tours[i].tour_id == tour_id) {
            found = 1;
            printf("Editing Tour ID %d:\n", tour_id);

            printf("Enter new destination: ");
            scanf("%s", tours[i].tour_destination);

            printf("Enter new number of available seats: ");
            scanf("%d", &tours[i].num_seats);

            printf("Enter new number of seats booked: ");
            scanf("%d", &tours[i].seats_booked);

            printf("Enter new tour time: ");
            scanf("%d", &tours[i].tour_time);

            printf("Tour ID %d updated successfully!\n", tour_id);
            break;
        }
    }

    if (!found) {
        printf("Tour ID %d not found.\n", tour_id);
    }
}

// Main Program
int main() {
    struct Passenger passengers[100];
    int num_passengers = 0;
    int choice = 0;

    // Define and initialize the bus array
    struct Bus bus[8] = {
        {'A', 19.99, 'E', 8, 10, 1},
        {'B', 25.50, 'L', 10, 5, 1},
        {'C', 15.00, 'E', 12, 20, 1},
        {'D', 30.00, 'L', 14, 8, 1},
        {'E', 22.75, 'E', 16, 12, 1},
        {'F', 18.50, 'L', 18, 14, 1},
        {'G', 20.00, 'E', 20, 6, 1},
        {'H', 28.75, 'L', 22, 3, 1}
    };

    // Define and initialize the tour array
    struct Tour tour[7] = {
        {1, "Destination A", 5, 15, 8},
        {2, "Destination B", 10, 8, 10},
        {3, "Destination C", 7, 13, 12},
        {4, "Destination D", 3, 17, 14},
        {5, "Destination E", 19, 1, 16},
        {6, "Destination F", 11, 9, 18},
        {7, "Destination G", 16, 4, 20}
    };

    while (choice != 7) {
        printf("\nChoose an option:\n");
        printf("1. List passengers\n2. Add a passenger\n3. Delete a passenger\n4. Edit a passenger\n5. List Tours\n6. Edit Tours\n7. Quit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                List_passengers(passengers, num_passengers);
                break;

            case 2: {
                struct Passenger new_passenger;
                printf("Enter passenger name: ");
                scanf("%s", new_passenger.name);
                printf("Enter passenger age: ");
                scanf("%d", &new_passenger.age);
                printf("Enter passenger gender (M/F): ");
                scanf(" %c", &new_passenger.gender);
                printf("Enter passenger location: ");
                scanf("%s", new_passenger.location);
                printf("Enter passenger destination: ");
                scanf("%s", new_passenger.dest);

                printf("Choose a bus trip from the list below: \n");
                availabletrips(bus, 8);
                char trip;
                printf("Enter the trip code: ");
                scanf(" %c", &trip);

                int found_trip = 0;
                for (int i = 0; i < 8; i++) {
                    if (bus[i].available_trips == trip) {
                        found_trip = 1;
                        if (bus[i].seats_avail == 0) {
                            printf("Sorry, the selected bus trip is already full.\n");
                        } else {
                            bus[i].seats_avail--;
                            new_passenger.seat_no = bus[i].seat_no++;
                            passengers[num_passengers++] = new_passenger;
                            printf("Passenger added successfully!\n");
                        }
                        break;
                    }
                }
                if (!found_trip) {
                    printf("Invalid trip code. Please try again.\n");
                }
                break;
            }

            case 3: {
                printf("Enter the name of the passenger to delete: ");
                char name[50];
                scanf("%s", name);
                Delete_passenger(passengers, &num_passengers, name);
                break;
            }

            case 4: {
                printf("Enter passenger seat number to edit: ");
                int seat_no, found = 0;
                scanf("%d", &seat_no);
                for (int i = 0; i < num_passengers; i++) {
                    if (passengers[i].seat_no == seat_no) {
                        editPassenger(&passengers[i]);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    printf("Passenger not found.\n");
                }
                break;
            }

            case 5:
                list_tours(tour, 7);
                break;

            case 6:
                editTour(tour, 7);
                break;

            case 7:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
