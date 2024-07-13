#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

double file_mean(const char *filename) {
    FILE *file = fopen(filename, "r");
    double a, sum, result;
    int count = 0;

    while (fscanf(file, "%lf", &a) != EOF) {
        sum += a;
        count++;
    }

    result = sum / count;
    fclose(file);

    return result;
}


void file_edit(const char *input_filename) {
    char output_filename[100] = {0};
    int i = 0;
    while (input_filename[i] != '.') {
        output_filename[i] = input_filename[i];
        i++;
    }

    strcat(output_filename, "_result.txt");

    FILE *input_file = fopen(input_filename, "r");
    FILE *result_file = fopen(output_filename, "wb");

    double a;
    double mean = file_mean(input_filename);
    i = 1;
    double sum_sigma = 0;
    while (fscanf(input_file, "%lf", &a) != EOF) {
        double res1 = a - mean;
        double res2 = res1 * res1;
        sum_sigma += res2;
        
        fprintf(result_file, "%2d %10.4lf %10.4lf %10.4lf\n", i, a, res1, res2);
        i++;
    }

    double real_sigma = sqrt(sum_sigma / (i - 2));

    fprintf(result_file, "\nmean  = %.4lf\n", mean);
    fprintf(result_file, "sigma = %.4lf\n", real_sigma);
    fprintf(result_file, "sum_sigma = %.4lf\n", sum_sigma);

    fclose(input_file);
    fclose(result_file);
}

int main() {
    char name[256] = "table.txt";
    file_edit(name);
    return 0;
}