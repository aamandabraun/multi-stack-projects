package br.edu.rabbitmq.consumer;

import br.edu.rabbitmq.config.DeadLetterListenerConfig;
import br.edu.rabbitmq.config.RabbitMQConfig;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.core.Message;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.stereotype.Component;

import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.Map;

/**
 * Consome a Dead Letter Queue apenas para registrar as mensagens inválidas.
 * Recebe a {@link Message} bruta: o payload pode nem ser um JSON válido.
 * O header x-death, adicionado pelo broker, informa a fila de origem e o motivo.
 */
@Component
public class DeadLetterConsumer {

    private static final Logger log = LoggerFactory.getLogger(DeadLetterConsumer.class);

    @RabbitListener(
            queues = RabbitMQConfig.FILA_DLQ,
            containerFactory = DeadLetterListenerConfig.DLQ_CONTAINER_FACTORY
    )
    public void registrar(Message message) {
        String payload = new String(message.getBody(), StandardCharsets.UTF_8);
        String origem = "desconhecida";
        String motivo = "desconhecido";

        List<Map<String, ?>> xDeath = message.getMessageProperties().getXDeathHeader();
        if (xDeath != null && !xDeath.isEmpty()) {
            origem = String.valueOf(xDeath.get(0).get("queue"));
            motivo = String.valueOf(xDeath.get(0).get("reason"));
        }

        log.warn("[DLQ] Mensagem inválida vinda de '{}' (motivo: {}): {}", origem, motivo, payload);
    }
}
