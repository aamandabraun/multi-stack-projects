package br.com.senai.app;

import br.com.senai.model.Cliente;
import br.com.senai.model.Produto;

import java.util.ArrayList;
import java.util.List;

public class LojaApp {

    static List<Cliente> clientes = new ArrayList<>();
    public static void main(String[] args) {
        Cliente cliente1 = new Cliente(001, "Amanda", "amanda@gmail.com", true);
        Cliente cliente2 = new Cliente(002, "Bruno", "bruno@gmail.com", true);
        Cliente cliente3 = new Cliente(003, "Cecília", "cecilia@gmail.com", true);

        clientes.add(cliente1);
        clientes.add(cliente2);
        clientes.add(cliente3);
    }

    static List<Produto> produtos = new ArrayList<>(); {
        Produto produto1 = new Produto(999, "Mouse", 29.90, 11);
        Produto produto2 = new Produto(998, "Monitor", 105.00, 3);
        Produto produto3 = new Produto(997, "Teclado", 78.90, 25);

        produtos.add(produto1);
        produtos.add(produto2);
        produtos.add(produto3);
    }

    private static void listarClientes() {
    }

    private static void listarProdutos() {
    }

}
