#include <stdio.h>
#include <iostream>
#include <vector>
#include <strings.h>
#include <string.h>
#include <pthread.h>

using namespace std;

typedef struct {
  pthread_mutex_t VlEmploye;
  pthread_mutex_t VlPdf;
  vector<string> lEmploye;
  vector<string> lPdf;
} verrou;
