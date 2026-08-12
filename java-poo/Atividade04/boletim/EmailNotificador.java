package boletim;

public class EmailNotificador implements Notificar{
    @Override
    public void notificar(String destinatario, String mensagem){
        System.out.println("Enviado e-mail para " + destinatario + ": " + mensagem);
    }
}
