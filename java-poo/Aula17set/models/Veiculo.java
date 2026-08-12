package models;

public class Veiculo {
    private String marca;
    private String cor;

    public void setMarca(String marca) {
        this.marca = marca;
    }
    public String getMarca() {
        return marca;
    }
    public void setCor(String cor) {
        this.cor = cor;
    }
    public String getCor() {
        return cor;
    }

    public void ligar(){
        System.out.println("Motor da " + marca + " " + cor + " ligando");
    }

    public Veiculo(String marca, String cor){
        this.marca = marca;
        this.cor = cor;
    }


}
