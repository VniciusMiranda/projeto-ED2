#include "airport_menu.h"


char* airport_menu_options[] = {
    "inserir novo aeroporto",
    "deletar aeroporto",
    "atualizar aeroporto",
    "ver aeroportos",
    "inserir nova conexao",
    "inserir novo aviao",
    "sair do menu",
    "sair da aplicacao"
};
int airport_menu_options_size = ARRAY_SIZE(airport_menu_options);


char* airport_fields_options[] = {
    "id",
    "nome",
    "codigo",
    "cidade",
    "pais",
};
int airport_fields_options_size = ARRAY_SIZE(airport_fields_options);


Airport_t* get_airport_from_user(FILE* f) {
    char name[AIRPORT_NAME_MAX];
    char code[AIRPORT_CODE_MAX];
    Location_t loc;

    clear_input_buffer();

    print_line(f, 80, '-');
    fprintf(f, "nome do aeroporto:");
    scanf ("%[^\n]%*c", name);

    fprintf(f, "codigo do aeroporto:");
    scanf ("%[^\n]%*c", code);

    fprintf(f, "cidade:");
    scanf ("%[^\n]%*c", loc.city);

    fprintf(f, "pais:");
    scanf ("%[^\n]%*c", loc.country);

    Airport_t* airport = create_airport(name, code, &loc);
    if(!airport) return NULL;

    return airport;
}

get_attr_func get_airport_field(FILE* f) {
    clear_input_buffer();
    set_color(f, WHITE, true);
    fprintf(f, "Por qual campo voce deseja filtrar?\n");
    reset_color(f);

    print_menu_options(f, BLUE, airport_fields_options, airport_fields_options_size);
    int selected_option = get_selected_option(f, BLUE, airport_fields_options, airport_fields_options_size);
    clear_input_buffer();


    switch(selected_option) {
        char country[COUNTRY_NAME_MAX];
        char name[AIRPORT_NAME_MAX];
        char code[AIRPORT_CODE_MAX];
        char city[CITY_NAME_MAX];
        long int id;

        case 1:
            return get_airport_id;
        
        case 2:
           return get_airport_name;

        case 3: 
            return get_airport_code;
           

        case 4: 
            return get_airport_city;

        case 5:
            return get_airport_country;

        default:
            return NULL;
    }
}

search_func get_airport_filter(FILE* f, void** field_value) {
    clear_input_buffer();
    set_color(f, WHITE, true);
    fprintf(f, "Por qual campo voce deseja filtrar?\n");
    reset_color(f);

    print_menu_options(f, BLUE, airport_fields_options, airport_fields_options_size);
    int selected_option = get_selected_option(f, BLUE, airport_fields_options, airport_fields_options_size);
    clear_input_buffer();


    switch(selected_option) {
        char country[COUNTRY_NAME_MAX];
        char name[AIRPORT_NAME_MAX];
        char code[AIRPORT_CODE_MAX];
        char city[CITY_NAME_MAX];
        long int id;

        case 1:
         print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "id:");
            scanf("%ld", &id);
            reset_color(f);

            *field_value = (void*) &id; 
            return find_airport_by_id;
        
        case 2:
            print_line_with_color(f, 80, 0, YELLOW, true);
            
            set_color(f, WHITE, true);
            fprintf(f, "nome:");
            scanf ("%[^\n]%*c", name);

            reset_color(f);

            *field_value = (void*) name; 
            return find_airport_by_name;

        case 3:
            print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "codigo:");
            scanf ("%[^\n]%*c", code);

            reset_color(f);

            *field_value = (void*) code; 
            return find_airport_by_code;
           

        case 4:
            print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "cidade:");
            scanf ("%[^\n]%*c", city);
            reset_color(f);

            *field_value = (void*) city; 
            return find_airport_by_city;

        case 5:
            print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "pais:");
            scanf ("%[^\n]%*c", country);
            reset_color(f);

            *field_value = (void*) country; 
            return find_airport_by_country;

        default:
            return NULL;
    }
}


int _insert_airport(FILE* f) {
    Airport_t* airport = get_airport_from_user(f);

    print_airport(f, (void*) airport, YELLOW, true);

    if(write_airport(airport)) return ERR;

    return OK;
}

int _delete_airport(FILE* f) {
    clear_input_buffer();
    
    set_color(f, YELLOW, true);
    print_line(f, 80, 0);
    reset_color(f);

    char option;

    set_color(f, WHITE, true);
    fprintf(f, "deseja filtrar por algum atributo?(y/n)\n");
    fprintf(f, ">");
    scanf("%c", &option);
    clear_input_buffer();

    if(option == 'n' || option == 'N') 
    {
        print_warning(f, "todos os registros serao apagados!");
        fprintf(f, "deseja continuar?(y/n)\n");
        fprintf(f, ">");
        scanf("%c", &option);
        reset_color(f);

        if(option == 'n' || option == 'N') {
            set_color(f, RED, true);
            fprintf(f, "operacao cancelada!\n");
            reset_color(f);
            return ERR;
        } 

        if(recreate_database_table(TABLE_NAME_AIRPORT) == ERR)
            return ERR;
        else {
            LAST_VALID_ID_AIRPORT = 0;
            return OK;
        }
    }

    void* field;
    bool (*search_func)(void*, void*) = get_airport_filter(f, &field);    
    return delete_airport(search_func, field);
}


