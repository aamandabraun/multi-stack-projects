package models;

import java.util.List;

public class Frota {
    
    private String nome;
    private List<Veiculo> veiculos;

    public Frota(List<Veiculo> veiculos){
        this.veiculos = veiculos;
    }

    public Frota(List<Veiculo> veiculos, String nome){
        this.veiculos = veiculos;
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }
    public void setNome(String nome) {
        this.nome = nome;
    }
    public List<Veiculo> getVeiculos() {
        return veiculos;
    }
    public void setVeiculos(List<Veiculo> veiculos) {
        this.veiculos = veiculos;
    }

    public String getNomeVeiculos(){
        String nomeVeiculos = "";
        for (Veiculo veiculo : this.veiculos){
            nomeVeiculos += veiculo.getMarca() + "";
        }

        return nomeVeiculos;
    }
}
