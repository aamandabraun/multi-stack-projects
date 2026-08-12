package boletim;

public class AvaliadorSituacao {
    private final double mediaAprovacao;

    public AvaliadorSituacao(double mediaAprovacao){
        this.mediaAprovacao = mediaAprovacao;
    }

    public String situacao(double media){
        return media >= mediaAprovacao ? "Aprovado" : "Reprovado";
    }
}
