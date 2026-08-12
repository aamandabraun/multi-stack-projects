package br.com.senai.entity;

public class Pessoa {

    //ATRIBUTOS
    private String nomePessoa;
    private int idade;
    private char sexo;


    //CONSTRUTORES
    public Pessoa(){
    }

    public Pessoa (String nomePessoa, int idade, char sexo){
        this.nomePessoa = nomePessoa;
        this.idade = idade;
        this.sexo = sexo;
    }

    //GET e SET encapsulamento de atributos
    public String getNomePessoa() {
        return nomePessoa;
    }
    public void setNomePessoa(String nomePessoa) {
        this.nomePessoa = nomePessoa;
    }

    public int getIdade() {
        return idade;
    }
    public void setIdade(int idade) {
        this.idade = idade;
    }

    public char getSexo() {
        return sexo;
    }
    public void setSexo(char sexo) {
        this.sexo = sexo;
    }
}