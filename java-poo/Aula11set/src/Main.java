import br.com.senai.trabalhador;

public class Main {

    public static void main(String[] args) {
        trabalhador trabalhador1 = new trabalhador();
        trabalhador trabalhador2 = new trabalhador();
        trabalhador trabalhador3 = new trabalhador();
        trabalhador trabalhador4 = new trabalhador("Amanda", "Migração", 3.500);

        trabalhador1.setNome("Adalberto");

        System.out.println(trabalhador.getTotalTrabalhadores());
        System.out.println(trabalhador4.getNome());
    }
}