
#include "teamlist.h"
#include <stdlib.h>

struct teamlist {
    Team **teams;
    int size;
    int capacity;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));

    if (tl == NULL)
        return NULL;

    tl->size = 0;
    tl->capacity = 4;

    tl->teams = malloc(tl->capacity * sizeof(Team *));

    if (tl->teams == NULL) {
        free(tl);
        return NULL;
    }

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    if (tl->size == tl->capacity) {
        int nova_capacidade = tl->capacity * 2;

        Team **temp = realloc(tl->teams,
                              nova_capacidade * sizeof(Team *));

        if (temp == NULL) {
            team_free(t);
            return;
        }

        tl->teams = temp;
        tl->capacity = nova_capacidade;
    }

    tl->teams[tl->size] = t;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    return tl->teams[i];
}

void tl_free(TeamList *tl) {
    if (tl == NULL)
        return;

    for (int i = 0; i < tl->size; i++) {
        team_free(tl->teams[i]);
    }

    free(tl->teams);
    free(tl);
}
