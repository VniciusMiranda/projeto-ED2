  #include "plane_menu.h"

char* plane_menu_options[] = {
    "inserir novo aviao",
    "deletar aviao",
    "atualizar aviao",
    "ver avioes",
    "sair do menu",
    "sair da aplicacao"
};
int plane_menu_options_size = ARRAY_SIZE(plane_menu_options);

char* plane_fields_options[] = {
    "id",
    "model",
    "company",
    "capacity",
};
int plane_fields_options_size = ARRAY_SIZE(plane_fields_options);

Plane_t* get_plane_from_user(FILE* f) {
    int capacidade;
    AirlineCompany_t *airlineCompany;
    clear_input_buffer();

    set_color(f, WHITE, true);

    print_line(f, 80, '-');
    int selectedOpt;
    while(true){
        fprintf(f, "escolha um modelo de aviao: ");
        for(int i = 1; i <= 10; i++){
            char buffer[TEXT_MAX];
            get_name_model(i, buffer);
            fprintf(f, "\n%d - %s", i, buffer);
        }
        fprintf(f, "\n\nescolha: ");
        scanf ("%d", &selectedOpt);
        if(selectedOpt < 1 || selectedOpt > 10){
            print_error(f, "Nao existe essa opcao!");
        }else {
            break;
        }
    }

    fprintf(f, "capacidade do avião: ");
    scanf ("%d", &capacidade);
    clear_input_buffer();
    char companyName[TEXT_MAX];
    char companyCountry[TEXT_MAX];
    fprintf(f, "nome da companhia aerea: ");
    scanf ("%[^\n]%*c", companyName);
    fprintf(f, "pais da companhia aerea: ");
    scanf ("%[^\n]%*c", companyCountry);

    airlineCompany = create_company(companyName, companyCountry);


    reset_color(f);

    Plane_t* plane = create_plane(capacidade, *airlineCompany, selectedOpt);

    if(!plane) return NULL;

    return plane;
}

get_attr_func get_plane_field(FILE* f) {
    clear_input_buffer();
    set_color(f, WHITE, true);
    fprintf(f, "Por qual campo voce deseja filtrar?\n");
    reset_color(f);

    print_menu_options(f, BLUE, plane_fields_options, plane_fields_options_size);
    int selected_option = get_selected_option(f, BLUE, plane_fields_options, plane_fields_options_size);
    clear_input_buffer();


    switch(selected_option) {
        case 1:
            return get_plane_id;
        
        case 2:
           return get_plane_model;

        case 3: 
            return get_plane_capacity;

        case 4: 
            return get_plane_company;

        default:
            return NULL;
    }
}

search_func get_plane_filter(FILE* f, void** field_value) {
    clear_input_buffer();
    set_color(f, WHITE, true);
    fprintf(f, "Por qual campo voce deseja filtrar?\n");
    reset_color(f);

    print_menu_options(f, BLUE, plane_fields_options, plane_fields_options_size);
    int selected_option = get_selected_option(f, BLUE, plane_fields_options, plane_fields_options_size);
    clear_input_buffer();

    long int* id = (long int *) malloc(sizeof(long int ));
    if(!id) return NULL;

    int* int_input = (int *) malloc(sizeof(int ));
    if(!int_input) return NULL;

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
            return find_plane_by_id;
        
        case 2:
            print_line_with_color(f, 80, 0, YELLOW, true);
            
            set_color(f, WHITE, true);
            fprintf(f, "modelo:");
            scanf ("%[^\n]%*c", str_input);

            reset_color(f);

            *field_value = (void*) str_input; 
            return find_plane_by_model;

        case 3:
            print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "companhia:");
            scanf ("%[^\n]%*c", str_input);

            reset_color(f);

            *field_value = (void*) str_input; 
            return find_plane_by_company;
           

        case 4:
            print_line_with_color(f, 80, 0, YELLOW, true);

            set_color(f, WHITE, true);
            fprintf(f, "capacidade:");
            scanf ("%d", int_input);
            reset_color(f);

            *field_value = (void*) int_input; 
            return find_plane_by_capacity;

        default:
            return NULL;
    }
}

int _insert_plane(FILE* f) {
    log_info("insert_plane(): init");
    Plane_t* plane = get_plane_from_user(f);

    print_plane(f, (void*) plane, YELLOW, true);


    log_info("writing plane on the database.");
    if(write_plane(plane)) return ERR;

    return OK;
}

int _delete_plane(FILE* f) {
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

        if(recreate_database_table(TABLE_NAME_PLANE) == ERR)
            return ERR;
        else {
            LAST_VALID_ID_PLANE = 0;
            return OK;
        }
    }

    void* field;
    bool (*search_func)(void*, void*) = get_plane_filter(f, &field);    
    log_info("got plane filter");
    return delete_plane(search_func, field);
}


int _update_plane(FILE* f) {
    clear_input_buffer();
    set_color(f, WHITE, true);
    fprintf(f, "insira os novos campos:\n");
    reset_color(f);

    Plane_t* plane = get_plane_from_user(f);
    if(!plane) return ERR;
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

        update_plane(plane, all_planes, NULL);
    }

    void* field;
    bool (*search_func)(void*, void*) = get_plane_filter(f, &field);    
    return update_plane(plane, search_func, field);
}

int _select_plane(FILE* f) {
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

    Planes_t planes;
    if(option == 'n' || option == 'N') 
        planes = read_plane(all_planes, NULL, false);
    else {
        void* field;
        bool (*search_func)(void*, void*) = get_plane_filter(f, &field);

        planes = read_plane(search_func, field, false);
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

        int (*get_attr_func)(void*) = get_plane_field(f);

        sort_list(planes, get_attr_func, order);
    } 

    if(is_empty_list(planes)) {
        set_color(f, CYAN, true);
        fprintf(f, "<VAZIO>\n\n");
        reset_color(f);

        set_color(f, RED, true);
        fprintf(f, "nenhum aviao encontrado!\n");
        reset_color(f);
        return ERR;
    }

    if(print_list(f, planes, print_plane, YELLOW, true) == ERR) 
        return ERR;

    return destroy_list(planes, dealloc_pl);
}


int run_plane_menu(FILE* f, bool* exit) {
    int selected_option;
    bool bye = false;

    char title[] = "Menu Aviao";

    while(!bye) {
        print_title(f, CYAN, title, '-', strlen(title));
        
        print_menu_options(f, BLUE, plane_menu_options, plane_menu_options_size);
        selected_option = get_selected_option(f, BLUE, plane_menu_options, plane_menu_options_size);

        switch(selected_option) {
            case _INSERT:
                _insert_plane(f) == ERR ? 
                    print_error(f, "nao foi possivel inserir o aviao.") :
                    print_success(f, "aviao inserido com sucesso!");

                break;

            case _DELETE:
                _delete_plane(f) == ERR ?
                    print_error(f, "nao foi possivel deletar o aviao.") :
                    print_success(f, "aviao deletado com sucesso!");
                break;

            case _UPDATE:
                _update_plane(f) == ERR ?
                    print_error(f, "nao foi possivel atualizar o aviao.") :
                    print_success(f, "aviao atualizado com sucesso!");
                break;

            case _SELECT: 
                _select_plane(f) == ERR ?
                    print_error(f, "nao foi possivel ver avioes.") :
                    print_success(f, "avioes encontrados com sucesso!");
                break;

            case 5:
                bye = true;
                break;

            case 6:
                *exit = true;
                bye = true;
                break;
        }

    }
}