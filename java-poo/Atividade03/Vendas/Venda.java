package Vendas;

import java.util.ArrayList;
import java.util.List;

public class Venda {
    private List<Produto> produtosVendidos = new ArrayList<>();
    private List<Integer> quantidades = new ArrayList<>();
    private double total = 0;

    public void adicionarProduto(Produto produto, int quantidade){
        if (produto.reduzirEstoque(quantidade)){
            produtosVendidos.add(produto);
            quantidade.add(quantidade);
            total += produto.getPreco() * quantidade;
        } else {
            System.out.println("Estoque insuficiente");
        }
    }

    public void exibirResumo(){
        System.out.println("==Resumo da venda==");
        for (int i = 0, i < produtosVendidos.size(), i++){
            Produtos p = produtosVendidos.get(i);
            int qtd = quantidade.get(i);
            System.out.println(p.getNome() + " x" + qtd + " + R$" + (p.getPreco() * qtd));
        }
        System.out.println("TOTAL: R$" + total);
    }
}
