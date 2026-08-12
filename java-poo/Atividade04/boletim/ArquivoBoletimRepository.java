package boletim;

import java.util.Locale;
import java.io.FileWriter;
import java.io.IOException;

public class ArquivoBoletimRepository implements BoletimRepository{
    @Override

    public void salvar (Boletim boletim, double media) throws IOException {
        String nome = boletim.getNomeAluno() + "_boletim.txt";
        try (FileWriter writer = new FileWriter(nome)){
            writer.write("Aluno: " + boletim.getNomeAluno() + " \n");
            writer.write("Média: " + String.format(Locale.US, "%.2f", media) + "\n");
        }
    }
}