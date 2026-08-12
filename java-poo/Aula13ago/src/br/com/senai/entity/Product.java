package br.com.senai.entity;

import br.com.senai.view.ProductView;

public class Product {

    //ATRIBUTOS
    private String nomeProduto;
    private Integer quantidade;
    private Double valor;

    //CONSTRUTORES
    public Product(String nomeProduto){
        this.nomeProduto = nomeProduto;
    }

    //GET e SET encapsulamento de atributos
    public String getNomeProduto() {
        return nomeProduto;
    }

    public void setNomeProduto(String nomeProduto) {
        this.nomeProduto = nomeProduto;
    }

    public Integer getQuantidade() {
        return quantidade;
    }

    public void setQuantidade(Integer quantidade) {
        this.quantidade = quantidade;
    }

    public Double getValor() {
        return valor;
    }

    public void setValor(Double valor) {
        this.valor = valor;
    }
}