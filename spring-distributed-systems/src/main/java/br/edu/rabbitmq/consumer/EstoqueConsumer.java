package br.edu.rabbitmq.consumer;

import br.edu.rabbitmq.config.RabbitMQConfig;
import br.edu.rabbitmq.model.Pedido;
import br.edu.rabbitmq.model.PedidoEvento;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.amqp.rabbit.annotation.RabbitListener;
import org.springframework.amqp.support.AmqpHeaders;
import org.springframework.messaging.handler.annotation.Header;
import org.springframework.stereotype.Component;

/** Recebe pedido.criado (reserva) e pedido.cancelado (devolução). */
@Component
public class EstoqueConsumer {

    private static final Logger log = LoggerFactory.getLogger(EstoqueConsumer.class);

    private final PedidoEventoValidator validator;

    public EstoqueConsumer(PedidoEventoValidator validator) {
        this.validator = validator;
    }

    @RabbitListener(queues = RabbitMQConfig.FILA_ESTOQUE)
    public void processar(PedidoEvento evento,
                          @Header(AmqpHeaders.RECEIVED_ROUTING_KEY) String routingKey) {
        validator.validar(evento, routingKey);
        Pedido pedido = evento.pedido();

        switch (routingKey) {
            case RabbitMQConfig.RK_PEDIDO_CRIADO -> log.info(
                    "[ESTOQUE] Reservando {} unidade(s) de '{}' para o pedido {}",
                    pedido.quantidade(), pedido.produto(), pedido.id());
            case RabbitMQConfig.RK_PEDIDO_CANCELADO -> log.info(
                    "[ESTOQUE] Devolvendo {} unidade(s) de '{}' ao estoque (pedido {} cancelado)",
                    pedido.quantidade(), pedido.produto(), pedido.id());
            default -> log.warn("[ESTOQUE] Evento {} ignorado", routingKey);
        }
    }
}
