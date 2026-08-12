package br.com.senai;

public class trabalhador {

    public String nome;
    public String setor;
    public double salario;
    private static int totalTrabalhadores = 0;

    public trabalhador(){
        totalTrabalhadores++;
    }

    public trabalhador(String nome, String setor, double salario){
        this();
        this.nome = nome;
        this.setor = setor;
        this.salario = salario;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getSetor() {
        return setor;
    }

    public void setSetor(String setor) {
        this.setor = setor;
    }

    public double getSalario() {
        return salario;
    }

    public void setSalario(double salario) {
        this.salario = salario;
    }

    public static int getTotalTrabalhadores() {
        return totalTrabalhadores;
    }

    public static void setTotalTrabalhadores(int totalTrabalhadores) {
        trabalhador.totalTrabalhadores = totalTrabalhadores;
    }
}
