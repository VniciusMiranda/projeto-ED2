#include "airport_menu.h"


char* airport_menu_options[] = {
    "inserir novo aeroporto",
    "deletar aeroporto",
    "atualizar aeroporto",
    "ver aeroportos",
    "sair do menu",
    "sair da aplicacao"
};
int airport_menu_options_size = ARRAY_SIZE(airport_menu_options);

char* airport_fields_options[] = {

};


int _insert_airport(FILE* f) {
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
    if(!airport) return ERR;


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

        return recreate_database_table(TABLE_NAME_AIRPORT);
    }

}

int _update_airport() {

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

    if(option == 'n' || option == 'N') {
        Airports_t airports = read_all_airports();
        if(is_empty_list(airports)) {
            set_color(f, CYAN, true);
            fprintf(f, "<VAZIO>\n\n");
            reset_color(f);

            set_color(f, RED, true);
            fprintf(f, "a tabela esta vazia!\n");
            reset_color(f);
            return ERR;
        }

        return print_list(f, airports, print_airport, YELLOW, true);
    }
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
                bye = true;
                break;

            case 6:
                *exit = true;
                bye = true;
                break;
        }

    }
}