/*
 * Bus Reservation System Mini Project in C
 * Features: Search, Book Ticket (Text File Save), Cancel Ticket, View History (Text File Read)
 */

#include <stdio.h>
#include <string.h>
#include <strings.h> // For strcasecmp

#ifdef _WIN32
#define strcasecmp _stricmp   // Windows compilers (MSVC) ke liye
#endif

// Structure to store Bus details
struct Bus {
    int bus_no, total_seats, available_seats;
    char destination[50];
    char timing[10];
};

int main() {
    int choice;

    // Inserting information of buses
    struct Bus buses[10] = {
        {101, 40, 40, "Delhi", "08:00 AM"},
        {102, 50, 50, "Jaipur", "10:30 AM"},
        {103, 30, 30, "Agra", "01:00 PM"},
        {104, 45, 45, "Delhi", "04:15 PM"},
        {105, 60, 60, "Chandigarh", "09:00 PM"},
        {106, 40, 40, "Mumbai", "07:00 AM"},
        {107, 50, 50, "Jaipur", "11:00 AM"},
        {108, 35, 35, "Pune", "06:30 PM"},
        {109, 55, 55, "Delhi", "10:00 PM"},
        {110, 50, 50, "Agra", "03:30 PM"}
    };

    do {
        printf("\n=========================================\n");
        printf("        BUS RESERVATION SYSTEM           \n");
        printf("=========================================\n");
        printf("1. Search Buses by Destination\n");
        printf("2. Book Ticket\n");
        printf("3. Cancel Ticket\n");
        printf("4. View Booking History\n");
        printf("5. Exit\n");
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char dest[50];
                int found = 0;
                printf("Enter destination city to search: ");
                scanf("%s", dest);
                printf("\n--- Available Buses to %s ---\n", dest);
                printf("%-10s %-15s %-15s %-15s\n", "Bus No", "Destination", "Timing", "Available Seats");
                for (int i = 0; i < 10; i++) {
                    if (strcasecmp(buses[i].destination, dest) == 0) {
                        printf("%-10d %-15s %-15s %-15d\n", buses[i].bus_no, buses[i].destination, buses[i].timing, buses[i].available_seats);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No buses found for this destination.\n");
                }
                break;
            }
            case 2: {
                int bno, seats, found = 0;
                char name[50], phone[15];
                printf("Enter Bus Number: ");
                scanf("%d", &bno);
                for (int i = 0; i < 10; i++) {
                    if (buses[i].bus_no == bno) {
                        found = 1;
                        printf("Enter Passenger Name: ");
                        scanf("%s", name);
                        printf("Enter Phone Number: ");
                        scanf("%s", phone);
                        printf("Enter Number of Seats to Book: ");
                        scanf("%d", &seats);

                        if (seats <= buses[i].available_seats && seats > 0) {
                            buses[i].available_seats -= seats;

                            // Save to file
                            FILE *file = fopen("bus_bookings.txt", "a");
                            if (file != NULL) {
                                fprintf(file, "Bus No: %d | Name: %s | Phone: %s | Seats Booked: %d | Destination: %s\n",
                                        buses[i].bus_no, name, phone, seats, buses[i].destination);
                                fclose(file);
                                printf("Ticket(s) booked successfully!\n");
                            } else {
                                printf("Error opening file for saving booking.\n");
                            }
                        } else {
                            printf("Not enough seats available or invalid seat count!\n");
                        }
                        break;
                    }
                }
                if (!found) {
                    printf("Invalid Bus Number!\n");
                }
                break;
            }
            case 3: {
                int bno, seats, found = 0;
                printf("Enter Bus Number to cancel tickets: ");
                scanf("%d", &bno);
                for (int i = 0; i < 10; i++) {
                    if (buses[i].bus_no == bno) {
                        found = 1;
                        printf("Enter number of seats to cancel: ");
                        scanf("%d", &seats);
                        if (seats > 0 && (buses[i].total_seats - buses[i].available_seats) >= seats) {
                            buses[i].available_seats += seats;
                            printf("Successfully cancelled %d seat(s).\n", seats);
                        } else {
                            printf("Invalid seat cancellation count!\n");
                        }
                        break;
                    }
                }
                if (!found) {
                    printf("Bus Number not found!\n");
                }
                break;
            }
            case 4: {
                FILE *file = fopen("bus_bookings.txt", "r");
                if (file == NULL) {
                    printf("No booking history found.\n");
                } else {
                    char line[256];
                    printf("\n--- Booking History ---\n");
                    while (fgets(line, sizeof(line), file) != NULL) {
                        printf("%s", line);
                    }
                    fclose(file);
                }
                break;
            }
            case 5:
                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice! Please enter between 1 and 5.\n");
        }
    } while (choice != 5);

    return 0;
}
