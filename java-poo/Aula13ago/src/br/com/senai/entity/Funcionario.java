package br.com.senai.entity;

public class Funcionario extends Pessoa{

    private String matricula;
    private String emailFuncional;
    private double salario;
    private String funcao;

    public Funcionario (){
    }

    public Funcionario(String matricula, String email, double salario, String funcao) {
        this.matricula = matricula;
        this.emailFuncional = email;
        this.salario = salario;
        this.funcao = funcao;
    }

    public Funcionario(String matricula, String email, double salario, String funcao, String nome, int idade) {
        super(nome,idade);
        this.matricula = matricula;
        this.emailFuncional = email;
        this.salario = salario;
        this.funcao = funcao;
    }

    public String getMatricula() {
        return matricula;
    }

    public void setMatricula(String matricula) {
        this.matricula = matricula;
    }

    public String getEmailFuncional() {
        return emailFuncional;
    }

    public void setEmailFuncional(String emailFuncional) {
        this.emailFuncional = emailFuncional;
    }

    public double getSalario() {
        return salario;
    }

    public void setSalario(double salario) {
        this.salario = salario;
    }

    public String getFuncao() {
        return funcao;
    }

    public void setFuncao(String funcao) {
        this.funcao = funcao;
    }
}
