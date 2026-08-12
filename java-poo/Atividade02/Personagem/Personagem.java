package Personagem;

abstract class Personagem {
    protected String nome;
    protected int vida;
    protected int ataque;
    protected int defesa;
    protected int nivel;
    protected int experiencia;

    public Personagem(String nome, int vida, int ataque, int defesa){
        this.nome = nome;
        this.vida = vida;
        this.ataque = ataque;
        this.defesa = defesa;
        this.nivel = 1;
        this.experiencia = 0;
    }

    public boolean estaVivo(){
        return vida > 0;
    }

    public void receberDano(int dano){
        vida -= dano;
        if (vida < 0) vida = 0;
    }

    public void atacar(Personagem inimigo){
        Random random = new Random;
        int danoBase = ataque - inimigo.defesa;
        int variacao = random.nextInt(5);
        int dano = Math.max(1, danoBase + variacao);

        System.out.println(nome + " ataca " + inimigo.nome + " causando " + dano + " de dano!");
        inimigo.receberDano(dano);
    }

    public void ganharExperiencia(int xp){
        experiencia += xp;
        System.out.println(nome + " ganhou " + xp + " de XP!");
        if (experiencia >= nivel * 10){
            subirNivel();
        }
    }

    public void subirNivel(){
        nivel++;
        experiencia = 0;
        vida += 10;
        ataque += 2;
        defesa += 1;
        System.out.println(nome + " subiu de nível para " + nivel + " !");
    }

    @Override
    public String toString(){
        return nome + " [Nível " + nivel + "] Vida: " + vida + " | Ataque: " + ataque + " | Defesa: " + defesa;
    }
}
