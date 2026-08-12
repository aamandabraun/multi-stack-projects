package Vendas;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Sistema {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        List<Produto> catalogo = new ArrayList<>();
        catalogo.add(new Produto(1, "Camiseta", 50, 12));
        catalogo.add(new Produto(2, "Calça", 25, 15));
        catalogo.add(new Produto(3, "Cinto", 10, 5));

        List<Venda> historico = new ArrayList<>();

        int opcao;
        do {
            System.out.println("\n==== SISTEMA DE VENDAS ====");
            System.out.println("1 - Listar produtos");
            System.out.println("2 - Realizar venda");
            System.out.println("3 - Relatório de vendas");
            System.out.println("0 - Sair");
            System.out.print("Escolha: ");
            opcao = sc.nextInt();

            switch (opcao) {
                case 1:
                    System.out.println("=== PRODUTOS ===");
                    for (Produto p : catalogo) {
                        System.out.println(p);
                    }
                    break;

                case 2:
                    Venda venda = new Venda();
                    char continuar;
                    do {
                        System.out.println("Digite o código do produto: ");
                        int cod = sc.nextInt();
                        System.out.println("Digite a quantidade: ");
                        int qtd = sc.nextInt();

                        Produto escolhido = null;
                        for (Produto p : catalogo) {
                            if (p.getCodigo() == cod) {
                                escolhido = p;
                                break;
                            }
                        }
                        if (escolhido != null) {
                            venda.adicionarProduto(escolhido, qtd);
                        } else {
                            System.out.println("⚠ Produto não encontrado.");
                        }

                        System.out.print("Adicionar outro produto? (s/n): ");
                        continuar = sc.next().charAt(0);
                    } while (continuar == 's' || continuar == 'S');

                    venda.exibirResumo();
                    historico.add(venda);
                    break;

                case 3:
                    System.out.println("=== RELATÓRIO DE VENDAS ===");
                    double totalGeral = 0;
                    for (Venda v : historico) {
                        totalGeral += v.getTotal();
                    }
                    System.out.println("Número de vendas: " + historico.size());
                    System.out.println("Faturamento total: R$ " + totalGeral);
                    break;

                case 0:
                    System.out.println("Encerrando o sistema...");
                    break;

                default:
                    System.out.println("Opção inválida!");
                }
                
        } while (opcao != 0);

        sc.close();
    }
}