int _update_airport(FILE* f) {
    clear_input_buffer();
    set_color(f, WHITE, true);
    fprintf(f, "insira os novos campos:\n");
    reset_color(f);

    Airport_t* airport = get_airport_from_user(f);
    if(!airport) return ERR;
    char option;

    set_color(f, WHITE, true);
    fprintf(f, "deseja filtrar por algum atributo?(y/n)\n");
    fprintf(f, ">");
    scanf("%c", &option);
    clear_input_buffer();

    if(option == 'n' || option == 'N') 
    {
        print_warning(f, "todos os registros serao atualizados para esses novos campos!");
        fprintf(f, "deseja continuar?(y/n)\n");
        fprintf(f, ">");
        scanf("%c", &option);
        reset_color(f);

        if(option == 'n' || option == 'N') {
            set_color(f, RED, true);
            fprintf(f, "operacao cancelada!\n");
            reset_color(f);
            return ERR;
        }

        update_airport(airport, all_airports, NULL);
    }

    void* field;
    bool (*search_func)(void*, void*) = get_airport_filter(f, &field);    
    return update_airport(airport, search_func, field);

}

int _select_airport(FILE* f) {
    clear_input_buffer();
    
    set_color(f, YELLOW, true);
    print_line(f, 80, 0);
    reset_color(f);

    char option;
    set_color(f, WHITE, true);
    fprintf(f, "deseja filtrar por algum atributo?(y/n)\n");
    scanf("%c", &option);
    reset_color(f);
    clear_input_buffer();

    Airports_t airports;
    if(option == 'n' || option == 'N') 
        airports = read_airport(all_airports, NULL);
    else {
        void* field;
        bool (*search_func)(void*, void*) = get_airport_filter(f, &field);

        airports = read_airport(search_func, field);
    }


    set_color(f, WHITE, true);
    fprintf(f, "deseja ordenar a lista?(y/n)\n");
    scanf("%c", &option);
    reset_color(f);
    clear_input_buffer();

    int order;
    set_color(f, WHITE, true);
    fprintf(f, "qual a ordem que sera usada?(1 para ascendente / 0 para descendente)\n");
    scanf("%d", &order);
    reset_color(f);
    clear_input_buffer();


    if(option == 'y' || option == 'Y') {
        set_color(f, WHITE, true);
        fprintf(f, "Por qual campo voce deseja ordenar?\n");
        reset_color(f);

        int (*get_attr_func)(void*) = get_airport_field(f);

        sort_list(airports, get_attr_func, order);
    } 

    if(is_empty_list(airports)) {
        set_color(f, CYAN, true);
        fprintf(f, "<VAZIO>\n\n");
        reset_color(f);

        set_color(f, RED, true);
        fprintf(f, "nenhum aeroporto encontrado!\n");
        reset_color(f);
        return ERR;
    }

    if(print_list(f, airports, print_airport, YELLOW, true) == ERR) 
        return ERR;

    return destroy_list(airports, dealloc_airport);
}


int run_airport_menu(FILE* f, bool* exit) {
    int selected_option;
    bool bye = false;

    char title[] = "Menu Aeroporto";

    while(!bye) {
        print_title(f, YELLOW, title, '-', strlen(title));
        
        print_menu_options(f, BLUE, airport_menu_options, airport_menu_options_size);
        selected_option = get_selected_option(f, BLUE, airport_menu_options, airport_menu_options_size);

        switch(selected_option) {
            case _INSERT:
                _insert_airport(f) == ERR ? 
                    print_error(f, "nao foi possivel inserir o aeroporto.") :
                    print_success(f, "aeroporto inserido com sucesso!");

                break;

            case _DELETE:
                _delete_airport(f) == ERR ?
                    print_error(f, "nao foi possivel deletar o aeroporto.") :
                    print_success(f, "aeroporto deletado com sucesso!");
                break;

            case _UPDATE:
                _update_airport(f) == ERR ?
                    print_error(f, "nao foi possivel atualizar o aeroporto.") :
                    print_success(f, "aeroporto atualizado com sucesso!");
                break;

            case _SELECT: 
                _select_airport(f) == ERR ?
                    print_error(f, "nao foi possivel ver aeroportos.") :
                    print_success(f, "aeroportos encontrados com sucesso!");
                break;

            case 5:
                break;
            case 6:
                break;
            case 7:
                bye = true;
                break;

            case 8:
                *exit = true;
                bye = true;
                break;
        }

    }
}