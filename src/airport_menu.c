#include "airport_menu.h"


char* airport_menu_options[] = {
    "inserir novo aeroporto",
    "deletar aeroporto",
    "atualizar aeroporto",
    "ver aeroportos",
    "inserir nova conexao",
    "inserir novo aviao",
    "ver conexoes de um aeroporto",
    "sair do menu",
    "sair da aplicacao",
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

    long int* id = (long int *) malloc(sizeof(long int ));
    if(!id) return NULL;

    char* str_input = (char*) malloc(sizeof(TEXT_MAX));
    if(!str_input) return NULL;

    switch(selected_option) {

        case 1:
         print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "id:");
            scanf("%ld", id);
            reset_color(f);

            *field_value = (void*) id; 
            return find_airport_by_id;
        
        case 2:
            print_line_with_color(f, 80, 0, YELLOW, true);
            
            set_color(f, WHITE, true);
            fprintf(f, "nome:");
            scanf ("%[^\n]%*c", str_input);

            reset_color(f);

            *field_value = (void*) str_input; 
            return find_airport_by_name;

        case 3:
            print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "codigo:");
            scanf ("%[^\n]%*c", str_input);

            reset_color(f);

            *field_value = (void*) str_input; 
            return find_airport_by_code;
           

        case 4:
            print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "cidade:");
            scanf ("%[^\n]%*c", str_input);
            reset_color(f);

            *field_value = (void*) str_input; 
            return find_airport_by_city;

        case 5:
            print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "pais:");
            scanf ("%[^\n]%*c", str_input);
            reset_color(f);

            *field_value = (void*) str_input; 
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


    int status = delete_airport(search_func, field);
    free(field);

    return status;
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

    int status = update_airport(airport, search_func, field);
    free(field);

    return status;
}

int _select_airport(FILE* f) {
    log_info("_select_airport(): init select_airport.");
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
    if(option == 'n' || option == 'N') {
        airports = read_airport(all_airports, NULL, false);
    }
    else {
        void* field;
        bool (*filter_func)(void*, void*) = get_airport_filter(f, &field);
        airports = read_airport(filter_func, field, false);
        free(field);
    }

    if(is_null_ptr(airports)) {
            log_error("_select_airport(): error while reading airports.");
            return ERR;
    }

    set_color(f, WHITE, true);
    fprintf(f, "deseja ordenar a lista?(y/n)\n");
    scanf("%c", &option);
    reset_color(f);
    clear_input_buffer();

    if(option == 'y' || option == 'Y') {

        int order;
        set_color(f, WHITE, true);
        fprintf(f, "qual a ordem que sera usada?(1 para ascendente / 0 para descendente)\n");
        scanf("%d", &order);
        reset_color(f);
        clear_input_buffer();

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

    log_info("_select_airport(): dealocating memory...");
    int status = destroy_list(airports, dealloc_airport);
    if(!error_in(status))
        log_info("_select_airport(): memory dealocated.");
    else
        log_info("_select_airport(): failed when dealocating memory.");

    return status;
}

int _insert_connection(FILE* f) {
    log_info("_insert_connection(): init insert.");
    clear_input_buffer();
    set_color(f, WHITE, true);

    fprintf(f, "Digite o ID do aeroporto onde adicionar a nova conexao:");
    unsigned long int airport_id;
    scanf("%ld", &airport_id);
    clear_input_buffer();

    log_info("reading airports...");
    Airports_t airports = read_airport(find_airport_by_id, &airport_id, false);
    if(!airports || airports->length > 1 || is_empty_list(airports)) {
        log_error("_insert_connection(): error when trying to read airports.");
        return ERR;
    }
    log_info("finish reading airports.");

    Airport_t* ap = (Airport_t*) airports->head->data;

    fprintf(f, "Digite o ID do aeroporto a ser adicionado como conexao:");
    unsigned long int connection_id;
    scanf("%ld", &connection_id);

    log_info("inserting connection...");
    if(insert_connection(ap, connection_id) == ERR){
        log_error("_insert_connection(): error while inserting connection.");
        return ERR;
    }
    log_info("connections inserted.");


    log_info("updating table airport");
    if(error_in(update_airport(ap, find_airport_by_id, &ap->id))) {
        log_error("_insert_connection(): error while updating airport.");
    }

    reset_color(f);
    log_info("cleaning memory...");
    int status = destroy_list(airports, dealloc_airport);
    log_info("memory cleaned.");
    return status;
}


int _select_connections(FILE* f) {
    log_info("_select_connections(): init.");

    fprintf(f, "Digite o ID do aeroporto:");
    unsigned long int airport_id;
    scanf("%ld", &airport_id);
    clear_input_buffer();

    log_info("reading airports...");
    Airports_t airports = read_airport(find_airport_by_id, &airport_id, false);
    if(!airports || airports->length > 1 || is_empty_list(airports)){
        log_error("_insert_connection(): error when trying to read airports.");
        return ERR;
    }
    log_info("finish reading airports.");

    Airport_t* ap = (Airport_t*) airports->head->data;
   
    set_color(f, PURPLE, true);
    print_line(f, 80, '-');
    fprintf(f, "CONEXOES\n"); 
    reset_color(f);

    int status = print_list(f, ap->connections, print_airport, PURPLE, true);
    status = destroy_list(airports, dealloc_airport);
    
    return status;
}

int _insert_plane_on_airport(FILE* f) {
    print_error(f, "nao implementado!");
    return ERR;
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
                error_in(_insert_airport(f)) ? 
                    print_error(f, "nao foi possivel inserir o aeroporto.") :
                    print_success(f, "aeroporto inserido com sucesso!");

                break;

            case _DELETE:
                error_in(_delete_airport(f)) ?
                    print_error(f, "nao foi possivel deletar o aeroporto.") :
                    print_success(f, "aeroporto deletado com sucesso!");
                break;

            case _UPDATE:
                error_in(_update_airport(f)) ?
                    print_error(f, "nao foi possivel atualizar o aeroporto.") :
                    print_success(f, "aeroporto atualizado com sucesso!");
                break;

            case _SELECT: 
                error_in(_select_airport(f)) ?
                    print_error(f, "nao foi possivel ver aeroportos.") :
                    print_success(f, "aeroportos encontrados com sucesso!");
                break;

            case 5:// inserir conexao
                error_in(_insert_connection(f)) ?
                    print_error(f, "nao foi possivel ver aeroportos.") :
                    print_success(f, "aeroportos encontrados com sucesso!");
                break;

            case 6: // inserir aviao
                error_in(_insert_plane_on_airport(f)) ?
                    print_error(f, "nao foi possivel ver aeroportos.") :
                    print_success(f, "aeroportos encontrados com sucesso!");
                break;
            case 7:
                error_in(_select_connections(f)) ?
                    print_error(f, "nao foi possivel ver aeroportos.") :
                    print_success(f, "aeroportos encontrados com sucesso!");
            case 8:
                bye = true;
                break;
            case 9:
                *exit = true;
                bye = true;
                break;
        }

    }
}