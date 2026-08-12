package models;

public class Motor {
    
    public Veiculo veiculo = new Veiculo("yamaha", "rosa");

    public void funcionar(){
        veiculo.ligar();
    }
}
