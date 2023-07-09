#include <stdio.h>
#include <string.h>

typedef struct {
    char name[20];
    char color[20];
    double price;
    int serial_number;
    int quantity;
}furniture;

int find_furniture_count() {
    FILE *fp;
    fp = fopen("furniture_database.txt","r");
    char c = fgetc(fp);
    int count = 0;
    while (c != EOF) {
        if (c == '\n') {
            count++;
        }
        c = fgetc(fp);
    }
    return count;
}

void update_furniture_database(furniture database[find_furniture_count()]) {
    int fcount = find_furniture_count();
    FILE *fp = fopen("furniture_database.txt","r");
    char c;
    while ((c = fgetc(fp)) != '\n');
    for (int i = 0; i < fcount; i++) {
        fscanf(fp,"%[^,]s", database[i].name);
        fgetc(fp);
        fscanf(fp,"%[^,]s", database[i].color);
        fgetc(fp);
        fscanf(fp,"%lf", &database[i].price);
        fgetc(fp);
        fscanf(fp,"%d", &database[i].serial_number);
        fgetc(fp);
        fscanf(fp,"%d", &database[i].quantity);
        fgetc(fp);
    }
    fclose(fp);
}

void list_all_furnitures() {
    int fcount = find_furniture_count();
    furniture database[fcount];
    update_furniture_database(database);
    for (int i = 0; i < fcount; i++) {
        printf("\nName: %s\n"
        "Color: %s\n"
        "Price: %.2f\n"
        "Serial Number: %d\n"
        "Quantity: %d\n",database[i].name,database[i].color,database[i].price,database[i].serial_number,database[i].quantity);
    }
    
}

void add_new_furniture() {
    furniture new_furniture;
    printf("Please enter the properties of new furniture(Name, color, price, serial number, quantity): ");
    scanf("%s %s %lf %d %d",new_furniture.name, new_furniture.color, &new_furniture.price, &new_furniture.serial_number, &new_furniture.quantity);

    while (new_furniture.price <= 0) {
        printf("Price can not be smaller or equal to 0. Please enter a valid price: ");
        scanf("%lf",&new_furniture.price);
    }
    while (new_furniture.serial_number < 100000 || new_furniture.serial_number > 999999) {
        printf("Invalid serial number, please enter a 6-digit serial number: ");
        scanf("%d",&new_furniture.serial_number);
    }
    while (new_furniture.quantity <= 0) {
        printf("Quantity can not be smaller or equal to 0. Please enter a valid quantity: ");
        scanf("%d",&new_furniture.quantity);
    }
    
    FILE *fp = fopen("furniture_database.txt","a");
    fprintf(fp,"\n%s,%s,%.2f,%d,%d",new_furniture.name, new_furniture.color, new_furniture.price, new_furniture.serial_number, new_furniture.quantity);
    fclose(fp);
}

void remove_furniture() {
    int rindex;
    int fcount = find_furniture_count();
    furniture database[fcount];
    update_furniture_database(database);
    printf("Enter the index of product you want to remove(0-%d): ",fcount-1);
    scanf("%d", &rindex);

    while (rindex < 0 || rindex > (fcount-1)) {
        printf("Invalid index number, Please enter a valid one: ");
        scanf("%d", &rindex);
    }

    FILE *fp = fopen("furniture_database.txt","w");
    fprintf(fp,"Name,Color,Price,Serial Number,Quantity");

    for (int i = 0; i < fcount; i++) {
        if (i != rindex) {
            fprintf(fp,"\n%s,%s,%.2f,%d,%d",database[i].name, database[i].color, database[i].price, database[i].serial_number, database[i].quantity);
        }
    }
    fclose(fp);
    
}

int recursive_search(int index, int fcount, furniture db[], char indicator, char property_value[20]) {

    if (index == fcount) {
        return 1; // Search complated
    }

    if (indicator == 'n') {
        if (strcmp(db[index].name,property_value) == 0) {
            printf("\nName: %s\n"
            "Color: %s\n"
            "Price: %.2f\n"
            "Serial Number: %d\n"
            "Quantity: %d\n",db[index].name,db[index].color,db[index].price,db[index].serial_number,db[index].quantity); 
        }    
    }
    else {
        if (strcmp(db[index].color,property_value) == 0) {
            printf("\nName: %s\n"
            "Color: %s\n"
            "Price: %.2f\n"
            "Serial Number: %d\n"
            "Quantity: %d\n",db[index].name,db[index].color,db[index].price,db[index].serial_number,db[index].quantity); 
        }  
    }
    return recursive_search(index+1, fcount, db, indicator, property_value);

    
    

    
    
}

void search_furniture() {
    int fcount = find_furniture_count();
    furniture database[fcount];
    update_furniture_database(database);

    char property;
    char property_value[20];
    char indicator;
    printf("Select a property to make search:\n\n"
    "1-Name\n"
    "2-Color\n\n"
    ">");
    scanf(" %c", &property);
    while ((getchar()) != '\n'); // Clear input buffer

    switch (property)
    {
    case '1':
        printf("Enter the name of product: ");
        scanf("%[^\n]s", property_value);
        recursive_search(0,find_furniture_count(),database,'n',property_value);
        break;
    case '2':
        printf("Enter the color of product: ");
        scanf("%[^\n]s", property_value);
        recursive_search(0,find_furniture_count(),database,'c',property_value);
        break;
    default:
        printf("Invalid property selection!");
        break;
    }
}

int main() {
    char selection;
    while (selection != '5') {
        printf("******************\n"
        "Welcome to database of furniture shop\n"
        "1-See all furnitures\n"
        "2-Add a new furniture\n"
        "3-Remove furniture\n"
        "4-Search product\n"
        "5- Exit\n"
        "\n> ");

        scanf(" %c", &selection);
        while ((getchar()) != '\n'); // Clear input buffer

        switch (selection)
        {
        case '1':
            list_all_furnitures();
            break;
        case '2':
            add_new_furniture();
            break;
        case '3':
            remove_furniture();
            break;
        case '4':
            search_furniture();
            break;
        case '5':
            printf("Program terminated...\n");
            break;
        default:
            printf("ERROR!\n");
            break;
        }
    }
    return 0;
}