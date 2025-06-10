#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TRILLION 1e12
#define GITHUB_USERNAME "your-username"  // Replace with your actual GitHub username
#define VERSION "1.1"
#define RELEASE_DATE "2024-06-11"

typedef struct {
    double total;
    double muscle;
    double blood;
    double neuron;
    double skin;
    double other;
} CellCount;

// Function declarations
double get_valid_age(void);
CellCount calculate_cell_distribution(double age);
void display_report(double age, CellCount count);
void display_header(void);
void display_footer(void);

int main(void) {
    display_header();
    
    double age = get_valid_age();
    CellCount cell_count = calculate_cell_distribution(age);

    display_report(age, cell_count);
    display_footer();

    return 0;
}

void display_header(void) {
    printf("====== CellCycle: Human Cell Estimator ======\n");
    printf("Version: %s | Released: %s\n", VERSION, RELEASE_DATE);
    printf("GitHub: github.com/%s\n\n", GITHUB_USERNAME);
}

void display_footer(void) {
    time_t now;
    time(&now);
    printf("\nReport generated on: %s", ctime(&now));
    printf("For more projects, visit: github.com/%s\n", GITHUB_USERNAME);
}

double get_valid_age(void) {
    double age;
    while (1) {
        printf("Enter your age (0.0 to 120.0): ");
        if (scanf("%lf", &age) != 1 || age < 0 || age > 120) {
            printf("Invalid input. Please enter a valid age.\n");
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    }
    return age;
}

CellCount calculate_cell_distribution(double age) {
    CellCount count;
    double base_cell_count;

    if (age < 1.0) {
        base_cell_count = 1.0 * TRILLION * (0.5 + age * 0.5); // Gradual increase in first year
    } else if (age <= 5.0) {
        base_cell_count = 5.0 * TRILLION + (age * 2.0 * TRILLION);
    } else if (age <= 20.0) {
        base_cell_count = 20.0 * TRILLION + ((age - 5.0) * 1.14 * TRILLION); // Adjusted growth rate
    } else {
        // Slight decrease after 30, more after 60
        double adjustment = age > 60 ? 0.9975 : (age > 30 ? 0.999 : 1.0);
        base_cell_count = 37.2 * TRILLION * pow(adjustment, age - 20);
    }

    // Cell type percentages with age adjustments
    double muscle_factor = 0.20 * (1.0 - 0.002 * (age > 30 ? age - 30 : 0));
    double blood_factor = 0.25 * (1.0 - 0.001 * (age > 40 ? age - 40 : 0));
    double neuron_factor = 0.05 * (1.0 - 0.003 * (age > 20 ? age - 20 : 0));
    double skin_factor = 0.15 * (1.0 + 0.001 * age); // Skin cells increase slightly

    count.total = base_cell_count;
    count.muscle = base_cell_count * muscle_factor;
    count.blood  = base_cell_count * blood_factor;
    count.neuron = base_cell_count * neuron_factor;
    count.skin   = base_cell_count * skin_factor;
    count.other  = base_cell_count - (count.muscle + count.blood + count.neuron + count.skin);

    return count;
}

void display_report(double age, CellCount count) {
    printf("\n========= Estimated Cell Count Report =========\n");
    printf("Age: %.1f years\n", age);
    printf("-------------------------------------------------\n");
    printf("Total Cells Estimated: %'.2lf trillion\n", count.total / TRILLION);
    printf(" - Muscle Cells:        %'.2lf trillion\n", count.muscle / TRILLION);
    printf(" - Blood Cells:         %'.2lf trillion\n", count.blood / TRILLION);
    printf(" - Neurons:             %'.2lf trillion\n", count.neuron / TRILLION);
    printf(" - Skin Cells:          %'.2lf trillion\n", count.skin / TRILLION);
    printf(" - Other Cells:         %'.2lf trillion\n", count.other / TRILLION);
    printf("-------------------------------------------------\n");
    printf("Note: These values are approximations based on current biological models.\n");
}
