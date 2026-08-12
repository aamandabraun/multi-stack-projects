package Personagem;

import java.util.Scanner;

public class RPG {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("=== Jogo de RPG ===");
        System.out.print("Digite o nome do seu personagem: ");
        String nome = scanner.nextLine();

        System.out.println("Escolha sua classe:");
        System.out.println("1 - Guerreiro");
        System.out.println("2 - Mago");
        System.out.println("3 - Arqueiro");
        int escolha = scanner.nextInt();

        Personagem jogador;
        switch (escolha) {
            case 1:
                jogador = new Guerreiro(nome);
                break;
            case 2:
                jogador = new Mago(nome);
                break;
            case 3:
                jogador = new Arqueiro(nome);
                break;
            default:
                System.out.println("Opção inválida. Será Guerreiro por padrão.");
                jogador = new Guerreiro(nome);
        }

        System.out.println("Você escolheu: " + jogador);

        Personagem inimigo = new Guerreiro("Inimigo Orc");

        System.out.println("\nUm inimigo apareceu: " + inimigo);
        while (jogador.estaVivo() && inimigo.estaVivo()) {
            System.out.println("\nSua vez!");
            jogador.atacar(inimigo);

            if (!inimigo.estaVivo()) {
                System.out.println(inimigo.nome + " foi derrotado!");
                jogador.ganharExperiencia(10);
                break;
            }

            System.out.println("\nVez do inimigo!");
            inimigo.atacar(jogador);

            if (!jogador.estaVivo()) {
                System.out.println(jogador.nome + " foi derrotado...");
                break;
            }
        }

        System.out.println("\nStatus final:");
        System.out.println(jogador);
        System.out.println(inimigo);

        scanner.close();
    }
}
