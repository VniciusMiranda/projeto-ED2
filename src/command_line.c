#include "command_line.h"


char* main_menu_options[] = {
    "acessar menu aeroporto",
    "acessar menu avioes",
    "sair",
};
int main_menu_options_size = ARRAY_SIZE(main_menu_options);

int print_goodbye(FILE* f, color_t color) {
    set_color(f, color, true);
    print_line(f, 80, 0);
    fprintf(f, "tchau :c\n");
    reset_color(f);
}

int run_command_line(FILE* f) {
    int EXIT = main_menu_options_size;
    int selected_option;
    bool bye = false;

    char title[] = "Airline-Management - Menu Principal";
    
    while(!bye) {
        print_title(f, RED, title, '=', strlen(title));

        print_menu_options(f, BLUE, main_menu_options, main_menu_options_size);
        selected_option = get_selected_option(f, BLUE, main_menu_options, main_menu_options_size);

        switch(selected_option) {
            case AIRPORT_MENU: 
                run_airport_menu(f, &bye);
                break;
            case PLANES_MENU: 
                print_warning(f, "menu dos avioes esta com varios bugs :/");
                run_plane_menu(f, &bye);
                break;
            case EXIT_APP:
                bye = true;
                break;
        }
    }

    print_goodbye(f, BLUE);
}
     