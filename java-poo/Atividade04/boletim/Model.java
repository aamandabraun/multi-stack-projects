package boletim;

public class Model {
    public static void main(String[] args) {
        Boletim boletim = new Boletim("Maria");
        boletim.adicionarNota(8.0);
        boletim.adicionarNota(6.5);
        boletim.adicionarNota(7.2);

        BoletimAppService app = new BoletimAppService(
            new CalcularMedia(),
            new AvaliadorSituacao(7.0),
            new ArquivoBoletimRepository(),
            new EmailNotificador()
        );

        try {
            app.processarBoletim(boletim, "maria@example.com");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

