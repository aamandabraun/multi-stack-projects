package br.com.senai.view;

import br.com.senai.entity.Product;
import br.com.senai.service.ProductService;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class ProductView {

    private Scanner tec;
    private boolean exec = true;
    private ProductService productService;
    private List<Product> products = new ArrayList<>();

    public void menu(){
        tec = new Scanner(System.in);
        do {
            System.out.println("1 - Cadastrar produto");
            System.out.println("2 - Listar produto");
            System.out.println("3 - Buscar produto");
            System.out.println("4 - Remover produto");
            System.out.println("5 - Editar produto");
            System.out.println("9 - Encerrar o sistema");

            System.out.print("Informe a opção desejada: ");
            executarMetodo(tec.nextInt());

        }while(this.exec);
    }

    private void executarMetodo(int opcao){
        productService = new ProductService();
        switch (opcao){

            case 1:
                String nomeProduto;
                Double valorProduto;
                int quantidadeProduto;

                System.out.println("Informe o nome do produto: ");
                tec.nextLine();
                nomeProduto = tec.nextLine();
                System.out.println("Informe o valor do produto: ");
                valorProduto = tec.nextDouble();
                System.out.println("Informe a quantidade do produto: ");
                quantidadeProduto = tec.nextInt();

                Product product = productService.cadastrarProduto(nomeProduto, valorProduto, quantidadeProduto);
                products.add(product);
                break;

            case 2:
                listarProdutos(productService.listarProduto(products));
                break;

            case 3:
                productService.buscarProduto();
                break;

            case 4:
                productService.removerProduto();
                break;

            case 5:
                //productService.editarProduto();
                break;

            case 9:
                this.exec = false;
                System.out.println("Sistema finalizado");
                break;

            default:
                System.out.println("Opção inválida!");
                break;

        }
    }

    private void listarProdutos(List<Product> produtos){
        System.out.println("PRODUTOS CADASTRADOS");
        System.out.printf("%-10s | %-10s | %-10s \n", "PRODUTO", "VALOR", "QUANTIDADE");

        for (int i = 0; i < produtos.size(); i++){
            System.out.printf("%-10s | %s%-10.2f | %-10d \n", produtos.get(i).getNomeProduto(), "R$", produtos.get(i).getValor(), produtos.get(i).getQuantidade());

            //System.out.println("Produto: " + produtos.get(i).getNomeProduto());
            //System.out.println("Valor: R$" + produtos.get(i).getValor());
            //System.out.println("Quantidade: " + produtos.get(i).getQuantidade());
        }
    }
}
