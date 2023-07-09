#include <stdio.h>
#include <math.h>
// Declare a struct for 3x3 matrix
typedef struct {
    double m[3][3];
    double det;
} matrix;

// Function that prints matrix
void print_matrix(matrix m) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf("%.4f %.4f %.4f\n", m.m[i][0], m.m[i][1], m.m[i][2]);
    }
}
// Function that calculates determinant of parameter matrix
double determinant(matrix m) {
    double det = 0;
    det += m.m[0][0] * (m.m[1][1] * m.m[2][2] - m.m[1][2] * m.m[2][1]);
    det -= m.m[0][1] * (m.m[1][0] * m.m[2][2] - m.m[1][2] * m.m[2][0]);
    det += m.m[0][2] * (m.m[1][0] * m.m[2][1] - m.m[1][1] * m.m[2][0]);
    // Return determinant
    return det;
}

// Declare struct for vector
typedef struct {
    double x,y,z;
} vector;

// PART 2 FUNC
double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec) {
    // Calculate dot product
    double dot_product = (vec_1.x * vec_2.x) + (vec_1.y * vec_2.y) + (vec_1.z * vec_2.z);
    // Calculate magnitude of first vector
    double vec_1_mag = sqrt(pow(vec_1.x,2)+pow(vec_1.y,2)+pow(vec_1.z,2));
    // Calculate magnitude of second vector
    double vec_2_mag = sqrt(pow(vec_2.x,2)+pow(vec_2.y,2)+pow(vec_2.z,2));
    // Calculate cos(theta)
    double cos_theta = dot_product/(vec_1_mag * vec_2_mag);
    // Calculate arccos(cos(theta)) in radians
    double theta = acos(cos_theta);
    // Convert radians to degrees
    theta = theta*180.0/M_PI;
    // Cross product vectors and store results in output vector
    output_vec->x = vec_1.y*vec_2.z - vec_1.z*vec_2.y;
    output_vec->y = vec_1.z*vec_2.x - vec_1.x*vec_2.z;
    output_vec->z = vec_1.x*vec_2.y - vec_1.y*vec_2.x;
    // Return theta
    return theta;    
}
// Declare struct for third order polynomial
typedef struct {
    double a,b,c,d;
    } third_order_polynomial;
// Declare struct for result polynomial
typedef struct {
    double a,b,c,d,e,f,g;
    double result;
    } polynomial;
    

polynomial get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b) {
    // Calculate multipled polynomial
    polynomial multipled = {p1.a+p2.a,p1.a+p2.b+p1.b+p2.a,p1.a+p2.c+p1.b+p2.b+p1.c+p2.a,p1.a+p2.d+p1.b+p2.c+p1.c+p2.b+p1.d+p2.a,p1.b+p2.d+p1.c+p2.c+p1.d+p2.b,p1.c+p2.d+p1.d,p2.c,p1.d*p2.d};
    // Calculate lower limit integral
    double lower = (multipled.a*pow(a,7)/7.0)+(multipled.b*pow(a,6)/6.0)+(multipled.c*pow(a,5)/5.0)+(multipled.d*pow(a,4)/4.0)+(multipled.e*pow(a,3)/3.0)+(multipled.f*pow(a,2)/2.0)+multipled.g*a;
    // Calculate upper limit integral
    double upper = (multipled.a*pow(b,7)/7.0)+(multipled.b*pow(b,6)/6.0)+(multipled.c*pow(b,5)/5.0)+(multipled.d*pow(b,4)/4.0)+(multipled.e*pow(b,3)/3.0)+(multipled.f*pow(b,2)/2.0)+multipled.g*b;
    // Calculate result
    multipled.result = upper-lower;
    // Return polynomial struct
    return multipled;
}

int main() {
    printf("\n-----PART1-----\n");
    matrix initial_m = {{{1, 0.9134, 0.2785}, {0.9058, 0.6324, 0.5469}, {0.1270, 0.0975, 0.9575}}, 0};
    // Print matrix
    print_matrix(initial_m);
    // Calculate determinant
    initial_m.det = determinant(initial_m);
    // Print determinant
    printf("\nDeterminant of initial matrix: %.2f\n", initial_m.det);
    // Declare vectors
    vector vec1 = {15, -20, 34};
    vector vec2 = {21, 10, -90};
    vector result;
    printf("\n-----PART2-----\n");
    printf("Vec1 (%.2f,%.2f,%.2f)\nVec2 (%.2f,%.2f,%.2f)\n",vec1.x,vec1.y,vec1.z,vec2.x,vec2.y,vec2.z);
    // Find angle between them
    double angle = find_orthogonal(vec1,vec2,&result);
    // Print angle and cross-product vector
    printf("Result vector: (%.2f,%.2f,%.2f)\nAngle: %.2f",result.x,result.y,result.z,angle);
    printf("\n-----PART3-----\n");
    // Declare variables for coefficents and get them from user
    double a1,a2,b1,b2,c1,c2,d1,d2;
    printf("\nax^3+bx^2+cx+d\nEnter coefficents for polynomial1 by seperating them with spaces:\n");
    scanf("%lf %lf %lf %lf",&a1,&b1,&c1,&d1);
    third_order_polynomial pol1 = {a1,b1,c1,d1}; // Declare a struct for 3rd order polynomial
    printf("ax^3+bx^2+cx+d\nEnter coefficents for polynomial2 by seperating them with spaces:\n");
    scanf("%lf %lf %lf %lf",&a2,&b2,&c2,&d2);
    third_order_polynomial pol2 = {a2,b2,c2,d2}; // Declare a struct for 3rd order polynomial
    int a,b; // Limits
    printf("Enter integral upper limit and lower limit by seperating them with spaces: ");
    scanf("%d %d",&a,&b);
    polynomial res_pol = get_integral(pol1,pol2,a,b); // Func call
    printf("Multipled Polynomial: (%.2lf)x^6+(%.2lf)x^5+(%.2lf)x^4+(%.2lf)x^3+(%.2lf)x^2+(%.2lf)x+(%.2lf)",res_pol.a,res_pol.b,res_pol.c,res_pol.d,res_pol.e,res_pol.f,res_pol.g);
    printf("\nIntegral from %d to %d: %lf",a,b,res_pol.result);
    return 0;
}