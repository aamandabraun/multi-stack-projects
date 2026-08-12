package models;

import java.util.ArrayList;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        // composição
        Motor motor = new Motor();
        //motor.funcionar(); 

        // agregação
        List<Veiculo> veiculos = new ArrayList<>();
        veiculos.add(motor.veiculo);
        
        Frota frota = new Frota(veiculos, "Frota da Amanda");
        String nomeVeiculos = frota.getNomeVeiculos();
        System.out.println(nomeVeiculos);
        System.out.println("Quantidade de veículos [" +frota.getNome()+"]: " + frota.getVeiculos().size());
    }
    
}
