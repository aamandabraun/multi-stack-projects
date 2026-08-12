package br.com.senai.demo.service;

import java.util.List;

import br.com.senai.demo.model.Produto;

import java.until.ArrayList;


public class ProdutoService {

    private static long idCounter = 1;
    private static List<Produto> = new ArrayList();

    public List<Produto> listarTodos(){
        return produtos;
    }

    public listarProdutos(long id){
        return produtos.stream().filter(Produto produto -> produto.Id() == id);
    }
}