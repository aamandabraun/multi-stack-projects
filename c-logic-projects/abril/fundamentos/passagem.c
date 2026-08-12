void dobrar(int *p) {
    *p = (*p) * 2; 
}

int main_referencia() {
    int num = 50;
    dobrar(&num);
    printf("Dobro: %d\n", num); 
    return 0;
}