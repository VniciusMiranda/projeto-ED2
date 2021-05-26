 #ifndef _PLANE_MENU_H_
#define _PLANE_MENU_H_

#include "utils.h"
#include "Plane.h"

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

Plane_t* get_plane_from_user(FILE* f);

get_attr_func get_plane_field(FILE* f);

search_func get_plane_filter(FILE* f, void** field_value);

int _insert_plane(FILE* f);

int _delete_plane(FILE* f);

int _update_plane(FILE* f);

int _select_plane(FILE* f);

int run_plane_menu(FILE* f, bool* exit);

#endif