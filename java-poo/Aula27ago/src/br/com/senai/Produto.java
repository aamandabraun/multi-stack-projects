package br.com.senai;

import java.security.PublicKey;

public class Produto {

    public String nomeProduto;
    public double precoProduto;
    public int quantidadeEstoque;

    public Produto (){
    }

    public Produto (String nomeProduto, double precoProduto, int quantidadeEstoque){
        this.nomeProduto = nomeProduto;
        this.precoProduto = precoProduto;
        this.quantidadeEstoque = quantidadeEstoque;
    }

    public String getNomeProduto() {
        return nomeProduto;
    } public void setNomeProduto(String nomeProduto){
        this.nomeProduto = nomeProduto;
    }

    public double getPrecoProduto(){
        return precoProduto;
    } public void setPrecoProduto (double precoProduto){
        this.precoProduto = precoProduto;
    }

    public int getQuantidadeEstoque (){
        return quantidadeEstoque;
    } public void setQuantidadeEstoque (int quantidadeEstoque){
        this.quantidadeEstoque = quantidadeEstoque;
    }

    public void setNome(String nomeProduto) {
        this.nomeProduto = nomeProduto;
    }

    public void setPreco(double precoProduto) {
        this.precoProduto = precoProduto;
    }

    public void exibirInformacoes() {
        System.out.println("Produto: " + nomeProduto);
        System.out.println("Preço: R$" + precoProduto);
        System.out.println("Estoque: " + quantidadeEstoque + " unidades");
        System.out.println(" ");
    }
}
