package boletim;

import java.util.List;

public class CalcularMedia {
    public double calcular (List<Double> notas){
        return notas.stream().mapToDouble(Double::doubleValue).average().orElse(0);
    }
}
