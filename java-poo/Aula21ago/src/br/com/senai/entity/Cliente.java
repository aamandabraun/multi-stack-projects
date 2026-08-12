package br.com.senai.entity;

public class Cliente {

    //ATRIBUTOS
    private String nomeCliente;
    private int id;


    //CONSTRUTORES
    public Cliente(){
    }

    public Cliente (String nomeCliente, int id){
        this.nomeCliente = nomeCliente;
        this.id = id;
    }

    //GET e SET encapsulamento de atributos
    public String getNomeCliente() {
        return nomeCliente;
    }
    public void setNomeCliente(String nomeCliente) {
        this.nomeCliente = nomeCliente;
    }

    public int getId() {
        return id;
    }
    public void setId(int id) {
        this.id = id;
    }

}
