/**
 * changes in local repo conflict change in local
 * */
struct hole_t
{
  int x;
  int y;
  hole_t *connect;
};


void connect(hole_t *, hole_t *);
void pair(hole_t *, int);

void init();
void processAllPairs();
