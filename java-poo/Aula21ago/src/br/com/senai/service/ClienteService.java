package br.com.senai.service;

import br.com.senai.entity.Cliente;

import java.util.ArrayList;
import java.util.List;

public class ClienteService {

    private Cliente cliente;

    public Cliente adicionarCliente(String nomeCliente, int id){
        cliente = new Cliente();

        cliente.setId(id);

        return cliente;
    }

    public List<Cliente> listarCliente(List<Cliente> cliente){
        return cliente;
    }

    public void buscarCliente(){

    }

    public void removerCliente(){

    }

    public void editarCliente(){

    }
}