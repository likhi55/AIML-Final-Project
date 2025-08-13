#!/usr/bin/env python3
import csv, sys, os
def read_csv(p): 
    with open(p, newline="") as f: return [r for r in csv.reader(f) if r]
def norm(rows):  return [[c.strip() for c in r] for r in rows]
def compare(g,a):
    g,a = norm(read_csv(g)), norm(read_csv(a))
    if len(g)!=len(a): return False,f"Row count mismatch: {len(g)} vs {len(a)}"
    for i,(gr,ar) in enumerate(zip(g,a)):
        if gr!=ar: return False,f"Row {i}:\n  GOLDEN:{gr}\n  ACTUAL:{ar}"
    return True,"OK"
if __name__=="__main__":
    if len(sys.argv)!=3: print("Usage: compare_csvs.py <golden> <actual>", file=sys.stderr); sys.exit(2)
    ok,msg = compare(sys.argv[1],sys.argv[2])
    print(("PASS: ","FAIL: ")[not ok] + os.path.basename(sys.argv[2]) + (""," -> "+msg)[not ok])
    sys.exit(0 if ok else 1)
