package br.com.senai.model;

public class Produto {

    private int codigo;
    public String nomeProduto;
    protected double preco;
    int quantidade;

    public Produto (){
    }

    public Produto (int codigo, String nomeProduto, double preco, int quantidade) {
        this.codigo = codigo;
        this.nomeProduto = nomeProduto;
        this.preco = preco;
        this.quantidade = quantidade;
    }

    private int getCodigo(){
        return codigo;
    } private void setCodigo (int codigo){
        this.codigo = codigo;
    }


    public String getNomeProduto(){
        return nomeProduto;
    } public void setNome (String nomeProduto){
        this.nomeProduto = nomeProduto;
    }


    protected Double getPreco(){
        return preco;
    }
    protected void setPreco (Double preco){
        this.preco = preco;
    }


    public void exibirInformacoes() {
        System.out.println("Produto: " + codigo);
        System.out.println("Nome do produto: " + nomeProduto);
        System.out.println("Preço: R$" + preco);
        System.out.println("Quantidade em estoque: " + quantidade + "unidades");
        System.out.println(" ");
    }
}
