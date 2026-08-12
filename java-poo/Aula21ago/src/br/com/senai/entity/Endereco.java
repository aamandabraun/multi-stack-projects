package br.com.senai.entity;

public class Endereco {

    //ATRIBUTOS
    private String nomeRua;
    private int numeroCasa;
    private String nomeBairro;
    private String nomeCidade;


    //CONSTRUTORES
    public Endereco(){
    }

    public Endereco (String nomeRua, int numeroCasa, String nomeBairro, String nomeCidade){
        this.nomeRua = nomeRua;
        this.numeroCasa = numeroCasa;
        this.nomeBairro = nomeBairro;
        this.nomeCidade = nomeCidade;
    }

    //GET e SET encapsulamento de atributos
    public String getNomeRua() {
        return nomeRua;
    }
    public void setNomeRua(String nomeRua) {
        this.nomeRua = nomeRua;
    }

    public int getNumeroCasa() {
        return numeroCasa;
    }
    public void setNumeroCasa(int numeroCasa) {
        this.numeroCasa = numeroCasa;
    }

    public String getNomeBairro() {
        return nomeBairro;
    }
    public void setNomeBairro(String nomeBairro) {
        this.nomeBairro = nomeBairro;
    }

    public String getNomeCidade() {
        return nomeCidade;
    }
    public void setNomeCidade(String nomeCidade) {
        this.nomeCidade = nomeCidade;
    }
}
