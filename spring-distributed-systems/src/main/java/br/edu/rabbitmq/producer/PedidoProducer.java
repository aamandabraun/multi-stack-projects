package br.edu.rabbitmq.producer;

import br.edu.rabbitmq.config.RabbitMQConfig;
import br.edu.rabbitmq.model.PedidoEvento;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.core.RabbitTemplate;
import org.springframework.stereotype.Service;

/**
 * Etapas 4 e 5: publica na exchange TOPIC com a routing key do evento.
 * O produtor não conhece as filas nem os consumidores — só a exchange.
 */
@Service
public class PedidoProducer {

    private static final Logger log = LoggerFactory.getLogger(PedidoProducer.class);

    private final RabbitTemplate rabbitTemplate;

    public PedidoProducer(RabbitTemplate rabbitTemplate) {
        this.rabbitTemplate = rabbitTemplate;
    }

    public void publicar(PedidoEvento evento) {
        rabbitTemplate.convertAndSend(
                RabbitMQConfig.EXCHANGE_PEDIDOS,
                evento.tipo(),
                evento
        );
        log.info("[PRODUCER] {} publicado para o pedido {}", evento.tipo(), evento.pedido().id());
    }
}
