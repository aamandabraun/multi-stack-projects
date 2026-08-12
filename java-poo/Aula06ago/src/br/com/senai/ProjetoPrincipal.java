package br.com.senai;

public class ProjetoPrincipal {
    public static void main(String[] args){

        System.out.println("Hello World");

        String nome = "Amanda";
        String sobrenome;
        sobrenome = "Braun";
        int idade = 21;
        boolean vivo = true;
        double altura = 1.67;

        System.out.println("O nome é " + nome + " " + sobrenome);

        if (idade>= 18) {
            System.out.println("Maior de idade");
        }
         else {
            System.out.println("Menor de idade");
        }
    }
};
