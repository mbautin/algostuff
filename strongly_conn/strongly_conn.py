#!/usr/bin/env python

import sys

from collections import defaultdict

sys.setrecursionlimit(1000000)

links = defaultdict(set)

cur_index = 0
index = {}
lowlink = {}
s = []
s_set = set()
scc_sizes = []


def walk(v):
  global cur_index
  index[v] = cur_index
  lowlink[v] = cur_index
  cur_index += 1
  s.append(v)
  s_set.add(v)

  for w in links[v]:
    if w not in index:
      walk(w)
      lowlink[v] = min(lowlink[v], lowlink[w])
    elif w in s_set:
      lowlink[v] = min(lowlink[v], index[w])

  if lowlink[v] == index[v]:
    cur_scc = []
    w = None
    while w != v:
      w = s.pop()
      s_set.remove(w)
      cur_scc.append(w)
    scc_sizes.append(len(cur_scc))


if __name__ == '__main__':
  graph_file_path = sys.argv[1]
  print 'Reading graph'
  vertices = set()
  with open(graph_file_path) as f:
    for line in f:
      line = line.strip()
      if not line:
        continue
      i, j = line.split()
      i = int(i)
      j = int(j)
      links[i].add(j)
      vertices.add(i)
      vertices.add(j)
  print 'Finished reading graph'
  print 'Found %d vertices' % len(vertices)
  for v in vertices:
    if v not in index:
      walk(v)

  print ','.join([int(s) for s in sorted(scc_sizes, reversed=True)[:5]])

