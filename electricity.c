#include <stdio.h>

#define MAX 100

struct Customer {
    int id;
    char name[50];
    int units;
    float bill;
};

struct Customer customers[MAX];
int count = 0;

float calculateBill(int units) {
    float bill = 0;

    if (units <= 100) {
        bill = units * 3.0;
    }
    else if (units <= 200) {
        bill = (100 * 3.0) +
               ((units - 100) * 5.0);
    }
    else {
        bill = (100 * 3.0) +
               (100 * 5.0) +
               ((units - 200) * 7.0);
    }

    return bill;
}

void loadData() {
    FILE *file = fopen("bills.txt", "r");

    if (file == NULL) {
        return;
    }

    while (count < MAX &&
           fscanf(file, "%d %49s %d %f",
                  &customers[count].id,
                  customers[count].name,
                  &customers[count].units,
                  &customers[count].bill) == 4) {
        count++;
    }

    fclose(file);
}

void saveData() {
    FILE *file = fopen("bills.txt", "w");

    if (file == NULL) {
        printf("Error saving file!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %d %.2f\n",
                customers[i].id,
                customers[i].name,
                customers[i].units,
                customers[i].bill);
    }

    fclose(file);
}

int findCustomer(int id) {
    for (int i = 0; i < count; i++) {
        if (customers[i].id == id) {
            return i;
        }
    }

    return -1;
}

void addCustomer() {
    if (count >= MAX) {
        printf("Customer limit reached!\n");
        return;
    }

    struct Customer c;

    printf("Enter Customer ID: ");
    if (scanf("%d", &c.id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    if (findCustomer(c.id) != -1) {
        printf("Customer ID already exists!\n");
        return;
    }

    printf("Enter Customer Name: ");
    scanf("%49s", c.name);

    printf("Enter Units Consumed: ");
    if (scanf("%d", &c.units) != 1 || c.units < 0) {
        printf("Invalid units!\n");
        return;
    }

    c.bill = calculateBill(c.units);

    customers[count] = c;
    count++;

    saveData();

    printf("\nBill generated successfully!\n");
    printf("Customer: %s\n", c.name);
    printf("Units: %d\n", c.units);
    printf("Total Bill: Rs. %.2f\n", c.bill);
}

void displayCustomers() {
    if (count == 0) {
        printf("No customer records found.\n");
        return;
    }

    printf("\n--- Electricity Bill Records ---\n");

    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Units: %d | Bill: Rs. %.2f\n",
               customers[i].id,
               customers[i].name,
               customers[i].units,
               customers[i].bill);
    }
}

void searchCustomer() {
    int id;

    printf("Enter Customer ID: ");

    if (scanf("%d", &id) != 1) {
        printf("Invalid ID!\n");
        return;
    }

    int index = findCustomer(id);

    if (index == -1) {
        printf("Customer not found!\n");
    }
    else {
        printf("\nCustomer Found!\n");
        printf("Name: %s\n", customers[index].name);
        printf("Units: %d\n", customers[index].units);
        printf("Bill: Rs. %.2f\n", customers[index].bill);
    }
}

int main() {
    int choice;

    loadData();

    while (1) {
        printf("\n===== ELECTRICITY BILL SYSTEM =====\n");
        printf("1. Add Customer Bill\n");
        printf("2. Display All Bills\n");
        printf("3. Search Customer\n");
        printf("4. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addCustomer();
                break;

            case 2:
                displayCustomers();
                break;

            case 3:
                searchCustomer();
                break;

            case 4:
                printf("Program closed.\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
