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
    return OK;
}

int _delete_airport() {

}

int _update_airport() {

}

int _select_airport() {

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
                _delete_airport();
                break;

            case _UPDATE:
                _update_airport();
                break;

            case _SELECT: 
                _select_airport();
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