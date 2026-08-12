package br.com.senai.service;

import br.com.senai.model.Cliente;
import br.com.senai.model.Produto;
import java.util.ArrayList; // precisa importar
import java.util.List;



public class Pedido {


    private List<Produto> listaDeProdutos = new ArrayList<>();
    private List<Cliente> listaDeClientes = new ArrayList<>();


    public void cadastrarProduto(Produto p) {
        listaDeProdutos.add(p);
    }

    public void listarProdutos() {
        for (Produto p : listaDeProdutos) {
            System.out.println(p);
        }
    }

    public void removerProdutoDoEstoque(String nome, int quantidade) {
        for (Produto p : listaDeProdutos) {
            if (p.getNomeProduto().equalsIgnoreCase(nome)) {
                p.setQuantidade(p.getQuantidade() - quantidade);
                break;
            }
        }
    }


    public void cadastrarCliente(Cliente c) {
        listaDeClientes.add(c);
    }

    public void listarClientes() {
        for (Cliente c : listaDeClientes) {
            System.out.println(c);
        }
    }



}
