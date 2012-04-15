#include <vector>
#include <iostream>
#include <set>

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <limits.h>

using namespace std;

const int MAX_N = 1000000;

vector<vector<int> > links;

int idx[MAX_N];
int lowlink[MAX_N];
int cur_idx = 0;

int s[MAX_N];
int s_top = 0;
bool in_s[MAX_N];

void walk(int v) {
  idx[v] = cur_idx;
  lowlink[v] = cur_idx;
  ++cur_idx;

  s[s_top++] = v;
  in_s[v] = true;

  vector<int>& out_links = links[v];
  for (vector<int>::iterator it = out_links.begin();
       it != out_links.end(); ++it) {
    int w = *it;
    if (idx[w] == -1) {
      walk(w);
      lowlink[v] = min(lowlink[v], lowlink[w]);
    } else if (in_s[w]) {
      lowlink[v] = min(lowlink[v], idx[w]);
    }
  }

  if (lowlink[v] == idx[v]) {
    int scc_size = 0;
    int w = -1;
    while (w != v) {
      w = s[--s_top];
      in_s[w] = false;
      ++scc_size;
    }
    cout << scc_size << endl;
  }

}

int main(int argc, char** argv) {
  int i, j;
  memset(&idx, 0xff, sizeof(idx));
  memset(&in_s, 0, sizeof(in_s));
  links.reserve(MAX_N);
  int min_v = INT_MAX;
  int max_v = INT_MIN;
  while (scanf("%d %d", &i, &j) == 2) {
    links[i].push_back(j);
    min_v = min(min(min_v, i), j);
    max_v = max(max(max_v, i), j);
  }
  for (int v = min_v; v <= max_v; ++v) {
    if (idx[v] == -1) {
      walk(v);
    }
  }
  return 0;
}

