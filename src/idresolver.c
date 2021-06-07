#include "idresolver.h"

long int (*resolve_functions[])() = {
    resolve_airport_id,
    resolve_plane_id,
};
int NUMB_IDS_TO_RESOLVE = ARRAY_SIZE(resolve_functions);

int resolve_table_ids(){
    log_info("resolving table ids...");
    for(int i = 0; i < NUMB_IDS_TO_RESOLVE; ) {

        resolve_functions[i]();
        i++;
        sprintf(LOG, "[%d %%] ids resolved.", (i/NUMB_IDS_TO_RESOLVE) * 100);
        log_info(LOG);
    }

    log_info("ids resolved.");

}