package br.com.senai.service;

import br.com.senai.entity.Endereco;

import java.util.ArrayList;
import java.util.List;

public class EnderecoService {

    private Endereco endereco;

    public Endereco adicionarEndereco(String nomeRua, int numeroCasa, String nomeBairro, String nomeCidade){
        endereco = new Endereco();

        endereco.setNumeroCasa(numeroCasa);
        endereco.setNomeBairro(nomeBairro);
        endereco.setNomeCidade(nomeCidade);

        return endereco;
    }

    public List<Endereco> listarEndereco(List<Endereco> endereco){
        return endereco;
    }

    public void buscarEndereco(){

    }

    public void removerEndereco(){

    }

    public void editarEndereco(){

    }
}
