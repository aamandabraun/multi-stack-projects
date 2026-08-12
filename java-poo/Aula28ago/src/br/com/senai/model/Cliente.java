package br.com.senai.model;

public class Cliente {

    private int id;
    protected String nome;
    String email;
    public boolean vip;

    public Cliente() {
    }

    public (int id, String nome, String email, boolean vip true) {
        this.id = id;
        this.nome = nome;
        this.email = email;
        this.vip = vip;
    }

    private int getId() {
        return id;
    }

    private void setId(int id) {
        this.id = id;
    }

    protected String getNome() {
        return nome;
    }

    protected void setNome(String nome) {
        this.nome = nome;
    }

    String getEmail() {
        return email;
    }

    void setEmail(String email) {
        this.email = email;
    }

    public boolean getVip() {
        return vip;
    }

    public void setVip(boolean vip) {
        this.vip = vip;
    }

    public void exibirInformacoes() {
        System.out.println("Cliente: " + id);
        System.out.println("Nome do cliente: " + nome);
        System.out.println("E-mail para contado: " + email);
        System.out.println(" ");

    }



}
