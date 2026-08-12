package br.com.senai;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class ControleEstoque{

    static Scanner tec = new Scanner(System.in);
    static List<String> nomeProdutos = new ArrayList<>();
    static List<Integer> quantidadeProdutos = new ArrayList<>();
    static List<Double> valorProdutos = new ArrayList<>();

    public static void main(String[] args){

        boolean exec = true;
        do {
            System.out.println("--MENU--");
            System.out.println("1 - Cadastrar");
            System.out.println("2 - Listar");
            System.out.println("3 - Buscar");
            System.out.println("4 - Editar");
            System.out.println("5 - Remover");
            System.out.println("9 - Encerrar o sistema");

            System.out.println("Informe a opção desejada: ");
            int opcao = tec.nextInt();
            switch (opcao) {
                case 1: //cadastrar
                    cadastrar();
                    break;
                case 2: //listar
                    listar();
                    break;
                case 3: //buscar
                    buscar();
                    break;
                case 4: //editar
                    editar();
                    break;
                case 5: //remover
                    remover();
                    break;
                case 9: //encerrar
                    exec = false;
                    break;
                default: //default
                    System.out.println("Opção inválida");
                    break;
            }
        } while (exec);
        System.out.println("Sistema encerrado");

    }

    public static void cadastrar(){
        String nome;
        int quantidade;
        double valor;

        System.out.println("Cadastrar");
        System.out.print("Informe o nome do produto: ");
        tec.nextLine();
        nome = tec.nextLine();

        System.out.print("Informe a quantidade: ");
        quantidade = tec.nextInt();

        System.out.print("Informe o valor: R$");
        valor = tec.nextDouble();

        nomeProdutos.add(nome);
        quantidadeProdutos.add(quantidade);
        valorProdutos.add(valor);
    }

    public static void listar(){
        System.out.println("Listar");
        double valorEmEstoque = 0;
        int quantidadeEmEstoque = 0;
        for (int i = 0; i < nomeProdutos.size(); i++){
            double valorTotalEmEstoque = quantidadeProdutos.get(i) * valorProdutos.get(i);
            System.out.print(i + " - Produto " + nomeProdutos.get(i));
            System.out.print(" Valor: R$" + valorProdutos.get(i));
            System.out.println(" Quantidade: " + quantidadeProdutos.get(i));

            valorEmEstoque += valorTotalEmEstoque;
            quantidadeEmEstoque += quantidadeProdutos.get(i);
        }

        System.out.println("Valor total do estoque: R$" + valorEmEstoque);
        System.out.println("QUantidade em estoque: " + quantidadeEmEstoque);
    }

    public static void buscar(){
        int ID;
        System.out.println("Buscar");
        System.out.print("Informe o ID do produto: ");
        ID = tec.nextInt();

        if(ID >= nomeProdutos.size() || ID < 0){
            System.out.println("Produto não cadastrado");

        } else {
            System.out.print(ID + " - Produto " + nomeProdutos.get(ID));
            System.out.print(" Valor: R$" + valorProdutos.get(ID));
            System.out.println(" Quantidade: " + quantidadeProdutos.get(ID));
        }
    }

    public static void editar(){
        int ID;
        System.out.println("Editar");
        System.out.println("Informe o ID do produto para editar: ");
        ID = tec.nextInt();

        System.out.println("Informe o novo nome: ");
        tec.nextLine();
        nomeProdutos.set(ID, tec.nextLine());

        System.out.println("Informe a nova quantidade: ");
        quantidadeProdutos.set(ID, tec.nextInt());

        System.out.println("Informe o novo valor: ");
        valorProdutos.set(ID, tec.nextDouble());
    }

    public static void remover(){
        int ID;
        System.out.println("Remover");
        listar();
        System.out.println("Informe o ID do produto para removê-lo: ");
        ID = tec.nextInt();

        nomeProdutos.remove(ID);
        quantidadeProdutos.remove(ID);
        valorProdutos.remove(ID);
    }
}
