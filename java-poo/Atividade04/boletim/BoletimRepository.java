package boletim;

import java.io.IOException;

public interface BoletimRepository {
    void salvar(Boletim boletim, double media) throws IOException;
}