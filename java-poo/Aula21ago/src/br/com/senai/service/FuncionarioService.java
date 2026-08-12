package br.com.senai.service;

import br.com.senai.entity.Funcionario;

import java.util.ArrayList;
import java.util.List;

public class FuncionarioService {

    private Funcionario funcionario;

    public Funcionario adicionarFuncionario(String nomeFuncionario, int idade, String setor){
        funcionario = new Funcionario();

        funcionario.setIdade(idade);
        funcionario.setSetor(setor);

        return funcionario;
    }

    public List<Funcionario> listarFuncionario(List<Funcionario> funcionario){
        return funcionario;
    }

    public void buscarFuncionario(){

    }

    public void removerFuncionario(){

    }

    public void editarFuncionario(){

    }
}
