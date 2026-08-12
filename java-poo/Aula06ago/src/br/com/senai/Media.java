package br.com.senai;

public class Media {
    public static void main(String[] args){
        String nome = "Ana";
        double nota1 = 2;
        double nota2 = 4.5;
        double nota3 = 10;
        double nota4 = 8;
        double nota = ((nota1 + nota2 + nota3 + nota4) / 4);


        if (nota <= 6.5){
            System.out.println("Parabéns! Você foi aprovado");
        } else {
            System.out.println("Reprovado");
        }
    }

}
