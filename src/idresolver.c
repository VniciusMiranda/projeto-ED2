#include "idresolver.h"

long int (*resolve_functions[])() = {
    resolve_airport_id,
};
int NUMB_IDS_TO_RESOLVE = ARRAY_SIZE(resolve_functions);

int resolve_table_ids(){
    log_info("resolving table ids...");
    for(int i = 0; i < NUMB_IDS_TO_RESOLVE; i++)
        resolve_functions[i]();
    log_info("ids resolved.");

}