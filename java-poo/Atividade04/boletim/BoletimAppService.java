package boletim;

import java.io.IOException;
import java.util.Locale;

public class BoletimAppService {
    private final CalcularMedia calculadoraMedia;
    private final AvaliadorSituacao avaliadorSituacao;
    private final BoletimRepository boletimRepository;
    private final Notificar notificador;

    public BoletimAppService(CalcularMedia calculadoraMedia,
                             AvaliadorSituacao avaliadorSituacao,
                             BoletimRepository boletimRepository,
                             Notificar notificador) {
        this.calculadoraMedia = calculadoraMedia;
        this.avaliadorSituacao = avaliadorSituacao;
        this.boletimRepository = boletimRepository;
        this.notificador = notificador;
    }

    public void processarBoletim(Boletim boletim, String emailDestino) throws IOException {
        double media = calculadoraMedia.calcular(boletim.getNotas());
        String situacao = avaliadorSituacao.situacao(media);

        boletimRepository.salvar(boletim, media);

        String msg = "Aluno: " + boletim.getNomeAluno() +
                     " | Média: " + String.format(Locale.US, "%.2f", media) +
                     " | Situação: " + situacao;
        notificador.notificar(emailDestino, msg);
    }
}
