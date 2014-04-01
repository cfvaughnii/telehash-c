#include "ext.h"


typedef struct seek_struct 
{
  bucket_t seeks;
} *seek_t;

seek_t seek_new(switch_t s)
{
  seek_t sk;
  sk = malloc(sizeof (struct seek_struct));
  memset(sk,0,sizeof (struct seek_struct));
  sk->seeks = bucket_new();
  return sk;
}

// create a seek to this hn and initiate connect
void seek_handler(switch_t s, hn_t hn)
{
//  seek_t sk = seek_get(s);
  DEBUG_PRINTF("seek connecting %s",hn->hexname);
}

void seek_auto(switch_t s)
{
  s->handler = seek_handler;
}

seek_t seek_get(switch_t s)
{
  seek_t sk;
  sk = xht_get(s->index,"seek");
  return sk ? sk : seek_new(s);
}

void seek_free(switch_t s)
{
  seek_t sk = seek_get(s);
  bucket_free(sk->seeks);
  free(sk);
}

void seek_peer(switch_t s, hn_t to, hn_t id)
{
  // create peer channel
  // handler for response as raw packets w/ path
}


// just call back note instead of auto-connect
void seek_note(switch_t s, hn_t h, packet_t note)
{
  
}