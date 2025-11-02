#include <stdio.h>

#define ROWS 3
#define COLS 3


#define POWER_BIT 0
#define OVERLOAD_BIT 1
#define MAINTENANCE_BIT 2


void updateSectorStatus(int grid[ROWS][COLS]);
void querySectorStatus(int grid[ROWS][COLS]);
void runDiagnostic(int grid[ROWS][COLS]);

int main() {
    int grid[ROWS][COLS] = {0}; 
    int choice;

    while (1) {
        printf("\n===== IESCO POWER GRID MONITORING SYSTEM =====\n");
        printf("1. Update Sector Status\n");
        printf("2. Query Sector Status\n");
        printf("3. Run System Diagnostic\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                updateSectorStatus(grid);
                break;
            case 2:
                querySectorStatus(grid);
                break;
            case 3:
                runDiagnostic(grid);
                break;
            case 4:
                printf("Exiting system... Thank you!\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void updateSectorStatus(int grid[ROWS][COLS]) {
    int row, col, flag, action;

    printf("Enter sector row (0-%d): ", ROWS - 1);
    scanf("%d", &row);
    printf("Enter sector column (0-%d): ", COLS - 1);
    scanf("%d", &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    printf("\nSelect flag to modify:\n");
    printf("0 - Power Status (1 = ON, 0 = OFF)\n");
    printf("1 - Overload Warning (1 = ON, 0 = OFF)\n");
    printf("2 - Maintenance Required (1 = YES, 0 = NO)\n");
    printf("Enter flag bit (0-2): ");
    scanf("%d", &flag);

    if (flag < 0 || flag > 2) {
        printf("Invalid flag!\n");
        return;
    }

    printf("Enter action (1 = Set, 0 = Clear): ");
    scanf("%d", &action);

    if (action == 1)
        grid[row][col] |= (1 << flag);    
    else
        grid[row][col] &= ~(1 << flag);   

    printf("Sector (%d,%d) updated successfully!\n", row, col);
}

void querySectorStatus(int grid[ROWS][COLS]) {
    int row, col, value;

    printf("Enter sector row (0-%d): ", ROWS - 1);
    scanf("%d", &row);
    printf("Enter sector column (0-%d): ", COLS - 1);
    scanf("%d", &col);

    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        printf("Invalid coordinates!\n");
        return;
    }

    value = grid[row][col];
    printf("\nStatus for sector (%d, %d):\n", row, col);

    if (value & (1 << POWER_BIT))
        printf("- Power: ON\n");
    else
        printf("- Power: OFF\n");

    if (value & (1 << OVERLOAD_BIT))
        printf("- Overload: WARNING\n");
    else
        printf("- Overload: NORMAL\n");

    if (value & (1 << MAINTENANCE_BIT))
        printf("- Maintenance: REQUIRED\n");
    else
        printf("- Maintenance: NOT REQUIRED\n");
}

void runDiagnostic(int grid[ROWS][COLS]) {
    int i, j;
    int overloadCount = 0, maintenanceCount = 0;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grid[i][j] & (1 << OVERLOAD_BIT))
                overloadCount++;
            if (grid[i][j] & (1 << MAINTENANCE_BIT))
                maintenanceCount++;
        }
    }

    printf("\n===== SYSTEM DIAGNOSTIC REPORT =====\n");
    printf("Total overloaded sectors: %d\n", overloadCount);
    printf("Total sectors requiring maintenance: %d\n", maintenanceCount);
    printf("====================================\n");
}

