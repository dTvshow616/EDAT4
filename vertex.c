#include "vertex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Vertex {
  long id;
  char tag[1024];
  Label state;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField(Vertex *v, char *key, char *value);

Status vertex_setField(Vertex *v, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return vertex_setId(v, atol(value));
  } else if (strcmp(key, "tag") == 0) {
    return vertex_setTag(v, value);
  } else if (strcmp(key, "state") == 0) {
    return vertex_setState(v, (Label)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr) {
  char buffer[1024];
  char *token;
  char *key;
  char *value;
  char *p;
  Vertex *v;

  /* Check args: */
  if (!descr) return NULL;

  /* Allocate memory for vertex: */
  v = vertex_init();
  if (!v) return NULL;

  /* Read and tokenize description: */
  sprintf(buffer, "%s", descr);
  token = strtok(buffer, " \t\n");
  while (token) {
    p = strchr(token, ':');
    if (!p) continue;

    *p = '\0';
    key = token;
    value = p + 1;

    vertex_setField(v, key, value);

    token = strtok(NULL, " \t\n");
  }

  return v;
}

/** rest of the functions in vertex.h **/

Vertex *vertex_init() {
  Vertex *vortice = (Vertex *)malloc(sizeof(Vertex));
  if (!vortice) {
    return NULL;
  }

  vortice->id = 0;
  strcpy(vortice->tag, "");
  vortice->state = WHITE;

  return vortice;
}

void vertex_free(void *v) {
  if (!v) {
    return;
  }

  free(v);
  v = NULL;
}

/*---------IDENTIFICADORES--------------- */
long vertex_getId(const Vertex *v) {
  if (!v) {
    return -1;
  }

  return v->id;
}

const char *vertex_getTag(const Vertex *v) {
  if (!v) {
    return NULL;
  }

  return v->tag;
}

Label vertex_getState(const Vertex *v) {
  if (!v) {
    return ERROR_VERTEX;
  }

  return v->state;
}

/*---------MODIFICADORES--------------- */
Status vertex_setId(Vertex *v, const long id) {
  if (!v) {
    return ERROR;
  }

  v->id = id;

  return OK;
}

Status vertex_setTag(Vertex *v, const char *tag) {
  if (!v) {
    return ERROR;
  }

  strcpy(v->tag, tag);

  return OK;
}

Status vertex_setState(Vertex *v, const Label state) {
  if (!v) {
    return ERROR;
  }

  v->state = state;

  return OK;
}

/*---------OTROS--------------- */
int vertex_cmp(const void *v1, const void *v2) {
  const Vertex *vertex_1 = (const Vertex *)v1;
  const Vertex *vertex_2 = (const Vertex *)v2;

  if (!vertex_1 || !vertex_2) {
    return 0;
  }

  if (vertex_1->id != vertex_2->id) {
    return vertex_1->id - vertex_2->id;
  }

  return strcmp(vertex_1->tag, vertex_2->tag);
}

void *vertex_copy(const void *src) {
  const Vertex *vertex_src = (const Vertex *)src;
  Vertex *vertex_copy;

  if (!vertex_src) {
    return NULL;
  }

  vertex_copy = vertex_init();
  if (!vertex_copy) {
    return NULL;
  }

  vertex_copy->id = vertex_src->id;
  strcpy(vertex_copy->tag, vertex_src->tag);
  vertex_copy->state = vertex_src->state;

  return vertex_copy;
}

int vertex_print(FILE *pf, const void *v) {
  const Vertex *vertex = (const Vertex *)v;

  if (!pf || !vertex) {
    return -1;
  }

  return fprintf(pf, "[%ld, %s, %d]", vertex->id, vertex->tag, vertex->state);
}