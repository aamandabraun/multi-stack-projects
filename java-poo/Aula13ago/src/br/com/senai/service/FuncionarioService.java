package br.com.senai.service;

import br.com.senai.entity.Endereco;
import br.com.senai.entity.Funcionario;
import br.com.senai.entity.Pessoa;

public class FuncionarioService {

    public void cadastrarFuncionario(){
        Funcionario carlos = new Funcionario();

        carlos.setNome("Carlos");
        carlos.setEmail("carlos@gmail.com");
        carlos.setMatricula("0001");

        Funcionario pedro = new Funcionario("0002", "pedro@gmail.com", 1800.00, "secretaria");

        System.out.println("Nome = " + carlos.getNome());
        System.out.println("Idade = " + carlos.getIdade());
        System.out.println("Matrícula = " + carlos.getMatricula());
        System.out.println("Funcao = " + carlos.getFuncao());
        System.out.println("Salário = " + carlos.getSalario());

        System.out.println("--------------------------------");

        System.out.println("Nome = " + pedro.getNome());
        System.out.println("Idade = " + pedro.getIdade());
        System.out.println("Matrícula = " + pedro.getMatricula());
        System.out.println("Funcao = " + pedro.getFuncao());
        System.out.println("Salário = " + pedro.getSalario());

        Pessoa lais = new Pessoa();
        lais.setNome("Lais");
        lais.setCpf("999.999.999-99");
        lais.setEmail("lais@gmail.com");

        Endereco enderecolais = new Endereco();
        lais.setEndereco(enderecolais);
        lais.setEndereco(new Endereco("Brasil", "SC", "Jaraguá do Sul", "Ilha da Figueira", "R Martim Kochella"));
    }

}
