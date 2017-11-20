#include <iostream>
#include <cassert>
#include <stdlib.h>
#include "pair.h"

hole_t *holes;
int count = 0;
int total_length;

void connect(hole_t *h1, hole_t *h2)
{
  if (h1->connect)
    h1->connect->connect = nullptr;
  if (h2->connect)
    h2->connect->connect = nullptr;
  h1->connect = h2;
  h2->connect = h1;
}

void pair(hole_t *phole, int length)
{
  if (length == 1)
  {
    processAllPairs();
    return;
  }
  if (phole->connect && phole->connect < phole)
  {
    pair(phole + 1, length - 1);
    return;
  }

  hole_t *pnext_hole;
  for (int i = 1; i < length; i++)
  {
    pnext_hole = phole + i;
    if (pnext_hole->connect && pnext_hole->connect < phole)
    {
      continue;
    }
    connect(phole, pnext_hole);
    pair(phole + 1, length - 1);
  }
}

void init()
{
  holes = (hole_t *)malloc(sizeof(hole_t) * total_length);
  for (int i = 0; i < total_length; i++)
  {
    holes[i].x = i;
    holes[i].y = i;
    holes[i].connect = nullptr;
  }
}

void processAllPairs()
{
  for (int i = 0; i < total_length; i++)
  {
    hole_t *h1, *h2;
    h1 = holes + i;
    h2 = h1->connect;

    assert(h1->connect);
    assert(h2->connect);
    assert(h1->connect == h2);
    assert(h2->connect == h1);
    assert(h1 != h2);

    if (h2 > h1)
    {
      std::cout << "(" << h1->x << "," << h1->y << ")";
      std::cout << "<=>";
      std::cout << "(" << h2->x << "," << h2->y << ")";
      std::cout << ", ";
    }
  }
  count++;
  std::cout << std::endl;
}


int main(int argc, char **argv)
{
  assert(argc == 2);
  int n = atoi(argv[1]);
  assert(n > 0);
  total_length = 2*n;
  init();
  pair(holes, total_length);
  std::cout << "Total " << count << " combinations in " << total_length << " wormholes!" << std::endl;
  return 0;
}