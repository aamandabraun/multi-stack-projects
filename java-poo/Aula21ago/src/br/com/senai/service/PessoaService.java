package br.com.senai.service;

import br.com.senai.entity.Pessoa;

import java.util.ArrayList;
import java.util.List;

public class PessoaService {

    private Pessoa pessoa;

    public Pessoa adicionarPessoa(String nomePessoa, int idade, char sexo){
        pessoa = new Pessoa();

        pessoa.setIdade(idade);
        pessoa.setSexo(sexo);

        return pessoa;
    }

    public List<Pessoa> listarPessoa(List<Pessoa> pessoa){
        return pessoa;
    }

    public void buscarPessoa(){

    }

    public void removerPessoa(){

    }

    public void editarPessoa(){

    }
}