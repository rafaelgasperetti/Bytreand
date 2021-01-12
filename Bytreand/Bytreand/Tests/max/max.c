#define N 2048

int main() {
  int v[N];
  int maxval = 0;
  int i;
  for (i=0; i<N; i++)
    if (v[i] > maxval)
      maxval = v[i];
  return maxval;
}

