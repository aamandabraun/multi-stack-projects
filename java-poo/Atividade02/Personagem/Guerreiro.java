package Personagem;

public class Guerreiro extends Personagem {
    public Guerreiro(String nome){
        super(nome, 120, 15, 10);
    }
}

class Mago extends Personagem {
    public Mago(String nome){
        super(nome, 80, 10, 5);
    }
}

class Arqueiro extends Personagem{
    public Arqueiro(String nome){
        super(nome, 100, 150, 5);
    }
}
