package br.com.senai.entity;

public class Funcionario {

    //ATRIBUTOS
    private String nomeFuncionario;
    private int idade;
    private String setor;

    //CONSTRUTORES
    public Funcionario() {
    }

    public Funcionario (String nomeFuncionario, int idade, String setor){
        this.nomeFuncionario = nomeFuncionario;
        this.idade = idade;
        this.setor = setor;
    }

    //GET e SET encapsulamento de atributos
    public String getNomeFuncionario() {
        return nomeFuncionario;
    }
    public void setNomeFuncionario(String nomeFuncionario) {
        this.nomeFuncionario = nomeFuncionario;
    }

    public int getIdade() {
        return idade;
    }
    public void setIdade(int idade) {
        this.idade = idade;
    }

    public String getSetor() {
        return setor;
    }
    public void setSetor(String setor) {
        this.setor = setor;
    }
}
