package biblioteca;

import java.util.Scanner;

public class Main {
    public static void main(String[] args){
        Secretaria secretaria = new Secretaria();
        Scanner Scanner = new Scanner(System.in);
        int opcao;

        do {
            System.out.println("\n=== Sistema Biblioteca ===");
            System.out.println("1 - Cadastrar livro");
            System.out.println("2 - Emprestar livro");
            System.out.println("3 - Devolver livro");
            System.out.println("4 - Consultar se está disponível");
            System.out.println("5 - Listar livros por autor");
            System.out.println("6 - Listar todos os livros");
            System.out.println("0 - Sair");
            System.out.println("Escolha uma opção: ");
            opcao = scanner.nextInt();
            scanner.nextLine();

            switch(opcao){

                case 1:
                    System.out.print("Título: ");
                    String titulo = scanner.nextLine();
                    System.out.print("Autor: ");
                    String autor = scanner.nextLine();
                    System.out.print("ISBN: ");
                    String isbn = scanner.nextLine();
                    System.out.print("Ano: ");
                    int ano = scanner.nextInt();
                    secretaria.cadastrarLivro(titulo, autor, isbn, ano);
                    break;
                case 2:
                    System.out.print("Informe o ISBN do livro: ");
                    isbn = scanner.nextLine();
                    secretaria.emprestarLivro(isbn);
                    break;
                case 3:
                    System.out.print("Informe o ISBN do livro: ");
                    isbn = scanner.nextLine();
                    secretaria.devolverLivro(isbn);
                    break;
                case 4:
                    System.out.print("Informe o ISBN do livro: ");
                    isbn = scanner.nextLine();
                    secretaria.consultarDisponibilidade(isbn);
                    break;
                case 5:
                    System.out.print("Informe o nome do autor: ");
                    autor = scanner.nextLine();
                    secretaria.listarLivrosPorAutor(autor);
                    break;
                case 6:
                    secretaria.listarTodos();
                    break;
                case 0:
                    System.out.println("Saindo...");
                    break;
                default:
                    System.out.println("Opção inválida.");
            }
        } while (opcao != 0);

        scanner.close();
    }
}
