package br.edu.rabbitmq.producer;

import br.edu.rabbitmq.config.RabbitMQConfig;
import br.edu.rabbitmq.dto.MensagemRequest;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.stereotype.Service;

/**
 * Etapas 1 e 2: envio direto pelo nome da fila.
 * Sem exchange explícita, o RabbitMQ usa a default exchange, que roteia
 * pela routing key igual ao nome da fila.
 */
@Service
public class MensagemProducer {

    private final RabbitTemplate rabbitTemplate;

    public MensagemProducer(RabbitTemplate rabbitTemplate) {
        this.rabbitTemplate = rabbitTemplate;
    }

    public void enviar(MensagemRequest mensagem) {
        rabbitTemplate.convertAndSend(RabbitMQConfig.FILA_MENSAGENS, mensagem);
    }
}
