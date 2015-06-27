#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "util.h"
#include "epoch.h"

epoch_t epoch_new(epoch_t next)
{
  epoch_t e;

  if(!(e = malloc(sizeof(struct epoch_struct)))) return LOG("OOM");
  memset(e,0,sizeof (struct epoch_struct));
  e->next = next;

  return e;
}

epoch_t epoch_free(epoch_t e)
{
  if(e->id) free(e->id);
  if(e->phy) LOG("epoch free'd leaking phy pointer");
  free(e);
  return NULL;
}

epoch_t epoch_import(epoch_t e, char *eid)
{
  if(!e || !eid) return NULL;
  if(base32_decode_length(strlen(eid)) != 16) return NULL;
  base32_decode_into(eid,0,e->bin);
  return epoch_reset(e);
}

epoch_t epoch_reset(epoch_t e)
{
  if(!e) return NULL;
  e3x_hash(e->bin,16,e->pad);
  if(e->id) free(e->id); // free up unused space
  e->id = NULL;
  // convenience pointer into bin
  e->type = e->bin[0];
  return e;
}

char *epoch_id(epoch_t e)
{
  if(!e) return NULL;
  if(!e->id) e->id = base32_encode(e->bin,16);
  return e->id;
}

// when is next knock, returns 0 if == from
uint64_t epoch_knock(epoch_t e, uint64_t from)
{
  return 0;
}

// sync point for given window
epoch_t epoch_sync(epoch_t e, uint32_t window, uint64_t at)
{
  return NULL;
}

// which channel to use at this time
uint32_t epoch_chan(epoch_t e, uint64_t at, uint8_t chans)
{
  return 0;
}