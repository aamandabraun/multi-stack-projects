package br.com.senai;

import java.util.ArrayList;
import java.util.List;

public class LojaApp {

    static List<Produto> produtos = new ArrayList<>();
    public static void main(String[] args) {
        Produto produto1 = new Produto("Maçã", 2.45, 45);
        Produto produto2 = new Produto("Banana", 1.89, 33);
        Produto produto3 = new Produto("Manga", 3.49, 41);

        produtos.add(produto1);
        produtos.add(produto2);
        produtos.add(produto3);

        System.out.println("Exibição");
        listarProdutos();

        produtos.remove(produto1);

        Produto produto4 = new Produto();
        produto4.setNome("Pera");
        produto4.setPreco(4.20);
        produto4.setQuantidadeEstoque(20);

        produtos.add(produto4);

        System.out.println("Exibição após as alterações");
        listarProdutos();
    }

    static void listarProdutos() {
        for (Produto p : produtos) {
            p.exibirInformacoes();
        }
    }
}