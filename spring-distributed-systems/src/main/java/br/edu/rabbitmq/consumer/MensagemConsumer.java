package br.edu.rabbitmq.consumer;

import br.edu.rabbitmq.config.RabbitMQConfig;
import br.edu.rabbitmq.dto.MensagemRequest;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.stereotype.Component;

/** Etapas 1 e 2 — Hello RabbitMQ. */
@Component
public class MensagemConsumer {

    private static final Logger log = LoggerFactory.getLogger(MensagemConsumer.class);

    @RabbitListener(queues = RabbitMQConfig.FILA_MENSAGENS)
    public void receber(MensagemRequest mensagem) {
        log.info("[MENSAGENS] Mensagem recebida: {}", mensagem.mensagem());
    }
}
