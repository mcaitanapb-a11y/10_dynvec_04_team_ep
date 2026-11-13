
#include "teamlist.h"
#include <stdlib.h>

struct node {
    Team *team;
    struct node *next;
    struct node *prev;
};

struct teamlist {
    struct node *first;
    struct node *last;
    int size;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));

    if (tl == NULL)
        return NULL;

    tl->first = NULL;
    tl->last = NULL;
    tl->size = 0;

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    struct node *novo = malloc(sizeof(struct node));

    if (novo == NULL) {
        team_free(t);
        return;
    }

    novo->team = t;
    novo->next = NULL;
    novo->prev = tl->last;

    if (tl->last == NULL) {
        tl->first = novo;
    } else {
        tl->last->next = novo;
    }

    tl->last = novo;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    struct node *atual = tl->first;

    for (int j = 0; j < i; j++) {
        atual = atual->next;
    }

    return atual->team;
}

void tl_free(TeamList *tl) {
    if (tl == NULL)
        return;

    struct node *atual = tl->first;

    while (atual != NULL) {
        struct node *proximo = atual->next;

        team_free(atual->team);
        free(atual);

        atual = proximo;
    }

    free(tl);
}
