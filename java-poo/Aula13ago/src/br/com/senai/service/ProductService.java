package br.com.senai.service;

    import br.com.senai.entity.Product;

    import java.util.ArrayList;
    import java.util.List;

public class ProductService {

    private Product produto;

    public Product cadastrarProduto(String nomeProduto, double valorProduto, int quantidadeProduto){
        produto = new Product(nomeProduto);

        produto.setValor(valorProduto);
        produto.setQuantidade(quantidadeProduto);

        return produto;
    }

    public List<Product> listarProduto(List<Product> products){
        return products;
    }

    public void buscarProduto(){

    }

    public void removerProduto(){

    }

}
