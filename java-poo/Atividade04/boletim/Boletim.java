package boletim;

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;

public class Boletim {
    private final String nomeAluno;
    private final List<Double> notas;

    public Boletim(String nomeAluno) {
        this.nomeAluno = nomeAluno;
        this.notas = new ArrayList<>();
    }

    public String getNomeAluno(){
        return nomeAluno;
    }

    public List<Double> getNotas(){
        return Collections.unmodifiableList(notas);
    }

    public void adicionarNota (double nota){
        notas.add(nota);
    }

}