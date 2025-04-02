#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000        
#define MAX_LINE_LENGTH 256

// Массив указателей на строки
char *lines[MAX_LINES];       

// Счётчик строк
int line_count = 0;

// Загрузка в память
void load_file(char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Не могу открыть файл! Создаю новый.\n");
        return;
    }
    
    char buffer[MAX_LINE_LENGTH];
    
    while (fgets(buffer, MAX_LINE_LENGTH, file) && line_count < MAX_LINES) {

        // Убираем \n
        buffer[strcspn(buffer, "\n")] = 0;  

        // Выделяем память
        lines[line_count] = (char *)malloc(strlen(buffer) + 1);  
        
        // Копируем строку
        strcpy(lines[line_count], buffer);  
        
        line_count++;
    }
    
    fclose(file);
}

// Сохраняет строки в файл
void save_file(char *filename) {
    FILE *file = fopen(filename, "w");

    for (int i = 0; i < line_count; i++) {

        // Записываем строку
        fprintf(file, "%s\n", lines[i]);  
    }
    
    fclose(file);
}

// Добавляет новой строки
void add_line() {
    if (line_count >= MAX_LINES) {
        printf("Слишком много строк!\n");

        return;
    }

    char buffer[MAX_LINE_LENGTH];

    printf("Введи строку: ");

    fgets(buffer, MAX_LINE_LENGTH, stdin);

    // Убираем \n
    buffer[strcspn(buffer, "\n")] = 0;  
    
    // Выделяем память
    lines[line_count] = (char *)malloc(strlen(buffer) + 1);  
    
    // Копируем строку
    strcpy(lines[line_count], buffer);  
    
    line_count++;
}

// Редактировать строки
void edit_line(int line_num) {
    if (line_num < 1 || line_num > line_count) {
        printf("Такой строки нет!\n");

        return;
    }

    char buffer[MAX_LINE_LENGTH];

    printf("Введи новую строку для %d: ", line_num);
    
    fgets(buffer, MAX_LINE_LENGTH, stdin);
    
    // Убирает \n
    buffer[strcspn(buffer, "\n")] = 0;  
    
    // Освобождает старую память
    free(lines[line_num - 1]);  
    
    // Новая память
    lines[line_num - 1] = (char *)malloc(strlen(buffer) + 1);  
    
    // Копирует новую строку
    strcpy(lines[line_num - 1], buffer);  
}

// Удаляет строки
void delete_line(int line_num) {
    if (line_num < 1 || line_num > line_count) {
        printf("Такой строки нет!\n");

        return;
    }

    // Освобождаем память
    free(lines[line_num - 1]);  
    
    for (int i = line_num - 1; i < line_count - 1; i++) {

        // Сдвигаем строки
        lines[i] = lines[i + 1];  
    }

    line_count--;
}

// Показывает все строки
void show_lines() {
    if (line_count == 0) {
        printf("Файл пуст!\n");
        
        return;
    }

    for (int i = 0; i < line_count; i++) {

        // Выводит номер и строку
        printf("%d: %s\n", i + 1, lines[i]);  
    }
}

// Главная функция
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Используй: %s <имя_файла>\n", argv[0]);  

        return 1;
    }

    // Имя файла с аргумента
    char *filename = argv[1];

    // Загружает файл
    load_file(filename);  
    
    while (1) {
        printf("\n1. Показать строки\n2. Добавить строку\n3. Изменить строку\n4. Удалить строку\n5. Сохранить и выйти\nВыбери: ");
        int choice;
        scanf("%d", &choice);

        // Убирает \n после stdin
        getchar();  
        
        if (choice == 1) {
            show_lines();
        } 
        else if (choice == 2) {
            add_line();
        } 
        else if (choice == 3) {
            int line_num;
        
            printf("Какую строку изменить? ");
            scanf("%d", &line_num);
            
            // Убирает \n после stdin
            getchar();
            edit_line(line_num);
        }
        else if (choice == 4) {
            int line_num;
        
            printf("Какую строку удалить? ");
            scanf("%d", &line_num);
            
            // Убирает \n после stdin
            getchar();
            delete_line(line_num);
        }
        else if (choice == 5) {
            
            // Сохраняет файл
            save_file(filename);  
        
            for (int i = 0; i < line_count; i++) {

                // Освобождает память
                free(lines[i]);  
            }
        
            break;
        }
    }

    return 0;
}