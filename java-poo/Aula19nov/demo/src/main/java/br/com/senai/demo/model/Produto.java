package br.com.senai.demo.model;

import jakarta.persistence.Entity;
import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;

@Entity 
@AllArgsConstructor
@NoArgsConstructor

public class Produto{
    private long id;
    private String nome;
    private String preco;
    private String descricao;
}