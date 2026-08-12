typedef struct ponto Ponto; 

Ponto* ponto_criar(float x, float y);
float ponto_distancia(Ponto *p1, Ponto *p2);
void ponto_destruir(Ponto *p);